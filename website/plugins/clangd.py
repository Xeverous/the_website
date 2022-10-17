import os
import json
import subprocess
import shutil
from typing import Union, Any
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

def lsp_make_text_document_identifier(path: str) -> dict[str, Any]:
    return {"uri": path_to_uri(path)}

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

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_documentSymbol
    # each symbol is reported only once; only symbols originating from the file are reported
    def text_document_semantic_tokens_full(self, path: str) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/semanticTokens/full", {
            "textDocument": lsp_make_text_document_identifier(path)
        })

    # https://microsoft.github.io/language-server-protocol/specifications/lsp/3.17/specification/#textDocument_semanticTokens
    # each occurrence of a symbol (typically an identifier) is reported; each symbol has a range, 1 type and 0+ modifiers
    def text_document_document_symbols(self, path: str) -> dict[str, Any]:
        return self.conn.make_lsp_request("textDocument/documentSymbol", {
            "textDocument": lsp_make_text_document_identifier(path)
        })

    def semantic_tokens_for_file(self, path: str):
        lines = self.text_document_open(path).splitlines()
        result = self.text_document_semantic_tokens_full(path)
        self.text_document_close(path)
        self.debug_print_semantic_tokens(result["data"], lines)

    def list_of_token_modifiers(self, token_modifiers: int) -> list[str]:
        result = []
        for i in range (0, len(self.semantic_tokens_modifiers)):
            if (1 << i) & token_modifiers != 0:
                result.append(self.semantic_tokens_modifiers[i])
        return result

    def debug_print_semantic_tokens(self, data: dict[str, Any], lines: list[str]):
        last_line = 0
        last_column = 0
        for i in range(0, len(data) // 5):
            idx = i * 5
            delta_line = data[idx]
            delta_column = data[idx + 1]
            length = data[idx + 2]
            token_type = data[idx + 3]
            token_modifiers = data[idx + 4]

            line = last_line + delta_line
            if delta_line != 0:
                # token column is only relative when on the same line
                last_column = 0
            column = last_column + delta_column

            token = lines[line][column:column+length]
            print(f'token: "{token}", type: {self.semantic_tokens_types[token_type]}, modifiers: {", ".join(self.list_of_token_modifiers(token_modifiers))}')

            last_line = line
            last_column = column


if __name__ == "__main__":
    clangd = Clangd()
    clangd.semantic_tokens_for_file("main.cpp")
