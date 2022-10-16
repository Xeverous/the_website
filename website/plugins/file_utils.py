import os

def is_relative_path(path: str) -> bool:
    return path[0] != "/"


def make_path(source_path: str, path: str) -> str:
    if is_relative_path(path):
        return os.path.join(os.path.dirname(source_path), path)
    else:
        return path


def read_file(path: str) -> str:
    with open(path, 'r', encoding="utf-8") as file:
        return file.read()
