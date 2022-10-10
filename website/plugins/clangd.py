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

HEADER_CONTENT_LENGTH = "Content-Length: "


def make_lsp_call_string(json_rpc_object: dict[str, Any]) -> str:
    string = json.dumps(json_rpc_object, indent=None)
    return f"{HEADER_CONTENT_LENGTH}{len(string)}\r\n\r\n{string}"

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

    def initialize(self):
        self.make_lsp_call("initialize", {"params": {
            "processId": None,
                "rootUri": None,
                "capabilities": {
                }
            }
        })

    def make_lsp_call(self, method: str, params):
        response = self.receive(self.send(method, params))
        print(response)

    def send(self, method: str, params) -> int:
        request = make_lsp_call_string(make_json_rpc_request(self.id, method, params))
        self.p.stdin.write(request.encode())
        self.p.stdin.flush()
        id = self.id
        self.id += 1
        return id

    def receive(self, id: int):
        headers = []

        while True:
            line = self.p.stdout.readline()
            if line != b"\r\n":
                headers.append(line)
            else:
                break

        length = 0
        for hdr in headers:
            hdr = hdr.decode()
            if HEADER_CONTENT_LENGTH in hdr:
                length = int(hdr.removeprefix(HEADER_CONTENT_LENGTH))
                break

        if length == 0:
            raise RuntimeError(f"invalid or missing '{HEADER_CONTENT_LENGTH}' header")

        return self.p.stdout.read(length).decode()

if __name__ == "__main__":
    conn = Connection()
    conn.initialize()
