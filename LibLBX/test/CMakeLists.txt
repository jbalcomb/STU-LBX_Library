
message(CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})
message(CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR})

message(VERSION: ${VERSION})
message(CMAKE_C_STANDARD: ${CMAKE_C_STANDARD})
message(PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR})      # C:/Development/STU-LBX_Library
message(BUILD_TESTING: ${BUILD_TESTING})
message(TEST_SOURCE_DIR: ${TEST_SOURCE_DIR})
message(CTEST_SOURCE_DIRECTORY: ${CTEST_SOURCE_DIRECTORY})

# message(LIBLBX_SOURCES: ${LIBLBX_SOURCES})
# message(TEST_LIBLBX_SOURCES: ${TEST_LIBLBX_SOURCES})

#set(TEST_LIBLBX_SOURCES
#        ../lib_lbx.c
#        ../lib_lbx.h
#        ../lib_lbx_display.c
#        ../lib_lbx_display.h
#        ../lib_lbx_meta_data.c
#        ../lib_lbx_meta_data.h
#        ../lib_lbx_record.c
#        ../lib_lbx_record.h
#        ../lib_lbx_record_type.c
#        ../lib_lbx_record_type.h
#        ../lib_lbx_record_subrecord.c
#        ../lib_lbx_record_subrecord.h
#        ../lib_lbx_util.c
#        ../lib_lbx_util.h
#        ../lbx_record_type_font.h
#        ../lbx_record_type_palette.h
#        ../lbx_record_type_image.h
#        ../lib_lbx_record_image.c
#        ../lib_lbx_record_image.h
#        ../lib_lbx_record_display.c
#        ../lib_lbx_record_display.h
#        ../lib_lbx_record_palette.c
#        ../lib_lbx_record_palette.h
#        ../per_game/MoM131/MoM131_palette.h
#        ../per_game/MoM131/FONTS_LBX.h
#        ../per_game/MoM131/MAIN_LBX.h
#        ../lib_lbx_load.c
#        ../lib_lbx_load.h
#        ../per_game/MoM131/MoM131_LBX_Files.h
#        ../lbx_graphics.h
#        ../lbx_sounds.h
#        ../lib_lbx_unbrun.c
#        ../lib_lbx_unbrun.h
#        ../lib_lbx_util_rle.c
#        ../lib_lbx_util_rle.h
#        ../lib_lbx_process_records.c
#        ../lib_lbx_process_records.h
#        ../lib_lbx_load_header.c
#        ../lib_lbx_load_header.h
#        ../lib_lbx_process_lbx.c
#        ../lib_lbx_process_lbx.h
#        ../lib_lbx_load_records.c
#        ../lib_lbx_load_records.h
#        ../lib_lbx_record_flic.c
#        ../lib_lbx_record_flic.h
#        ../lib_lbx_file_type_bmp.c
#        ../lib_lbx_file_type_bmp.h
#        ../ATS/ats_matrix_transform.c
#        ../ATS/ats_matrix_transform.h
#        ../ATS/unicode_box_drawing_block.h
#        ../ATS/ats_print_box.c
#        ../ATS/ats_print_box.h)


#find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
# include_directories(${TEST_SOURCE_DIR}/src)
#ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

# add_executable(testy lib_lbx_test.c ${TEST_SOURCE_DIR}/src/lib_lbx_test.c)
# add_executable(testy lib_lbx_test.c)
add_executable(TestyTester ${TEST_LIBLBX_SOURCES})

target_link_libraries(
        TestyTester
        LibLBX
)

# enable_testing() # already specified in the parent CMakeLists.txt
add_test(TestyTesterTest TestyTester)

target_sources(TestyTester
        PRIVATE
            lib_lbx_test.c
            lib_lbx_test.h
        PUBLIC
            # N/A
        INTERFACE
            # N/A
        )
