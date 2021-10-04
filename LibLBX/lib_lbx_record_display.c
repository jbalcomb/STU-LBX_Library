#include <malloc.h>         /* malloc(), realloc(); */
#include <stdio.h>
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */

#include "lib_lbx_record_display.h"     /* liblbx_display_lbx_record_file_name_base(); */
#include "lbx_record_type_flic.h"
#include "lib_lbx.h"
#include "lib_lbx_record_image.h"
#include "lbx_record_type_flic.h"
#include "lib_lbx_record_type.h"

void liblbx_display_lbx_record_file_name_base(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_display_lbx_record_file_name_base()\n");

    int itr_entry_index;
    lbx_uint16 tmp_entry_index;
    int tmp_len_entry_number_string;
    char * tmp_entry_index_string;

    printf("++%13s=%18s=%11s=%21s++\n", "=============", "==================", "===========", "=====================");
    printf("||%-13s|%-18s|%-11s|%-21s||\n", "LBX File Name", "LBX File Name Base", "Entry Index", "Record File Name Base");
    printf("++%13s-%18s-%11s-%21s++\n", "-------------", "------------------", "-----------", "---------------------");
    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        tmp_entry_index = itr_entry_index;
        tmp_len_entry_number_string = snprintf( NULL, 0, "%d", tmp_entry_index);
        tmp_entry_index_string = malloc(tmp_len_entry_number_string + 1);
        snprintf(tmp_entry_index_string, tmp_len_entry_number_string + 1, "%d", tmp_entry_index);

        printf("||%-13s|%-18s|%11s|%-21s||\n", lbx->file->file_name, lbx->file->file_name_base, tmp_entry_index_string, lbx->record->entry[itr_entry_index].record_file_name_base);
    }
    printf("++%13s=%18s=%11s=%21s++\n", "=============", "==================", "===========", "=====================");

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_display_lbx_record_file_name_base()\n");
}

void liblbx_display_lbx_record_type(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_display_lbx_record_file_name_base()\n");

    int itr_entry_index;

    int tmp_len_entry_number_string;
    char * tmp_entry_index_string;
    int tmp_len_record_type_string;
    char * tmp_record_type_string;
    int tmp_len_record_type_description_string;
    char * tmp_record_type_description_string;

    printf("++%13s=%11s=%11s=%23s++\n", "=============", "===========", "===========", "=======================");
    printf("||%-13s|%-11s|%-11s|%-23s||\n", "LBX File Name", "Entry Index", "Record Type", "Record Type Description");
    printf("++%13s-%11s-%11s-%23s++\n", "-------------", "-----------", "-----------", "-----------------------");
    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        tmp_len_entry_number_string = snprintf( NULL, 0, "%d", itr_entry_index);
        tmp_entry_index_string = malloc(tmp_len_entry_number_string + 1);
        snprintf(tmp_entry_index_string, tmp_len_entry_number_string + 1, "%d", itr_entry_index);

        tmp_len_record_type_string = snprintf(NULL, 0, "%d", lbx->record->entry[itr_entry_index].type);
        tmp_record_type_string = malloc(tmp_len_record_type_string + 1);
        snprintf(tmp_record_type_string, tmp_len_record_type_string + 1, "%d", lbx->record->entry[itr_entry_index].type);

        tmp_len_record_type_description_string = snprintf(NULL, 0, "%s", LBX_Record_Type_Description[lbx->record->entry[itr_entry_index].type]);
        tmp_record_type_description_string = malloc(sizeof(char) * (tmp_len_record_type_description_string + 1));
        snprintf(tmp_record_type_description_string, tmp_len_record_type_description_string + 1, "%s", LBX_Record_Type_Description[lbx->record->entry[itr_entry_index].type]);

        printf("||%-13s|%11s|%11s|%-23s||\n", lbx->file->file_name, tmp_entry_index_string, tmp_record_type_string, tmp_record_type_description_string);
    }
    printf("++%13s=%11s=%11s=%23s++\n", "=============", "===========", "===========", "=======================");

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_display_lbx_record_file_name_base()\n");
}

void liblbx_display_lbx_record_headers_long(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_display_lbx_record_headers_long()\n");

    int itr_entry_index;
    int itr_lbx_flic_frame_offset_table;
    int itr_frame_index;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        int len_width = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
        char * str_width = malloc(len_width + 1);
        snprintf(str_width, len_width + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width);

        int len_height = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
        char * str_height = malloc(len_height + 1);
        snprintf(str_height, len_height + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);

        int len_compression = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame);
        char * str_compression = malloc(len_compression + 1);
        snprintf(str_compression, len_compression + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame);

        int len_frame_count = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count);
        char * str_frame_count = malloc(len_frame_count + 1);
        snprintf(str_frame_count, len_frame_count + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count);

        int len_frame_delay = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame);
        char * str_frame_delay = malloc(len_frame_delay + 1);
        snprintf(str_frame_delay, len_frame_delay + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame);

        int len_flags1 = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle);
        char * str_flags1 = malloc(len_flags1 + 1);
        snprintf(str_flags1, len_flags1 + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle);

        int len_flags2 = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page);
        char * str_flags2 = malloc(len_flags2 + 1);
        snprintf(str_flags2, len_flags2 + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page);

        int len_reserved = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset);
        char * str_reserved = malloc(len_reserved + 1);
        snprintf(str_reserved, len_reserved + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset);

        int len_palette_info_offset = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset);
        char * str_palette_info_offset = malloc(len_palette_info_offset + 1);
        snprintf(str_palette_info_offset, len_palette_info_offset + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset);

        int len_unknown = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown);
        char * str_unknown = malloc(len_unknown + 1);
        snprintf(str_unknown, len_unknown + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown);

        printf("++%19s=%6s=%6s++\n", "===================", "======", "======");
        printf("||%-19s|%6s|%6s||\n", "Field", "Dec", "Hex");
        printf("||%19s|%6s|%6s||\n", "-------------------", "------", "------");
        printf("||%-19s|%6u|%6s||\n", "frame_width", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width, str_width);
        printf("||%-19s|%6u|%6s||\n", "frame_height", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height, str_height);
        printf("||%-19s|%6u|%6s||\n", "current_frame", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame, str_compression);
        printf("||%-19s|%6u|%6s||\n", "frame_count", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count, str_frame_count);
        printf("||%-19s|%6u|%6s||\n", "loop_frame", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame, str_frame_delay);
        printf("||%-19s|%6u|%6s||\n", "emm_handle", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle, str_flags1);
        printf("||%-19s|%6u|%6s||\n", "emm_logical_page", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page, str_flags2);
        printf("||%-19s|%6u|%6s||\n", "emm_data_offset", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset, str_reserved);
        printf("||%-19s|%6u|%6s||\n", "palette_info_offset", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset, str_palette_info_offset);
        printf("||%-19s|%6u|%6s||\n", "unknown", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown, str_unknown);
        printf("++%19s=%6s=%6s++\n", "===================", "======", "======");


        for (itr_lbx_flic_frame_offset_table = 0; itr_lbx_flic_frame_offset_table < lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count + 1; itr_lbx_flic_frame_offset_table++)
        {
            printf("LBX: %s entry_index[%d]: frame_offset_table[%d]: %u\n", lbx->file->file_name, itr_entry_index, itr_lbx_flic_frame_offset_table, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_lbx_flic_frame_offset_table].begin);
        }

        for (itr_frame_index = 0; itr_frame_index < lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count; itr_frame_index++)
        {
            printf("LBX: %s entry_index[%d]: frame_index[%d]: frame_data_size: %u (0x%02X)\n", lbx->file->file_name, itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data_size);
            printf("LBX: %s entry_index[%d]: frame_index[%d]: frame_type: %u (0x%02X)\n", lbx->file->file_name, itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type);
        }

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_display_lbx_record_headers_long()\n");
}

void liblbx_display_lbx_record_headers_wide(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_display_lbx_record_headers_long()\n");

    int itr_entry_index;

    int tmp_len_entry_number_string;
    char * tmp_entry_index_string;
    int tmp_len_record_type_description_string;
    char * tmp_record_type_description_string;

    printf("++%-12s=%-5s=%-13s=%11s=%12s=%13s=%11s=%10s=%10s=%16s=%15s=%19s=%7s=%14s=%19s=%19s=%18s++\n", "============", "=====", "=============", "===========", "============", "=============", "===========", "==========", "==========", "================", "===============", "===================", "=======", "==============", "===================", "===================", "==================");
    printf("||%-12s|%-5s|%-13s|%11s|%12s|%13s|%11s|%10s|%10s|%16s|%15s|%19s|%7s|%14s|%19s|%19s|%18s||\n", "File", "Entry", "Type", "frame_width", "frame_height", "current_frame", "frame_count", "loop_frame", "emm_handle", "emm_logical_page", "emm_data_offset", "palette_info_offset", "unknown", "palette_offset", "palette_color_index", "palette_color_count", "first_frame_offset");
    printf("++%-12s-%-5s-%-13s-%11s-%12s-%13s-%11s-%10s-%10s-%16s-%15s-%19s-%7s-%14s-%19s-%19s-%18s++\n", "------------", "-----", "-------------", "-----------", "------------", "-------------", "-----------", "----------", "----------", "----------------", "---------------", "-------------------", "-------", "--------------", "-------------------", "-------------------", "------------------");


    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {

        tmp_len_entry_number_string = snprintf( NULL, 0, "%d", itr_entry_index);
        tmp_entry_index_string = malloc(tmp_len_entry_number_string + 1);
        snprintf(tmp_entry_index_string, tmp_len_entry_number_string + 1, "%d", itr_entry_index);

        tmp_len_record_type_description_string = snprintf(NULL, 0, "%s", LBX_Record_Type_Description[lbx->record->entry[itr_entry_index].type]);
        tmp_record_type_description_string = malloc(sizeof(char) * (tmp_len_record_type_description_string + 1));
        snprintf(tmp_record_type_description_string, tmp_len_record_type_description_string + 1, "%s", LBX_Record_Type_Description[lbx->record->entry[itr_entry_index].type]);


        int len_width = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
        char * str_width = malloc(len_width + 1);
        snprintf(str_width, len_width + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width);

        int len_height = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
        char * str_height = malloc(len_height + 1);
        snprintf(str_height, len_height + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);

        int len_compression = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame);
        char * str_compression = malloc(len_compression + 1);
        snprintf(str_compression, len_compression + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame);

        int len_frame_count = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count);
        char * str_frame_count = malloc(len_frame_count + 1);
        snprintf(str_frame_count, len_frame_count + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count);

        int len_frame_delay = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame);
        char * str_frame_delay = malloc(len_frame_delay + 1);
        snprintf(str_frame_delay, len_frame_delay + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame);

        int len_flags1 = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle);
        char * str_flags1 = malloc(len_flags1 + 1);
        snprintf(str_flags1, len_flags1 + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle);

        int len_flags2 = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page);
        char * str_flags2 = malloc(len_flags2 + 1);
        snprintf(str_flags2, len_flags2 + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page);

        int len_reserved = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset);
        char * str_reserved = malloc(len_reserved + 1);
        snprintf(str_reserved, len_reserved + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset);

        int len_palette_info_offset = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset);
        char * str_palette_info_offset = malloc(len_palette_info_offset + 1);
        snprintf(str_palette_info_offset, len_palette_info_offset + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset);

        int len_unknown = snprintf(NULL, 0, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown);
        char * str_unknown = malloc(len_unknown + 1);
        snprintf(str_unknown, len_unknown + 1, "0x%02X", lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown);
        
        printf("||%-12s|%-5s|%-13s|%11u|%12u|%13u|%11u|%10u|%10u|%16u|%15u|%19u|%7u|%14u|%19u|%19u|%18u||\n",
               lbx->file->file_name,
               tmp_entry_index_string,
               tmp_record_type_description_string,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->current_frame,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->loop_frame,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_handle,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_logical_page,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->emm_data_offset,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->palette_info_offset,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->unknown,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_offset,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_index,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette_header->palette_color_count,
               lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[0].begin
        );

    }
    printf("++%-12s=%-5s=%-13s=%11s=%12s=%13s=%11s=%10s=%10s=%16s=%15s=%19s=%7s=%14s=%19s=%19s=%18s++\n", "============", "=====", "=============", "===========", "============", "=============", "===========", "==========", "==========", "================", "===============", "===================", "=======", "==============", "===================", "===================", "==================");

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_display_lbx_record_headers_long()\n");
}

void liblbx_display_lbx_record_flic_header(LBX_DATA * lbx)
{

}

void display_lbx_flic_header(LBX_DATA * lbx, unsigned int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: display_lbx_flic_header()\n");

    int record_type;
    record_type = get_record_type(lbx, entry_number);

    /* if ((record_type != LBX_RECORD_TYPE_IMAGE) & (record_type != LBX_RECORD_TYPE_ANIMATION)) */
    if (record_type != LBX_RECORD_TYPE_FLIC)
    {
        /* printf("Record is NEITHER an image NOR an animation.\n"); */
        printf("Record is NOT a FLIC.\n");
    }
    else
    {
        LBX_FLIC_INFO_HEADER * lbx_image_header;
        lbx_image_header = get_lbx_image_header(lbx, entry_number);

        /*
         * int len_entry_count = snprintf(NULL, 0, "0x%02X", lbx->header->entry_count);
         * char * str_entry_count = malloc(len_entry_count + 1);
         * snprintf(str_entry_count, len_entry_count + 1, "0x%02X", lbx->header->entry_count);
         * */

        int len_width = snprintf(NULL, 0, "0x%02X", lbx_image_header->frame_width);
        char * str_width = malloc(len_width + 1);
        snprintf(str_width, len_width + 1, "0x%02X", lbx_image_header->frame_width);

        int len_height = snprintf(NULL, 0, "0x%02X", lbx_image_header->frame_height);
        char * str_height = malloc(len_height + 1);
        snprintf(str_height, len_height + 1, "0x%02X", lbx_image_header->frame_height);

        int len_compression = snprintf(NULL, 0, "0x%02X", lbx_image_header->current_frame);
        char * str_compression = malloc(len_compression + 1);
        snprintf(str_compression, len_compression + 1, "0x%02X", lbx_image_header->current_frame);

        int len_frame_count = snprintf(NULL, 0, "0x%02X", lbx_image_header->frame_count);
        char * str_frame_count = malloc(len_frame_count + 1);
        snprintf(str_frame_count, len_frame_count + 1, "0x%02X", lbx_image_header->frame_count);

        int len_frame_delay = snprintf(NULL, 0, "0x%02X", lbx_image_header->loop_frame);
        char * str_frame_delay = malloc(len_frame_delay + 1);
        snprintf(str_frame_delay, len_frame_delay + 1, "0x%02X", lbx_image_header->loop_frame);

        int len_flags1 = snprintf(NULL, 0, "0x%02X", lbx_image_header->emm_handle);
        char * str_flags1 = malloc(len_flags1 + 1);
        snprintf(str_flags1, len_flags1 + 1, "0x%02X", lbx_image_header->emm_handle);

        int len_flags2 = snprintf(NULL, 0, "0x%02X", lbx_image_header->emm_logical_page);
        char * str_flags2 = malloc(len_flags2 + 1);
        snprintf(str_flags2, len_flags2 + 1, "0x%02X", lbx_image_header->emm_logical_page);

        int len_reserved = snprintf(NULL, 0, "0x%02X", lbx_image_header->emm_data_offset);
        char * str_reserved = malloc(len_reserved + 1);
        snprintf(str_reserved, len_reserved + 1, "0x%02X", lbx_image_header->emm_data_offset);

        int len_palette_info_offset = snprintf(NULL, 0, "0x%02X", lbx_image_header->palette_info_offset);
        char * str_palette_info_offset = malloc(len_palette_info_offset + 1);
        snprintf(str_palette_info_offset, len_palette_info_offset + 1, "0x%02X", lbx_image_header->palette_info_offset);

        int len_unknown = snprintf(NULL, 0, "0x%02X", lbx_image_header->unknown);
        char * str_unknown = malloc(len_unknown + 1);
        snprintf(str_unknown, len_unknown + 1, "0x%02X", lbx_image_header->unknown);

        printf("++%12s=%6s=%6s++\n", "============", "======", "======");
        printf("||%12s|%6s|%6s||\n", "Field", "Dec", "Hex");
        printf("||%12s|%6s|%6s||\n", "------------", "------", "------");
        printf("||%12s|%6u|%6s||\n", "width", lbx_image_header->frame_width, str_width);
        printf("||%12s|%6u|%6s||\n", "height", lbx_image_header->frame_height, str_height);
        printf("||%12s|%6u|%6s||\n", "compression", lbx_image_header->current_frame, str_compression);
        printf("||%12s|%6u|%6s||\n", "frame_count", lbx_image_header->frame_count, str_frame_count);
        printf("||%12s|%6u|%6s||\n", "frame_delay", lbx_image_header->loop_frame, str_frame_delay);
        printf("||%12s|%6u|%6s||\n", "flags1", lbx_image_header->emm_handle, str_flags1);
        printf("||%12s|%6u|%6s||\n", "flags2", lbx_image_header->emm_logical_page, str_flags2);
        printf("||%12s|%6u|%6s||\n", "reserved", lbx_image_header->emm_data_offset, str_reserved);
        printf("||%12s|%6u|%6s||\n", "palette_info_offset", lbx_image_header->palette_info_offset, str_palette_info_offset);
        printf("||%12s|%6u|%6s||\n", "unknown", lbx_image_header->unknown, str_unknown);
        printf("++%12s=%6s=%6s++\n", "============", "======", "======");

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: display_lbx_flic_header()\n");
}

void display_lbx_image_custom_palette_header(LBX_DATA * lbx, unsigned int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: display_lbx_image_custom_palette_header()\n");

    int record_type;
    record_type = get_record_type(lbx, entry_number);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_type: %d\n", record_type);

    /* if ((record_type != LBX_RECORD_TYPE_IMAGE) & (record_type != LBX_RECORD_TYPE_ANIMATION)) */
    if (record_type != LBX_RECORD_TYPE_FLIC)
    {
        printf("Record is NEITHER an image NOR an animation.\n");
    }
    else
    {
        LBX_FLIC_PALETTE_HEADER * lbx_image_custom_palette_header;
        lbx_image_custom_palette_header = get_lbx_image_custom_palette_header(lbx, entry_number);

        if (!lbx_image_custom_palette_header) {
            if (LBX_DEBUG_MODE) printf("DEBUG: No custom palette contained here-in.\n");
            lbx_image_custom_palette_header = NULL;
        }
        else
        {
            /*
         * int len_entry_count = snprintf(NULL, 0, "0x%02X", lbx->header->entry_count);
         * char * str_entry_count = malloc(len_entry_count + 1);
         * snprintf(str_entry_count, len_entry_count + 1, "0x%02X", lbx->header->entry_count);
         * */

            int len_palette_offset = snprintf(NULL, 0, "0x%02X", lbx_image_custom_palette_header->palette_offset);
            char * str_palette_offset = malloc(len_palette_offset + 1);
            snprintf(str_palette_offset, len_palette_offset + 1, "0x%02X", lbx_image_custom_palette_header->palette_offset);

            int len_palette_color_index = snprintf(NULL, 0, "0x%02X", lbx_image_custom_palette_header->palette_color_index);
            char * str_palette_color_index = malloc(len_palette_color_index + 1);
            snprintf(str_palette_color_index, len_palette_color_index + 1, "0x%02X", lbx_image_custom_palette_header->palette_color_index);

            int len_palette_color_count = snprintf(NULL, 0, "0x%02X", lbx_image_custom_palette_header->palette_color_count);
            char * str_palette_color_count = malloc(len_palette_color_count + 1);
            snprintf(str_palette_color_count, len_palette_color_count + 1, "0x%02X", lbx_image_custom_palette_header->palette_color_count);

            printf("++%12s=%6s=%6s++\n", "============", "======", "======");
            printf("||%12s|%6s|%6s||\n", "Field", "Dec", "Hex");
            printf("||%12s|%6s|%6s||\n", "------------", "------", "------");
            printf("||%12s|%6u|%6s||\n", "palette_offset", lbx_image_custom_palette_header->palette_offset, str_palette_offset);
            printf("||%12s|%6u|%6s||\n", "palette_color_index", lbx_image_custom_palette_header->palette_color_index, str_palette_color_index);
            printf("||%12s|%6u|%6s||\n", "palette_color_count", lbx_image_custom_palette_header->palette_color_count, str_palette_color_count);
            printf("++%12s=%6s=%6s++\n", "============", "======", "======");
        }

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: display_lbx_image_custom_palette_header()\n");
}