#ifndef LBX_RECORD_TYPE_IMAGE_H
#define LBX_RECORD_TYPE_IMAGE_H

/*
 * ? structure for /image/ of non- index color mapped ?
 * i.e. byte = width * height * [R,G,B] or even [A,R,G,B]
 *
 * ? Raster ?
 * https://docs.oracle.com/javase/7/docs/api/java/awt/image/IndexColorModel.html
 * |-> https://docs.oracle.com/javase/7/docs/api/java/awt/image/IndexColorModel.html#convertToIntDiscrete(java.awt.image.Raster,%20boolean)
 *
 * ? https://www.w3.org/Graphics/Color/sRGB.html ?
 *
 * ? https://docs.oracle.com/javase/7/docs/api/java/awt/Font.html#createGlyphVector(java.awt.font.FontRenderContext,%20char[]) ?
 *
 * ? structure for CMAP (Color Map)
 *
 */

#include "lbx.h"
#include "lib_lbx_types.h"

/*
 * 0xDE0A = 56842 = 1101111000001010
 * 0x0ADE =  2782 = 0000101011011110
 * 0xDE = 222 = 11011110
 * 0x0A =  10 = 00001010
 */

/*
 * FLIC386P/LIBSRC/INC/FLI.H:#define MAXFRAMES (4*1000)    / * Max number of frame_raw... * /
 */

/* J:\STU-EduMat\_FileFormats\FLIC\flic.asc */
/*
switch (chunk->type)
    {
    case COLOR_256:
        decode_color_256((Uchar huge *)(chunk+1), flic, s);
        break;
    case DELTA_FLC:
        decode_delta_flc((Uchar huge *)(chunk+1), flic, s);
        break;
    case COLOR_64:
        decode_color_64((Uchar huge *)(chunk+1), flic, s);              NOTE: this is the 256 color, full frame_raw (NOT delta, NOT compressed (LC/BR))
        break;
    case DELTA_FLI:
        decode_delta_fli((Uchar huge *)(chunk+1), flic, s);
        break;
    case BLACK:
        decode_black((Uchar huge *)(chunk+1), flic, s);
        break;
    case BYTE_RUN:
        decode_byte_run((Uchar huge *)(chunk+1), flic, s);
        break;
    case LITERAL:
        decode_literal((Uchar huge *)(chunk+1), flic, s);
        break;
    default:
        break;
    }
 */

/* J:\STU\DBWD\developc\_AnimatorPro\src\V\fli.h */
/*
#define FLI_COL 0
#define FLI_WRUN 1
#define FLI_WSKIP 2
#define FLI_WSKIP2 3
#define FLI_COL2 4
#define FLI_WSKIPRUN 5
#define FLI_BSKIP 6
#define FLI_BSKIPRUN 7
#define FLI_BSC 8
#define FLI_SBSC 9
#define FLI_SBSRSC 10
#define FLI_COLOR 11
#define FLI_LC	12
#define FLI_BLACK 13
#define FLI_ICOLORS 14
#define FLI_BRUN 15
#define FLI_COPY 16
*/

/*
 * ST LBX 'Frame/Chunk Types'
 */
enum {
    LBX_FLI_LC,
    LBX_FLI_BRUN
} LBX_FRAME_TYPE;


/* J:\STU-EduMat\_FileFormats\PCX\Translating_PCX_Files(DDJ198908)\pcx.h */
#define LBX_IMG_COMPRESSED 0xC0
#define LBX_IMG_MASK 0x3F


/* J:\STU-EduMat\_FileFormats\FLIC\Dr Dobbs Journal 199303 - contains FLIC ASC and ARC\9303\flic_arc\FLIC.H */
/*
	/ * Values for FlicHead.flags * /
#define FLI_FINISHED 0x0001
#define FLI_LOOPED	 0x0002
*/

struct s_LBX_FLIC_FRAME_RLE_PACKET_HEADER {
    lbx_uint8 rle_packet_operation_code;
    lbx_uint8 byte_count;
    lbx_uint8 sequence_count;
    lbx_uint8 delta;
};
typedef struct s_LBX_FLIC_FRAME_RLE_PACKET_HEADER LBX_FLIC_FRAME_RLE_PACKET_HEADER;

struct s_LBX_FLIC_FRAME_RLE_PACKET {
    LBX_FLIC_FRAME_RLE_PACKET_HEADER * lbx_flic_frame_rle_packet_header;
    unsigned char packet;
};
typedef struct s_LBX_FLIC_FRAME_RLE_PACKET LBX_FLIC_FRAME_RLE_PACKET;

struct s_LBX_FLIC_FRAME_HEADER {
    lbx_uint8 frame_type;
};
typedef struct s_LBX_FLIC_FRAME_HEADER LBX_FLIC_FRAME_HEADER;

struct s_LBX_FLIC_FRAME {
    LBX_FLIC_FRAME_HEADER frame_header;
    unsigned char * frame_data;
    unsigned char * frame_raw;
    lbx_size frame_data_size;
    unsigned char * encoded_frame_buffer;
    unsigned char * decoded_frame_buffer;
};
typedef struct s_LBX_FLIC_FRAME LBX_FLIC_FRAME;

struct s_LBX_IMAGE_FRAMES_DATA {
    LBX_FLIC_FRAME frame[99]; /* The prescribed maximum frame_raw count is (4*1000+1 = 4001), per the FLIC spec. */
};
typedef struct s_LBX_IMAGE_FRAMES_DATA LBX_FLIC_FRAMES_DATA;

struct s_LBX_IMAGE_FRAME_OFFSET_TABLE_ENTRY {
    lbx_uint32 begin;                               /* Offset from Beginning of LBX Record (BOR) */
};
typedef struct s_LBX_IMAGE_FRAME_OFFSET_TABLE_ENTRY LBX_IMAGE_FRAME_OFFSET_TABLE_ENTRY;

struct s_LBX_IMAGE_FRAME_OFFSET_TABLE {
    LBX_IMAGE_FRAME_OFFSET_TABLE_ENTRY entry[99]; /* The prescribed maximum frame_raw count is (4*1000+1 = 4001), per the FLIC spec. */
};
typedef struct s_LBX_IMAGE_FRAME_OFFSET_TABLE LBX_FLIC_FRAME_OFFSET_TABLE;

/* looks to be the same for MoM and MoO1 */
/* (/drake178) ~= ...FLIC_HEADER - ? SIMTEX, SIMTEX_V1, MOM, MOM131, ... ? */
struct s_LBX_FLIC_INFO_HEADER {
    lbx_uint16  frame_width;
    lbx_uint16  frame_height;
    lbx_uint16  current_frame;
    lbx_uint16  frame_count;
    lbx_uint16  loop_frame;                         /* ? not frame_speed/delay ? */
    lbx_uint8   emm_handle;                         /* Run-Time (MS-DOS EMM EMS) */
    lbx_uint8   emm_logical_page;                   /* Run-Time (MS-DOS EMM EMS) */
    lbx_uint16  emm_data_offset;                    /* Run-Time (MS-DOS EMM EMS) */
    lbx_uint16  palette_info_offset;                /* (0 if N/A) Offset to Palette Info Header, relative to BOR */
    lbx_uint16  unknown;                            /* noted in 1oom and IME LbxExtract, but not in MoM-RTGT or drake178 */
};
typedef struct s_LBX_FLIC_INFO_HEADER LBX_FLIC_INFO_HEADER;

/* ~= FLIC.H: typedef struct { ... } FlicHead; */
/*
struct s_LBX_FLIC_INFO_HEADER {
    lbx_uint16    width;
    lbx_uint16    height;
    lbx_uint16    compression;
    lbx_uint16    frame_count;
    lbx_uint16    frame_delay;
    lbx_uint16    flags;                            / * ? may be 2X uint8 ? NOT FlicHead.flags {FLI_FINISHED=0x0001, FLI_LOOPED0x0002} * /
    lbx_uint16    reserved;
    lbx_uint16    palette_info_offset;
    lbx_uint16    unknown;
};
typedef struct s_LBX_FLIC_INFO_HEADER LBX_FLIC_INFO_HEADER;
*/

/* ~= CHUNK_TYPE: COLOR_64 */
struct s_LBX_FLIC_PALETTE_HEADER
{
    lbx_uint16    palette_offset;
    lbx_uint16    palette_color_index;              /* ~= CHUNK_TYPE: COLOR_64: BYTE SkipCount */
    lbx_uint16    palette_color_count;              /* ~= CHUNK_TYPE: COLOR_64: BYTE ColorCount */
};
typedef struct s_LBX_FLIC_PALETTE_HEADER LBX_FLIC_PALETTE_HEADER;

struct s_LBX_FLIC_RECORD_HEADER
{
    LBX_FLIC_INFO_HEADER * lbx_flic_info_header;
    LBX_FLIC_PALETTE_HEADER * lbx_flic_palette_header;
    LBX_FLIC_FRAME_OFFSET_TABLE * lbx_flic_frame_offset_table;
    /*LBX_PALETTE * lbx_palette;*/
    lbx_uint8 * lbx_flic_palette;
    lbx_uint8 * lbx_flic_frame;
    LBX_FLIC_FRAMES_DATA * lbx_flic_frames;
};
typedef struct s_LBX_FLIC_RECORD_HEADER LBX_FLIC_RECORD_HEADER;


/* J:\STU-DASM\drake178\MAGIC.inc */
/*
LBX_IMG_HDR struc ; (sizeof=0x10, standard type)
Width dw ?
Height dw ?
Current_Frame dw ?
Frame_Count dw ?
Loop_Frame dw ?
EMM_Handle db ?
EMM_Logical_Page db ?
EMM_Data_Offset	dw ?
Palette_Data_Offset dw ?
LBX_IMG_HDR ends
*/


/* F:\Development_OPC\momrtgt-code\MoMModel\MoMTemplate.h */
typedef struct /* PACKED_STRUCT */ /* // LBX_ImageHeader */
{
    uint16_t    width;                              // 00
    uint16_t    height;                             // 02
    uint16_t    compression;                        // 04   0=RLE, 0xDE0A=uncompressed
    uint16_t    nframes;                            // 06   0=uncompressed, 1+=RLE
    uint16_t    frameDelay;                         // 08
    uint16_t    flags;                              // 0A
    uint16_t    reserved_0C;                        // 0C
    uint32_t    paletteInfoOffset;                  // 0E
    // SIZE 12
} MoMImageHeaderLbx;

/* VM: Win98SE_Dev; C:\devel\MoM-IME\LBXExtract\LBXClasses.pas */
typedef uint32_t Word;
typedef struct /* PACKED_STRUCT */
{
    Word Width;
    Word Height;
    Word Unknown1;
    Word BitmapCount;
    Word Unknown2;
    Word Unknown3;
    Word Unknown4;
    Word PaletteInfoOffset;
    Word Unknown5;

} TGfxHeader;

    /* J:\STU\STU-OPP\1oom\1oom-1.0\1oom-1.0\share\doc\1oom\format_lbx.txt */
/*
gfx format

offset  sz  description
0       2   width
2       2   height
4       2   frame_raw (current: 0 in file)
6       2   frame_raw
8       2   set current frame_raw to this when frame_raw == frame_raw (0, frame_raw-1...)
a       1   0x00 (runtime: emm handle)
b       1   0x00 (runtime: emm page)
c       2   0x0000 (runtime: ?)
e       2   offset to palette (or 0 if none)
10      1   independent frame_raw : 0x00/0x01  (if 0 then need to draw frame_raw 0..n-1 before n)
11      1   gfx format ; 0x00 except council.lbx i1 == 0x01
12+4*I  4   offset to frame_raw I data start (data ends at next I start)


frame_raw data

offset  sz  description
0       1   (unused) if 0: overlay on previous frame_raw ; 1: clear buffer
1..     ?   columnwise pixel data
            - 0xff: skip this column
            - 0x00: uncompressed:
                - total_len
                    - part_len, skip_pixels, pixel*part_len
                        - v=geti(); puto(v, 1);
            - 0x80: compressed:
                - total_len
                    - part_len, skip_pixels, compressed_data*part_len
                        - v=geti(); if (v>223) { len=v-223; v=geti(); } else { len=1; } ; puto(v, len);
            - puto(v, len)
                - format 0
                    - while (len--) { put_pixel(x, y, v); ++y }
                - format 1
                    - if (v>=0xe8) {
                        tbl = lut[v-0xe8];
                        while (len--) { v = tbl[get_pixel(x, y)]; put_pixel(x, y, v); ++y; }
                      } else {
                        while (len--) { put_pixel(x, y, v); ++y }
                      }


palette metadata

offset  sz  description
0       2   offset to palette data (from gfx data start)
2       2   first changed color
4       2   number of changed colors
6       2   ? 0x00 0x00 (offset points to 8...)

palette data

offset  sz  description
3*N     3   RGB palette values (6bpp per item)
*/

/* ILSe - MoM-RTGT: ...\QMoMDialogs\DialogLbxEditor.cpp */
/* void DialogLbxEditor::loadPaletteForFile(const QString &filename) */
/*
// CONQUEST???
    if (0 == filetitle.compare("LOAD.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 3;
    }
    else if (0 == filetitle.compare("MAINSCRN.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 4;
    }
    else if (0 == filetitle.compare("WIZLAB.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 5;
    }
    else if (0 == filetitle.compare("SPLMASTR.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 6;
    }
    else if (0 == filetitle.compare("WIN.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 7;
    }
    else if ((0 == filetitle.compare("LOSE.LBX", Qt::CaseInsensitive))
             || (0 == filetitle.compare("SPELLOSE.LBX", Qt::CaseInsensitive)))
    {
        lbxIndex = 8;
    }
    else
    {
        lbxIndex = 2;
    }
*/

#endif  /* LBX_RECORD_TYPE_IMAGE_H */
