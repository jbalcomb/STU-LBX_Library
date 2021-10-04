#include "lib_lbx_util_rle.h"
#include "lbx_types.h"

/*
 * https://wiki.nesdev.com/w/index.php/Tile_compression
 */

/*
 * Run Length Encoding (RLE)
 * Adaptive Run Length Encoding (ARLE)
 *
 * There are many, many RLE algorithms.
 *
 * There is a common overlap for RLE with image and video/animation data.
 * The two key concepts are intra-frame_raw encoding and inter-frame_raw encoding.
 * Inter-frame_raw encoding consists of encoding the delta between the current-frame_raw and previous-frame_raw.
 * In the context of inter-frame_raw encoding, the intra-frame_raw encoding contains additional information.
 * i.e., If an area of the image has not changed between frame_raw, the current-frame_raw encoding information will include skipping that area.
 *
 * The two basic operations are:
 * 'copy 1 byte n times'
 * 'copy n bytes 1 time'
 *
 * There are various other custom operations, often specific to the type of data being encoded.
 *
 * The minimum size of a repeated sequence of encoded bytes is two, otherwise a sequence of one byte would be encoded in two bytes.
 *
 */

/*
 * The Simtex RLE algorithm used in MoM v1.31 appear to be similar to the standard PCX image format RLE algorithm.
 * And, as best as I can tell, it is not the "Byte Run" (brun, unbrun) from the FLIC Lib/VPaint/Autodesk Animator (Pro)
 * At the lest, I see no reference/correlation in the source code for "FF" as an 'OpCode'.
 *
 * Operation Codes (OpCode):
 * {0x00, 0x80, 0xFF}
 * 0x00:
 * 0x80:
 * 0xFF:
 *
 * Skip Count:
 * Size or Count:
 * Data/Value:
 *
 */

/*
 * NOTE: The documentation says "BYTE" and "WORD", but the source code uses UBYTE and UWORD.
 *
 * Per the the FLIC Lib/Vpaint/Autodesk Animator (Pro) source code, ...
 * FLI_LC Chunks: (Delta - previous-frame_raw, current-frame_raw
 * WORD Lines to Skip
 * WORD Lines to Change
 * BYTE Number of Packets
 * Packet:
 * BYTE
 */

/*
 * J:\STU\DBWD\developc\Animator\src\COMMON\comp_.c
 * void unlccomp(const UBYTE *src, UBYTE *dst)
 */

/*
 * src: buffer of encoded image data - /frame_raw data/ from LBX Image (single-frame_raw animation)
 * dst: buffer for decoded image data; size is (image_width * image_height * bytes_per_pixel)
 *
 * Line?
 * Packet?
 *
 * e.g, 80 0B 09 00 E1 0D E4 0E E7 80 E3 0E 0A
 *     read('0x80');
 *     read('0x0B');
 *     ? do something 11 times ?
 *     read('0x09');
 *     ? do something 9 times ?
 *     read('0x00');
 *     packet_byte = read('0xE1');
 *     if >= 224 (0xE0) then copy_count = packet_byte - 0xE0
 *     read('0x0D');
 *     read('0xE4');
 *     read('0x0E');
 *     read('0xE7');
 *     read('0x80');
 *     read('0xE3');
 *
 *     read('0x0E');
 *     read('0x0A');
 */
void decompress_lbx_new_frame_line_compressed_flic_frame(lbx_uint8 * dst, lbx_uint8 * src)
{
    lbx_uint16 image_height = 320;
    lbx_uint16 image_width = 200;

    /* Iterate through the count of columns in the image - image_width */
    lbx_uint8 itr_columns;  /* X AKA Columns AKA Image Width, from Top-Left (TL) */
    itr_columns = 0;

    lbx_uint8 * ptr_line;

    while ( itr_columns < image_width)
    {

        itr_columns = itr_columns + 1;
    }

}

void decompress_lbx_delta_frame_line_compressed_flic_frame(lbx_uint8 * dst, lbx_uint8 * src)
{
    lbx_uint16 image_height = 320;
    lbx_uint16 image_width = 200;

    /* Iterate through the count of columns in the image - image_width */
    lbx_uint8 itr_columns;  /* X AKA Columns AKA Image Width, from Top-Left (TL) */
    itr_columns = 0;

    lbx_uint8 * ptr_line;

    while ( itr_columns < image_width)
    {

        itr_columns = itr_columns + 1;
    }

}

void process_lbx_image_frame_data(lbx_uint8 * dst, lbx_uint8 * src)
{
    switch (*src)
    {
        case 0:
            decompress_lbx_delta_frame_line_compressed_flic_frame(dst, src);
            break;
        case 1:
            decompress_lbx_new_frame_line_compressed_flic_frame(src, dst);
            break;
        default:
            break;
    }
}