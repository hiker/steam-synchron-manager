# Steam-Synchron-Mmanager
A simple wrapper around some SteamWorks API calls.
Commands can be entered on the command line, and a reply will be printed
to stdout.

# Compilation
Use cmake:
mkdir bld
cd bld
cmake ..

The SteamWorks SDK must be installed either inside of this project, or
on the same level (otherwise define STEAM_DIR).

Installing the dependencies:
mkdir -p dependencies/include
cp ../stk-code/bld/bld/libpng/RelWithDebInfo/libpng15_static.lib dependencies
cp ../stk-code/lib/libpng/*.h dependencies/include

Combining with STK:
cp ./bld/bin/Debug/ssm.exe         ../stk-code/bld/
cp ./bld/bin/Debug/steam_api.dll   ../stk-code/bld
cp ./bld/bin/Debug/steam_appid.txt ../stk-code/bld

