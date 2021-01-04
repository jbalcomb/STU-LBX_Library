#ifndef LIB_LBX_H
#define LIB_LBX_H

#include "lbx.h"
#include "lbx_defs.h"
#include "lbx_meta.h"
#include "lbx_types.h"

extern int LBX_DEBUG_MODE;
extern int LBX_DEBUG_VERBOSE_MODE;
extern int LBX_DEBUG_STRUGGLE_MODE;
extern int LBX_DEBUG_LEVEL;
extern int lbx_debug_mode;
extern int lbx_debug_verbose_mode;
extern int lbx_debug_struggle_mode;

extern int LBX_EXPORT_MODE;
extern int LBX_EXPORT_CSV;
extern int LBX_EXPORT_BIN;
extern int LBX_EXPORT_C;
extern int LBX_EXPORT_HEX;


/* iso8601 */
#define ISO8601_STRING "0000-00-00T00:00:00Z"
#define ISO8601_FORMAT_STRING "%Y-%m-%dT%H:%M:%SZ"

/* SEE: stdlib.h */
#define MAX_PATH 260
#define MAX_DRIVE 3
#define MAX_DIR 256
#define MAX_FNAME 256
#define MAX_EXT 256

/* SEE: ????????.h */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* SEE: langinfo.h; inspired by YESSTR, NOSTR */
#define TRUE_STRING "TRUE"
#define FALSE_STRING "FALSE"


/* 2^32 = 4294967296 */
/* 2^31 = 2147483648 */
/* 0x7FFFFFFF = (1<<31)-1 = 2147483647 */
/* 11111111 11111111 11111111 11111111 */
/*       FF       FF       FF       FF */
/* 01111111 11111111 11111111 11111111 */
/*       7F       FF       FF       FF */
/* two's complement notation */
/* You can identify the counterpart of the positive number by inverting its all bits and adding 1.
 * Thus, the counterpart for the maximal integer is 0x80000001, however it is NOT the minimal number.
 * The minimal number in two's complement notation is 0x80000000 = -2147483648.
 * */
/* The number 2,147,483,647 (or hexadecimal 7FFFFFFF16) is the maximum positive value for a 32-bit signed binary integer in computing. */
/* The XDR standard defines signed integers as integer. A signed integer is a 32-bit datum that encodes an integer in the range [-2147483648 to 2147483647]. */
#define INT_32_MIN -2147483647                      /* 2^31 2147483648; 2^32 = 4294967296 */
#define INT_32_MAX +2147483647
#define INT_32_MAGIC -2147483648                      /* 2^31 2147483648; 2^32 = 4294967296 */



enum LBX_Type {
    LBX_TYPE_DEFAULT = 0,
    LBX_TYPE_UNKNOWN_1 = 1,
    LBX_TYPE_UNKNOWN_2 = 2,
    LBX_TYPE_UNKNOWN_3 = 3,
    LBX_TYPE_UNKNOWN_4 = 4,
    LBX_TYPE_UNKNOWN_5 = 5
};

/*
 * "Used for array indexes!  Don't change the numbers!" - SO-404231 <https://stackoverflow.com/a/404263>
 */
enum LBX_Record_Type {
    LBX_RECORD_TYPE_EMPTY = 0,          /* 0 bytes */
    LBX_RECORD_TYPE_ARRAY = 1,          /* <n> <recordsize> equals size */
    LBX_RECORD_TYPE_SOUND_XMIDI = 2,          /* 0xDEAF 0x0001 */
    LBX_RECORD_TYPE_SOUND_VOC = 3,            /* 0xDEAF 0x0002 */
    LBX_RECORD_TYPE_SOUND_UNKNOWN = 4,            /* 0xDEAF 0x???? */
    LBX_RECORD_TYPE_PALETTE = 5,        /* FONTS.LBX 2+ */
    LBX_RECORD_TYPE_IMAGES = 6,         /* <width> <height> = 3x3 (in MAIN.LBX) up to 320x200 */
    LBX_RECORD_TYPE_FONT = 7,           /* FONTS.LBX 0 */
    LBX_RECORD_TYPE_AIL_AIL_DRIVER = 8,  /* SNDDRV.LBX */
    LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER = 9,  /* SNDDRV.LBX */
    LBX_RECORD_TYPE_CUSTOM = 10,         /* Other (sound drivers, TERR*.LBX) */
    LBX_RECORD_TYPE_UNKNOWN = 11,
    LBX_RECORD_TYPE_COUNT
};

#ifndef LBX_RECORD_TYPE_INDEX
#define LBX_RECORD_TYPE_INDEX
/*
char LBX_Record_Type_Name[12][34] = {
        "LBX_RECORD_TYPE_EMPTY",
        "LBX_RECORD_TYPE_ARRAY",
        "LBX_RECORD_TYPE_SOUND_XMIDI",
        "LBX_RECORD_TYPE_SOUND_VOC",
        "LBX_RECORD_TYPE_SOUND_UNKNOWN",
        "LBX_RECORD_TYPE_PALETTE",
        "LBX_RECORD_TYPE_IMAGES",
        "LBX_RECORD_TYPE_FONT",
        "LBX_RECORD_TYPE_AIL_AIL_DRIVER",
        "LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER",
        "LBX_RECORD_TYPE_CUSTOM",
        "LBX_RECORD_TYPE_UNKNOWN"
};
*/
#endif /* LBX_RECORD_TYPE_INDEX */

enum LBX_Sound_Type {
    LBX_SOUND_TYPE_UNKNOWN = 0,
    LBX_SOUND_TYPE_XMIDI = 1,
    LBX_SOUND_TYPE_VOC = 2,
};



struct s_LBX_DATA {
    char * file_path;
    FILE * file_stream;
    LBX_HEADER * header;
    LBX_META_DATA * meta;
};
typedef struct s_LBX_DATA LBX_DATA;



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void set_debug_mode(LBX_DATA * lbx);
void set_debug_verbose_mode(LBX_DATA * lbx);

/* Creation and Destruction. */
/* LBX_DATA * create_lbx_data(); */
LBX_DATA * create_lbx_data(char * file_path);
void destroy_lbx_data(LBX_DATA* lbx);

/*
void lbx_open_file(LBX_DATA* lbx, char * file_path_and_name);
void lbx_init_io(LBX_DATA * lbx, FILE * ptrStreamFileIn);
void lbx_close_file(FILE * ptrStreamFileIn);
*/
void lbx_open_file(LBX_DATA * lbx);
void lbx_close_file(LBX_DATA * lbx);

void lbx_load_header(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif /* LIB_LBX_H */
