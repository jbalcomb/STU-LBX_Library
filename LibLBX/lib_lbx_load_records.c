#include <stdio.h>
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_load_records.h"
#include "lbx.h"
#include "lib_lbx.h"
#include "lib_lbx_util.h"   /* liblbx_read_2byte_le(), liblbx_read_4byte_le(); */
#include "lib_lbx_load.h"
#include "lib_lbx_load_header.h"
#include "lib_lbx_record.h"
#include "lib_lbx_record_type.h"        /* get_record_type(); */



void liblbx_populate_lbx_record_file_name_base(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_populate_lbx_record_file_name_base()\n");

    int itr_entry_index;
    char * tmp_entry_number_string;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        /*lbx->record->entry[itr_entry_index].tmp_record_file_name_base = get_record_file_name_base(lbx, itr_entry_index);*/

        tmp_entry_number_string = liblbx_convert_entry_index_to_string(itr_entry_index, LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_entry_number_string: %s\n", tmp_entry_number_string);


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].record_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT + 1));\n");
        lbx->record->entry[itr_entry_index].record_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT + 1));
        if (lbx->record->entry[itr_entry_index].record_file_name_base == NULL)
        {
            printf("FAILURE: lbx->record->entry[itr_entry_index].record_file_name_base = malloc(%u);\n", sizeof(char) * (strlen(lbx->file->file_name_base) + LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT + 1));
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].record_file_name_base = malloc(sizeof(char) * (strlen(lbx->file->file_name_base) + LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT + 1));\n");


        strcpy(lbx->record->entry[itr_entry_index].record_file_name_base, lbx->file->file_name_base);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[itr_entry_index].record_file_name_base: %s\n", lbx->record->entry[itr_entry_index].record_file_name_base);

        strcat(lbx->record->entry[itr_entry_index].record_file_name_base, tmp_entry_number_string);
        if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->record->entry[itr_entry_index].record_file_name_base: %s\n", lbx->record->entry[itr_entry_index].record_file_name_base);

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_populate_lbx_record_file_name_base()\n");
}

void liblbx_populate_lbx_record_type(LBX_DATA * lbx)
{
    int itr_entry_index;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {
        /*lbx->record->entry[itr_entry_index].type = get_record_type(lbx, itr_entry_index);*/
        lbx->record->entry[itr_entry_index].type = liblbx_deduce_lbx_record_type(lbx, lbx->record->entry[itr_entry_index].record_buffer, lbx->record->entry[itr_entry_index].size, lbx->file->file_name, itr_entry_index);

    }

}

/*!
 *
 * @param lbx
 */
void liblbx_load_lbx_record_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_record_data()\n");

    int itr_entry_index;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {

        lbx->record->entry[itr_entry_index].size = lbx->header->offset_table->entry[itr_entry_index + 1].begin - lbx->header->offset_table->entry[itr_entry_index].begin;

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(char) * tmp_record_size);\n");
        lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(unsigned char) * lbx->record->entry[itr_entry_index].size);
        if (lbx->record->entry[itr_entry_index].record_buffer == NULL)
        {
            printf("FAILURE: lbx->record->entry[itr_entry_index].record_buffer = malloc(%u);\n", sizeof(unsigned char) * lbx->record->entry[itr_entry_index].size);
            exit(EXIT_FAILURE);
        }
        else
        {
            g_MemoryAllocated = g_MemoryAllocated + (sizeof(unsigned char) * lbx->record->entry[itr_entry_index].size);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: g_MemoryAllocated: %X (%u)\n", g_MemoryAllocated, g_MemoryAllocated);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[itr_entry_index].record_buffer = malloc(sizeof(char) * tmp_record_size);\n");

        fseek(lbx->file->file_stream, lbx->header->offset_table->entry[itr_entry_index].begin, SEEK_SET);

        fread(lbx->record->entry[itr_entry_index].record_buffer, sizeof(unsigned char), lbx->record->entry[itr_entry_index].size, lbx->file->file_stream);

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_record_data()\n");
}
