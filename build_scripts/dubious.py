# script that copies an existing executable, and replaces a known string with a new one
# useful to tell stormground how to run

import sys
import os
import re
from pathlib import Path

FILE = sys.argv[1]
NAME = sys.argv[2]

if sys.platform == "win32":
  EXT = ".exe"
else:
  EXT = ""

def main():
  with open(FILE, "rb") as file:
    content = bytearray(file.read())
    r = re.compile(b"sg#{61}")
    m = r.search(content)
    if m == None:
      return
    N:bytearray = NAME
    N = N[:63]
    for i in range(63- len(NAME)):
      N = N + "#"
    for i in range(m.start(), m.end()):
      content[i] = ord(N[i - m.start()])
    with open(os.path.join(Path(FILE).parent.absolute(), NAME + EXT), "wb") as out:
      out.write(content)

if __name__ == "__main__":
  main();
