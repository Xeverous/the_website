import os
import json
import subprocess
import shutil
from typing import Union, Any


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


def json_rpc_response_extract_content(response: dict[str, Any], id: Union[str, int]) -> tuple[dict[str, Any], bool]:
    """extract result or error subobject, return this object + False if object is error"""
    response_id = response.get("id")
    if not response_id:
        raise RuntimeError(f"no id object in response:\n{json.dumps(response, indent=4)}")
    if response_id != id:
        raise RuntimeError(f"expected response with id {id} but got {response_id}")

    # use "in" instead of ".get()" to differentiate between no item and item with value None
    # (some JSON RPC calls can return "result": null)
    if "result" in response:
        return response.get("result"), True

    error = response.get("error")
    if error:
        return error, False

    raise RuntimeError(f"invalid JSON RPC response:\n{json.dumps(response, indent=4)}")


HEADER_CONTENT_LENGTH = "Content-Length: "

def lsp_make_message(json_rpc_object: dict[str, Any]) -> bytes:
    body = json.dumps(json_rpc_object, indent=None).encode()
    return f"{HEADER_CONTENT_LENGTH}{len(body)}\r\n\r\n".encode() + body

def lsp_make_text_document_identifier(uri: str) -> dict[str, Any]:
    return {"uri": uri}

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

    def _send(self, message: bytes) -> None:
        bytes_written = self.p.stdin.write(message)
        if bytes_written != len(message):
            raise RuntimeError(f"Wrote only {bytes_written} of {len(message)} bytes when sending:\n{message.decode()}")

        self.p.stdin.flush()

    def _receive(self) -> str:
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
        self._send(lsp_make_message(json_rpc_make_notification(method, params)))

    def make_lsp_request(self, method: str, params: Any) -> Any:
        id = self.id
        self._send(lsp_make_message(json_rpc_make_request(id, method, params)))
        self.id += 1
        response, is_success = json_rpc_response_extract_content(json.loads(self._receive()), id)

        if is_success:
            return response
        else:
            raise RuntimeError(f"JSON RPC call failed: {json.dumps(response, indent=None)}")

    def initialize(self):
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
                            "multilineTokenSupport": True
                        }
                    }
                }
                # TODO workspaceFolders
            })
        self.initialized = True
        print(json.dumps(result, indent=4))

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


if __name__ == "__main__":
    conn = Connection()
