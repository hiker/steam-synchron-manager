# root CMakeLists for the SuperTuxKart project
project(SteamSynchronManager)
set(PROJECT_VERSION "0.1")

cmake_minimum_required(VERSION 2.8.4)
if(NOT (CMAKE_MAJOR_VERSION VERSION_LESS 3))
  cmake_policy(SET CMP0043 OLD)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(CMakeDependentOption)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Define install paths
set(SSM_INSTALL_BINARY_DIR "bin" CACHE
    STRING "Install executable to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")


if(WIN32)
    set(ENV{PATH} "$ENV{PATH};${PROJECT_SOURCE_DIR}/dependencies/include")
    set(ENV{LIB} ${PROJECT_SOURCE_DIR}/dependencies/lib)
endif()


# Set include paths
include_directories(".")

# Add libpng:
include_directories("${PROJECT_SOURCE_DIR}/dependencies/include")


# Set some compiler options
if(UNIX OR MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-invalid-offsetof")
endif()

if(MINGW AND CMAKE_BUILD_TYPE MATCHES Release)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--subsystem,windows")
endif()


if(WIN32)
    # And shut up about unsafe stuff, causes steam compilation errors
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(MSVC)
    # VS will automatically add NDEBUG for release mode, but only _DEBUG in debug mode.
    # Since SSM uses DEBUG, this is added for debug compilation only:
    set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS_DEBUG DEBUG)
    set(ADDITIONAL_LIBS ${PROJECT_SOURCE_DIR}/dependencies/libpng15_static.lib
                        ${PROJECT_SOURCE_DIR}/dependencies/zlibstatic.lib      )

else()
    # All non VS generators used create only a single compile mode, so
    # compile flags can be simplye be added
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DDEBUG)
    else()
        add_definitions(-DNDEBUG)
    endif()
    find_Package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    set(ADDITIONAL_LIBS ${PNG_LIBRARY})
endif()

find_package(Steam)

include_directories(${STEAM_INCLUDE_DIR})

set(SSM_SOURCES
    main.cpp
    steam.cpp steam.hpp
    )

add_executable(ssm
	${SSM_SOURCES}
	)
	
target_link_libraries(ssm 
                      ${STEAM_LIBRARIES}
                      ${ADDITIONAL_LIBS}
                      )

if(MSVC OR MINGW)
  add_custom_command(TARGET ssm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${STEAM_ROOT}/steam_api.dll"
        $<TARGET_FILE_DIR:ssm>)
endif()

add_custom_command(TARGET ssm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "../steam_appid.txt"
        $<TARGET_FILE_DIR:ssm>)
