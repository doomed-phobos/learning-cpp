import sys
import os
import colorama
import subprocess
from typing import List, Tuple

CWD = os.path.dirname(__file__)
DATA_DIR = f"{CWD}\data"
SUCCESS_STYLE = colorama.Fore.LIGHTYELLOW_EX
ERROR_STYLE = colorama.Fore.LIGHTRED_EX

def has_one_empty(list: List):
   for item in list:
      if not item:
         return True
   return False

def get_name_and_dir(text: str) -> Tuple[str, str]:
   for line in text.split(";"):
      if line:
         nd = line.split("|")
         if not has_one_empty(nd):
            yield tuple(nd)

def main(argv):
   # Iniciando colorama
   colorama.init(True)
   # Limpiando la consola
   if sys.platform == "win32":
      os.system("cls")

   try:
      with open(DATA_DIR) as f:
         lines = f.readlines()
         BUILD_DIR =  lines[0]
         subprocess.run(f"cmake --build {BUILD_DIR}".strip()).check_returncode()
         for name, dir in get_name_and_dir(lines[1]):
            if name == argv[1]:
               subprocess.run(f"{dir}/Debug/{name}.exe").check_returncode()
   except IndexError:
      print(SUCCESS_STYLE + "Warning: No se pasó ningun proyecto a ejecutar")
   except subprocess.CalledProcessError as e:
      print(ERROR_STYLE + f"CalledProcessError: {e}")
   except BaseException as e:
      print(f"Error: {e}")

if __name__ == "__main__":
   main(sys.argv)