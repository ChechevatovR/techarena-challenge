import subprocess
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import List, Iterable

UPDATE_INPUTS = True
EXECUTOR = '/home/roman/cpp/cmake-build-debug/solution'
CWD = '/home/roman/runner-cwd/'


def read_inputs() -> Iterable[str]:
    return map(str, range(20, 0, -1))


def write_subprocess_input(filename: str, input: str) -> None:
    with open(CWD + filename, "w") as file:
        print(input, file=file)


def run_subprocess(id: int) -> None:
    proc = subprocess.Popen([EXECUTOR, str(id)], cwd=CWD, stderr=subprocess.PIPE)
    proc.wait()
    return


def read_subprocess_output(filename: str) -> str:
    with open(CWD + filename, "r") as file:
        return file.read()


def run_task(id: int, task_input: str) -> str:
    print(f"Thread: {id} start")
    if UPDATE_INPUTS:
        write_subprocess_input(f'{id}.in', task_input)
    run_subprocess(id)
    task_output = read_subprocess_output(f'{id}.out')
    print(f"Thread: {id} done")
    return task_output


def main():
    inputs = list(read_inputs())
    with ThreadPoolExecutor(max_workers=8) as pool:
        futures = pool.map(run_task, range(len(inputs)), inputs)
        for future in futures:
            print(future)


if __name__ == '__main__':
    main()
