/*
 * Read/Load Header (ALL)
 * Read/Load Header - Preamble
 * Read/Load Header - Offset Table
 * Read/Load Header - String Table
 *
 * Read/Load LBX Entry, by Entry Number (LBX File Name, LBX Entry Number)
 * Read/Load LBX Entry, by Name (LBX File Name, LBX Entry Name)
 *
 * Populate LBX File Information
 *
 * Process Single File
 * Process Multiple Files
 *
 */

/*
 * read_lbx_via_file_name()
 * read_lbx_via_file_stream_pointer()
 * read_lbx_via_byte_buffer()
 * void read_lbx(FILE *fp, int sig_read)
 * void read_lbx(char *file_name)
 * */

#include <malloc.h>         /* malloc(), realloc(); */
#include <stdio.h>          /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <stdint.h>         /* ? */
#include <stdlib.h>         /* itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#ifdef _WIN32
#include <direct.h>
#include <unistd.h>
#include <sys/stat.h>
/* #define stat _stat */
#elif defined __linux__
#include <sys/types.h>
#include <sys/stat.h>
#endif

/* #include "../../Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/i686-w64-mingw32/include/stdlib.h" */
#include <limits.h> /* INT_MAX, INT_MIN */
#include <errno.h> /* errno() */
#include <sys/stat.h>

// #include "lbx.h"
// #include "lbx_meta.h"
// #include "lib_lbx_types.h"
#include "lib_lbx.h"
#include "lib_lbx_util.h"

int LBX_DEBUG_MODE = 0;
int LBX_DEBUG_VERBOSE_MODE = 0;
int LBX_DEBUG_STRUGGLE_MODE = 0;
int LBX_DEBUG_LEVEL = 0;
int lbx_debug_mode = 0;
int lbx_debug_verbose_mode = 0;
int lbx_debug_struggle_mode = 0;


void set_debug_mode(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: set_debug_mode()\n");

    lbx_debug_mode = 1;

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: set_debug_mode()\n");
}

void set_debug_verbose_mode(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: set_debug_verbose_mode()\n");

    lbx_debug_verbose_mode = 1;

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: set_debug_verbose_mode()\n");
}

void set_debug_struggle_mode(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: set_debug_verbose_mode()\n");

    lbx_debug_struggle_mode = 1;

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: set_debug_verbose_mode()\n");
}

/* Creation and Destruction. */
LBX_DATA * create_lbx_data(char * file_path)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: create_lbx_data()\n");

    LBX_DATA * lbx;
    lbx = malloc(sizeof(LBX_DATA));
    lbx->header = malloc(sizeof(LBX_HEADER));
    lbx->header->offset_table = malloc(sizeof(LBX_HEADER_OFFSET_TABLE));
    lbx->header->string_table = malloc(sizeof(LBX_HEADER_STRING_TABLE));

    lbx->meta = malloc(sizeof(LBX_META_DATA));
    lbx->meta->records = malloc(sizeof(LBX_RECORD_META_DATA));

    if (LBX_DEBUG_MODE == 1)
    {
        set_debug_mode(lbx);
    }
    if (LBX_DEBUG_VERBOSE_MODE == 1)
    {
        set_debug_verbose_mode(lbx);
    }
    if (LBX_DEBUG_STRUGGLE_MODE == 1)
    {
        set_debug_struggle_mode(lbx);
    }

    lbx->file_path = malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(lbx->file_path, file_path);
    lbx->meta->meta_file_path = malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(lbx->meta->meta_file_path, file_path);

    lbx_open_file(lbx);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: create_lbx_data()\n");
    return lbx;
}

void destroy_lbx_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: destroy_lbx_data()\n");

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_close_file(lbx)\n");
    lbx_close_file(lbx);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->file_path)\n");
    free(lbx->file_path);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->meta->records)\n");
    free(lbx->meta->records);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->meta)\n");
    free(lbx->meta);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->header->string_table)\n");
    free(lbx->header->string_table);
    /* TODO(JWB): figure out why freeing the offset table is causing it to crash (?only in run-debug?) */
    /*
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->header->offset_table)\n");
    free(lbx->header->offset_table);
    */
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->header)\n");
    free(lbx->header);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx)\n");
    free(lbx);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: destroy_lbx_data()\n");
}

void lbx_open_file(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: lbx_open_file()\n");

    lbx->file_stream = fopen(lbx->file_path, "rb");

    if (lbx->file_stream == NULL) {
        printf("FAILURE: Error opening file: %s\n", lbx->file_path);
        exit(EXIT_FAILURE);
    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: lbx_open_file()\n");
}

void lbx_close_file(LBX_DATA * lbx)
{
    fclose(lbx->file_stream);
}

void lbx_load_header(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: lbx_load_header()\n");

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: Declare Variables\n");

    size_t tmp_pos;
    uint32_t tmp_offset;
    int itr_lbx_offset_table;
    int itr_lbx_string_table;
    int tmp_string_table_length;

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: Declare Variables\n");

    tmp_pos = ftell(lbx->file_stream);

    fseek(lbx->file_stream, LBX_OFFSET_TO_HEADER_PREAMBLE, SEEK_SET);

    /*#################################**
    **###     Header - Preamble     ###**
    **#################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - Preamble\n");

    lbx->header->entry_count = lbx_read_2byte_le(lbx->file_stream);
    lbx->header->magic = lbx_read_2byte_le(lbx->file_stream);
    lbx->header->unknown = lbx_read_2byte_le(lbx->file_stream);
    lbx->header->type = lbx_read_2byte_le(lbx->file_stream);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->entry_count: %d\n", lbx->header->entry_count);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->magic: %d\n", lbx->header->magic);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->reserved: %d\n", lbx->header->unknown);
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: lbx->header->preamble->type: %d\n", lbx->header->type);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - Preamble\n");

    /*#####################################**
    **###     Header - Offset Table     ###**
    **#####################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - Offset Table\n");

    /* TODO(JWB): fix the "125 + 1" entry count; add MAX or memset('\0') or ? */
    for (itr_lbx_offset_table = 0; itr_lbx_offset_table < LBX_OFFSET_TABLE_MAXIMUM; itr_lbx_offset_table++)
    {
        tmp_offset = lbx_read_4byte_le(lbx->file_stream);
        lbx->header->offset_table->entry[itr_lbx_offset_table].begin = tmp_offset;
    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - Offset Table\n");

    /*#####################################**
    **###     Header - String Table     ###**
    **#####################################*/

    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: Header - String Table\n");

    /* TODO(JWB): fix the nonsense here with the in-line flags and calculations */

    lbx->meta->header_length_total = lbx->header->offset_table->entry[0].begin;

    lbx->meta->header_padding_length_total = lbx->meta->header_length_total - LBX_LENGTH_HEADER_DEFAULT;

    if (lbx->meta->header_length_total > LBX_LENGTH_HEADER_DEFAULT)
    {
        lbx->meta->has_string_table = 1;
        tmp_string_table_length = lbx->header->entry_count * LBX_LENGTH_STRING_TABLE_ENTRY;

        if (lbx->meta->header_padding_length_total > tmp_string_table_length)
        {
            lbx->meta->equal_header_padding_length_string_table_length = 0;
            lbx->meta->string_table_length = tmp_string_table_length;
        }
        else
        {
            lbx->meta->equal_header_padding_length_string_table_length = 1;
            lbx->meta->string_table_length = lbx->meta->header_length_total - LBX_LENGTH_HEADER_DEFAULT;
        }

        lbx->meta->string_table_entry_count = lbx->meta->string_table_length / LBX_LENGTH_STRING_TABLE_ENTRY;

        lbx->meta->header_length_used = LBX_LENGTH_HEADER_DEFAULT + lbx->meta->string_table_length;

        lbx->meta->header_padding_length = lbx->meta->header_length_total - LBX_LENGTH_HEADER_DEFAULT - lbx->meta->string_table_length;

        lbx->meta->header_padding_length_used = lbx->meta->header_padding_length;

        for (itr_lbx_string_table = 0; itr_lbx_string_table < lbx->meta->string_table_entry_count; itr_lbx_string_table++)
        {
            /* TODO(JWB): add specific functions to handle reading the string table name and description (maybe read 32, split 9 & 23) */
            /* TODO(JWB): fix-up up the erroneous null-terminator in the string table names e.g., {'T','E','S','T','\0','F','L','C','\0'} */
            fread(lbx->header->string_table->entry[itr_lbx_string_table].name, LBX_LENGTH_STRING_TABLE_ENTRY_NAME, 1, lbx->file_stream);
            fread(lbx->header->string_table->entry[itr_lbx_string_table].description, LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION, 1, lbx->file_stream);
        }
    }
    else
    {
        lbx->meta->has_string_table = 0;
        lbx->meta->string_table_length = 0;
        lbx->meta->string_table_entry_count = 0;
        lbx->meta->header_padding_length = (int)lbx->header->offset_table->entry[0].begin - LBX_LENGTH_HEADER_DEFAULT;

        lbx->meta->header_length_used = lbx->meta->header_length_total;

        lbx->meta->header_padding_length_used = lbx->meta->header_padding_length_total;
    }

    lbx->meta->header_length = lbx->meta->header_length_used;
    lbx->meta->header_padding_length = lbx->meta->header_padding_length_used;

    if (LBX_DEBUG_MODE) printf("DEBUG: END: Header - String Table\n");

    fseek(lbx->file_stream, tmp_pos, SEEK_SET);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_header()\n");
}
