import sys
import glob
import shutil
import os

def find_files_recursive_glob(directory, filename):
  filename += ".dll"
  pattern = os.path.join(directory, '**', filename)
  return glob.glob(pattern, recursive=True)

if len(sys.argv) < 3:
    print("Invalid engine build script arguments")
    exit
debug = sys.argv[1] == "debug"
outdir = sys.argv[2]
engdir = sys.argv[3] + "/engine"
tpdir = sys.argv[3] + "/third_party"

build_cmd = ""
if debug:
  build_cmd = "dotnet build"
else:
  build_cmd = "dotnet publish"

os.chdir(engdir)
os.system(build_cmd)

for i in range(4, len(sys.argv)):
  files = find_files_recursive_glob(engdir, sys.argv[i])
  files += find_files_recursive_glob(tpdir, sys.argv[i])
  if len(files) == 0:
    print(f"Couldn't find any matching files for {sys.argv[i]} :|")
    continue
  for x in files:
    #print(f"match: {sys.argv[i]} -> {x}")
    if os.path.isfile(x):
      print(f"Found match: {sys.argv[i]} -> {x}")
      #print(f"Found match: {os.path.dirname(x) + "/" + sys.argv[i] + ".pdb"} -> {outdir + sys.argv[i] + ".pdb"}")
      shutil.copy(x,outdir + os.path.basename(x))
      shutil.copy(os.path.dirname(x) + "/" + sys.argv[i] + ".pdb", outdir + sys.argv[i] + ".pdb")
      break

