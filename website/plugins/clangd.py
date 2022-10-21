from bisect import bisect_left
import os
import json
import subprocess
import shutil
from typing import Optional, Union, Any
from file_utils import read_file

# All of URI handling is done manually instead of through a dedicated library because:
# 1) For LSP, URIs are only a form of identification and their actual content doesn't matter
# 2) python's uri library is broken (import error) (https://github.com/marrow/uri/issues/19)
# 3) We need only path-to-URI and URI-to-path functionality
# https://en.wikipedia.org/wiki/File_URI_scheme
URI_FILE_PREFIX = "file:///"
def path_to_uri(path: str) -> str:
    return f"{URI_FILE_PREFIX}{path}"

def uri_to_path(uri: str) -> str:
    if uri.startswith(URI_FILE_PREFIX):
        return uri.removeprefix(URI_FILE_PREFIX)
    else:
        raise RuntimeError(f"URI {uri} is not valid or unsupported")

def json_rpc_make_notification(method: str, params: Union[tuple, list, dict, None]) -> dict[str, Any]:
    message = {
        "jsonrpc": "2.0",
        "method": method
    }

    if params is not None:
        if isinstance(params, (list, tuple, dict)):
            message["params"] = params
        else:
            raise RuntimeError(f"params is not a structured type: {params}")

    return message


def json_rpc_make_request(id: Union[str, int], method: str, params: Union[tuple, list, dict, None]) -> dict[str, Any]:
    if not isinstance(id, (str, int)):
        raise RuntimeError(f"id should be a number or a string: {id}")

    message = json_rpc_make_notification(method, params)
    message["id"] = id
    return message


def json_rpc_is_error(message: dict[str, Any]) -> bool:
    return "error" in message


def json_rpc_is_notification(message: dict[str, Any]) -> bool:
    return "id" not in message and "method" in message


def json_rpc_response_extract_error(response: dict[str, Any]) -> dict[str, Any]:
    return response["error"]


def json_rpc_response_extract_result(response: dict[str, Any], id: Union[str, int]) -> Any:
    response_id = response.get("id")
    if not response_id:
        raise RuntimeError(f"no id object in JSON RPC response:\n{json.dumps(response, indent=4)}")
    if response_id != id:
        raise RuntimeError(f"expected JSON RPC response with id {id} but got {response_id}")

    # use "in" instead of ".get()" to differentiate between no item and item with value None
    # (some JSON RPC calls can return "result": null)
    if "result" in response:
        return response["result"]
    else:
        raise RuntimeError(f"expected result in JSON RPC response:\n{json.dumps(response, indent=4)}")


HEADER_CONTENT_LENGTH = "Content-Length: "

def lsp_make_message(json_rpc_object: dict[str, Any]) -> bytes:
    body = json.dumps(json_rpc_object, indent=None).encode()
    return f"{HEADER_CONTENT_LENGTH}{len(body)}\r\n\r\n".encode() + body

def lsp_make_position(line: int, character: int) -> dict[str, int]:
    if line < 0 or character < 0:
        raise RuntimeError(f"position with line {line} and character {character} is invalid")

    return { "line": line, "character": character }

def lsp_make_range(start_line: int, start_character: int, end_line: int, end_character: int) -> dict[str, dict[str, int]]:
    return {
        "start": lsp_make_position(start_line, start_character),
        "end": lsp_make_position(end_line, end_character)
    }

def lsp_make_range_whole_file(num_lines: int) -> dict[str, dict[str, int]]:
    return lsp_make_range(0, 0, num_lines, 0)

def lsp_make_text_document_identifier(path: str) -> dict[str, Any]:
    return {"uri": path_to_uri(path)}

def lsp_make_text_document_position_params(path: str, position: dict[str, int]):
    return {
        "textDocument": lsp_make_text_document_identifier(path),
        "position": position
    }

def lsp_make_text_document_item(path: str, text: str) -> dict[str, Any]:
    return {
        "uri": path_to_uri(path),
        "languageId": "cpp",
        "version": 0,
        "text": text
    }

def get_clangd_path() -> str:
    env_name = os.environ.get("CLANGD")
    if env_name:
        result = shutil.which(env_name)
        if result:
            return result

    result = shutil.which("clangd")
    if result:
        return result

    raise RuntimeError("clangd not found. Specify env variable CLANGD that points to the executable or to a name searchable in PATH")


class Connection:
    def __init__(self, connect=True, initialize=True):
        self.clangd_path = get_clangd_path()
        # TODO: log clangd version
        self.id = 1
        self.p = None
        self.initialized = False
        if connect:
            self.open_connection()
            if initialize:
                self.initialize()

    def open_connection(self) -> None:
        self.p = subprocess.Popen([self.clangd_path, "--log=error"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    def send(self, message: bytes) -> None:
        bytes_written = self.p.stdin.write(message)
        if bytes_written != len(message):
            raise RuntimeError(f"Wrote only {bytes_written} of {len(message)} bytes when sending:\n{message.decode()}")

        self.p.stdin.flush()

    def receive(self) -> str:
        headers = []

        while True:
            line = self.p.stdout.readline()
            if line == b"\r\n":
                break
            else:
                headers.append(line)

        length = 0
        for hdr in headers:
            hdr = hdr.decode()
            if HEADER_CONTENT_LENGTH in hdr:
                length = int(hdr.removeprefix(HEADER_CONTENT_LENGTH))
                break

        if length == 0:
            raise RuntimeError(f'invalid or missing "{HEADER_CONTENT_LENGTH}" header')

        return self.p.stdout.read(length).decode()

    def make_lsp_notification(self, method: str, params: Any) -> None:
        self.send(lsp_make_message(json_rpc_make_notification(method, params)))

    def receive_response(self, id: Union[str, int]) -> Any:
        while True:
            message = json.loads(self.receive())
            if json_rpc_is_error(message):
                raise RuntimeError(f"JSON RPC error:\n{json.dumps(json_rpc_response_extract_error(message), indent=4)}")
            elif json_rpc_is_notification(message):
                print("NOTIFICATION:")
                print(json.dumps(message, indent=4))
            else:
               return json_rpc_response_extract_result(message, id)

    def make_lsp_request(self, method: str, params: Any) -> Any:
        id = self.id
        self.send(lsp_make_message(json_rpc_make_request(id, method, params)))
        self.id += 1
        return self.receive_response(id)

    def initialize(self) -> Any:
        if not self.p:
            raise RuntimeError("initialization requires opened connection")

        result = self.make_lsp_request("initialize", {
            "processId": os.getpid(),
                "rootUri": None,
                # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#clientCapabilities
                "capabilities": {
                    "workspace": {
                        # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#semanticTokensWorkspaceClientCapabilities
                        "semanticTokens": {
                        }
                    },
                    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocumentClientCapabilities
                    "textDocument": {
                        # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#semanticTokensClientCapabilities
                        "semanticTokens" : {
                            "requests": {
                                "range": True,
                                "full": {
                                    "delta": False
                                }
                            },
                            "tokenTypes": [],
                            "tokenModifiers": [],
                            "formats": [], # no support for relative as of now (absolute is implicitly assumed)
                            "overlappingTokenSupport": False,
                            # even if given True, clangd-15.0.2 doesn't report any multiline tokens
                            # instead, it always reports many whole-line tokens with identical type and modifers
                            "multilineTokenSupport": False
                        }
                    }
                }
                # TODO workspaceFolders
            })
        self.initialized = True
        return result

    def shutdown(self) -> None:
        if not self.initialized:
            return

        result = self.make_lsp_request("shutdown", None)
        if result is not None:
            raise RuntimeError(f"shutdown call failed: {json.dumps(result, indent=None)}")

        self.initialized = False

    def close_connection(self) -> None:
        self.shutdown()
        self.make_lsp_notification("exit", None)
        self.p = None

    def __del__(self):
        self.close_connection()

class SemanticToken:
    def __init__(self, line_num: int, column: int, length: int, token_type: int, token_modifiers: int):
        self.line_num = line_num
        self.column = column
        self.length = length
        self.token_type = token_type
        self.token_modifiers = token_modifiers
        self.color_variant = 0 # (no variance)
        self.last_highlight = False

    def __eq__(self, other) -> bool:
        return self.line_num == other.line_num and self.column == other.column and self.length == other.length

    def __ne__(self, other) -> bool:
        return not self.__eq__(other)

    def __lt__(self, other) -> bool:
        return (self.line_num, self.column, self.length) < (other.line_num, other.column, other.length)

    def __le__(self, other) -> bool:
        return (self.line_num, self.column, self.length) <= (other.line_num, other.column, other.length)

    def __gt__(self, other) -> bool:
        return (self.line_num, self.column, self.length) > (other.line_num, other.column, other.length)

    def __ge__(self, other) -> bool:
        return (self.line_num, self.column, self.length) >= (other.line_num, other.column, other.length)

# https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_semanticTokens
# the data is packed in an array of integers, where each 5 consecutive integers denote specific attributes
def parse_semantic_token_data(data: list[int]) -> list[SemanticToken]:
    result = []

    last_line = 0
    last_column = 0

    for i in range(0, len(data) // 5):
        idx = i * 5
        delta_line = data[idx]
        delta_column = data[idx + 1]
        length = data[idx + 2]
        token_type = data[idx + 3]
        token_modifiers = data[idx + 4]

        # token column is only relative when on the same line
        if delta_line != 0:
            last_column = 0

        line = last_line + delta_line
        column = last_column + delta_column

        result.append(SemanticToken(line, column, length, token_type, token_modifiers))

        last_line = line
        last_column = column

    return result


def document_highlight_find_matching_token(highlight: dict[str, Any], semantic_tokens: list[SemanticToken]) -> Optional[SemanticToken]:
    range = highlight["range"]
    start = range["start"]
    end = range["end"]
    start_line = start["line"]
    start_column = start["character"]
    end_line = end["line"]
    end_column = end["character"]

    if start_line != end_line:
        raise RuntimeError(f"line-breaking highlights are not supported: {json.dumps(highlight, indent=4)}")

    length = end_column - start_column

    token_to_find = SemanticToken(start_line, start_column, length, 0, 0)
    i = bisect_left(semantic_tokens, token_to_find)

    if i == len(semantic_tokens):
        return None

    if semantic_tokens[i] == token_to_find:
        return semantic_tokens[i]
    else:
        return None


class Clangd:
    def __init__(self, connect=True, initialize=True):
        self.conn = Connection(connect, False)
        if initialize:
            self.initialize()

    def initialize(self):
        result = self.conn.initialize()
        print(json.dumps(result, indent=4))
        print(f'Using clangd version: {result["serverInfo"]["version"]}')
        self.parse_capabilities(result["capabilities"])

    def parse_capabilities(self, capabilities: dict[str, Any]):
        semantic_tokens_legend = capabilities["semanticTokensProvider"]["legend"]
        self.semantic_tokens_types: list[str] = semantic_tokens_legend["tokenTypes"]
        self.semantic_tokens_modifiers: list[str] = semantic_tokens_legend["tokenModifiers"]
        print(f"SEMANTIC TOKENS TYPES")
        print(self.semantic_tokens_types)
        print(f"SEMANTIC TOKENS MODIFIERS")
        print(self.semantic_tokens_modifiers)

    # return an array of semantic token types that are suitable for token-specific colorization
    def get_semantic_tokens_object_types(self) -> list[int]:
        if not hasattr(self, "semantic_tokens_types"):
            raise RuntimeError("semantic tokens capabilities unavailable - missing initialization")

        result = []
        for i in range(0, len(self.semantic_tokens_types)):
            # clangd reports semantic token types with duplicate entries
            # it's important to make a full loop as there may be many matching indexes
            if self.semantic_tokens_types[i] in ["variable", "parameter", "property"]:
                result.append(i)
        return result

    def text_document_open(self, path: str) -> str:
        # TODO this triggers a notification textDocument/publishDiagnostics
        # which can be later used to verify that the code is correct
        text = read_file(path)
        self.conn.make_lsp_notification("textDocument/didOpen", {
            "textDocument": lsp_make_text_document_item(path, text)
        })
        return text

    def text_document_close(self, path: str) -> None:
        self.conn.make_lsp_notification("textDocument/didClose", {
            "textDocument": lsp_make_text_document_identifier(path)
        })

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_semanticTokens
    # each occurrence of a symbol (typically an identifier) is reported; each symbol has a range, 1 type and 0+ modifiers
    def text_document_semantic_tokens_full(self, path: str) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/semanticTokens/full", {
            "textDocument": lsp_make_text_document_identifier(path)
        })

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_documentSymbol
    # each symbol is reported only once; only symbols originating from the file are reported
    def text_document_document_symbols(self, path: str) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/documentSymbol", {
            "textDocument": lsp_make_text_document_identifier(path)
        })

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_references
    # returns positions of usages of the entity at specified position; note that there may a different entity with
    # the same name in a different scope; for this reason this call requires a position, not a name
    def text_document_references(self, path: str, position: dict[str, int], include_declaration: bool = True):
        params = lsp_make_text_document_position_params(path, position)
        params["context"] = {"includeDeclaration": include_declaration}
        return self.conn.make_lsp_request("textDocument/references", params)

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_documentHighlight
    # like textDocument/references, but allowed to be fuzzy
    # also delivers more information: DocumentHighlightKind which is 1 (Text), 2 (Read) or 3 (Write)
    # clangd reports DocumentHighlightKind poorly: there are many 1s and out params may not be 3
    def text_document_document_highlight(self, path: str, position: dict[str, int]) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/documentHighlight", lsp_make_text_document_position_params(path, position))

    # https://clangd.llvm.org/extensions#ast
    # very rich information, too rich and undocumented, can not easily extract things such as overloaded operators
    # the highest-level node that entirely contains the range is returned; no way to call for all ASTs in the file
    def text_document_ast(self, path: str, range: dict[str, dict[str, int]]) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/ast", {
            "textDocument": lsp_make_text_document_identifier(path),
            "range": range
        })

    def semantic_tokens_for_file(self, path: str):
        lines = self.text_document_open(path).splitlines()
        semantic_tokens = parse_semantic_token_data(self.text_document_semantic_tokens_full(path)["data"])
        self.text_document_close(path)
        self.debug_print_semantic_tokens(semantic_tokens, lines)

    def semantic_tokens_with_variant_color(self, path: str):
        lines = self.text_document_open(path).splitlines()
        semantic_tokens = parse_semantic_token_data(self.text_document_semantic_tokens_full(path)["data"])
        semantic_tokens_object_types = self.get_semantic_tokens_object_types()

        color_variant = 1
        for token in semantic_tokens:
            # skip tokens that have color variant already applied
            if token.color_variant != 0:
                continue
            # do not variant-color tokens of uninteresting types
            if not token.token_type in semantic_tokens_object_types:
                continue

            highlights = self.text_document_document_highlight(path, lsp_make_position(token.line_num, token.column))
            for idx, hl in enumerate(highlights):
                matching_token = document_highlight_find_matching_token(hl, semantic_tokens)
                if matching_token is None:
                    self.debug_print_semantic_tokens(semantic_tokens, lines)
                    raise RuntimeError(
                        f"highlight failed to find a matching token\nhighlight:\n{json.dumps(hl, indent=4)}")

                matching_token.color_variant = color_variant
                if idx + 1 == len(highlights):
                    matching_token.last_highlight = True

            color_variant += 1

        self.text_document_close(path)
        self.debug_print_semantic_tokens(semantic_tokens, lines)

    def list_of_token_modifiers(self, token_modifiers: int) -> list[str]:
        result = []
        for i in range (0, len(self.semantic_tokens_modifiers)):
            if (1 << i) & token_modifiers != 0:
                result.append(self.semantic_tokens_modifiers[i])
        return result

    def debug_print_semantic_tokens(self, semantic_tokens: list[SemanticToken], lines: list[str]) -> None:
        for token in semantic_tokens:
            token_string = lines[token.line_num][token.column:token.column+token.length]
            print(
                f'line|col+len|cv: {token.line_num:>3}|{token.column:>3}+{token.length:>2}|{token.color_variant:>2}, '
                f'token: {token_string:<16}, '
                f'type: {self.semantic_tokens_types[token.token_type]:<13}, '
                f'modifiers: {", ".join(self.list_of_token_modifiers(token.token_modifiers))}'
            )

if __name__ == "__main__":
    clangd = Clangd()
    clangd.semantic_tokens_with_variant_color("main.cpp")
