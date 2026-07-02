Stormground
=====

Stormworks Lua drawing API replica, with some creative liberties.
With support for Windows, Linux, and Mac.

Getting Started
-----

It is reccomended to download an appropriate binary from the GitHub [releases](https://github.com/MerianBerry/stormground/releases) page. All you need to do is download the archive, extract it, and run stormground.

If you wish to build Stormground from source, see the [building documentation](docs/building.md). But note that Stormground can only build for Windows on a Linux machine.

After you have acquired the Stormground executable, it is recommended that you check out the [manual](docs/manual.md).

Documentation
-----

All documentation for using Stormground is inside the [manual](docs/manual.md).

v1.5 Order Of Business
-----
The end goal for v1.5 is to refactor the entire source to a more modern codebase, with better tools, to facilitate v2 devolopment. However, instead of jumping straight there, I want to make a sort of "beta" version, being 1.5. The backend will be almost if not entirely different, however the frontend (user side) will be almost identical.

The end result will be use wise the same. But will release a lot of tech-debt, and be in a much better condition to grow.

- [x] Change build system to CMake. C0
- [x] Swap window libraries to SDL3. C1
- [ ] Port source code to C++ (and integrate SCL). C1
  - This will use the modern version of SCL, the C++ version. Note that in the current version (an in-dev version), the xml sublib does not work, but wont be needed in any capacity for v1.5.
- [ ] Refresh and swap to Vesuvius, a Vulkan abstraction layer. C2
  - Requires vesuvius to get new code, as it is incomplete. To be fully integrated, it will require VSH, an at-runtime shader cross-compiler, to also be integrated, though that is much more complete. Note that to keep things simpler, vesuvius will NOT be ported to C++, and will remain in C.
- [ ] Swap Lua runtimes to Luajit, and modify api (lua shim w/ ffi C calls). C1
  - By this i mean write an in-script user facing api, matching the current api. But under that, it uses luajit's ffi library to do native calls to exposed stormground functions.
- [ ] Use SCL pack and other means to create self-contained binaries. C1 - C2
  - On windows this should be pretty simple, by setting a resource in the binary with the content packs. On linux, you should be able to patch the pack in as a custom section. For macos, idk some macho stuff.
- [ ] Investigate Vulkan on MacOS

License
-----

Stormground v1 and all minor versions are not licensed, but use 3rd party libraries which are:

* [`glfw`](https://github.com/glfw/glfw): Zlib
* [`cJSON`](https://github.com/DaveGamble/cJSON): MIT
* [`minilua`](https://github.com/edubart/minilua): MIT
