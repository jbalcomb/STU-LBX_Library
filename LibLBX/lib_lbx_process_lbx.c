#include <malloc.h>         /* malloc(), realloc(); */

#include "lib_lbx_process_lbx.h"
#include "lib_lbx.h"  /* LBX_DATA LBX_EXPORT_BMP */
#include "lib_lbx_load_header.h"
#include "lib_lbx_meta_data.h"
#include "lib_lbx_util.h"
#include "lib_lbx_process_records.h"
#include "lib_lbx_record.h"
#include "lib_lbx_record_type.h"        /* get_record_type(); */
#include "lib_lbx_load_records.h"
#include "lib_lbx_record_display.h"     /* liblbx_display_lbx_record_file_name_base(); */
#include "lib_lbx_record_flic.h"
#include "lib_lbx_file_type_bmp.h"

/*
 * /Process/ /LBX/
 * /Process/, as in ? Read, Load, Prepare EVERYTHING ?
 * /LBX/, as in 'LBX File' <-> 'LBX Structure'
 *
 * Load Header - Preamble, Offset Table, and String Table
 * ...
 * Load Record Data
 * ...
 * Deduce Record Type
 * ...
 * Populate Meta-Data
 *
 */
void liblbx_process_lbx_file(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: liblbx_process_lbx_file()\n");

    /*
        LBX_DATA * tmp_lbx_data;
        tmp_lbx_data = liblbx_create_lbx_data(TEST_FILE_PATH);
        ...
        liblbx_open_file(lbx);

        liblbx_load_header(lbx);
        liblbx_load_record_data(lbx);

        liblbx_close_file(lbx);

        liblbx_destroy_lbx_data(lbx);
    */

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



//    liblbx_load_lbx_record_flic_frame_data(lbx);
//    liblbx_display_lbx_record_headers_long(lbx);
//    /*liblbx_display_lbx_flic_frame_header();*/
//
//    /* if frame_type = 1 */
//
//    /*
//     * lbx->record->entry[0].headers->flic->lbx_flic_frames->frame[0].frame_data;
//     */
//    liblbx_decompress_flic_rle_record_data(lbx);
//    /*
//     * Convert to BMP
//     */
//    if (LBX_EXPORT_BMP == 1)
//    {
//        BMP_FILE * bmp;
//        bmp = malloc(sizeof(BMP_FILE));
//        // liblbx_convert_flic_frame_to_bmp(bmp, lbx);
//        /* 0: MAIN000, MAINSCRN - main screen, 320x200, 1 frame; 1: MAIN001, MAINBUTN - game button, 39x12, 2 frames */
//        liblbx_convert_flic_frame_to_bmp(bmp, lbx, 0, 0);
//        liblbx_convert_flic_frame_to_bmp(bmp, lbx, 1, 0);
//    }
//


    liblbx_populate_lbx_meta_data(lbx);
    /*
        populate_lbx_header_meta_data(lbx);
        populate_lbx_file_meta_data(lbx);
        populate_lbx_info_meta_data(lbx);
        populate_lbx_record_meta_data(lbx);
    */


    if (LBX_DEBUG_MODE) printf("DEBUG: END: liblbx_process_lbx_file()\n");
}