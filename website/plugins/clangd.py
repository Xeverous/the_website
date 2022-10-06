import os
import json
import subprocess
import shutil
from typing import Union, List, Dict, Tuple


def make_json_rpc_request(id: Union[str, int], method: str, params: Union[Tuple, List, Dict]):
    if not isinstance(id, (str, int)):
        raise RuntimeError(f"id should be a number or a string: {id}")

    request = {
        "jsonrpc": "2.0",
        "id": id,
        "method": method
    }

    if params is not None:
        if isinstance(params, (list, tuple, dict)):
            request["params"] = params
        else:
            raise RuntimeError(f"params is not a structured type: {params}")

    return request


def make_lsp_request(json_rpc_request):
    string = json.dumps(json_rpc_request, indent=None)
    string = f"Content-Length: {len(string)}\r\n\r\n{string}"
    return string

def get_clangd_path():
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
        self.p = subprocess.Popen([self.clangd_path], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        self.id = 1

    def send(self, method: str, params):
        request = make_lsp_request(make_json_rpc_request(self.id, method, params))
        self.p.stdin.write(request.encode())
        self.p.stdin.flush()
        self.id += 1

    def receive(self):
        pass


if __name__ == "__main__":
    conn = Connection()
    conn.send("initialize", {"params": {
        "processId": None,
      		"rootUri": None,
      		"capabilities": {
		}
    }})
    print(conn.p.stdout.read1())
