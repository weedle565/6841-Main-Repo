cmake_minimum_required(VERSION 3.22)
project(6841Project C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR C:/clibs/SDL/include)
set(SDL2_LIB_DIR C:/clibs/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_TFF_INCLUDE_DIR C:/clibs/tff/include)
set(SDL2_TFF_LIB_DIR C:/clibs/tff/lib/x64)

include_directories(${SDL2_TFF_INCLUDE_DIR})
link_directories(${SDL2_TFF_LIB_DIR})

set(SDL2_sdl_image_INCLUDE_DIR C:/clibs/sdl_image/include)
set(SDL2_sdl_image_LIB_DIR C:/clibs/sdl_image/lib/x64)

include_directories(${SDL2_sdl_image_INCLUDE_DIR})
link_directories(${SDL2_sdl_image_LIB_DIR})

add_executable(6841Project server/server.c server/microui.c server/microui.h server_window.c server/render.c server/render.h
        client/system.c
        client/system.h)

target_link_libraries(6841Project SDL2main SDL2)
target_link_libraries(6841Project SDL2_image)
target_link_libraries(6841Project SDL2_ttf)

if(WIN32)
    target_link_libraries(6841Project wsock32 ws2_32)
endif()
