#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <string.h> /* strcat() */
#include <stdlib.h> /* itoa(), splitpath(); EXIT_FAILURE; */
#include <limits.h>  /* INT_MAX, INT_MIN */
#include <malloc.h>         /* ?<stdlib.h>? malloc(), realloc(); */
#include <sys/stat.h>  /* fstat(); stat; */
#include <time.h>

#include "lib_lbx_meta_data.h"
#include "lib_lbx.h"
#include "lib_lbx_record.h"
#include "lib_lbx_record_type.h"
#include "lib_lbx_record_subrecord.h"
#include "lib_lbx_util.h"



/*
 * Header, Info, File, Records[]
 */

void liblbx_populate_lbx_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: liblbx_populate_lbx_meta_data()\n");
    populate_lbx_header_meta_data(lbx);
    populate_lbx_file_meta_data(lbx);
    populate_lbx_info_meta_data(lbx);
    populate_lbx_record_meta_data(lbx);
    if (LBX_DEBUG_MODE) printf("DEBUG: END: liblbx_populate_lbx_meta_data()\n");
}

void populate_lbx_header_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: populate_lbx_header_meta_data()\n");

    /*
     * Entry Count
     */
    lbx->meta->entry_count = lbx->header->entry_count;
    int tmp_len_entry_count_string_dec = snprintf( NULL, 0, "%d", lbx->meta->entry_count);
    lbx->meta->entry_count_string_dec = malloc(tmp_len_entry_count_string_dec + 1);
    snprintf(lbx->meta->entry_count_string_dec, tmp_len_entry_count_string_dec + 1, "%d", lbx->meta->entry_count);
    int tmp_len_entry_count_string_hex = snprintf( NULL, 0, "%d", lbx->meta->entry_count);
    lbx->meta->entry_count_string_hex = malloc(tmp_len_entry_count_string_hex + 1);
    snprintf(lbx->meta->entry_count_string_hex, tmp_len_entry_count_string_hex + 1, "%d", lbx->meta->entry_count);

    /*
     * Magic / File Type Signature
     */
    lbx->meta->magic = lbx->header->magic;
    int tmp_len_magic_string_dec = snprintf( NULL, 0, "%d", lbx->meta->magic);
    lbx->meta->magic_string_dec = malloc(tmp_len_magic_string_dec + 1);
    snprintf(lbx->meta->magic_string_dec, tmp_len_magic_string_dec + 1, "%d", lbx->meta->magic);
    int tmp_len_magic_string_hex = snprintf( NULL, 0, "0x%04X", lbx->meta->magic);
    lbx->meta->magic_string_hex = malloc(tmp_len_magic_string_hex + 1);
    snprintf(lbx->meta->magic_string_hex, tmp_len_magic_string_hex + 1, "0x%04X", lbx->meta->magic);

    /*
     * Unknown / Unused / Reserved
     */
    lbx->meta->unknown = lbx->header->unknown;
    int tmp_len_unknown_string_dec = snprintf( NULL, 0, "%d", lbx->meta->unknown);
    lbx->meta->unknown_string_dec = malloc(tmp_len_unknown_string_dec + 1);
    snprintf(lbx->meta->unknown_string_dec, tmp_len_unknown_string_dec + 1, "%d", lbx->meta->unknown);
    int tmp_len_unknown_string_hex = snprintf( NULL, 0, "0x%04X", lbx->meta->unknown);
    lbx->meta->unknown_string_hex = malloc(tmp_len_unknown_string_hex + 1);
    snprintf(lbx->meta->unknown_string_hex, tmp_len_unknown_string_hex + 1, "0x%04X", lbx->meta->unknown);

    /*
     * LBX Type
     */
    lbx->meta->type = lbx->header->type;
    int tmp_len_type_string_dec = snprintf( NULL, 0, "%d", lbx->meta->type);
    lbx->meta->type_string_dec = malloc(tmp_len_type_string_dec + 1);
    snprintf(lbx->meta->type_string_dec, tmp_len_type_string_dec + 1, "%d", lbx->meta->type);
    int tmp_len_type_string_hex = snprintf( NULL, 0, "0x%04X", lbx->meta->type);
    lbx->meta->type_string_hex = malloc(tmp_len_type_string_hex + 1);
    snprintf(lbx->meta->type_string_hex, tmp_len_type_string_hex + 1, "0x%04X", lbx->meta->type);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: populate_lbx_header_meta_data()\n");
}

void populate_lbx_file_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: populate_lbx_file_meta_data()\n");

    /*
     * File Path, Directory Path, File Name, File Name Base
     */

    lbx->meta->meta_file_path = malloc(sizeof(char) * (strlen(lbx->file->file_path) + 1));
    strcpy(lbx->meta->meta_file_path, lbx->file->file_path);

    lbx->meta->meta_directory_path = malloc(sizeof(char) * (strlen(lbx->file->directory_path) + 1));
    strcpy(lbx->meta->meta_directory_path, lbx->file->directory_path);

    lbx->meta->meta_file_name = malloc(sizeof(char) * (strlen(lbx->file->file_name) + 1));
    strcpy(lbx->meta->meta_file_name, lbx->file->file_name);

    lbx->meta->meta_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + 1));
    strcpy(lbx->meta->meta_file_name_base, lbx->file->file_name_base);

    /*
     * File Size
     */
    lbx->meta->file_size = liblbx_file_size_via_seek(lbx->file->file_stream);
    int tmp_len_file_size_string = snprintf( NULL, 0, "%d", lbx->meta->file_size);
    lbx->meta->file_size_string = malloc(tmp_len_file_size_string + 1);
    snprintf(lbx->meta->file_size_string, tmp_len_file_size_string + 1, "%d", lbx->meta->file_size);

    /*
     * File Timestamp, Earliest
     */
    liblbx_earliest_timestamp_via_stat(lbx);
    lbx->meta->earliest_timestamp_string = malloc(sizeof(char) * (strlen(ISO8601_STRING) + 1));
    strftime(lbx->meta->earliest_timestamp_string, (sizeof(char) * (strlen(ISO8601_STRING) + 1)), ISO8601_FORMAT_STRING, gmtime(&lbx->meta->earliest_timestamp));

    /*
     * Checksums - CRC32
     */
    liblbx_compute_crc32_file(lbx->file->file_stream, &lbx->meta->file_checksum_crc32);
    int tmp_len_file_checksum_crc32_string = snprintf( NULL, 0, "%08lX", lbx->meta->file_checksum_crc32);
    lbx->meta->file_checksum_crc32_string = malloc(tmp_len_file_checksum_crc32_string + 1);
    snprintf(lbx->meta->file_checksum_crc32_string, tmp_len_file_checksum_crc32_string + 1, "%08lX", lbx->meta->file_checksum_crc32);

    /*
     * Checksums - MD5
     */
    lbx->meta->file_checksum_md5_string = malloc(sizeof(char) * (strlen("N/A") + 1));
    strcpy(lbx->meta->file_checksum_md5_string, "N/A");

    /*
     * Checksums - SHA1
     */
    lbx->meta->file_checksum_sha1_string = malloc(sizeof(char) * (strlen("N/A") + 1));
    strcpy(lbx->meta->file_checksum_sha1_string, "N/A");

    /*
     * Checksums - SHA256
     */
    lbx->meta->file_checksum_sha256_string = malloc(sizeof(char) * (strlen("N/A") + 1));
    strcpy(lbx->meta->file_checksum_sha256_string, "N/A");

    if (LBX_DEBUG_MODE) printf("DEBUG: END: populate_lbx_file_meta_data()\n");
}

void populate_lbx_info_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: populate_lbx_meta_data()\n");

    /*
     * Header Length, Used, Padding
     * String Table
     */
    int tmp_len_header_length_string_dec = snprintf( NULL, 0, "%d", lbx->meta->header_length);
    lbx->meta->header_length_string_dec = malloc(tmp_len_header_length_string_dec + 1);
    snprintf(lbx->meta->header_length_string_dec, tmp_len_header_length_string_dec + 1, "%d", lbx->meta->header_length);

    int tmp_len_header_length_total_string_dec = snprintf( NULL, 0, "%d", lbx->meta->header_length_total);
    lbx->meta->header_length_total_string_dec = malloc(tmp_len_header_length_total_string_dec + 1);
    snprintf(lbx->meta->header_length_total_string_dec, tmp_len_header_length_string_dec + 1, "%d", lbx->meta->header_length_total);

    int tmp_len_header_length_used_string_dec = snprintf( NULL, 0, "%d", lbx->meta->header_length_used);
    lbx->meta->header_length_used_string_dec = malloc(tmp_len_header_length_used_string_dec + 1);
    snprintf(lbx->meta->header_length_used_string_dec, tmp_len_header_length_used_string_dec + 1, "%d", lbx->meta->header_length_used);

    int tmp_len_header_padding_length_string_dec = snprintf( NULL, 0, "%d", lbx->meta->header_padding_length);
    lbx->meta->header_padding_length_string_dec = malloc(tmp_len_header_padding_length_string_dec + 1);
    snprintf(lbx->meta->header_padding_length_string_dec, tmp_len_header_padding_length_string_dec + 1, "%d", lbx->meta->header_padding_length);

    if (lbx->meta->has_string_table == 1)
    {
        lbx->meta->has_string_table_string = malloc(sizeof(char) * (strlen("TRUE") + 1));
        strcpy(lbx->meta->has_string_table_string, "TRUE");
    }
    else
    {
        lbx->meta->has_string_table_string = malloc(sizeof(char) * (strlen("FALSE") + 1));
        strcpy(lbx->meta->has_string_table_string, "FALSE");
    }

    if (lbx->meta->has_string_table == 1)
    {
        int tmp_len_string_table_length_string = snprintf( NULL, 0, "%d", lbx->meta->string_table_length);
        lbx->meta->string_table_length_string = malloc(tmp_len_string_table_length_string + 1);
        snprintf(lbx->meta->string_table_length_string, tmp_len_string_table_length_string + 1, "%d", lbx->meta->string_table_length);
    }
    else
    {
        lbx->meta->string_table_length_string = malloc(sizeof(char) * (strlen("N/A") + 1));
        strcpy(lbx->meta->string_table_length_string, "N/A");
    }

    if (lbx->meta->has_string_table == 1)
    {
        int tmp_len_string_table_entry_count_string = snprintf( NULL, 0, "%d", lbx->meta->string_table_entry_count);
        lbx->meta->string_table_entry_count_string = malloc(tmp_len_string_table_entry_count_string + 1);
        snprintf(lbx->meta->string_table_entry_count_string, tmp_len_string_table_entry_count_string + 1, "%d", lbx->meta->string_table_entry_count);
    }
    else
    {
        lbx->meta->string_table_entry_count_string = malloc(sizeof(char) * (strlen("N/A") + 1));
        strcpy(lbx->meta->string_table_entry_count_string, "N/A");
    }

    if (lbx->meta->equal_header_padding_length_string_table_length == 1)
    {
        lbx->meta->equal_header_padding_length_string_table_length_string = malloc(sizeof(char) * (strlen("TRUE") + 1));
        strcpy(lbx->meta->equal_header_padding_length_string_table_length_string, "TRUE");
    }
    else
    {
        lbx->meta->equal_header_padding_length_string_table_length_string = malloc(sizeof(char) * (strlen("FALSE") + 1));
        strcpy(lbx->meta->equal_header_padding_length_string_table_length_string, "FALSE");
    }

    /*
     * Offset BOF & EOF
     * Offset BOD & EOD
     * EOD is EOF
     */
    lbx->meta->offset_bod = lbx->header->offset_table->entry[0].begin;
    int tmp_len_offset_bod_string_dec = snprintf( NULL, 0, "%d", lbx->meta->offset_bod);
    lbx->meta->offset_bod_string_dec = malloc(tmp_len_offset_bod_string_dec + 1);
    snprintf(lbx->meta->offset_bod_string_dec, tmp_len_offset_bod_string_dec + 1, "%d", lbx->meta->offset_bod);
    int tmp_len_offset_bod_string_hex = snprintf( NULL, 0, "0x%08X", lbx->meta->offset_bod);
    lbx->meta->offset_bod_string_hex = malloc(tmp_len_offset_bod_string_hex + 1);
    snprintf(lbx->meta->offset_bod_string_hex, tmp_len_offset_bod_string_hex + 1, "0x%08X", lbx->meta->offset_bod);

    lbx->meta->offset_eod = lbx->header->offset_table->entry[lbx->header->entry_count].begin;
    int tmp_len_offset_eod_string_dec = snprintf( NULL, 0, "%d", lbx->meta->offset_eod);
    lbx->meta->offset_eod_string_dec = malloc(tmp_len_offset_eod_string_dec + 1);
    snprintf(lbx->meta->offset_eod_string_dec, tmp_len_offset_eod_string_dec + 1, "%d", lbx->meta->offset_eod);
    int tmp_len_offset_eod_string_hex = snprintf( NULL, 0, "0x%08X", lbx->meta->offset_eod);
    lbx->meta->offset_eod_string_hex = malloc(tmp_len_offset_eod_string_hex + 1);
    snprintf(lbx->meta->offset_eod_string_hex, tmp_len_offset_eod_string_hex + 1, "0x%08X", lbx->meta->offset_eod);

    /*
     * EOD is EOF
     */
    if (lbx->meta->offset_eod == lbx->meta->file_size)
    {
        lbx->meta->equal_eod_eof = 1;
    }
    else
    {
        lbx->meta->equal_eod_eof = 0;
    }
    if (lbx->meta->equal_eod_eof == 1)
    {
        lbx->meta->equal_eod_eof_string = malloc(sizeof(char) * (strlen("TRUE") + 1));
        strcpy(lbx->meta->equal_eod_eof_string, "TRUE");
    }
    else
    {
        lbx->meta->equal_eod_eof_string = malloc(sizeof(char) * (strlen("FALSE") + 1));
        strcpy(lbx->meta->equal_eod_eof_string, "FALSE");
    }

    /*
     * Record Size - Minimum, Maximum, Average
     * Empty Record Count
     */
    int record_size;
    int empty_record_count;

    int record_size_minimum;
    int record_size_maximum;
    int record_size_accumulator;

    empty_record_count = 0;
    record_size_minimum = INT_32_MAX;
    record_size_maximum = INT_32_MIN;
    record_size_accumulator = 0;

    int entry_count;
    int itr_entry_index;

    entry_count = lbx->header->entry_count;

    for (itr_entry_index = 0; itr_entry_index < entry_count; itr_entry_index++) {
        record_size = get_record_size(lbx, itr_entry_index);
        if (lbx->record->entry[itr_entry_index].size != 0)
        {
            record_size_accumulator = record_size_accumulator + lbx->record->entry[itr_entry_index].size;
            if (lbx->record->entry[itr_entry_index].size < record_size_minimum) {
                record_size_minimum = lbx->record->entry[itr_entry_index].size;
            }
            if (lbx->record->entry[itr_entry_index].size > record_size_maximum) {
                record_size_maximum = lbx->record->entry[itr_entry_index].size;
            }
        }
        else
        {
            empty_record_count = empty_record_count + 1;
        }
    }
    lbx->meta->empty_record_count = empty_record_count;
    lbx->meta->record_size_minimum = record_size_minimum;
    lbx->meta->record_size_maximum = record_size_maximum;
    lbx->meta->record_size_average = record_size_accumulator / entry_count;

    int tmp_len_record_size_minimum_string = snprintf( NULL, 0, "%d", lbx->meta->record_size_minimum);
    lbx->meta->record_size_minimum_string = malloc(tmp_len_record_size_minimum_string + 1);
    snprintf(lbx->meta->record_size_minimum_string, tmp_len_record_size_minimum_string + 1, "%d", lbx->meta->record_size_minimum);

    int tmp_len_record_size_maximum_string = snprintf( NULL, 0, "%d", lbx->meta->record_size_maximum);
    lbx->meta->record_size_maximum_string = malloc(tmp_len_record_size_maximum_string + 1);
    snprintf(lbx->meta->record_size_maximum_string, tmp_len_record_size_maximum_string + 1, "%d", lbx->meta->record_size_maximum);

    int tmp_len_record_size_average_string = snprintf( NULL, 0, "%d", lbx->meta->record_size_average);
    lbx->meta->record_size_average_string = malloc(tmp_len_record_size_average_string + 1);
    snprintf(lbx->meta->record_size_average_string, tmp_len_record_size_average_string + 1, "%d", lbx->meta->record_size_average);

    int tmp_len_empty_record_count_string = snprintf( NULL, 0, "%d", lbx->meta->empty_record_count);
    lbx->meta->empty_record_count_string = malloc(tmp_len_empty_record_count_string + 1);
    snprintf(lbx->meta->empty_record_count_string, tmp_len_empty_record_count_string + 1, "%d", lbx->meta->empty_record_count);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: populate_lbx_meta_data()\n");
}

void populate_lbx_record_meta_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: populate_lbx_record_meta_data()\n");

    if (LBX_DEBUG_MODE) printf("DEBUG: file_name: %s\n", lbx->file->file_name);

    int itr_entry_index;
    int entry_count;

    entry_count = lbx->header->entry_count;

    for (itr_entry_index = 0; itr_entry_index < entry_count; itr_entry_index++)
    {
        if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: %s[%d]:\n", lbx->file->file_name_base, itr_entry_index);

        /*
         * Record Entry Number
         */
        lbx->meta->records->entry[itr_entry_index].meta_entry_number = itr_entry_index;
        int tmp_len_entry_number_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].meta_entry_number);
        lbx->meta->records->entry[itr_entry_index].entry_number_string = malloc(tmp_len_entry_number_string + 1);
        snprintf(lbx->meta->records->entry[itr_entry_index].entry_number_string, tmp_len_entry_number_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].meta_entry_number);

        /*
         * Record Entry Name
         */
//        lbx->meta->records->entry[itr_entry_index].entry_name = lbx->header->string_table->entry[itr_entry_index].name;
//        int tmp_len_entry_name_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].entry_name);
//        lbx->meta->records->entry[itr_entry_index].entry_name = malloc(tmp_len_entry_name_string + 1);
//        snprintf(lbx->meta->records->entry[itr_entry_index].entry_name, tmp_len_entry_name_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].entry_name);
        strcpy(lbx->meta->records->entry[itr_entry_index].entry_name, lbx->header->string_table->entry[itr_entry_index].name);

        /*
         * Record Entry Description
         */
//        lbx->meta->records->entry[itr_entry_index].entry_description = lbx->header->string_table->entry[itr_entry_index].name;
//        int tmp_len_entry_description_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].entry_description);
//        lbx->meta->records->entry[itr_entry_index].entry_description = malloc(tmp_len_entry_description_string + 1);
//        snprintf(lbx->meta->records->entry[itr_entry_index].entry_description, tmp_len_entry_description_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].entry_description);
        strcpy(lbx->meta->records->entry[itr_entry_index].entry_description, lbx->header->string_table->entry[itr_entry_index].description);

        /*
         * Record Type, Record Type Description
         */
        lbx->meta->records->entry[itr_entry_index].meta_type = get_record_type(lbx, itr_entry_index);
        int tmp_len_type_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].meta_type);
        lbx->meta->records->entry[itr_entry_index].type_string = malloc(tmp_len_type_string + 1);
        snprintf(lbx->meta->records->entry[itr_entry_index].type_string, tmp_len_type_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].meta_type);

        // int tmp_len_type_description_string = snprintf(NULL, 0, "%s", l_LBX_Record_Type_Description[lbx->meta->records->entry[itr_entry_index].meta_type]);
        int tmp_len_type_description_string = snprintf(NULL, 0, "%s", LBX_Record_Type_Description[lbx->meta->records->entry[itr_entry_index].meta_type]);
        lbx->meta->records->entry[itr_entry_index].type_description_string = malloc(sizeof(char) * (tmp_len_type_description_string + 1));
        // snprintf(lbx->meta->records->entry[itr_entry_index].type_description_string, tmp_len_type_description_string + 1, "%s", l_LBX_Record_Type_Description[lbx->meta->records->entry[itr_entry_index].meta_type]);
        snprintf(lbx->meta->records->entry[itr_entry_index].type_description_string, tmp_len_type_description_string + 1, "%s", LBX_Record_Type_Description[lbx->meta->records->entry[itr_entry_index].meta_type]);

        /*
         * Record Size
         */
        lbx->meta->records->entry[itr_entry_index].meta_size = get_record_size(lbx, itr_entry_index);
        int tmp_len_size_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].meta_size);
        lbx->meta->records->entry[itr_entry_index].size_string = malloc(tmp_len_size_string + 1);
        snprintf(lbx->meta->records->entry[itr_entry_index].size_string, tmp_len_size_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].meta_size);

        /*
         * Record File Name Base
         */
        lbx->meta->records->entry[itr_entry_index].meta_record_file_name_base = get_record_file_name_base(lbx, itr_entry_index);

        /*
         * Checksums - CRC32
         */
        lbx->meta->records->entry[itr_entry_index].record_checksum_crc32 = get_record_checksum_crc32(lbx, itr_entry_index);
        int tmp_len_record_checksum_crc32_string = snprintf( NULL, 0, "%08lX", lbx->meta->records->entry[itr_entry_index].record_checksum_crc32);
        lbx->meta->records->entry[itr_entry_index].record_checksum_crc32_string = malloc(tmp_len_record_checksum_crc32_string + 1);
        snprintf(lbx->meta->records->entry[itr_entry_index].record_checksum_crc32_string, tmp_len_record_checksum_crc32_string + 1, "%08lX", lbx->meta->records->entry[itr_entry_index].record_checksum_crc32);
        /*
         * Checksums - MD5
         */
        lbx->meta->records->entry[itr_entry_index].record_checksum_md5_string = malloc(sizeof(char) * (strlen("N/A") + 1));
        strcpy(lbx->meta->records->entry[itr_entry_index].record_checksum_md5_string, "N/A");
        /*
         * Checksums - SHA1
         */
        lbx->meta->records->entry[itr_entry_index].record_checksum_sha1_string = malloc(sizeof(char) * (strlen("N/A") + 1));
        strcpy(lbx->meta->records->entry[itr_entry_index].record_checksum_sha1_string, "N/A");
        /*
         * Checksums - SHA256
         */
        lbx->meta->records->entry[itr_entry_index].record_checksum_sha256_string = malloc(sizeof(char) * (strlen("N/A") + 1));
        strcpy(lbx->meta->records->entry[itr_entry_index].record_checksum_sha256_string, "N/A");

        /*
         * subrecord_count
         */
        /* TODO(JWB): add check for record types that actually qualify for a sub-record count */
        lbx->meta->records->entry[itr_entry_index].subrecord_count = get_record_subrecord_count(lbx, itr_entry_index);
        int tmp_len_subrecord_count_string = snprintf( NULL, 0, "%d", lbx->meta->records->entry[itr_entry_index].subrecord_count);
        lbx->meta->records->entry[itr_entry_index].subrecord_count_string = malloc(tmp_len_subrecord_count_string + 1);
        snprintf(lbx->meta->records->entry[itr_entry_index].subrecord_count_string, tmp_len_subrecord_count_string + 1, "%d", lbx->meta->records->entry[itr_entry_index].subrecord_count);

    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: populate_lbx_record_meta_data()\n");
}


/*
 * Populate LBX_RECORD_DATA
 */
void populate_record_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: populate_record_data()\n");

    int tmp_entry_count;
    int itr_entry_count;
    int tmp_entry_number;

    tmp_entry_count = lbx->header->entry_count;
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->entry_count: %d\n", lbx->header->entry_count);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: tmp_entry_count: %d\n", tmp_entry_count);

    for (itr_entry_count = 0; itr_entry_count < tmp_entry_count; itr_entry_count++) {
        /* tmp_entry_number = itr_entry_count + 1; */
        /* TODO(JWB): decide on language/approach for "Entry Number" vs. '(Record) Index' */
        tmp_entry_number = itr_entry_count;

    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: populate_record_data()\n");
}
