# - Try to find Steamworks API
# Once done this will define
#
#  STEAM_FOUND - system has angelscript
#  STEAM_INCLUDE_DIR - the steam include directory
#  STEAM_LIBRARIES - the libraries needed to use angelscript
#

FIND_PATH(STEAM_INCLUDE_DIR steam/steam_api.h
    ${STEAM_DIR}/public
    ../steam-sdk/public
    ./steam-sdk/public
    )
if(WIN32)
    FIND_LIBRARY(STEAM_LIBRARIES steam_api PATHS
        ${STEAM_DIR}/redistributable_bin
        ../steam-sdk/redistributable_bin
        ./steam-sdk/redistributable_bin         )
else()   # linux
    FIND_LIBRARY(STEAM_LIBRARIES steam_api PATHS
    ${STEAM_DIR}/redistributable_bin/linux64
    ../steam-sdk/redistributable_bin/linux64
    ./steam-sdk/redistributable_bin/linux64     )
endif()

# Handle the QUIETLY and REQUIRED arguments and set STEAM_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Steam DEFAULT_MSG STEAM_LIBRARIES
                                                    STEAM_INCLUDE_DIR)

MARK_AS_ADVANCED(STEAM_LIBRARIES STEAM_INCLUDE_DIR)
set(STEAM_ROOT ${STEAM_LIBRARIES}/..)
