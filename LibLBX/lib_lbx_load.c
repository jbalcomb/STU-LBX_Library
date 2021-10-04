#include <stdio.h>
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_load.h"
#include "lbx.h"
#include "lib_lbx_util.h"   /* liblbx_read_2byte_le(), liblbx_read_4byte_le(); */
#include "lib_lbx_load_header.h"
#include "lib_lbx_record.h"

void liblbx_load_lbx_from_file_path(LBX_DATA * lbx, char * file_path)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_from_file_path()\n");

    lbx->file->file_stream = fopen(file_path, "rb");

    if (lbx->file->file_stream == NULL) {
        printf("FAILURE: Error opening file: %s\n", lbx->file->file_path);
        exit(EXIT_FAILURE);
    }

    /* lbx = create_lbx_data(); */

    liblbx_load_lbx(lbx);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_from_file_path()\n");
}

void liblbx_load_lbx_from_file_handle(LBX_DATA * lbx, FILE * file_handle)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_from_file_handle()\n");

    /* lbx = create_lbx_data(); */

    liblbx_load_lbx(lbx);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_from_file_handle()\n");
}

/*
 * LBX Structure contains FILE Structure which contains File Path and FILE Handle
 * FILE Structure contains File Path and FILE Handle
 * MUST populate File Name, Directory Path, and File Name Base
 */
void liblbx_load_lbx(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx()\n");

    lbx_uint32 tmp_offset;
    int itr_lbx_offset_table;
    int itr_lbx_string_table;
    int tmp_header_length_total;
    int tmp_string_table_length;
    int tmp_string_table_entry_count;
    lbx_uint32 tmp_offset_begin;
    lbx_uint32 tmp_offset_end;
    lbx_uint32 tmp_data_offset;
    lbx_uint32 tmp_record_size;
    int itr_entry_index;


    liblbx_directory_path_and_file_name(lbx);
    liblbx_file_name_base(lbx);



    liblbx_load_lbx_file_header_from_lbx_data_file_handle(lbx);



    /*#####################################**
    **###     Record Data               ###**
    **#####################################*/

    /*
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record_buffer_array = malloc(sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);\n");
    lbx->record_buffer_array = malloc(sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);
    if (lbx->record_buffer_array == NULL)
    {
        printf("FAILURE: lbx->record_buffer_array = malloc(%u);\n", sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record_buffer_array = malloc(sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);\n");
    */

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        lbx->record->entry[itr_entry_index].record_file_name_base = get_record_file_name_base(lbx, itr_entry_index);

        tmp_record_size = lbx->header->offset_table->entry[itr_entry_index + 1].begin - lbx->header->offset_table->entry[itr_entry_index].begin;

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(char) * tmp_record_size);\n");
        lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(char) * tmp_record_size);
        if (lbx->record->entry[itr_entry_index].record_buffer == NULL)
        {
            printf("FAILURE: lbx->record->entry[itr_entry_index].record_buffer = malloc(%u);\n", sizeof(char) * tmp_record_size);
            exit(EXIT_FAILURE);
        }
        else
        {
            g_MemoryAllocated = g_MemoryAllocated +  (sizeof(char) * tmp_record_size);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: g_MemoryAllocated: %X (%u)\n", g_MemoryAllocated, g_MemoryAllocated);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(char) * tmp_record_size);\n");

        fseek(lbx->file->file_stream, lbx->header->offset_table->entry[itr_entry_index].begin, SEEK_SET);

        fread(lbx->record->entry[itr_entry_index].record_buffer, tmp_record_size, 1, lbx->file->file_stream);

    }



    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx()\n");
}

void lbx_unload_lbx_file(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_unload_lbx_file()\n");

    int itr_entry_index;

    /*#####################################**
    **###     Record Data               ###**
    **#####################################*/

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: free(lbx->record_buffer_array[itr_record_data]);\n");
        if (lbx->record->entry[itr_entry_index].record_buffer)
        {
            free(lbx->record->entry[itr_entry_index].record_buffer);
            lbx->record->entry[itr_entry_index].record_buffer = NULL;
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: free(lbx->record_buffer_array[itr_record_data]);\n");
    }

    /*
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record_buffer_array = malloc(sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);\n");
    if (lbx->record_buffer_array)
    {
        free(lbx->record_buffer_array);
        lbx->record_buffer_array = NULL;
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record_buffer_array = malloc(sizeof(*lbx->record_buffer_array) * lbx->header->entry_count);\n");
    */

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_unload_lbx_file()\n");
}

unsigned char * liblbx_load_lbx_entry(char * lbx_file_path, int lbx_entry_index)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_entry()\n");

    char * lbx_file_name_base;
    int itr_lbx_file_name_base;
    unsigned int tmp_strlen_lbx_file_path;
    FILE * file_stream;
    lbx_uint16 entry_count;
    lbx_uint32 tmp_offset_begin;
    lbx_uint32 tmp_offset_end;
    lbx_uint32 tmp_data_offset;
    lbx_uint32 tmp_record_size;
    unsigned char * record_data;

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_file_path: %s\n", lbx_file_path);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_entry_index: %d\n", lbx_entry_index);

    tmp_strlen_lbx_file_path = strlen(lbx_file_path);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_strlen_lbx_file_path: %d\n", tmp_strlen_lbx_file_path);

    /*
    g_LbxFileName = realloc(g_LbxFileName, sizeof(lbx_file_path) + 1);
    strcpy(g_LbxFileName, lbx_file_path);
    */


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx_file_name_base = malloc(tmp_strlen_lbx_file_path);\n");
    lbx_file_name_base = malloc(tmp_strlen_lbx_file_path);
    if (lbx_file_name_base == NULL)
    {
        printf("FAILURE: lbx_file_name_base = malloc(%u);\n", tmp_strlen_lbx_file_path);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("SUCCESS: lbx_file_name_base = malloc(%u);\n", tmp_strlen_lbx_file_path);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx_file_name_base = malloc(tmp_strlen_lbx_file_path);\n");

    strcpy(lbx_file_name_base, lbx_file_path);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_file_name_base: %s\n", lbx_file_name_base);

    for (itr_lbx_file_name_base = 0; itr_lbx_file_name_base < tmp_strlen_lbx_file_path; itr_lbx_file_name_base++)
    {
        if (lbx_file_name_base[itr_lbx_file_name_base] == '.') {
            lbx_file_name_base[itr_lbx_file_name_base] = '\0';
            break;
        }
    }

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_file_name_base: %s\n", lbx_file_name_base);

    /*
    g_LbxFileNameBase = realloc(g_LbxFileNameBase,sizeof(lbx_file_name_base) + 1);
    strcpy(g_LbxFileNameBase, lbx_file_name_base);
    */

    /*
    g_LbxEntryNumber = lbx_entry_index;
    */
    file_stream = fopen(lbx_file_path, "rb");

    if (file_stream == NULL) {
        printf("FAILURE: Error opening file: %s\n", lbx_file_path);
        exit(EXIT_FAILURE);
    }

    /*
    g_LbxFileStream = file_stream;
    */

    /*fseek(file_stream, LBX_OFFSET_TO_HEADER_PREAMBLE, SEEK_SET);*/

    entry_count = liblbx_read_2byte_le(file_stream);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: entry_count: %d\n", entry_count);

    /*
    g_LbxEntryCount = entry_count;
    */
    unsigned int tmp_file_offset_to_offset_table;
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: LBX_OFFSET_TO_OFFSET_TABLE: %u\n", LBX_OFFSET_TO_OFFSET_TABLE);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: LBX_LENGTH_OFFSET_TABLE_ENTRY: %u\n", LBX_LENGTH_OFFSET_TABLE_ENTRY);
    tmp_file_offset_to_offset_table = ( LBX_OFFSET_TO_OFFSET_TABLE + ( lbx_entry_index * LBX_LENGTH_OFFSET_TABLE_ENTRY ) );
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_file_offset_to_offset_table: %u\n", tmp_file_offset_to_offset_table);

    fseek(file_stream, ( LBX_OFFSET_TO_OFFSET_TABLE + ( lbx_entry_index * LBX_LENGTH_OFFSET_TABLE_ENTRY ) ), SEEK_SET);

    tmp_offset_begin = liblbx_read_4byte_le(file_stream);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_offset_begin: %d (0x%04X)\n", tmp_offset_begin, tmp_offset_begin);

    tmp_offset_end = liblbx_read_4byte_le(file_stream);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_offset_end: %d (0x%04X)\n", tmp_offset_end, tmp_offset_end);

    tmp_record_size = tmp_offset_end - tmp_offset_begin;
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_record_size: %d\n", tmp_record_size);

    /*
    tmp_data_offset = tmp_offset_begin - (4 * lbx_entry_index) - 8;
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_data_offset: %d (0x%04X)\n", tmp_data_offset, tmp_data_offset);

    fseek(file_stream, tmp_data_offset, SEEK_SET);
    */

    fseek(file_stream, tmp_offset_begin, SEEK_SET);


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: record_data = malloc(tmp_record_size);\n");
    record_data = malloc(tmp_record_size);
    if (lbx_file_name_base == NULL)
    {
        printf("FAILURE: record_data = malloc(%u);\n", tmp_record_size);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("SUCCESS: record_data = malloc(%u);\n", tmp_record_size);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: record_data = malloc(tmp_record_size);\n");


    fread(record_data, sizeof(unsigned char), tmp_record_size, file_stream);

    fclose(file_stream);

    unsigned int itr_record_data;

    for (itr_record_data = 0; itr_record_data < 32; itr_record_data++)
    {
        printf("[%u] %u (0x%02X)\n", itr_record_data, record_data[itr_record_data], record_data[itr_record_data]);
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_entry()\n");

    return record_data;
}
