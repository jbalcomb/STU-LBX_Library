
# * the relative paths need to be relative to where the target is created, i.e. the add_executable(...) call.
# * 'include_directories' is the older style CMake and will apply to all targets created after it.
#   Use 'target_include_directories' instead for the more modern target-centric approach of having commands only apply to the appropriate target instead of globally.
# * Rather than use a list of sources, you can also use the 'target_sources' command to programmatically add source files to a target based on necessary logic.
#   The same restriction applies though that the sources added need to be relative to the target location or an absolute path.
# * The preferred project layout for CMake is to really have out-of-source builds.
#   So instead having bin as a sub-directory of your project, just eliminate that level entirely.

message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})
message(CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR})


cmake_minimum_required(VERSION 3.17)


message(STU_LBX_LIBRARY_SOURCE_DIR: ${STU_LBX_LIBRARY_SOURCE_DIR})
message(STU_LBX_Library_SOURCE_DIR: ${STU_LBX_Library_SOURCE_DIR})
project(STU_LBX_Library C)
message(STU_LBX_LIBRARY_SOURCE_DIR: ${STU_LBX_LIBRARY_SOURCE_DIR})
message(STU_LBX_Library_SOURCE_DIR: ${STU_LBX_Library_SOURCE_DIR})


# set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD 99)


include(CTest)
enable_testing()
add_subdirectory(LibLBX/test)
# if(BUILD_TESTING)
#     # ... CMake code to create tests ...
# endif()
# add_test(test_name Exe_Name.exe arg1 arg2 ...)

message(VERSION: ${VERSION})
message(CMAKE_C_STANDARD: ${CMAKE_C_STANDARD})
message(PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR})      # C:/Development/STU-LBX_Library
message(BUILD_TESTING: ${BUILD_TESTING})



#set(LIBLBX_SOURCES
#        LibLBX/lib_lbx.c
#        LibLBX/lib_lbx.h
#        LibLBX/lib_lbx_display.c
#        LibLBX/lib_lbx_display.h
#        LibLBX/lib_lbx_meta_data.c
#        LibLBX/lib_lbx_meta_data.h
#        LibLBX/lib_lbx_record.c
#        LibLBX/lib_lbx_record.h
#        LibLBX/lib_lbx_record_type.c
#        LibLBX/lib_lbx_record_type.h
#        LibLBX/lib_lbx_record_subrecord.c
#        LibLBX/lib_lbx_record_subrecord.h
#        LibLBX/lib_lbx_util.c
#        LibLBX/lib_lbx_util.h
#        LibLBX/lbx_record_type_font.h
#        LibLBX/lbx_record_type_palette.h
#        LibLBX/lbx_record_type_image.h
#        LibLBX/lib_lbx_record_image.c
#        LibLBX/lib_lbx_record_image.h
#        LibLBX/lib_lbx_record_display.c
#        LibLBX/lib_lbx_record_display.h
#        LibLBX/lib_lbx_record_palette.c
#        LibLBX/lib_lbx_record_palette.h
#        LibLBX/per_game/MoM131/MoM131_palette.h
#        LibLBX/per_game/MoM131/FONTS_LBX.h
#        LibLBX/per_game/MoM131/MAIN_LBX.h
#        LibLBX/lib_lbx_load.c
#        LibLBX/lib_lbx_load.h
#        LibLBX/per_game/MoM131/MoM131_LBX_Files.h
#        LibLBX/lbx_graphics.h
#        LibLBX/lbx_sounds.h
#        LibLBX/lib_lbx_unbrun.c
#        LibLBX/lib_lbx_unbrun.h
#        LibLBX/lib_lbx_util_rle.c
#        LibLBX/lib_lbx_util_rle.h
#        LibLBX/lib_lbx_process_records.c
#        LibLBX/lib_lbx_process_records.h
#        LibLBX/lib_lbx_load_header.c
#        LibLBX/lib_lbx_load_header.h
#        LibLBX/lib_lbx_process_lbx.c
#        LibLBX/lib_lbx_process_lbx.h
#        LibLBX/lib_lbx_load_records.c
#        LibLBX/lib_lbx_load_records.h
#        LibLBX/lib_lbx_record_flic.c
#        LibLBX/lib_lbx_record_flic.h
#        LibLBX/test/lib_lbx_test.c
#        LibLBX/test/lib_lbx_test.h
#        LibLBX/lib_lbx_file_type_bmp.c
#        LibLBX/lib_lbx_file_type_bmp.h
#        LibLBX/ATS/ats_matrix_transform.c
#        LibLBX/ATS/ats_matrix_transform.h
#        LibLBX/ATS/unicode_box_drawing_block.h
#        LibLBX/ATS/ats_print_box.c
#        LibLBX/ATS/ats_print_box.h
#        LibLBX/ATS/ats_array_test.c
#        LibLBX/ATS/ats_array_test.h)

# add_library(LibLBX ${LIBLBX_SOURCES})

add_library(LibLBX)

target_sources(LibLBX
        PRIVATE
            # N/A
        PUBLIC
            LibLBX/lib_lbx.c
            LibLBX/lib_lbx.h
            LibLBX/lib_lbx_display.c
            LibLBX/lib_lbx_display.h
            LibLBX/lib_lbx_meta_data.c
            LibLBX/lib_lbx_meta_data.h
            LibLBX/lib_lbx_record.c
            LibLBX/lib_lbx_record.h
            LibLBX/lib_lbx_record_type.c
            LibLBX/lib_lbx_record_type.h
            LibLBX/lib_lbx_record_subrecord.c
            LibLBX/lib_lbx_record_subrecord.h
            LibLBX/lib_lbx_util.c
            LibLBX/lib_lbx_util.h
            #LibLBX/lbx_record_type_font.h
            #LibLBX/lbx_record_type_palette.h
            #LibLBX/lbx_record_type_flic.h
            #LibLBX/lib_lbx_record_image.c
            #LibLBX/lib_lbx_record_image.h
            #LibLBX/lib_lbx_record_display.c
            #LibLBX/lib_lbx_record_display.h
            #LibLBX/lib_lbx_record_palette.c
            #LibLBX/lib_lbx_record_palette.h
            #LibLBX/per_game/MoM131/MoM131_palette.h
            #LibLBX/per_game/MoM131/FONTS_LBX.h
            #LibLBX/per_game/MoM131/MAIN_LBX.h
            #LibLBX/lib_lbx_load.c
            #LibLBX/lib_lbx_load.h
            #LibLBX/per_game/MoM131/MoM131_LBX_Files.h
            #LibLBX/lbx_graphics.h
            #LibLBX/lbx_sounds.h
            #LibLBX/lib_lbx_unbrun.c
            #LibLBX/lib_lbx_unbrun.h
            #LibLBX/lib_lbx_util_rle.c
            #LibLBX/lib_lbx_util_rle.h
            LibLBX/lib_lbx_process_records.c
            LibLBX/lib_lbx_process_records.h
            LibLBX/lib_lbx_load_header.c
            LibLBX/lib_lbx_load_header.h
            LibLBX/lib_lbx_process_lbx.c
            LibLBX/lib_lbx_process_lbx.h
            LibLBX/lib_lbx_load_records.c
            LibLBX/lib_lbx_load_records.h
            #LibLBX/lib_lbx_record_flic.c
            #LibLBX/lib_lbx_record_flic.h
            #LibLBX/test/lib_lbx_test.c
            #LibLBX/test/lib_lbx_test.h
            #LibLBX/lib_lbx_file_type_bmp.c
            #LibLBX/lib_lbx_file_type_bmp.h
            #LibLBX/ATS/ats_matrix_transform.c
            #LibLBX/ATS/ats_matrix_transform.h
            #LibLBX/ATS/unicode_box_drawing_block.h
            #LibLBX/ATS/ats_print_box.c
            #LibLBX/ATS/ats_print_box.h
            #LibLBX/ATS/ats_array_test.c
            #LibLBX/ATS/ats_array_test.h
            #LibLBX/ATS/unicode_superscript.h
            #LibLBX/ATS/unicode_subscript.h
            #LibLBX/ATS/ats_alphabets.h
            #LibLBX/ATS/ats_array_print.c
            #LibLBX/ATS/ats_array_print.h
            #LibLBX/ATS/ats_matrix_utility.c
            #LibLBX/ATS/ats_matrix_utility.h
            #LibLBX/ATS/ats_console.c
            #LibLBX/ATS/ats_console.h
            #LibLBX/ATS/ats_palette.c
            #LibLBX/ATS/ats_palette.h
            #LibLBX/per_game/MoM131/FONTS_LBX_002.h
            #LibLBX/per_game/MoM131/MoM131_font_record.h
            #LibLBX/per_game/MoM131/MoM131_palette_record.h
            #LibLBX/lbx_record_type_palette.c
            #LibLBX/ST_Game/MoM/lib_lbx_mom.c
            #LibLBX/ST_Game/MoM/lib_lbx_mom.h

        INTERFACE
            # N/A
        )
