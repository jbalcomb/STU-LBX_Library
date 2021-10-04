#ifndef LBX_RECORD_TYPE_PALETTE_H
#define LBX_RECORD_TYPE_PALETTE_H

#include "lbx_types.h"

/* These should probably ref the unadulterated src:
 * ---J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro---
 * F:\Development_OPC\Animator-Pro__original_source */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\inc\cmap.h */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\pjhigh\colload.c */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\rastlib\cmapshif.c */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\pjhigh\palread.c */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\fli\readcolo.c */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\inc\fli.h */
/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\inc\stdtypes.h */

// /* BYTE, UBYTE, etc is to keep code portable between different compilers
//   where especially 'int' can mean different things. */
//typedef  int8_t      AA_BYTE;
//typedef uint8_t     AA_UBYTE;
//typedef  int16_t     AA_SHORT;
//typedef uint16_t    AA_USHORT;
//typedef  int32_t     AA_LONG;
//typedef uint32_t    AA_ULONG;
//typedef double      AA_FLOAT;
//typedef AA_UBYTE *     AA_PTR;

/* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\STDTYPES.H */
/* BYTE, UBYTE, etc is to keep code portable between different compilers
   where especially 'int' can mean different things. */
typedef signed char 	AA_BYTE;
typedef unsigned char	AA_UBYTE;
typedef signed short	AA_SHORT;
typedef unsigned short	AA_USHORT;
typedef signed long 	AA_LONG;
typedef unsigned long	AA_ULONG;
typedef double			AA_FLOAT;
typedef AA_UBYTE		   *AA_PTR;


#define AA_COLORS 256
#define AA_RGB_MAX 256

typedef struct AA_rgb3 {
    AA_UBYTE r,g,b;
} AA_Rgb3;
/*STATIC_ASSERT(cmap, sizeof(Rgb3) == 3);*/

typedef struct AA_cmap {
    AA_LONG num_colors;
    AA_Rgb3 ctab[AA_COLORS];
} AA_Cmap;

/*
Palette Files (.COL)
    A color file is just a binary image of the color palette.
    It consists of 768 bytes - 3 bytes for each color.
    Each byte has a value from 0 to 63.
    The red byte comes first, then the green, then the blue.
*/


/* VM: Win98SE_Dev; C:\devel\MoM-IME\LBXtract\LBXClasses.pas */
/*
{==========================================================================
|
| Constant    : Various
| Description : Special source colour values, as above
|
=========================================================================}
SHADOW_COLOUR = $B4A0A0;
FLAG_COLOURS: Array [1..3] of Cardinal = ($00BC00, $00A400, $007C00);

{==========================================================================
|
| Constant    : Various
| Description : Special destination colour values
|
=========================================================================}
REPLACEMENT_FLAG_COLOURS: Array [1..3] of Cardinal = ($FFFFFF, $E6E6E6, $BEBEBE);
 */

#define TRANSPARENT_COLOR_MAP_INDEX = 0;

/*typedef lbx_uint8 * LBX_PALETTE;*/
typedef lbx_uint8 LBX_PALETTE;
#define LBX_PALETTE_SIZE 768

/*
typedef unsigned int RGB;  / * RGB triplet * /

struct s_LBX_PALETTE_ENTRY
{
    lbx_uint8 Red;
    lbx_uint8 Green;
    lbx_uint8 Blue;
};
typedef struct s_LBX_PALETTE_ENTRY LBX_PALETTE_ENTRY;

LBX_PALETTE_ENTRY RGB_BLACK = {0x00,0x00,0x00};
LBX_PALETTE_ENTRY RGB_WHITE = {0xFF,0xFF,0x0FF};

struct s_LBX_PALETTE
{
    LBX_PALETTE_ENTRY lbx_palette[255];
};
typedef struct s_LBX_PALETTE LBX_PALETTE;
*/

#define DEFAULT_GAME_PALETTE_NUMBER 3
typedef enum {
    PALETTE_0,           /* FONTS.LBX, Entry 2 */
    PALETTE_1,           /* FONTS.LBX, Entry 3 */
    PALETTE_2,           /* FONTS.LBX, Entry 4 */
    PALETTE_3,           /* FONTS.LBX, Entry 5 */
    PALETTE_4,           /* FONTS.LBX, Entry 6 */
    PALETTE_5,           /* FONTS.LBX, Entry 7 */
    PALETTE_6,           /* FONTS.LBX, Entry 8 */
    ENUMEND_PALETTE_ID
} palette_id;
typedef enum {
    PALETTE_NUMBER_1,           /* FONTS.LBX, Entry 2 */
    PALETTE_NUMBER_2,           /* FONTS.LBX, Entry 3 */
    PALETTE_NUMBER_3,           /* FONTS.LBX, Entry 4 */
    PALETTE_NUMBER_4,           /* FONTS.LBX, Entry 5 */
    PALETTE_NUMBER_5,           /* FONTS.LBX, Entry 6 */
    PALETTE_NUMBER_6,           /* FONTS.LBX, Entry 7 */
    PALETTE_NUMBER_7,           /* FONTS.LBX, Entry 8 */
    ENUMEND_PALETTE_NUMBERS
} palette_numbers;
typedef enum {
    PALETTE_ENTRY_NUMBER_2,           /* FONTS.LBX, Entry 2 */
    PALETTE_ENTRY_NUMBER_3,           /* FONTS.LBX, Entry 3 */
    PALETTE_ENTRY_NUMBER_4,           /* FONTS.LBX, Entry 4 */
    PALETTE_ENTRY_NUMBER_5,           /* FONTS.LBX, Entry 5 */
    PALETTE_ENTRY_NUMBER_6,           /* FONTS.LBX, Entry 6 */
    PALETTE_ENTRY_NUMBER_7,           /* FONTS.LBX, Entry 7 */
    PALETTE_ENTRY_NUMBER_8,           /* FONTS.LBX, Entry 8 */
    ENUMEND_PALETTE_ENTRY_NUMBERS
} palette_entry_numbers;

enum mom_palette_number {
    EMPERATO = 1,           /* FONTS.LBX, Entry Index 2 */
    LOADSAVE,               /* FONTS.LBX, Entry Index 3 */
    ARCANUS,                /* FONTS.LBX, Entry Index 4 */
    WIZLAB,                 /* FONTS.LBX, Entry Index 5 */
    TEST,                   /* FONTS.LBX, Entry Index 6 */
    BACKGRND,               /* FONTS.LBX, Entry Index 7 */
    LOSE                    /* FONTS.LBX, Entry Index 8 */
};
//enum mom_palette_number;
extern char mom_palette_name[8][9];

/* F:\Development_OPC\momrtgt-code\MoMModel\MoMTemplate.h */
/*
typedef struct PACKED_STRUCT // LBX_PaletteInfo
{
    uint16_t    paletteOffset;                      // 00
    uint16_t    firstPaletteColorIndex;             // 02
    uint16_t    paletteColorCount;                  // 04
    // SIZE 6
} MoMPaletteInfoLbx;
*/

/* F:\Development_OPC\momrtgt-code\QMoMCommon\QMoMLbx.h */
/*
#include <QImage>  / * <- #include "qimage.h" <- #include <QtGui/qrgb.h> * /
#include <QVector>
typedef QVector<QRgb> QMoMPalette;
*/
/*
#include <QImage>
|-> #include "qimage.h"
|-> #include <QtGui/qrgb.h>
|->
    typedef unsigned int QRgb;                        // RGB triplet
    // non-namespaced Qt global variable
    const Q_DECL_UNUSED QRgb  RGB_MASK    = 0x00ffffff;     // masks RGB values
    inline Q_DECL_CONSTEXPR int qRed(QRgb rgb)                // get red part of RGB
    { return ((rgb >> 16) & 0xff); }
    inline Q_DECL_CONSTEXPR int qGreen(QRgb rgb)                // get green part of RGB
    { return ((rgb >> 8) & 0xff); }
    inline Q_DECL_CONSTEXPR int qBlue(QRgb rgb)                // get blue part of RGB
    { return (rgb & 0xff); }
*/

/* VM: Win98SE_Dev; C:\devel\MoM-IME\LBXtract\LBXClasses.pas */
/*
typedef struct PACKED_STRUCT
{
    Word PaletteOffset;
    Word FirstPaletteColourIndex;
    Word PaletteColourCount;
    Word Unknown;
} TGfxPaletteInfo;
*/

/* VM: Win98SE_Dev; C:\devel\MoM-IME\LBXtract\LBXClasses.pas */
/*
typedef struct PACKED_STRUCT
{
    Byte r;
    Byte g;
    Byte b;
} TGfxPaletteEntry;
*/

/* VM: Win98SE_Dev; C:\devel\MoM-IME\LBXtract\LBXClasses.pas */
/*
typedef TGfxPalette[255];
*/

#endif  /* LBX_RECORD_TYPE_PALETTE_H */
