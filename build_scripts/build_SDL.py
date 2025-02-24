# heavily based off of a build script by trojanfoe
# at https://gist.github.com/trojanfoe/aae4fe796c7bb8a58fd53d6562b4400d

import os
import shutil
import subprocess
import sys

SDL_TAG = "release-3.2.4"
WORKING_DIR = os.path.expanduser("~/source/SDL3")

platform = sys.platform

if platform == "win32":
  BUILD_FLAGS = ["--config Release"]
  BINARY_DIR = "Release\\"
  INSTALL_DIR = sys.argv[1]
  INSTALL_INCLUDE_DIR = os.path.join(INSTALL_DIR, "SDL3")
else:
  raise RuntimeError("Unsupported platform")


def main():
  #os.makedirs(WORKING_DIR, exist_ok=True)

  if installed():
    return;

  os.makedirs(INSTALL_DIR, exist_ok=True)

  clone_and_build_sdl()

  clone_and_build_shadercross();

  if platform == "win32":
    install_binaries_windows()


def clone_and_build_sdl():
  git_dir = os.path.join(WORKING_DIR, "SDL")
  if not os.path.exists(git_dir):
    run("Cloning SDL", ["git", "clone", "https://github.com/libsdl-org/SDL", git_dir])
    run(f"Fetching SDL origin", ["git", "fetch", "origin"], cwd=git_dir)
    run(f"Resetting SDL to {SDL_TAG}", ["git", "reset", "--hard", SDL_TAG], cwd=git_dir)

  build_dir = os.path.join(git_dir, "build")
  #if os.path.exists(build_dir):
  #    shutil.rmtree(build_dir)

  run(f"Configuring SDL", ["cmake", "-Bbuild", "-S.", "-DCMAKE_BUILD_TYPE=Release"], cwd=git_dir)
  build_args = ["cmake", "--build", "build"]
  for i in BUILD_FLAGS:
    build_args.append(i)
  run(f"Building SDL", build_args, cwd=git_dir)


def clone_and_build_shadercross():
  git_dir = os.path.join(WORKING_DIR, "SDL_shadercross")
  if not os.path.exists(git_dir):
    run("Cloning shadercross",
        ["git", "clone", "--recursive", "https://github.com/libsdl-org/SDL_shadercross", git_dir])
    run(f"Fetching shadercross origin", ["git", "fetch", "origin"], cwd=git_dir)
    run(f"Resetting shadercross to origin/main", ["git", "reset", "--hard", "origin/main"], cwd=git_dir)

  build_dir = os.path.join(git_dir, "build")
  #if os.path.exists(build_dir):
  #    shutil.rmtree(build_dir)

  run(f"Configuring shadercross",
      ["cmake", "-Bbuild", "-S.", "-DCMAKE_BUILD_TYPE=Release", "-DSDLSHADERCROSS_DXC=ON",
        "-DSDLSHADERCROSS_VENDORED=ON", "-DSDL3_DIR=../SDL/build"],
      cwd=git_dir)
  build_args = ["cmake", "--build", "build"]
  for i in BUILD_FLAGS:
    build_args.append(i)
  run(f"Building shadercross", build_args, cwd=git_dir)


def installed():
  if platform == "win32":
    return os.path.exists(os.path.join(INSTALL_INCLUDE_DIR, "SDL_shadercross.h"))


def install_binaries_windows():
  print(f"Installing binaries to {INSTALL_DIR}")

  shadercross_source_dir = os.path.join(WORKING_DIR, "SDL_shadercross")

  shadercross_build_dir = os.path.join(shadercross_source_dir, "build")

  shutil.copy(os.path.join(shadercross_build_dir, BINARY_DIR + "shadercross.exe"), INSTALL_DIR)

  shutil.copy(os.path.join(shadercross_build_dir, BINARY_DIR, "SDL3_shadercross-static.lib"), INSTALL_DIR)

  spirv_cross_build_dir = os.path.join(shadercross_build_dir, "external", "SPIRV-Cross", BINARY_DIR)

  shutil.copy(os.path.join(spirv_cross_build_dir, "spirv-cross-c-shared.dll"), INSTALL_DIR)

  directx_shader_compiler_build_dir = os.path.join(shadercross_build_dir, "external", "DirectXShaderCompiler", BINARY_DIR, "bin")

  shutil.copy(os.path.join(directx_shader_compiler_build_dir, "dxcompiler.dll"), INSTALL_DIR)

  sdl_source_dir = os.path.join(WORKING_DIR, "SDL")

  sdl_build_dir = os.path.join(sdl_source_dir, "build", BINARY_DIR)


  shutil.copy(os.path.join(sdl_build_dir, "SDL3.dll"), INSTALL_DIR)

  shutil.copy(os.path.join(sdl_build_dir, "SDL3.lib"), INSTALL_DIR)

  shutil.copytree(os.path.join(sdl_source_dir, "include", "SDL3"), INSTALL_INCLUDE_DIR, dirs_exist_ok=True)
  shutil.copytree(os.path.join(shadercross_source_dir, "include", "SDL3_shadercross"), INSTALL_INCLUDE_DIR, dirs_exist_ok=True)

  #shutil.rmtree(INSTALL_DIR)



def run(purpose, cmd_line, cwd=None):
  print("{}: {}".format(purpose, " ".join(cmd_line)))
  subprocess.run(cmd_line, check=True, encoding="utf-8", cwd=cwd)

if __name__ == "__main__":
  main();
