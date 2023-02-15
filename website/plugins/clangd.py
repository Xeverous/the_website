from bisect import bisect_left, bisect_right
import os
import json
import subprocess
import shutil
import sys
from typing import Callable, Sequence, Union, Any
from file_utils import read_file
from nikola.utils import get_logger

DEBUG = os.environ.get("CLANGD_DEBUG") is not None
logger = get_logger("clangd_plugin")

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
        self.id = 1
        self.p = None
        self.initialized = False
        self.clangd_path = get_clangd_path()
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
                if DEBUG:
                    logger.info(f"NOTIFICATION:\n{json.dumps(message, indent=4)}")
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
                            # Even if given True, clangd-15.0.2 doesn't report any multiline tokens.
                            # Instead, it always reports multiple tokens with identical type and modifers.
                            # Tokens that hypothetically can be multiline are disabled (ifdefed out) code and
                            # anything split using splice mechanism (\ at the end of a line).
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
        if self.p:
            self.make_lsp_notification("exit", None)
            self.p = None

    def __del__(self):
        self.close_connection()

class SemanticToken:
    def __init__(self, line: int, column: int, length: int, token_type: int, token_modifiers: int):
        self.line = line
        self.column = column
        self.length = length
        self.token_type = token_type
        self.token_modifiers = token_modifiers
        self.color_variant = 0 # (no variance)
        self.last_reference = False

    def __eq__(self, other) -> bool:
        return self.line == other.line and self.column == other.column and self.length == other.length

    def __ne__(self, other) -> bool:
        return not self.__eq__(other)

    def __lt__(self, other) -> bool:
        return (self.line, self.column, self.length) < (other.line, other.column, other.length)

    def __le__(self, other) -> bool:
        return (self.line, self.column, self.length) <= (other.line, other.column, other.length)

    def __gt__(self, other) -> bool:
        return (self.line, self.column, self.length) > (other.line, other.column, other.length)

    def __ge__(self, other) -> bool:
        return (self.line, self.column, self.length) >= (other.line, other.column, other.length)

# bisect_left supports custom comparison in Python 3.10, in 3.9 there is a workaround:
# https://stackoverflow.com/questions/27672494/how-to-use-bisect-insort-left-with-a-key
class KeyWrapper:
    def __init__(self, iterable: Sequence, key: Callable):
        self.iterable = iterable
        self.key = key

    def __getitem__(self, i: int):
        return self.key(self.iterable[i])

    def __len__(self) -> int:
        return len(self.iterable)

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

# Highlights are defined by DocumentHighlight type, which has a Range member.
# Ranges can be multiline. In clangd, a highlight can match multiple semantic
# tokens because these can not be multiline and clangd reports spliced code
# as multiple tokens.
# For this reason this function returns a list, not Optional[SemanticToken]
def document_highlight_find_matching_tokens(highlight: dict[str, Any], semantic_tokens: list[SemanticToken]) -> list[SemanticToken]:
    range = highlight["range"]
    start = range["start"]
    end = range["end"]
    start_line = start["line"]
    start_column = start["character"]
    end_line = end["line"]
    end_column = end["character"]

    key = lambda token: (token.line, token.column)
    l = bisect_left(KeyWrapper(semantic_tokens, key), (start_line, start_column))
    r = bisect_right(KeyWrapper(semantic_tokens, key), (end_line, end_column))
    return semantic_tokens[l:r]

# https://stackoverflow.com/questions/67680296/syntaxerror-f-string-expression-part-cannot-include-a-backslash
def list_of_strings_to_pretty_str(l: list[str]) -> str:
    if l:
        s = '", "'
        return f'["{s.join(l)}"]'
    else:
        return "[]"

class Clangd:
    def __init__(self, connect=True, initialize=True):
        self.conn = Connection(connect, False)
        if initialize:
            self.initialize()

    def initialize(self):
        result = self.conn.initialize()
        if DEBUG:
            logger.info(json.dumps(result, indent=4))
        logger.info(f'Using clangd version: {result["serverInfo"]["version"]}')
        self._parse_capabilities(result["capabilities"])
        logger.info("Successful initialization")

    def _parse_capabilities(self, capabilities: dict[str, Any]):
        semantic_tokens_legend = capabilities["semanticTokensProvider"]["legend"]
        self.semantic_token_types: list[str] = semantic_tokens_legend["tokenTypes"]
        self.semantic_token_modifiers: list[str] = semantic_tokens_legend["tokenModifiers"]
        logger.info(
            f"initialization - supported semantic token types: "
            f"{list_of_strings_to_pretty_str(self.semantic_token_types)}")
        logger.info(
            f"initialization - supported semantic token modifiers: "
            f"{list_of_strings_to_pretty_str(self.semantic_token_modifiers)}")
        self.semantic_token_type_indexes_for_color_variants = self._get_semantic_token_type_indexes_for_color_variants()

    # return an array of semantic token types that are suitable for token-specific colorization
    def _get_semantic_token_type_indexes_for_color_variants(self) -> list[int]:
        result = []
        for i in range(0, len(self.semantic_token_types)):
            # clangd reports semantic token types with duplicate entries
            # it's important to make a full loop as there may be many matching indexes
            if self.semantic_token_types[i] in ["variable", "parameter", "property"]:
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

    def file_content_and_semantic_tokens(self, path: str):
        file_content = self.text_document_open(path)
        semantic_tokens = parse_semantic_token_data(self.text_document_semantic_tokens_full(path)["data"])
        self.text_document_close(path)
        return file_content, semantic_tokens

    def file_content_and_semantic_tokens_with_color_variance(self, path: str):
        file_content = self.text_document_open(path)
        semantic_tokens = parse_semantic_token_data(self.text_document_semantic_tokens_full(path)["data"])

        # The goal:
        # - for each token that has a type eligible for color variance:
        #   - find its usages (highlights)
        #   - for each highlight:
        #     - apply the same color variant ID
        #     - mark the last usage (this will inform ACH that after this token the ID can be recycled)
        #   - change ID for the next token
        #
        # complexity: O(n) where n is len(semantic_tokens)
        # explanation:
        # - each token is visited at most once
        # - the more highlights a given token has the more later tokens will be skipped
        color_variant = 1
        for token in semantic_tokens:
            # skip tokens that have color variant already applied
            if token.color_variant != 0:
                continue
            # do not variant-color tokens of uninteresting types
            if not token.token_type in self.semantic_token_type_indexes_for_color_variants:
                continue

            highlights = self.text_document_document_highlight(path, lsp_make_position(token.line, token.column))
            for idx, hl in enumerate(highlights):
                matching_tokens = document_highlight_find_matching_tokens(hl, semantic_tokens)
                if not matching_tokens:
                    raise RuntimeError(
                        f"failed to apply color variance to semantic tokens for file: {path}\n"
                        f"reason: failed to find matching semantic token(s) for this highlight:\n{json.dumps(hl, indent=4)}\n"
                        f"semantic tokens for this file (with color variance modifications so far):\n"
                        f"{self.semantic_tokens_debug_info(semantic_tokens, file_content.splitlines())}")

                for mt in matching_tokens:
                    mt.color_variant = color_variant
                    if idx + 1 == len(highlights):
                        mt.last_reference = True

            color_variant += 1

        self.text_document_close(path)
        return file_content, semantic_tokens

    def list_of_token_modifiers(self, token_modifiers: int) -> list[str]:
        result = []
        for i in range (0, len(self.semantic_token_modifiers)):
            if (1 << i) & token_modifiers != 0:
                result.append(self.semantic_token_modifiers[i])
        return result

    def semantic_tokens_debug_info(self, semantic_tokens: list[SemanticToken], lines: list[str]) -> str:
        output_lines = []
        for token in semantic_tokens:
            token_string = lines[token.line][token.column:token.column+token.length]
            output_lines.append(
                f'line|col+len|cv: {token.line:>3}|{token.column:>3}+{token.length:>2}|{token.color_variant:>2}, '
                f'token: {token_string:<16}, '
                f'type: {self.semantic_token_types[token.token_type]:<13}, '
                f'modifiers: {", ".join(self.list_of_token_modifiers(token.token_modifiers))}\n'
            )
        return "".join(output_lines)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("specify 1 path (absolute or relative) to read")
        exit()

    clangd = Clangd()
    file_content, semantic_tokens = clangd.file_content_and_semantic_tokens_with_color_variance(sys.argv[1])
    print(clangd.semantic_tokens_debug_info(semantic_tokens, file_content.splitlines()))
