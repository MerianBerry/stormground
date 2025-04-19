Building
=====

All building is done with make, so make sure that is installed.

Windows
-----

Stormground can only be built for Windows on a Linux machine.

1. With whichever package manager you have on your distro, install the x86-64 versions of mingw.
2. Check that mingw installed by running `x86_64-w64-mingw32-gcc --version` in your terminal.
3. Run `make mingw` in a terminal in Stormground's root directory.
4. If no errors occured, `sg.exe` will be in the `build` directory.

Linux
-----

Stormground can only be built for Linux on a Linux machine.

1. gcc should be installed by default, but if not, install with whichever package manager your distro has.
2. Run `make` in a terminal in Stormground's root directory.
3. If no errors occured, `sg` will be in the `build` directory.

MacOS
-----

Stormground can only be built for Mac on a Mac machine.
