cmake_minimum_required(VERSION 3.22)
project(6841Project C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR C:/clibs/SDL/include)
set(SDL2_LIB_DIR C:/clibs/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_TFF_INCLUDE_DIR C:/clibs/tff/include)
set(SDL2_TFF_LIB_DIR C:/clibs/tff/lib/x86)

include_directories(${SDL2_TFF_INCLUDE_DIR})
link_directories(${SDL2_TFF_LIB_DIR})

set(SDL2_sdl_image_INCLUDE_DIR C:/clibs/sdl_image/include)
set(SDL2_sdl_image_LIB_DIR C:/clibs/sdl_image/lib/x86)

include_directories(${SDL2_sdl_image_INCLUDE_DIR})
link_directories(${SDL2_sdl_image_LIB_DIR})

add_executable(6841Project server.c microui.c microui.h server_window.c render.c render.h)
