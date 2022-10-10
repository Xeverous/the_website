import os
import json
import subprocess
import shutil
from typing import Union, Any


def make_json_rpc_notification(method: str, params: Union[tuple, list, dict, None]) -> dict[str, Any]:
    message = {
        "jsonrpc": "2.0",
        "id": id,
        "method": method
    }

    if params is not None:
        if isinstance(params, (list, tuple, dict)):
            message["params"] = params
        else:
            raise RuntimeError(f"params is not a structured type: {params}")

    return message


def make_json_rpc_request(id: Union[str, int], method: str, params: Union[tuple, list, dict, None]) -> dict[str, Any]:
    if not isinstance(id, (str, int)):
        raise RuntimeError(f"id should be a number or a string: {id}")

    message = make_json_rpc_notification(method, params)
    message["id"] = id
    return message


def json_rpc_response_extract_content(response: dict[str, Any], id: Union[str, int]) -> tuple[dict[str, Any], bool]:
    """extract result or error subobject, return this object + False if object is error"""
    response_id = response.get("id")
    if not response_id:
        raise RuntimeError(f"no id object in response:\n{json.dumps(response, indent=4)}")
    if response_id != id:
        raise RuntimeError(f"expected response with id {id} but got {response_id}")

    result = response.get("result")
    if result:
        return result, True

    error = response.get("error")
    if error:
        return error, False

    raise RuntimeError(f"invalid JSON RPC response:\n{json.dumps(response, indent=4)}")


HEADER_CONTENT_LENGTH = "Content-Length: "

def make_lsp_message(json_rpc_object: dict[str, Any]) -> bytes:
    body = json.dumps(json_rpc_object, indent=None).encode()
    return f"{HEADER_CONTENT_LENGTH}{len(body)}\r\n\r\n".encode() + body

def get_clangd_path() -> str:
    result = shutil.which("clangd")
    if result:
        return result

    env_name = os.environ.get("CLANGD")
    if env_name:
        result = shutil.which(env_name)
        if result:
            return result

    raise RuntimeError("clangd not found. Specify env variable CLANGD that points to the executable or to a name searchable in PATH")


class Connection:
    def __init__(self):
        self.clangd_path = get_clangd_path()
        # TODO: log clangd version
        self.p = subprocess.Popen([self.clangd_path, "--log=error"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        self.id = 1

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
        self._send(make_lsp_message(make_json_rpc_notification(method, params)))

    def make_lsp_request(self, method: str, params: Any) -> Any:
        id = self.id
        self._send(make_lsp_message(make_json_rpc_request(id, method, params)))
        self.id += 1
        response, is_success = json_rpc_response_extract_content(json.loads(self._receive()), id)

        if is_success:
            return response
        else:
            raise RuntimeError(f"JSON RPC call failed: {json.dumps(response, indent=None)}")

    def initialize(self):
        result = self.make_lsp_request("initialize", {"params": {
            "processId": None,
                "rootUri": None,
                "capabilities": {
                }
            }
        })
        print(result)

if __name__ == "__main__":
    conn = Connection()
    conn.initialize()
