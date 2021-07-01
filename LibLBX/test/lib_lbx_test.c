#include <malloc.h>         /* malloc(), realloc(); */
#include <stdlib.h>         /* itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcat(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_test.h"

#include "../lib_lbx_process_lbx.h"
#include "../lib_lbx_record_flic.h"

#include "../ATS/ats_matrix_transform.h"
#include "../ATS/ats_print_box.h"
#include "../ATS/ats_array_test.h"
#include "../ATS/ats_array_print.h"
#include "../ATS/ats_matrix_utility.h"
#include "../lib_lbx_display.h"
#include "../lib_lbx_record_display.h"
#include "../lib_lbx_process_records.h"
#include "../lib_lbx_load_records.h"
#include "../lib_lbx_util.h"
#include "../lib_lbx_load_header.h"
#include "../lib_lbx_meta_data.h"
#include "../lib_lbx_file_type_bmp.h"
#include "../lib_lbx_load.h"
#include "../lib_lbx_record_flic.h"
#include "../lib_lbx_record_palette.h"

char TEST_DIRECTORY_PATH[] = "F:\\devel_data\\STU\\MoM131_LBX\\";
char TEST_FILE_PATH[] = "F:\\devel_data\\STU\\MoM131_LBX\\MAIN.LBX";
int TEST_ENTRY_INDEX = 0;
char TARGET_DIRECTORY_PATH[] = "F:\\devel_data\\STU\\MoM131_LBX\\";
char TARGET_FILE_PATH[] = "F:\\devel_data\\STU\\MoM131_LBX\\MAIN.LBX";
char TARGET_FILE_NAME[] = "MAIN.LBX";
char TARGET_FILE_NAME_BASE[] = "MAIN";
unsigned int TARGET_ENTRY_INDEX = 0;

// int row_count = 3;
// int column_count = 5;
//
//int redirected_index(int idx_1d, int columns, int col_idx, int rows)
//{
//    return (3 * idx_1d) % (15) + col_idx;
//}
//
//
//void test_hurubon_modular_arithmetic()
//{
//    int source[3][5] = {
//            0, 3, 6,  9, 12,
//            1, 4, 7, 10, 13,
//            2, 5, 8, 11, 14
//    };
//    int destination[3][5];
//    int* src_ptr = &source[0][0];
//    int* dest_ptr = &destination[0][0];
//
//    for (int i = 0; i < 5; ++i)
//    {
//        for (int j = 0; j < 3; ++j)
//        {
//            int const index = redirected_index(j * 5 + i, 5, j, 3);
//            printf("r(%d) = %d\n", source[j][i], index);
//            dest_ptr[index] = source[j][i];
//        }
//    }
//
//    for (int i = 0; i < 3; ++i)
//    {
//        for (int j = 0; j < 5; ++j)
//            printf("%d ", destination[i][j]);
//        puts("");
//    }
//
//}




//void test_scratch()
//{
//    LBX_DATA * lbx;
//
//    lbx->header->entry_count = 0x01;
//    lbx->header->magic = 0xFEAD;
//    lbx->header->unknown = 0x00;
//    lbx->header->type = 0x00;
//
//    char * frame_data_decoded;
//    frame_data_decoded = malloc(64000);
//
//    char * frame_data_encoded;
//    frame_data_encoded = malloc(12275);
//    char * ptr_frame_data_encoded;
//    ptr_frame_data_encoded = frame_data_encoded;
//    *ptr_frame_data_encoded = 0x01;
//    ptr_frame_data_encoded++;
//    *ptr_frame_data_encoded = 0x80;
//    ptr_frame_data_encoded++;
//    *ptr_frame_data_encoded = 0x0B;
//    ptr_frame_data_encoded++;
//    *ptr_frame_data_encoded = 0x09;
//    ptr_frame_data_encoded++;
//    *ptr_frame_data_encoded = 0x00;
//
//    frame_data_encoded[0] = 0x01;
//    frame_data_encoded[1] = 0x80;
//    frame_data_encoded[2] = 0x0B;
//    frame_data_encoded[3] = 0x09;
//    frame_data_encoded[4] = 0x00;
//
//    frame_data_encoded[12275] = 0xBB;
//
//
//    int bad_baito;
//    bad_baito = 0x80;
//    char good_baito;
//    good_baito = *(char *)&bad_baito;
//    char AL_baito;
//    AL_baito = (bad_baito & 0xFF);
//    char mc_baito;
//    memcpy(&mc_baito, (char *)&bad_baito, 1);
//    char mc_baito_3;
//    memcpy(&mc_baito_3, (char *)&bad_baito + 3, 1);
//    char mc_baito_2;
//    memcpy(&mc_baito_2, (char *)&bad_baito + 2, 1);
//    char mc_baito_1;
//    memcpy(&mc_baito_1, (char *)&bad_baito + 1, 1);
//    char mc_baito_0;
//    memcpy(&mc_baito_0, (char *)&bad_baito + 0, 1);
//    char id_baito;
//    id_baito = (char) bad_baito;
//    printf("bad_baito: %d\n", bad_baito);
//    printf("good_baito: %d\n", good_baito);
//    printf("AL_baito: %d\n", AL_baito);
//    printf("mc_baito: %d\n", mc_baito);
//    printf("mc_baito_3: %d\n", mc_baito_3);
//    printf("mc_baito_2: %d\n", mc_baito_2);
//    printf("mc_baito_1: %d\n", mc_baito_1);
//    printf("mc_baito_0: %d\n", mc_baito_0);
//    printf("id_baito: %d\n", id_baito);
//
//    exit(EXIT_SUCCESS);
//
//
//    liblbx_decompress_flic_rle_record_data(lbx);
//
//}

void test_print_array()
{
    unsigned int row_count;
    unsigned int column_count;
    unsigned int element_count;
    unsigned char * array_buffer;

    row_count = 8;
    column_count = 5;
    element_count = column_count * row_count;

    array_buffer = (unsigned char *)malloc(element_count);
    memcpy(array_buffer, test_array_pixels_onscreen, sizeof(test_array_pixels_onscreen));
    print_array(array_buffer, element_count);

    print_array(array_buffer, element_count);

}

void test_test_print_arrays_orders()
{
    // test_print_arrays_orders();
    unsigned int row_count;
    unsigned int column_count;
    unsigned int element_count;

    unsigned char * array_tlo_rmo;
    unsigned char * array_tlo_cmo;
    unsigned char * array_blo_rmo;
    unsigned char * array_blo_cmo;

    row_count = 5;
    column_count = 8;
    element_count = column_count * row_count;

    array_tlo_rmo = malloc(element_count);
    array_tlo_cmo = malloc(element_count);
    array_blo_rmo = malloc(element_count);
    array_blo_cmo = malloc(element_count);

    // print_array_in_row_major_order(array_tlo_rmo, row_count, column_count);
    // print_array_in_column_major_order(array_tlo_rmo, row_count, column_count);

//    print_array(test_array_pixels_onscreen, element_count);
//    print_matrix_with_box(test_array_pixels_onscreen, row_count, column_count);
//    print_array_with_matrix_indices(test_array_pixels_onscreen, element_count, row_count, column_count);

//    /* Top-Left Origin, Row-Major-Order */
//    /*  */
//    memcpy(array_tlo_rmo, test_array_pixels_onscreen, sizeof(test_array_pixels_onscreen));
//    print_array(array_tlo_rmo, element_count);
//    printf("\n");
//    printf("Top-Left Origin, Row-Major-Order\n");
//    print_matrix_with_box(array_tlo_rmo, row_count, column_count);
//    printf("\n");
//
//    /* Top-Left Origin, Column-Major-Order */
//    /*  */
//    // array_tlo_cmo = copy_array_to_tlo_cmo_from_array_tlo_rmo(array_tlo_rmo, row_count, column_count);
//    array_tlo_cmo = alloc_transpose(array_tlo_rmo, row_count, column_count);
//    print_array(array_tlo_cmo, element_count);
//    printf("\n");
//    printf("Top-Left Origin, Column-Major-Order\n");
//    print_matrix_with_box(array_tlo_cmo, column_count, row_count);
//    printf("\n");

//    unsigned char * flipped_array_tlo_rmo;
//    flipped_array_tlo_rmo = malloc(element_count);
//    memcpy(flipped_array_tlo_rmo, test_array_pixels_onscreen, sizeof(test_array_pixels_onscreen));
//    flip_array_horizontal(&flipped_array_tlo_rmo, row_count, column_count);
//    print_array(flipped_array_tlo_rmo, element_count);
//    printf("\n");
//    printf("Flipped - Top-Left Origin, Row-Major-Order\n");
//    print_matrix_with_box(flipped_array_tlo_rmo, row_count, column_count);
//    printf("\n");

    unsigned char * flic_test_fake;
    flic_test_fake = malloc(element_count);
    memcpy(flic_test_fake, flic_array_test_fake, sizeof(test_array_pixels_onscreen));
    printf("\n");
    printf("FLIC Test Fake\n");
    print_matrix_with_box(flic_test_fake, column_count, row_count);
    printf("\n");

    unsigned char * transposed_flic_test_fake;
    transposed_flic_test_fake = malloc(element_count);
    transpose(transposed_flic_test_fake, flic_test_fake, column_count, row_count);
    print_array(transposed_flic_test_fake, element_count);
    printf("\n");
    printf("Transposed - FLIC Test Fake\n");
    print_matrix_with_box(transposed_flic_test_fake, row_count, column_count);
    printf("\n");

    unsigned char * flipped_transposed_flic_test_fake;
    flipped_transposed_flic_test_fake = malloc(element_count);
    flipH(flipped_transposed_flic_test_fake, transposed_flic_test_fake, row_count, column_count);
    print_array(flipped_transposed_flic_test_fake, element_count);
    printf("\n");
    printf("Flipped, Transposed - FLIC Test Fake\n");
    print_matrix_with_box(flipped_transposed_flic_test_fake, row_count, column_count);
    printf("\n");


    /* Bottom-Left Origin, Row-Major-Order */
    /*  */
    /*array_blo_rmo = to_array_blo_rmo_from_array_tlo_rmo(array_tlo_cmo, row_count, column_count);*/

    /* Bottom-Left Origin, Column-Major-Order */
    /*  */
    /*array_blo_cmo = to_array_blo_cmo_from_array_tlo_rmo(array_tlo_cmo, row_count, column_count);*/


    // test_matrix_8x5_pixels_onscreen


}

void test_export_MAIN000_FF0_BMP()
{
    printf("LBX_DEBUG_MODE: %u\n", LBX_DEBUG_MODE);
    printf("LBX_DEBUG_VERBOSE_MODE: %u\n", LBX_DEBUG_VERBOSE_MODE);
    printf("LBX_DEBUG_STRUGGLE_MODE: %u\n", LBX_DEBUG_STRUGGLE_MODE);

    // char * test_lbx_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\FONTS.LBX";
    char * test_lbx_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\MAIN.LBX";

    LBX_DATA * lbx;

    lbx = create_lbx_data(test_lbx_file_path);

    /*
     * liblbx_process_lbx_file(lbx);
     * */
    liblbx_directory_path_and_file_name(lbx);
    liblbx_file_name_base(lbx);
    liblbx_load_lbx_file_header_from_lbx_data_file_handle(lbx);
    liblbx_populate_lbx_record_file_name_base(lbx);
    /*liblbx_display_lbx_record_file_name_base(lbx);*/
    liblbx_load_lbx_record_data(lbx);
    liblbx_populate_lbx_record_type(lbx);
    /*liblbx_display_lbx_record_type(lbx);*/
    liblbx_load_lbx_record_headers(lbx);
    /*liblbx_display_lbx_record_headers_long(lbx);*/
    /*liblbx_display_lbx_record_headers_wide(lbx);*/
    liblbx_load_lbx_record_flic_frame_data(lbx);
    /*liblbx_display_lbx_record_headers_long(lbx);*/
    /*liblbx_display_lbx_flic_frame_header();*/

    liblbx_decompress_flic_rle_record_data(lbx);

    BMP_FILE * bmp;
    bmp = malloc(sizeof(BMP_FILE));
//    // liblbx_convert_flic_frame_to_bmp(bmp, lbx);
//    /* 0: MAIN000, MAINSCRN - main screen, 320x200, 1 frame; 1: MAIN001, MAINBUTN - game button, 39x12, 2 frames */
    // liblbx_convert_flic_frame_to_bmp(bmp, lbx, 0, 0);
    LBX_DEBUG_MODE = 1;
    LBX_DEBUG_VERBOSE_MODE = 1;
    LBX_DEBUG_STRUGGLE_MODE = 1;


    liblbx_convert_flic_frame_to_bmp(bmp, lbx, 0, 0, EMPERATO);

}

void test_lbx()
{
    printf("LBX_DEBUG_MODE: %u\n", LBX_DEBUG_MODE);
    printf("LBX_DEBUG_VERBOSE_MODE: %u\n", LBX_DEBUG_VERBOSE_MODE);
    printf("LBX_DEBUG_STRUGGLE_MODE: %u\n", LBX_DEBUG_STRUGGLE_MODE);

    // char * test_lbx_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\FONTS.LBX";
    char * test_lbx_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\MAIN.LBX";

    LBX_DATA * lbx;

    lbx = create_lbx_data(test_lbx_file_path);

    /*
     * liblbx_process_lbx_file(lbx);
     * */
    liblbx_directory_path_and_file_name(lbx);
    liblbx_file_name_base(lbx);
    liblbx_load_lbx_file_header_from_lbx_data_file_handle(lbx);
    liblbx_populate_lbx_record_file_name_base(lbx);
    /*liblbx_display_lbx_record_file_name_base(lbx);*/
    liblbx_load_lbx_record_data(lbx);
    liblbx_populate_lbx_record_type(lbx);
    /*liblbx_display_lbx_record_type(lbx);*/
    liblbx_load_lbx_record_headers(lbx);
    /*liblbx_display_lbx_record_headers_long(lbx);*/
    /*liblbx_display_lbx_record_headers_wide(lbx);*/
    liblbx_load_lbx_record_flic_frame_data(lbx);
    /*liblbx_display_lbx_record_headers_long(lbx);*/
    /*liblbx_display_lbx_flic_frame_header();*/

    liblbx_decompress_flic_rle_record_data(lbx);

    BMP_FILE * bmp;
    bmp = malloc(sizeof(BMP_FILE));
//    // liblbx_convert_flic_frame_to_bmp(bmp, lbx);
//    /* 0: MAIN000, MAINSCRN - main screen, 320x200, 1 frame; 1: MAIN001, MAINBUTN - game button, 39x12, 2 frames */
    // liblbx_convert_flic_frame_to_bmp(bmp, lbx, 0, 0);
    LBX_DEBUG_MODE = 1;
    LBX_DEBUG_VERBOSE_MODE = 1;
    LBX_DEBUG_STRUGGLE_MODE = 1;


    liblbx_convert_flic_frame_to_bmp(bmp, lbx, 1, 0, EMPERATO);


//    liblbx_populate_lbx_meta_data(lbx);
//    /*
//        populate_lbx_header_meta_data(lbx);
//        populate_lbx_file_meta_data(lbx);
//        populate_lbx_info_meta_data(lbx);
//        populate_lbx_record_meta_data(lbx);
//    */

//    /*display_lbx_meta_data(lbx);*/
//    /*
//        ? populate_lbx_header_meta_data(lbx);
//        display_lbx_file_meta_data(lbx);
//        ? populate_lbx_info_meta_data(lbx);
//        display_lbx_record_meta_data(lbx);
//    */

//    unsigned int itr_entry_index;
//    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
//    {
//        printf("%s %03u (%d of %d) [%s]\n", lbx->file->file_name_base, itr_entry_index, itr_entry_index + 1, lbx->meta->entry_count, lbx->meta->records->entry[itr_entry_index].entry_name);
//        /*display_lbx_flic_header(lbx, itr_entry_index);*/
//        /*display_lbx_image_custom_palette_header(lbx, itr_entry_index);*/
//    }

//    if (LBXMGR_OUTPUT_CSV == 1)
//    {
//        // EXPORT/MAIN/CSV/MAIN.CSV
//        lbxmgr_output_to_csv(lbxmgr_data->lbx_data_array[itr_filenames]);
//        // EXPORT/LBX_FILE_INFO.CSV
//        lbxmgr_output_csv_lbx_files(lbxmgr_data);
//        // EXPORT/LBX_RECORD_INFO.CSV
//        lbxmgr_output_csv_lbx_records(lbxmgr_data);
//    }

//    if (LBX_EXPORT_BIN == 1)
//    {
//        lbxmgr_export_records_to_bin(lbx);
//    }

//    if (LBX_EXPORT_BMP == 1)
//    {
//        // lbxmgr_export_records_to_bmp(lbx);
//    }


}


/* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\STDTYPES.H */
typedef unsigned char	PJ_UBYTE;
typedef signed long 	PJ_LONG;
/* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\CMAP.H */
#define PJ_COLORS 256
#define PJ_RGB_MAX 256
typedef struct PJ_rgb3 {
    PJ_UBYTE r,g,b;
} PJ_Rgb3;

typedef struct PJ_colormap {
    PJ_LONG num_colors;
    PJ_Rgb3 ctab[PJ_COLORS];
} PJ_Cmap;

/* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\PJHIGH\COLLOAD.C */
#define OLD_SIZE (3*COLORS)

void test_load_lbx_palette()
{

    /* lbx_record_type_palette.h enum mom_palette_number */
    unsigned char * lbx_palette_record;
    lbx_palette_record = liblbx_load_palette_record(g_palette_file_path, EMPERATO);

    unsigned char * lbx_palette;
    lbx_palette = liblbx_load_palette(g_palette_file_path, EMPERATO);


    unsigned int itr_lbx_palette;

    for (itr_lbx_palette = 0; itr_lbx_palette < 32; itr_lbx_palette++)
    {
        printf("[%u] %u (0x%02X)\n", itr_lbx_palette, lbx_palette[itr_lbx_palette], lbx_palette[itr_lbx_palette]);
    }

    int itr_lbx_palette_number;
    char * export_palette_file_path_base;

    for (itr_lbx_palette_number = 1; itr_lbx_palette_number <= 7; itr_lbx_palette_number++)
    {
        export_palette_file_path_base = malloc(MAX_PATH);
        strcpy(export_palette_file_path_base, "F:");
        strcat(export_palette_file_path_base, "\\");
        strcat(export_palette_file_path_base, "devel_data\\STU\\MoM131_LBX");
        strcat(export_palette_file_path_base, "\\");
        strcat(export_palette_file_path_base, "EXPORT");
        strcat(export_palette_file_path_base, "\\");
        strcat(export_palette_file_path_base, mom_palette_name[itr_lbx_palette_number]);
        printf("export_palette_file_path_base: %s\n", export_palette_file_path_base);
        printf("Palette: %d %s\n", itr_lbx_palette_number, mom_palette_name[itr_lbx_palette_number]);
        liblbx_export_palette(g_palette_file_path, itr_lbx_palette_number, export_palette_file_path_base);
    }


}

void test()
{

}


int main()
{
    printf("\n");
    printf("\n");
    printf("Beginning Testing...\n");
    printf("\n");
    printf("\n");
    printf("\n");

    LBX_DEBUG_MODE = 1;
    LBX_DEBUG_VERBOSE_MODE = 1;
    LBX_DEBUG_STRUGGLE_MODE = 1;

//    // test();
//    // test_print_array();
//    test_test_print_arrays_orders();
//
//    // test_hurubon_modular_arithmetic();

    // test_lbx();

    // test_load_lbx_palette();

    test_export_MAIN000_FF0_BMP();


    printf("\n");
    printf("\n");
    printf("\n");
    printf("Ending Testing...\n");
    printf("\n");
    printf("\n");
    return 0;
}
