from typing import Callable


def get_lambda(prompt: str, check: Callable[[str], bool]) -> str:
    """
    Get a string from the user that passes a check. Error messages to the user can be printed in the check function.
    :param prompt:
    :param check:
    :return:
    """
    while True:
        value = input(prompt)
        if check(value):
            return value