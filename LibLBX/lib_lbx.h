#ifndef LIB_LBX_H
#define LIB_LBX_H

#include <stdio.h>

#include "lbx.h"
#include "lbx_defs.h"
#include "lbx_meta.h"
#include "lbx_types.h"  /* lbx_uint8, lbx_uint16, lbx_uint32 */
#include "lbx_record_type_palette.h"  /* LBX_PALETTE */



/*
 * http://ensembles-eu.metoffice.com/met-res/aries/technical/GSPC_UDF.PDF
 * The SSFTC Structure (Subfile Offset Pointers Directory). ...
 * http://www.ggu.ac.in/download/Model%20Answer%20Dec%2013/AgniveshPandeyBtechVII-MultimediaSystemDesign4.12.13.pdf
 * are known as a TIFF subfile. There is no limit to the number of subfiles a TIFF image file ... DWORD IFDOffset; / * Offset of the first Image File Directory * /.
 */

/*
 * Bumped into this while figuring out the LBX_IMG to BMP conversion, around 20210224.
 * It seems a novel approach and more deterministic than the current LBX_RECORD_TYPE deduction /algorithm/.
 * TODO(JWB): research, decide, and code /composite/ header for various LBX_RECORD_TYPE's
 */
/* J:\STU-EduMat\_FileFormats\Encyclopedia of Graphics File Formats\EncyclopediaOfGraphicsFileFormatsCompanionCd-rom\GFF_CD\FORMATS\MSBMP\CODE\BMP_CODE.TXT */
/*
 * / *
 * ** Composite structure of the BMP image file format.
 * **
 * ** This structure holds information for all three flavors of the BMP format.
 * * /
 * typedef struct _BmpHeader
 * {
 *     BMPINFO      Header;        / * Bitmap Header                * /
 *     PMINFOHEAD   PmInfo;        / * OS/2 1.x Information Header  * /
 *     PMRGBTRIPLE *PmColorTable;  / * OS/2 1.x Color Table         * /
 *     WININFOHEAD  WinInfo;       / * Windows 3 Information Header * /
 *     WINRGBQUAD  *WinColorTable; / * Windows 3 Color Table        * /
 *     PM2INFOHEAD  Pm2Info;       / * OS/2 2.0 Information Header  * /
 *     PM2RGBQUAD  *Pm2ColorTable; / * OS/2 2.0 Color Table         * /
 * } BMPHEADER;
 */


//#define FONTS_FILE_NAME "FONTS.LBX"
//#define PALETTES_FILE_NAME "FONTS.LBX"
//char * fonts_file_name = "FONTS.LBX";
//char * palettes_file_name = "FONTS.LBX";
extern char * font_file_name;
extern char * palette_file_name;
extern char * fonts_file_name;
extern char * palettes_file_name;
extern char * fonts_file_name_mom;
extern char * palettes_file_name_mom;
extern char * fonts_file_name_mom_131;
extern char * palettes_file_name_mom_131;
extern char * font_file_path;
extern char * g_palette_file_path;


/* Global Variables for FONTS.LBX File */
extern FILE * g_FontsLbxFileStream;
extern unsigned char * g_FontsLbxFileBuffer;
extern lbx_uint32 g_FontsLbxFileBuffer_len;
extern char * g_FontsLbxFileName;
extern char * g_FontsLbxFileNameBase;
extern lbx_uint8 g_FontsLbxEntryNumber;
extern lbx_uint8 g_FontsLbxEntryCount;
extern lbx_uint16 g_FontsLbxFileSize;
extern lbx_uint16 g_FontsLbxRecordSize;

/* Global Variables for Current LBX File */
extern FILE * g_LbxFileStream;
extern char * g_LbxFileName;
extern char * g_LbxFileNameBase;
extern lbx_uint8 g_LbxEntryNumber;
extern lbx_uint8 g_LbxEntryCount;
extern lbx_uint16 g_LbxFileSize;
extern lbx_uint16 g_LbxRecordSize;
extern unsigned char * g_LbxFileBuffer;
/* Global Variables for Current Font */

/* Global Variables for Current Palette */
extern LBX_PALETTE g_LbxPalette;

/* Global Variables for ALL LBX Files */

/* Global Variables for ALL LBX Entries */

/* Global Variables for ALL LBX Records */

/* Global Variables for ALL Fonts */

/* Global Variables for ALL Palettes */
extern char * g_PaletteNumberZero;
extern char * g_PaletteNumberOne;
extern char * g_PaletteNumberTwo;
extern char * g_PaletteNumberThree;
extern char * g_PaletteNumberFour;
extern char * g_PaletteNumberFive;
extern char * g_PaletteNumberSix;
extern char * g_PaletteNumberSeven;

/* Global Variables for Debug Mode Flags & Levels */
extern int LBX_DEBUG_MODE;
extern int LBX_DEBUG_VERBOSE_MODE;
extern int LBX_DEBUG_STRUGGLE_MODE;
extern int LBX_DEBUG_LEVEL;
extern int lbx_debug_mode;
extern int lbx_debug_verbose_mode;
extern int lbx_debug_struggle_mode;

/* Global Variables for Program Diagnostics */
extern unsigned int g_MemoryAllocated;



extern int LBX_EXPORT_MODE;
extern int LBX_EXPORT_GRAPHICS;
extern int LBX_EXPORT_SOUNDS;
extern int LBX_EXPORT_ANIMATION;
extern int LBX_EXPORT_IMAGE;
extern int LBX_EXPORT_MUSIC;
extern int LBX_EXPORT_SOUNDFX;
extern int LBX_EXPORT_BIN;
extern int LBX_EXPORT_C;
extern int LBX_EXPORT_HEX;
extern int LBX_EXPORT_BMP;
extern int LBX_EXPORT_FLI;
extern int LBX_EXPORT_FLC;
extern int LBX_EXPORT_GIF;
extern int LBX_EXPORT_PNG;
extern int LBX_EXPORT_COL;
extern int LBX_EXPORT_PAL;
extern int LBX_EXPORT_FNT;
extern int LBX_EXPORT_MID;
extern int LBX_EXPORT_VOC;
extern int LBX_EXPORT_WAV;
extern int LBX_EXPORT_XMI;

extern char * ptrPaletteNumberZero;
extern char * ptrPaletteNumberOne;
extern char * ptrPaletteNumberTwo;


/* iso8601 */
#define ISO8601_STRING "0000-00-00T00:00:00Z"
#define ISO8601_FORMAT_STRING "%Y-%m-%dT%H:%M:%SZ"

#define LBX_ENTRY_INDEX_STRING_LENGTH_DEFAULT 3

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
    /* LBX_RECORD_TYPE_IMAGE = 6,         / * <width> <height> = 3x3 (in MAIN.LBX) up to 320x200 * / */
    LBX_RECORD_TYPE_FLIC = 6,
    LBX_RECORD_TYPE_FONT = 7,           /* FONTS.LBX 0 */
    LBX_RECORD_TYPE_AIL_AIL_DRIVER = 8,  /* SNDDRV.LBX */
    LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER = 9,  /* SNDDRV.LBX */
    LBX_RECORD_TYPE_CUSTOM = 10,         /* Other (sound drivers, TERR*.LBX) */
    LBX_RECORD_TYPE_UNKNOWN = 11,
    /* LBX_RECORD_TYPE_ANIMATION = 12, / * frame_raw/nFrames/frame_count > 0 i.e., not an Image (single-frame_raw animation) * / */
    LBX_RECORD_TYPE_COUNT
};
// enum LBX_Record_Type;
extern char LBX_Record_Type_Description[13][34];


enum LBX_Sounds_Type {
    LBX_SOUNDS_TYPE_UNKNOWN = 0,
    LBX_SOUNDS_TYPE_XMIDI = 1,
    LBX_SOUNDS_TYPE_VOC = 2,
};

enum LBX_Graphics_Type {
    LBX_GRAPHICS_TYPE_UNKNOWN = 0,
    LBX_GRAPHICS_TYPE_IMAGE = 1,
    LBX_GRAPHICS_TYPE_ANIMATION = 2,
};


/* Composite structure of the LBX subfile format - Optional Headers for various LBX Record Types */
struct s_LBX_RECORD_HEADER {
    LBX_FLIC_RECORD_HEADER * flic;
    lbx_uint8 have_loaded_flic_header;

};
typedef struct s_LBX_RECORD_HEADER LBX_RECORD_HEADER;

struct s_LBX_RECORD_DATA_ENTRY {
    int type;
    lbx_uint32 size;
    char * record_file_name_base;                                       // e.g., MAIN.LBX, 64 = MAIN064
    unsigned char * record_buffer;
    LBX_RECORD_HEADER * headers;
};
typedef struct s_LBX_RECORD_DATA_ENTRY LBX_RECORD_DATA_ENTRY;

struct s_LBX_RECORD_DATA {
    LBX_RECORD_DATA_ENTRY entry[LBX_ENTRY_COUNT_MAXIMUM];
};
typedef struct s_LBX_RECORD_DATA LBX_RECORD_DATA;

struct s_LBX_FILE_DATA {
    FILE * file_stream;
    char * file_path;
    char * directory_path;
    char * file_name;
    char * file_name_base;
};
typedef struct s_LBX_FILE_DATA LBX_FILE_DATA;

struct s_LBX_DATA {
    /*char * file_path;*/
    /*FILE * file_stream;*/
    LBX_FILE_DATA * file;
    LBX_RECORD_DATA * record;
    LBX_HEADER * header;
    LBX_META_DATA * meta;
};
typedef struct s_LBX_DATA LBX_DATA;

struct s_LBX {
    LBX_HEADER * header;
    LBX_RECORD_DATA * record;
};
typedef struct s_LBX LBX;

struct s_LIBLBX {
    LBX_FILE_DATA * file;
    LBX * lbx;
    LBX_META_DATA * meta;
};
typedef struct s_LIBLBX LIBLBX;


/*
 * Function Prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void lbx_set_debug_mode();
void lbx_set_debug_verbose_mode();
void lbx_set_debug_struggle_mode();

/* Creation and Destruction. */
/* LBX_DATA * create_lbx_data(); */
LBX_DATA * create_lbx_data(char * file_path);
void destroy_lbx_data(LBX_DATA* lbx);

/*
void liblbx_open_file(LBX_DATA* lbx, char * file_path_and_name);
void lbx_init_io(LBX_DATA * lbx, FILE * ptrStreamFileIn);
void liblbx_close_file(FILE * ptrStreamFileIn);
*/
void liblbx_open_file(LBX_DATA * lbx);
void liblbx_close_file(LBX_DATA * lbx);

void lbx_load_header(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif /* LIB_LBX_H */
