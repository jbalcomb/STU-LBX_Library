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
        LibLBX/lib_lbx_util.h)

add_library(LibLBX ${LIBLBX_SOURCES})
