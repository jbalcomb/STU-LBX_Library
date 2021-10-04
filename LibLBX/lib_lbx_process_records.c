#include <malloc.h>         /* malloc(), realloc(); */
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */

#include "lib_lbx_process_records.h"
#include "lib_lbx_record_type.h"
/*#include "lbx_record_type_flic.h"*/
#include "lib_lbx_record.h"


// 2021-10-04 10:54
// Commenting out everything that should have been in Graphics/FLIC/BMP/Palette/Font
//void liblbx_load_lbx_record_headers(LBX_DATA * lbx)
//{
//    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_record_headers()\n");
//
//    int itr_entry_index;
//    int itr_lbx_flic_frame_offset_table;
//
//    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++) {
//
//        if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: itr_entry_index: %d\n", itr_entry_index);
//
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));
//        lbx->record->entry[itr_entry_index].headers = malloc(sizeof(LBX_RECORD_HEADER));
//        if (lbx->record->entry[itr_entry_index].headers == NULL) {
//            printf("FAILURE: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));
//            exit(EXIT_FAILURE);
//        }
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));
//
//
//        /* void liblbx_load_lbx_record_header_flic(LBX_DATA * lbx) */
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers->flic = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_RECORD_HEADER));
//        lbx->record->entry[itr_entry_index].headers->flic = malloc(sizeof(LBX_FLIC_RECORD_HEADER));
//        if (lbx->record->entry[itr_entry_index].headers->flic == NULL) {
//            printf("FAILURE: lbx->record->entry[%d].headers->flic = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_RECORD_HEADER));
//            exit(EXIT_FAILURE);
//        }
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers->flic = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_RECORD_HEADER));
//
//
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers->flic->lbx_flic_info_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_INFO_HEADER));
//        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));
//        if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header == NULL)
//        {
//            printf("FAILURE: lbx->record->entry[%d].headers->flic->lbx_flic_info_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_INFO_HEADER));
//            exit(EXIT_FAILURE);
//        }
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers->flic->lbx_flic_info_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_INFO_HEADER));
//
//
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers->flic->lbx_flic_palette_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_PALETTE_HEADER));
//        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header = malloc(sizeof(LBX_FLIC_PALETTE_HEADER));
//        if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header == NULL)
//        {
//            printf("FAILURE: lbx->record->entry[%d].headers->flic->lbx_flic_palette_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_PALETTE_HEADER));
//            exit(EXIT_FAILURE);
//        }
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers->flic->lbx_flic_palette_header = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_PALETTE_HEADER));
//
//
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers->flic->lbx_flic_frame_offset_table = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAME_OFFSET_TABLE));
//        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table = malloc(sizeof(LBX_FLIC_FRAME_OFFSET_TABLE));
//        if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table == NULL)
//        {
//            printf("FAILURE: lbx->record->entry[%d].headers->flic->lbx_flic_frame_offset_table = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAME_OFFSET_TABLE));
//            exit(EXIT_FAILURE);
//        }
//        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers->flic->lbx_flic_frame_offset_table = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAME_OFFSET_TABLE));
//
//        /* TODO(JWB): extract this to a stand-alone function */
//        if (lbx->record->entry[itr_entry_index].type == LBX_RECORD_TYPE_EMPTY)
//        {
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: LBX_RECORD_TYPE_EMPTY\n");
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_offset = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_index = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_count = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[0].begin = 0;
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[1].begin = 0;
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: LBX_RECORD_TYPE_EMPTY\n");
//        }
//        else
//        {
//
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));\n");
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));
//            if (lbx->record->entry[itr_entry_index].headers->flic == NULL)
//            {
//                printf("FAILURE: lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header = malloc(%u);\n", sizeof(LBX_FLIC_INFO_HEADER));
//                exit(EXIT_FAILURE);
//            }
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));\n");
//
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[0];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[2];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[4];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[6];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[8];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[10];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[11];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[12];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[14];
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[16];
//
//
//            if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset == 0) {
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_offset = 0;
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_index = 0;
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_count = 0;
//            }
//            else
//            {
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_offset = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset + 0];
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_index = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset + 2];
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_count = *(lbx_uint16*)&lbx->record->entry[itr_entry_index].record_buffer[lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset + 4];
//            }
//
//            for (itr_lbx_flic_frame_offset_table = 0; itr_lbx_flic_frame_offset_table < lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count + 1; itr_lbx_flic_frame_offset_table++)
//            {
//                lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_lbx_flic_frame_offset_table].begin = *(lbx_uint32*)&lbx->record->entry[itr_entry_index].record_buffer[18 + (itr_lbx_flic_frame_offset_table * sizeof(lbx_uint32))];
//            }
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: SUCCESS: FRAME DATA LOADED\n");
//            lbx->record->entry[itr_entry_index].headers->have_loaded_flic_header = 1;
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[itr_entry_index].headers->have_loaded_flic_header: %u\n", lbx->record->entry[itr_entry_index].headers->have_loaded_flic_header);
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width: %u\n", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width);
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height: %u\n", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
//
//        }
//
//    }
//
//    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_record_headers()\n");
//}

void liblbx_load_lbx_record_headers(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_record_headers()\n");

    int itr_entry_index;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++) {

        if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: itr_entry_index: %d\n", itr_entry_index);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));
        lbx->record->entry[itr_entry_index].headers = malloc(sizeof(LBX_RECORD_HEADER));
        if (lbx->record->entry[itr_entry_index].headers == NULL) {
            printf("FAILURE: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].headers = malloc(%u);\n", itr_entry_index, sizeof(LBX_RECORD_HEADER));

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_record_headers()\n");
}

/*!
 * Calculate Record Size, Read Record, Deduce Record Type, Build Record File Name Base
 * @param lbx
 */
void liblbx_process_lbx_records(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_process_lbx_records()\n");

    int itr_entry_index;


    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {

        /*
         * Record Size
         */

        lbx->record->entry[itr_entry_index].size = (lbx->header->offset_table->entry[itr_entry_index + 1].begin - lbx->header->offset_table->entry[itr_entry_index].begin);


        /*
         * Record Data
         */

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%d].record_buffer = malloc(%u);\n", itr_entry_index, lbx->record->entry[itr_entry_index].size);
        lbx->record->entry[itr_entry_index].record_buffer = malloc(lbx->record->entry[itr_entry_index].size);
        if (lbx->record->entry[itr_entry_index].record_buffer == NULL)
        {
            printf("FAILURE: lbx->record->entry[%d].record_buffer = malloc(%u);\n", itr_entry_index, lbx->record->entry[itr_entry_index].size);
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%d].record_buffer = malloc(%u);\n", itr_entry_index, lbx->record->entry[itr_entry_index].size);

        fseek(lbx->file->file_stream, lbx->header->offset_table->entry[itr_entry_index].begin, SEEK_SET);

        fread(lbx->record->entry[itr_entry_index].record_buffer, 1, lbx->record->entry[itr_entry_index].size, lbx->file->file_stream);

        /*
         * Record Type
         */

        lbx->record->entry[itr_entry_index].type = liblbx_deduce_lbx_record_type(lbx, lbx->record->entry[itr_entry_index].record_buffer, lbx->record->entry[itr_entry_index].size, lbx->file->file_name, itr_entry_index);

        /*
         * Record Type - Header
         */
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].headers = malloc(sizeof(LBX_RECORD_HEADER));\n");
        lbx->record->entry[itr_entry_index].headers = malloc(sizeof(LBX_RECORD_HEADER));
        if (lbx->record->entry[itr_entry_index].headers == NULL)
        {
            printf("FAILURE: lbx->record->entry[itr_entry_index].headers = malloc(%u);\n", sizeof(LBX_RECORD_HEADER));
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].headers = malloc(sizeof(LBX_RECORD_HEADER));\n");

        /*
         * Record Type - Header - FLIC
         */

// 2021-10-04 10:54
// Commenting out everything that should have been in Graphics/FLIC/BMP/Palette/Font
//        /* if (lbx->record->entry[itr_entry_index].type == LBX_RECORD_TYPE_IMAGE) */
//        if (lbx->record->entry[itr_entry_index].type == LBX_RECORD_TYPE_FLIC)
//        {
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].record_buffer = malloc(lbx->record->entry[itr_entry_index].size);\n");
//            lbx->record->entry[itr_entry_index].headers->flic = malloc(sizeof(LBX_FLIC_RECORD_HEADER));
//            if (lbx->record->entry[itr_entry_index].headers->flic == NULL)
//            {
//                printf("FAILURE: lbx->record->entry[itr_entry_index].record_buffer = malloc(%u);\n", lbx->record->entry[itr_entry_index].size);
//                exit(EXIT_FAILURE);
//            }
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].record_buffer = malloc(lbx->record->entry[itr_entry_index].size);\n");
//        }


    }


    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_process_lbx_records()\n");
}

void process_lbx_record(char * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: process_lbx_record()\n");



    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: process_lbx_record()\n");
}
