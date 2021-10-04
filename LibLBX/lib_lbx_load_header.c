#include <stdio.h>
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_load_header.h"
#include "lib_lbx.h"
#include "lbx.h"
#include "lib_lbx_util.h"   /* liblbx_read_2byte_le(), liblbx_read_4byte_le(); */

void liblbx_load_lbx_file_header_from_lbx_data_file_handle(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_file_header_from_lbx_data_file_handle()\n");

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
    int itr_record_data;


    /*
     * Fast API:
     *   "Let it Crash"
     * Safe API:
     * if FILE == NULL
     * if ftell() != 0
     */
    fseek(lbx->file->file_stream, LBX_OFFSET_TO_HEADER_PREAMBLE, SEEK_SET);


    /*#################################**
    **###     Header - Preamble     ###**
    **#################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - Preamble\n");

    lbx->header->entry_count = liblbx_read_2byte_le(lbx->file->file_stream);
    lbx->header->magic = liblbx_read_2byte_le(lbx->file->file_stream);
    lbx->header->unknown = liblbx_read_2byte_le(lbx->file->file_stream);
    lbx->header->type = liblbx_read_2byte_le(lbx->file->file_stream);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->entry_count: %d\n", lbx->header->entry_count);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->magic: %d\n", lbx->header->magic);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->reserved: %d\n", lbx->header->unknown);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->type: %d\n", lbx->header->type);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - Preamble\n");

    /*#####################################**
    **###     Header - Offset Table     ###**
    **#####################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - Offset Table\n");

    for (itr_lbx_offset_table = 0; itr_lbx_offset_table < LBX_OFFSET_TABLE_MAXIMUM; itr_lbx_offset_table++)
    {
        tmp_offset = liblbx_read_4byte_le(lbx->file->file_stream);
        lbx->header->offset_table->entry[itr_lbx_offset_table].begin = tmp_offset;
    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - Offset Table\n");

    /*#####################################**
    **###     Header - String Table     ###**
    **#####################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - String Table\n");

    tmp_header_length_total = lbx->header->offset_table->entry[0].begin;

    if (tmp_header_length_total > LBX_LENGTH_HEADER_DEFAULT)
    {
        tmp_string_table_length = tmp_header_length_total - LBX_LENGTH_HEADER_DEFAULT;

        tmp_string_table_entry_count = tmp_string_table_length / LBX_LENGTH_STRING_TABLE_ENTRY;

        for (itr_lbx_string_table = 0; itr_lbx_string_table < tmp_string_table_entry_count; itr_lbx_string_table++)
        {
            fread(lbx->header->string_table->entry[itr_lbx_string_table].name, LBX_LENGTH_STRING_TABLE_ENTRY_NAME, 1, lbx->file->file_stream);
            fread(lbx->header->string_table->entry[itr_lbx_string_table].description, LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION, 1, lbx->file->file_stream);
        }
    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - String Table\n");

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_file_header_from_lbx_data_file_handle()\n");
}
