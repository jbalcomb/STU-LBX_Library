cmake_minimum_required(VERSION 3.17)
project(STU_LBX_Library C)

set(CMAKE_C_STANDARD 90)

set(LIBLBX_SOURCES
        LibLBX/lbx.h
        LibLBX/lbx_defs.h
        LibLBX/lbx_meta.h
        LibLBX/lbx_types.h
        LibLBX/lib_lbx.c
        LibLBX/lib_lbx.h
        LibLBX/lib_lbx_display.c
        LibLBX/lib_lbx_display.h
        LibLBX/lib_lbx_meta.c
        LibLBX/lib_lbx_meta.h
        LibLBX/lib_lbx_record.c
        LibLBX/lib_lbx_record.h
        LibLBX/lib_lbx_record_type.c
        LibLBX/lib_lbx_record_type.h
        LibLBX/lib_lbx_record_subrecord.c
        LibLBX/lib_lbx_record_subrecord.h
        LibLBX/lib_lbx_types.h
        LibLBX/lib_lbx_util.c
        LibLBX/lib_lbx_util.h
        LibLBX/SDL2/palette_viewer.c
        LibLBX/SDL2/palette_viewer.h
        LibLBX/SDL2/sdl_colormap.c
        LibLBX/SDL2/sdl_colormap.h
        LibLBX/SDL2/mom_main_colormap.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

#set(SDL2_PATH "E:/devel_lib/SDL2-devel-2.0.14-mingw/SDL2-2.0.14/x86_64-w64-mingw32")
set(SDL2_PATH "E:/devel_lib/SDL2-devel-2.0.14-mingw/SDL2-2.0.14/i686-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(LibLBX ${LIBLBX_SOURCES})
