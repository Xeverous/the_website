import os

def is_relative_path(path: str) -> bool:
    return path[0] != "/"


def path_description(is_relative: bool) -> str:
    if is_relative:
        return "relative"
    else:
        return "absolute"


def make_path_absolute(base_path: str, path: str) -> str:
    if is_relative_path(path):
        return os.path.join(os.path.dirname(base_path), path)
    else:
        return path


def read_file(path: str) -> str:
    with open(path, 'r', encoding="utf-8") as file:
        return file.read()
