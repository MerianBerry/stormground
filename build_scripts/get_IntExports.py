import sys
import glob
import shutil
import os
import re

platform = sys.platform
WORKING_DIR = sys.argv[1]

def main():
  if platform == "win32":
    os.chdir(WORKING_DIR)
    os.system("echo Looking for candidates")

    cmds = glob.glob('C:\\Program Files\\Microsoft Visual Studio\\*\\*\\Common7\\Tools\\VsDevCmd.bat')
    for x in cmds:
      os.system("echo Candidate: " + x)
    if len(cmds) == 0:
      print("No dev environment candidates :(")
      return
    get_valid_funcs()
    get_exports_windows(cmds[0])


  else:
    raise RuntimeError("Unsupported platform")

blacklist = re.compile("GDK")
function = re.compile(r"((SDL|Storm)_[a-zA-Z]*(?= *\(.*\);))", re.S | re.M)
searches = {"SDL3/SDL_events.h", "SDL3/SDL_video.h", "SDL3/SDL_audio.h", "SDL3/SDL_gamepad.h", "SDL3/SDL_gpu.h", "../../core/api.hpp"}
sdlsym = re.compile("(?:External *\\| )(SDL_[a-zA-Z]*(Event|Window|Audio|GPU|Gamepad|^Init$|^Quit$)[a-zA-Z]*$)")
vfuncs: dict = {}


def get_valid_funcs():
  for search in searches:
    with open(search) as file:
      content = file.read()
      m = function.findall(content)
      for x in m:
        y = x[0]
        if not y in vfuncs:
          vfuncs[y] = y


def get_exports_windows(cmd):
  os.system(cmd + " & dumpbin /SYMBOLS SDL3-static.lib > symbols.txt")
  exports: dict = {
  }

  get_exports(exports, "symbols.txt")
  write_exports(exports)


def get_exports(exports: dict, path: str):
  with open(path) as file:
    for line in file:
      m = sdlsym.findall(line)
      if len(m) > 0 and export_is_valid(exports, m[0][0]):
        m = m[0][0]
        #print("Match: " + m)
        exports[m] = m
  with open("../../core/api.hpp") as file:
    content = file.read()
    m = function.findall(content)
    for x in m:
        y = x[0]
        if export_is_valid(exports, y):
          exports[y] = y


def export_is_valid(exports: dict, export):
  return not export in exports and export in vfuncs and not len(blacklist.findall(export))


def write_exports(exports: dict):
  out = open("exports.hpp", "w")
  out.write("""// This is an auto-generated file. modify it, or dont idc

#include "SDL3/SDL.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_gamepad.h"
#include "api.hpp"
#include <map>
#include <string>

static const std::map<std::string, void*> Exports = {
""")
  for x in exports:
    out.write(f'{{\"{x}", (void*){x}}},\n')

  out.write("""
};

static const std::map<std::string, void*> &GetExports() {
  return Exports;
}
""")

if __name__ == "__main__":
  main();
