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
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), memset(), strcpy(), strncpy(), strlen(); */

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
#include "lbx_record_type_palette.h"  /* LBX_PALETTE */



char * font_file_name = "FONTS.LBX";
char * palette_file_name = "FONTS.LBX";
char * fonts_file_name = "FONTS.LBX";
char * palettes_file_name = "FONTS.LBX";
char * fonts_file_name_mom = "FONTS.LBX";
char * palettes_file_name_mom = "FONTS.LBX";
char * fonts_file_name_mom_131 = "FONTS.LBX";
char * palettes_file_name_mom_131 = "FONTS.LBX";
char * font_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\FONTS.LBX";
char * g_palette_file_path = "F:\\devel_data\\STU\\MoM131_LBX\\FONTS.LBX";

/* Global Variables for FONTS.LBX File */
FILE * g_FontsLbxFileStream;
unsigned char * g_FontsLbxFileBuffer;
lbx_uint32 g_FontsLbxFileBuffer_len;
char * g_FontsLbxFileName = "FONTS.LBX";
char * g_FontsLbxFileNameBase = "FONTS";
lbx_uint8 g_FontsLbxEntryNumber;
lbx_uint8 g_FontsLbxEntryCount = 9;
lbx_uint16 g_FontsLbxFileSize = 57536;
lbx_uint16 g_FontsLbxRecordSize;

/* Global Variables for Current LBX File */
FILE * g_LbxFileStream;
unsigned char * g_LbxFileBuffer;
char * g_LbxFileName;
char * g_LbxFileNameBase;
lbx_uint8 g_LbxEntryNumber;
lbx_uint8 g_LbxEntryCount;
lbx_uint16 g_LbxFileSize;
lbx_uint16 g_LbxRecordSize;

/* Global Variables for Current Font */

/* Global Variables for Current Palette */
LBX_PALETTE g_LbxPalette;
/* Global Variables for ALL LBX Files */

/* Global Variables for ALL LBX Entries */

/* Global Variables for ALL LBX Records */

/* Global Variables for ALL Fonts */

/* Global Variables for ALL Palettes */
char * g_PaletteNumberZero;
char * g_PaletteNumberOne;
char * g_PaletteNumberTwo;
char * g_PaletteNumberThree;
char * g_PaletteNumberFour;
char * g_PaletteNumberFive;
char * g_PaletteNumberSix;
char * g_PaletteNumberSeven;

/* Global Variables for Debug Mode Flags & Levels */
int LBX_DEBUG_MODE;
int LBX_DEBUG_VERBOSE_MODE;
int LBX_DEBUG_STRUGGLE_MODE;
int LBX_DEBUG_LEVEL;
int lbx_debug_mode;
int lbx_debug_verbose_mode;
int lbx_debug_struggle_mode;
/* TODO(JWB): figure out and fix the debug flags coming in from the client app */

/* Global Variables for Program Diagnostics */
unsigned int g_MemoryAllocated = 0;

int LBX_EXPORT_BMP;

/*
 * "Used for array indexes!  Don't change the numbers!" - SO-404231 <https://stackoverflow.com/a/404263>
 */
//enum LBX_Record_Type {
//    LBX_RECORD_TYPE_EMPTY = 0,          /* 0 bytes */
//    LBX_RECORD_TYPE_ARRAY = 1,          /* <n> <recordsize> equals size */
//    LBX_RECORD_TYPE_SOUND_XMIDI = 2,          /* 0xDEAF 0x0001 */
//    LBX_RECORD_TYPE_SOUND_VOC = 3,            /* 0xDEAF 0x0002 */
//    LBX_RECORD_TYPE_SOUND_UNKNOWN = 4,            /* 0xDEAF 0x???? */
//    LBX_RECORD_TYPE_PALETTE = 5,        /* FONTS.LBX 2+ */
//    /* LBX_RECORD_TYPE_IMAGE = 6,         / * <width> <height> = 3x3 (in MAIN.LBX) up to 320x200 * / */
//    LBX_RECORD_TYPE_FLIC = 6,
//    LBX_RECORD_TYPE_FONT = 7,           /* FONTS.LBX 0 */
//    LBX_RECORD_TYPE_AIL_AIL_DRIVER = 8,  /* SNDDRV.LBX */
//    LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER = 9,  /* SNDDRV.LBX */
//    LBX_RECORD_TYPE_CUSTOM = 10,         /* Other (sound drivers, TERR*.LBX) */
//    LBX_RECORD_TYPE_UNKNOWN = 11,
//    /* LBX_RECORD_TYPE_ANIMATION = 12, / * frame_raw/nFrames/frame_count > 0 i.e., not an Image (single-frame_raw animation) * / */
//    LBX_RECORD_TYPE_COUNT
//};
/* TODO(JWB): move this to where the RECORD_TYPE enum is */
//char l_LBX_Record_Type_Description[13][34] = {
//        "EMPTY",
//        "Array",
//        "XMIDI",
//        "VOC",
//        "Sound",
//        "Palette",
//        "Image",
//        "Font",
//        "AIL Driver",
//        "DIGPAK Driver",
//        "Custom",
//        "UNKNOWN",
//        "Animation"
//};
//#ifndef LBX_RECORD_TYPE_INDEX
//#define LBX_RECORD_TYPE_INDEX
///*
//char LBX_Record_Type_Name[12][34] = {
//        "LBX_RECORD_TYPE_EMPTY",
//        "LBX_RECORD_TYPE_ARRAY",
//        "LBX_RECORD_TYPE_SOUND_XMIDI",
//        "LBX_RECORD_TYPE_SOUND_VOC",
//        "LBX_RECORD_TYPE_SOUND_UNKNOWN",
//        "LBX_RECORD_TYPE_PALETTE",
//        "LBX_RECORD_TYPE_IMAGE",
//        "LBX_RECORD_TYPE_FONT",
//        "LBX_RECORD_TYPE_AIL_AIL_DRIVER",
//        "LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER",
//        "LBX_RECORD_TYPE_CUSTOM",
//        "LBX_RECORD_TYPE_UNKNOWN"
//};
//*/
//#endif /* LBX_RECORD_TYPE_INDEX */
char LBX_Record_Type_Description[13][34] = {
        "EMPTY",
        "Array",
        "XMIDI",
        "VOC",
        "Sound",
        "Palette",
        /* "image", */
        "FLIC",
        "Font",
        "AIL Driver",
        "DIGPAK Driver",
        "Custom",
        "UNKNOWN",
        /* "Animation", */
        "LBX_RECORD_TYPE_COUNT"
};

void lbx_set_debug_mode()
{
    lbx_debug_mode = 1;
    LBX_DEBUG_MODE = 1;
}

void lbx_set_debug_verbose_mode()
{
    lbx_debug_mode = 1;
    LBX_DEBUG_MODE = 1;
    lbx_debug_verbose_mode = 1;
    LBX_DEBUG_VERBOSE_MODE = 1;
}

void lbx_set_debug_struggle_mode()
{
    lbx_debug_mode = 1;
    LBX_DEBUG_MODE = 1;
    lbx_debug_verbose_mode = 1;
    LBX_DEBUG_VERBOSE_MODE = 1;
    lbx_debug_struggle_mode = 1;
    LBX_DEBUG_STRUGGLE_MODE = 1;
}

/* Creation and Destruction. */
LBX_DATA * create_lbx_data(char * file_path)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: create_lbx_data()\n");

    LBX_DATA * lbx;
    lbx = malloc(sizeof(LBX_DATA));
    lbx->file = malloc(sizeof(LBX_FILE_DATA));
    lbx->record = malloc(sizeof(LBX_RECORD_DATA));

    lbx->header = malloc(sizeof(LBX_HEADER));
    lbx->header->offset_table = malloc(sizeof(LBX_HEADER_OFFSET_TABLE));
    lbx->header->string_table = malloc(sizeof(LBX_HEADER_STRING_TABLE));

    lbx->meta = malloc(sizeof(LBX_META_DATA));
    lbx->meta->records = malloc(sizeof(LBX_RECORD_META_DATA));

    if (LBX_DEBUG_MODE == 1)
    {
        lbx_set_debug_mode();
    }
    if (LBX_DEBUG_VERBOSE_MODE == 1)
    {
        lbx_set_debug_verbose_mode();
    }
    if (LBX_DEBUG_STRUGGLE_MODE == 1)
    {
        lbx_set_debug_struggle_mode();
    }

    lbx->file->file_path = malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(lbx->file->file_path, file_path);

    liblbx_open_file(lbx);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: create_lbx_data()\n");
    return lbx;
}

void destroy_lbx_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: destroy_lbx_data()\n");

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: liblbx_close_file(lbx)\n");
    liblbx_close_file(lbx);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->file_path)\n");
    free(lbx->file->file_path);

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

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->record)\n");
    free(lbx->record);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx->file)\n");
    free(lbx->file);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: free(lbx)\n");
    free(lbx);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: destroy_lbx_data()\n");
}

void liblbx_open_file(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: liblbx_open_file()\n");

    lbx->file->file_stream = fopen(lbx->file->file_path, "rb");

    if (lbx->file->file_stream == NULL) {
        printf("FAILURE: Error opening file: %s\n", lbx->file->file_path);
        exit(EXIT_FAILURE);
    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: liblbx_open_file()\n");
}

void liblbx_close_file(LBX_DATA * lbx)
{
    fclose(lbx->file->file_stream);
}

void lbx_load_header(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: lbx_load_header()\n");

    size_t tmp_pos;
    uint32_t tmp_offset;
    int itr_lbx_offset_table;
    int itr_lbx_string_table;
    int tmp_string_table_length;


    tmp_pos = ftell(lbx->file->file_stream);

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

    /* TODO(JWB): fix the "125 + 1" entry count; add MAX or memset('\0') or ? */
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
            fread(lbx->header->string_table->entry[itr_lbx_string_table].name, LBX_LENGTH_STRING_TABLE_ENTRY_NAME, 1, lbx->file->file_stream);
            fread(lbx->header->string_table->entry[itr_lbx_string_table].description, LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION, 1, lbx->file->file_stream);
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

    fseek(lbx->file->file_stream, tmp_pos, SEEK_SET);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_header()\n");
}
