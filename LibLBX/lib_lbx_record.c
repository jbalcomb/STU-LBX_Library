
#include <malloc.h>     /* malloc(), realloc() */
#include <stdio.h>      /* fclose(), fopen(), fread(), fwrite() */
#include <string.h>     /* strcmp() */
#include <stdlib.h>     /* itoa() */

#include "lib_lbx_record.h"
#include "lib_lbx.h"
#include "lib_lbx_util.h"


char * get_record_data(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_data()\n");

    int tmp_record_size;
    char * record_data;
    size_t tmp_pos;

    tmp_record_size = get_record_size(lbx, entry_number);

    record_data = malloc(tmp_record_size);

    tmp_pos = ftell(lbx->file_stream);

    fseek(lbx->file_stream, lbx->header->offset_table->entry[entry_number].begin, SEEK_SET);

    fread(record_data, tmp_record_size, 1, lbx->file_stream);

    fseek(lbx->file_stream, tmp_pos, SEEK_SET);


    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_data()\n");
    return record_data;
}

int get_record_size(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_size()\n");

    unsigned int record_size;

    record_size = (lbx->header->offset_table->entry[entry_number + 1].begin - lbx->header->offset_table->entry[entry_number].begin);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: record_size: %d\n", record_size);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_size()\n");
    return (int)record_size;
}

unsigned long int get_record_checksum_crc32(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_checksum_crc32()\n");

    unsigned long int record_checksum_crc32;
    char * tmp_record_data;
    size_t tmp_record_size;
    unsigned long int record_checksum_crc32_alt;

    tmp_record_data = get_record_data(lbx, entry_number);
    tmp_record_size = get_record_size(lbx, entry_number);

    lbx_compute_crc32_char_buffer(tmp_record_data, tmp_record_size, &record_checksum_crc32);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_checksum_crc32: %lu\n", record_checksum_crc32);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_checksum_crc32: %08lX\n", record_checksum_crc32);

    /*
    record_checksum_crc32_alt = 0;
    record_checksum_crc32_alt = ats_compute_crc32(record_checksum_crc32_alt, tmp_record_data, tmp_record_size);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_checksum_crc32_alt: %lu\n", record_checksum_crc32_alt);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_checksum_crc32_alt: %08lX\n", record_checksum_crc32_alt);
    */

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_checksum_crc32()\n");
    return record_checksum_crc32;
}

/* TODO)JWB): move this out of ~= 'Lib LBX - Core' (i.e., NOT pack/unpack/in-game) */
/* TODO(JWB): figure out how to make this return what/how it should, given the prevailing philosophy of C89 */
char * get_record_file_name_base(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_file_name_base()\n");

    /*
    strcpy(lbx->records->entry[itr_entry_count].record_file_name_base, lbx->file->file_name_base);
    itoa(itr_entry_count + 1, tmp_entry_number_string, 10);
    tmp_entry_number_string_length = strlen(tmp_entry_number_string);
    if (tmp_entry_number_string_length == 1) {
        strcat(lbx->records->entry[itr_entry_count].record_file_name_base, "00");
    }
    if (tmp_entry_number_string_length == 2) {
        strcat(lbx->records->entry[itr_entry_count].record_file_name_base, "0");
    }
    strcat(lbx->records->entry[itr_entry_count].record_file_name_base, tmp_entry_number_string);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->records->entry[itr_entry_count].record_file_name_base: %s\n", lbx->records->entry[itr_entry_count].record_file_name_base);
    */

    char * record_file_name_base;

    /* strcpy(lbx->records->entry[entry_number].record_file_name_base, lbx->file->file_name_base); */

    /*
    record_file_name_base = malloc(sizeof(char) * MAX_FNAME);
    strcpy(record_file_name_base, lbx->file->file_name_base);
    */

    /*
    record_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + 1));
    strcpy(record_file_name_base, lbx->file->file_name_base);
    */

    /*
    int tmp_len_entry_number_string;
    tmp_len_entry_number_string = snprintf( NULL, 0, "%d", entry_number);
    record_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + tmp_len_entry_number_string + 1));
    strcpy(record_file_name_base, lbx->file->file_name_base);
    */

    int tmp_len_entry_number_string;

    tmp_len_entry_number_string = snprintf( NULL, 0, "%d", entry_number);

    int tmp_len_entry_number_padding_string;

    if (tmp_len_entry_number_string == 1) {
        tmp_len_entry_number_padding_string = 2;
    }
    else if (tmp_len_entry_number_string == 2) {
        tmp_len_entry_number_padding_string = 1;
    }
    else {
        tmp_len_entry_number_padding_string = 0;
    }

    record_file_name_base = malloc(sizeof(char) * (strlen(lbx->meta->meta_file_name_base) + tmp_len_entry_number_padding_string + tmp_len_entry_number_string + 1));
    strcpy(record_file_name_base, lbx->meta->meta_file_name_base);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_file_name_base: %s\n", record_file_name_base);

    char * tmp_entry_number_string;

    tmp_entry_number_string = malloc(tmp_len_entry_number_string + 1);
    snprintf(tmp_entry_number_string, tmp_len_entry_number_string + 1, "%d", entry_number);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_entry_number_string: %s\n", tmp_entry_number_string);

    char * tmp_entry_number_padding_string;

    if (tmp_len_entry_number_string == 1) {
        strcat(record_file_name_base, "00");
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_file_name_base: %s\n", record_file_name_base);
    }
    if (tmp_len_entry_number_string == 2) {
        strcat(record_file_name_base, "0");
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_file_name_base: %s\n", record_file_name_base);
    }

    strcat(record_file_name_base, tmp_entry_number_string);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: record_file_name_base: %s\n", record_file_name_base);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_file_name_base()\n");
    return record_file_name_base;
}
