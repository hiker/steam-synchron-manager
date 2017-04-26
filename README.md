# Steam-Synchron-Mmanager
A simple wrapper around some SteamWorks API calls.
Commands can be entered on the command line, and a reply will be printed
to stdout.

# Installing Dependencies
You can download the SteamWorks API from https://partner.steamgames.com/ .
You need to login with your steam account details in order to download it.
Unpack the file either inside of this project, or
on the same level (otherwise define STEAM_DIR). By default the Steam-SDK
is unpacked in a directory called 'sdk' - rename this directory to 'steam-sdk'.

## Installing the dependencies:
```
mkdir -p dependencies/include
cp ../stk-code/bld/lib/libpng/RelWithDebInfo/libpng15_static.lib dependencies
cp ../stk-code/bld/lib/zlib/RelWithDebInfo/zlibstatic.lib
cp ../stk-code/lib/libpng/*.h dependencies/include
```

# Compilation
Use cmake:
```
mkdir bld
cd bld
cmake ..
```
Then start Visual Studio, open the solution in the bld directory, and compile.

# Combining with STK:
```
cp ./bld/bin/Debug/ssm.exe         ../stk-code/bld/
cp ./bld/bin/Debug/steam_api.dll   ../stk-code/bld
cp ./bld/bin/Debug/steam_appid.txt ../stk-code/bld
```
