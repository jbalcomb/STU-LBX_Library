#include <malloc.h>         /* malloc(), realloc(); */
#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <string.h>         /* memcpy(), strncpy(), strlen(); */

#include "lib_lbx_display.h"



void lbx_display_header(LBX_DATA * lbx_data)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_header()\n");

    lbx_display_header_preamble(lbx_data);
    lbx_display_header_offset_table(lbx_data);
    lbx_display_header_string_table(lbx_data);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_header()\n");
}

void lbx_display_header_preamble(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_header_preamble()\n");

    int len_entry_count = snprintf(NULL, 0, "0x%04X", lbx->header->entry_count);
    char * str_entry_count = malloc(len_entry_count + 1);
    snprintf(str_entry_count, len_entry_count + 1, "0x%04X", lbx->header->entry_count);
    int len_magic = snprintf(NULL, 0, "0x%04X", lbx->header->magic);
    char * str_magic = malloc(len_magic + 1);
    snprintf(str_magic, len_magic + 1, "0x%04X", lbx->header->magic);
    int len_reserved = snprintf(NULL, 0, "0x%04X", lbx->header->unknown);
    char * str_reserved = malloc(len_reserved + 1);
    snprintf(str_reserved, len_reserved + 1, "0x%04X", lbx->header->unknown);
    int len_type = snprintf(NULL, 0, "0x%04X", lbx->header->type);
    char * str_type = malloc(len_type + 1);
    snprintf(str_type, len_type + 1, "0x%04X", lbx->header->type);

    printf("++%12s=%6s=%6s++\n", "============", "======", "======");
    printf("||%12s|%6s|%6s||\n", "Field", "Dec", "Hex");
    printf("||%12s|%6s|%6s||\n", "------------", "------", "------");
    printf("||%12s|%6u|%6s||\n", "entry_count", lbx->header->entry_count, str_entry_count);
    printf("||%12s|%6u|%6s||\n", "magic", lbx->header->magic, str_magic);
    printf("||%12s|%6u|%6s||\n", "unknown", lbx->header->unknown, str_reserved);
    printf("||%12s|%6u|%6s||\n", "type", lbx->header->type, str_type);
    printf("++%12s=%6s=%6s++\n", "============", "======", "======");

    free(str_entry_count);
    free(str_magic);
    free(str_reserved);
    free(str_type);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_header_preamble()\n");
}

void lbx_display_header_offset_table(LBX_DATA * lbx_data)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_header_offset_table()\n");

    int itr_header_offset_table;
    int len_offset_begin;
    char* str_offset_begin;
    int len_offset_end;
    char* str_offset_end;

    printf("++%18s=%18s=%18s=%18s++\n", "==================", "==================", "==================", "==================");
    printf("||%18s|%18s|%18s|%18s||\n", "Offset Begin (Dec)", "Offset End (Dec)", "Offset Begin (Hex)", "Offset End (Hex)");
    printf("||%18s|%18s|%18s|%18s||\n", "------------------", "------------------", "------------------", "------------------");
    for(itr_header_offset_table = 0; itr_header_offset_table < lbx_data->header->entry_count; itr_header_offset_table++)
    {
        len_offset_begin = snprintf(NULL, 0, "0x%08X", lbx_data->header->offset_table->entry[itr_header_offset_table].begin);
        str_offset_begin = malloc(len_offset_begin + 1);
        snprintf(str_offset_begin, len_offset_begin + 1, "0x%08X", lbx_data->header->offset_table->entry[itr_header_offset_table].begin);
        len_offset_end = snprintf(NULL, 0, "0x%08X", lbx_data->header->offset_table->entry[itr_header_offset_table + 1].begin);
        str_offset_end = malloc(len_offset_end + 1);
        snprintf(str_offset_end, len_offset_end + 1, "0x%08X", lbx_data->header->offset_table->entry[itr_header_offset_table + 1].begin);

        printf("||%18d|%18d|%18s|%18s||\n", lbx_data->header->offset_table->entry[itr_header_offset_table].begin, lbx_data->header->offset_table->entry[itr_header_offset_table + 1].begin, str_offset_begin, str_offset_end);

        free(str_offset_begin);
    }
    printf("++%18s=%18s=%18s=%18s++\n", "==================", "==================", "==================", "==================");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_header_offset_table()\n");
}

void lbx_display_header_string_table(LBX_DATA * lbx_data)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_header_string_table()\n");

    int itr_string_offset_table;

    printf("++%9s=%23s++\n", "=========", "=======================");
    printf("||%-9s|%-23s||\n", "Name", "Description");
    printf("||%9s|%23s||\n", "---------", "-----------------------");
    if (lbx_data->meta->has_string_table == 0)
    {
        printf("||%9s|%23s||\n", "N/A", "N/A");
    }
    else
    {
        for(itr_string_offset_table = 0; itr_string_offset_table < lbx_data->header->entry_count; itr_string_offset_table++)
        {
            printf("||%-9s|%-23s||\n", lbx_data->header->string_table->entry[itr_string_offset_table].name, lbx_data->header->string_table->entry[itr_string_offset_table].description);
        }
    }
    printf("++%9s=%23s++\n", "=========", "=======================");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_header_string_table()\n");
}

void display_lbx_file_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_lbx_file_meta_data()\n");

    char * print_padding_characters = "................................................................................";
    int target_string_length = 10;
    /*
     * int padLen = targetStrLen - strlen(myString); // Calc Padding length
     * if(padLen < 0) padLen = 0;    // Avoid negative length
     * printf("[%*.*s%s]", padLen, padLen, padding, myString);  // LEFT Padding
     * printf("[%s%*.*s]", myString, padLen, padLen, padding);  // RIGHT Padding
     * ...
     * char *s = "MyText";
     * unsigned int sz = 9;
     * char *pad = "########################################";
     * printf ("%.*s%s\n", (sz < strlen(s)) ? 0 : sz - strlen(s), pad, s);
     */

    printf("++%20s=%43s++\n", "====================", "===========================================");
    printf("||%-20s|%-43s||\n", "Name", "Value");
    printf("||%20s|%43s||\n", "--------------------", "-------------------------------------------");
    /*
     * File Names
     */
    printf("||%-20s|%-43s||\n", "File Path", lbx->meta->file_path);
    printf("||%-20s|%-43s||\n", "Directory Path", lbx->meta->directory_path);
    printf("||%-20s|%-43s||\n", "File Name", lbx->meta->file_name);
    printf("||%-20s|%-43s||\n", "File Name Base", lbx->meta->file_name_base);
    /*
     * File Size
     */
    printf("||%-20s|%-43s||\n", "File Size", lbx->meta->file_size_string);
    /*
     * File Timestamp, Earliest
     */
    printf("||%-20s|%-43s||\n", "File Timestamp", lbx->meta->earliest_timestamp_string);
    /*
     * Checksums - CRC32
     */
    printf("||%-20s|%-43s||\n", "File CRC32", lbx->meta->file_checksum_crc32_string);
    /*
     * Checksums - MD5
     */
    printf("||%-20s|%-43s||\n", "File MD5", lbx->meta->file_checksum_md5_string);
    /*
     * Checksums - SHA1
     * */
    printf("||%-20s|%-43s||\n", "File SHA1", lbx->meta->file_checksum_sha1_string);

    printf("++%20s=%43s++\n", "====================", "===========================================");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_lbx_file_meta_data()\n");
}

void display_lbx_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_lbx_meta_data()\n");

    printf("++%22s=%12s++\n", "======================", "============");
    printf("||%-22s|%-12s||\n", "Name", "Value");
    printf("||%22s|%12s||\n", "----------------------", "------------");
    /*
     * Entry Count
     */
    printf("||%-22s|%-12s||\n", "Entries", lbx->meta->entry_count_string_dec);
    /*
     * LBX Type
     */
    printf("||%-22s|%-12s||\n", "Type (Dec)", lbx->meta->type_string_dec);
    printf("||%-22s|%-12s||\n", "Type (Hex)", lbx->meta->type_string_hex);
    /*
     * Header Length, Used, Padding
     * String Table
     */
    printf("||%-22s|%-12s||\n", "Header Length", lbx->meta->header_length_string_dec);
    printf("||%-22s|%-12s||\n", "Header Length, Total", lbx->meta->header_length_total_string_dec);
    printf("||%-22s|%-12s||\n", "Header Length, Used", lbx->meta->header_length_used_string_dec);
    printf("||%-22s|%-12s||\n", "Header Padding Length", lbx->meta->header_padding_length_string_dec);
    printf("||%-22s|%-12s||\n", "No Header Padding", lbx->meta->equal_header_padding_length_string_table_length_string);
    printf("||%-22s|%-12s||\n", "Has String Table", lbx->meta->has_string_table_string);
    printf("||%-22s|%-12s||\n", "String Table Length", lbx->meta->string_table_length_string);
    printf("||%-22s|%-12s||\n", "String Table Entries", lbx->meta->string_table_entry_count_string);
    /*
     * Offset BOF & EOF
     * Offset BOD & EOD
     * EOD is EOF
     */
    printf("||%-22s|%-12s||\n", "Offset BOD (Dec)", lbx->meta->offset_bod_string_dec);
    printf("||%-22s|%-12s||\n", "Offset BOD (Hex)", lbx->meta->offset_bod_string_hex);
    printf("||%-22s|%-12s||\n", "Offset EOD (Dec)", lbx->meta->offset_eod_string_dec);
    printf("||%-22s|%-12s||\n", "Offset EOD (Hex)", lbx->meta->offset_eod_string_hex);
    printf("||%-22s|%-12s||\n", "EOD is EOF", lbx->meta->equal_eod_eof_string);
    /*
     * Record Size - Minimum, Maximum, Average
     * Empty Record Count
     */
    printf("||%-22s|%-12s||\n", "Record Size, Minimum", lbx->meta->record_size_minimum_string);
    printf("||%-22s|%-12s||\n", "Record Size, Maximum", lbx->meta->record_size_maximum_string);
    printf("||%-22s|%-12s||\n", "Record Size, Average", lbx->meta->record_size_average_string);
    printf("||%-22s|%-12s||\n", "Empty Records", lbx->meta->empty_record_count_string);

    printf("++%22s=%12s++\n", "======================", "============");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_lbx_meta_data()\n");
}

void display_lbx_record_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: display_lbx_record_meta_data()\n");

    int itr_entry_count;
    int tmp_entry_count;
    char sub_record_attributes[256];

    tmp_entry_count = lbx->header->entry_count;

    printf("++%5s=%8s=%4s=%13s++\n", "=====", "========", "====", "=============");
    printf("||%-5s|%-8s|%-4s|%-13s||\n", "Entry", "Size", "Type", "Type Desc");
    printf("++%5s=%8s=%4s=%13s++\n", "=====", "========", "====", "=============");

    for (itr_entry_count = 0; itr_entry_count < tmp_entry_count; itr_entry_count++)
    {
        if (lbx->meta->records->entry[itr_entry_count].type == LBX_RECORD_TYPE_IMAGES)
        {
            strcpy(sub_record_attributes, "Height, Width");
        }

        printf("||%-5s-%8s-%-4s-%-13s||\n", "-----", "--------", "----", "-------------");
        printf("||%-5s|%8s|%-4s|%-13s||\n",
               lbx->meta->records->entry[itr_entry_count].entry_number_string,
               lbx->meta->records->entry[itr_entry_count].size_string,
               lbx->meta->records->entry[itr_entry_count].type_string,
               lbx->meta->records->entry[itr_entry_count].type_description_string);
    }

    printf("++%5s=%8s=%4s=%13s++\n", "=====", "========", "====", "=============");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: display_lbx_record_meta_data()\n");
}
