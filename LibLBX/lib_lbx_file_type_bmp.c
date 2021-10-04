#include <malloc.h>         /* malloc(), realloc(); */
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */

#include "lib_lbx_file_type_bmp.h"
#include "lib_lbx.h"  /* LBX_DATA, LBX_DEBUG_STRUGGLE_MODE; */
#include "ATS/ats_matrix_transform.h"
#include "ATS/ats_matrix_utility.h"
#include "lib_lbx_record_palette.h"

//void convert_standard_color_map_to_bmp_palette()
//{
//
//}
//
//void convert_bmp_palette_to_standard_color_map()
//{
//
//}

// void liblbx_convert_flic_frame_to_bmp(BMP_FILE * bmp, LBX_DATA * lbx)
void liblbx_convert_flic_frame_to_bmp(BMP_FILE * bmp, LBX_DATA * lbx, unsigned int itr_entry_index, unsigned int itr_frame_index, int palette_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_convert_flic_frame_to_bmp()\n");

//    unsigned int itr_entry_index = 0; /* 0: MAIN000, MAINSCRN - main screen, 320x200, 1 frame; 1: MAIN001, MAINBUTN - game button, 39x12, 2 frames */
//    unsigned int itr_frame_index = 0;

    unsigned char * ptr_decoded_flic_frame_buffer;
    ptr_decoded_flic_frame_buffer = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer;
// lbx->record[itr_entry_index].entry->



    lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette = liblbx_load_palette(g_palette_file_path, palette_number);



    /* ***************************************** *
     *                                           *
     *   BEGIN: Image Data Layout Rearrangement  *
     *                                           *
     * ***************************************** */

    unsigned int row_count;
    unsigned int column_count;
    unsigned int element_count;

    row_count = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height;
    // lbx->record[itr_entry_index].entry->
    // column_count = row_count = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width;
    column_count = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width;
    // lbx->record[itr_entry_index].entry->
    element_count = row_count * column_count;

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: row_count: %u\n", row_count);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: column_count: %u\n", column_count);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: element_count: %u\n", element_count);

    unsigned char * transposed_decoded_frame_buffer;
    transposed_decoded_frame_buffer = malloc(element_count);

    transpose(transposed_decoded_frame_buffer, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, column_count, row_count);
    // transpose(transposed_decoded_frame_buffer, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, row_count, column_count);

    // lbx->record[itr_entry_index].entry->
    unsigned char * flipped_transposed_decoded_frame_buffer;
    flipped_transposed_decoded_frame_buffer = malloc(element_count);
    flipH(flipped_transposed_decoded_frame_buffer, transposed_decoded_frame_buffer, row_count, column_count);

//    unsigned char * ptr_flipped_transposed_decoded_frame_buffer;
//    ptr_flipped_transposed_decoded_frame_buffer = flipped_transposed_decoded_frame_buffer;


    /* ***************************************** *
     *                                           *
     *   END: Image Data Layout Rearrangement    *
     *                                           *
     * ***************************************** */


    // int bmp_image_buffer_size;
    // unsigned char * bmp_image_buffer;
    // unsigned char * ptr_bmp_image_buffer;
    BMP_PALETTE * bmp_palette_buffer;
    unsigned char * ptr_bmp_palette_buffer;

    /* ************************* *
     *                           *
     *   BEGIN: MS BMP/DIB 6bpp  *
     *                           *
     * ************************* */

    /* Image image_data_buffer Buffer Size, General Equation: (Image Width * Image Height * Bytes Per Pixel) */

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp = malloc(%u);\n", sizeof(*bmp));
    bmp = malloc(sizeof(*bmp));
    if (bmp == NULL)
    {
        printf("FAILURE: bmp = malloc(%u);\n", sizeof(*bmp));
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp = malloc(%u);\n", sizeof(*bmp));


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp->bmp_bitmap_file_header = malloc(%u);\n", sizeof(BMP_BITMAP_FILE_HEADER));
    bmp->bmp_bitmap_file_header = malloc(sizeof(BMP_BITMAP_FILE_HEADER));
    if (bmp->bmp_bitmap_file_header == NULL)
    {
        printf("FAILURE: bmp->bmp_bitmap_file_header = malloc(%u);\n", sizeof(BMP_BITMAP_FILE_HEADER));
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp->bmp_bitmap_file_header = malloc(%u);\n", sizeof(BMP_BITMAP_FILE_HEADER));


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp->bmp_bitmap_info_header = malloc(%u);\n", sizeof(BMP_BITMAP_INFO_HEADER));
    bmp->bmp_bitmap_info_header = malloc(sizeof(BMP_BITMAP_INFO_HEADER));
    if (bmp->bmp_bitmap_info_header == NULL)
    {
        printf("FAILURE: bmp->bmp_bitmap_info_header = malloc(%u);\n", sizeof(BMP_BITMAP_INFO_HEADER));
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp->bmp_bitmap_info_header = malloc(%u);\n", sizeof(BMP_BITMAP_INFO_HEADER));



//    bmp_image_buffer_size = lbx->record[itr_entry_index].entry->headers->flic->lbx_flic_info_header->frame_width * lbx->record[itr_entry_index].entry->headers->flic->lbx_flic_info_header->frame_height;
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_image_buffer_size: %d\n", bmp_image_buffer_size);
//
//
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp_image_buffer = malloc(%u);\n", bmp_image_buffer_size);
//    bmp_image_buffer = malloc(bmp_image_buffer_size);
//    if (bmp_image_buffer == NULL)
//    {
//        printf("FAILURE: bmp_image_buffer = malloc(%u);\n", bmp_image_buffer_size);
//        exit(EXIT_FAILURE);
//    }
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp_image_buffer = malloc(%u);\n", bmp_image_buffer_size);
//
//    ptr_bmp_image_buffer = bmp_image_buffer;



    /* ******************** *
     *                      *
     *   Transform Palette  *
     *                      *
     * ******************** */


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp_palette_buffer = malloc(%u);\n", BMP_PALETTE_SIZE);
    bmp_palette_buffer = malloc(BMP_PALETTE_SIZE);
    if (bmp_palette_buffer == NULL)
    {
        printf("FAILURE: bmp_palette_buffer = malloc(%u);\n", BMP_PALETTE_SIZE);
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp_palette_buffer = malloc(%u);\n", BMP_PALETTE_SIZE);

    /* TODO(JWB): move the palette population and transform to separate functions */
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: bmp_palette_buffer[ ] = lbx_palette[ ]\n");
    int itr_bmp_bgrx_quad;
    for (itr_bmp_bgrx_quad = 0; itr_bmp_bgrx_quad < 256; itr_bmp_bgrx_quad++)
    {
//        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 0)] = 0x00;
//        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 1)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 2))];
//        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 2)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 1))];
//        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 3)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 0))];
//        // lbx->record[0]
        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 0)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 2))];
        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 1)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 1))];
        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 2)] = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette[((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 0))];
        bmp_palette_buffer[((itr_bmp_bgrx_quad * 4) + 3)] = 0x00;


        /*
        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_palette_buffer[%u] = %u\n", ((itr_bmp_bgrx_quad * 4) + 0), 0x00);
        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_palette_buffer[%u] = lbx_palette[%u]\n", ((itr_bmp_bgrx_quad * 4) + 1), ((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 2)));
        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_palette_buffer[%u] = lbx_palette[%u]\n", ((itr_bmp_bgrx_quad * 4) + 2), ((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 1)));
        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_palette_buffer[%u] = lbx_palette[%u]\n", ((itr_bmp_bgrx_quad * 4) + 3), ((itr_bmp_bgrx_quad * 4) + (-itr_bmp_bgrx_quad + 0)));
         */
    }
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: bmp_palette_buffer[ ] = lbx_palette[ ]\n");



//    /* ****************** *
//     *                    *
//     *   Transform Image  *
//     *                    *
//     * ****************** */
//
//    /*
//    ptr_decoded_flic_frame_buffer
//    ptr_bmp_image_buffer
//
//     bmp_image_buffer[0,0] = decoded_frame_buffer[0,199]
//     ...
//     bmp_image_buffer[0,199] = decoded_frame_buffer[0,0]
//     ...
//     bmp_image_buffer[1,0] = decoded_frame_buffer[1,199]
//     ...
//     bmp_image_buffer[1,199] = decoded_frame_buffer[1,0]
//    */
//
//    int image_height;
//    int image_width;
//    int bytes_per_pixel;
//    image_height = 200;
//    image_width = 320;
//    bytes_per_pixel = 8;
//
//    int image_line_size;
//    image_line_size = image_width * bytes_per_pixel;
//    if ((image_line_size % 4) != 0)
//    {
//        image_line_size = ((image_line_size / 4) + 1) * 4; /* align 4-byte boundary */
//    }
//
//    int itr_image_column;
//    int itr_image_row;
//    unsigned int flic_byte_index;
//    unsigned int bmp_x;
//    unsigned int bmp_y;
//    unsigned int bmp_byte_index;
//    unsigned char flic_baito;
//    for (itr_image_column = 0; itr_image_column < image_width; itr_image_column++)
//    {
//        for (itr_image_row = 0; itr_image_row < image_height; itr_image_row++)
//        {
//
//            /*
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: ST FLIC Byte Index: %d ((%d*%d)+%d))\n",
//                                                ( ( itr_image_column * image_height ) + itr_image_row ),
//                                                itr_image_column,
//                                                image_height,
//                                                itr_image_row);
//            */
//
//            /* flic_byte_index = ( ( itr_image_column * image_height ) + itr_image_row ); */
//            flic_byte_index = ats_calculate_array_offset(itr_image_row, itr_image_column, image_height);
//
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: flic_byte_index: %d ( ( %d * %d ) + %d ) )\n",
//                                                flic_byte_index,
//                                                itr_image_column,
//                                                image_height,
//                                                itr_image_row);
//
//
//            bmp_x = ( flic_byte_index - ( image_width * (int)( flic_byte_index / image_width ) ) );
//            bmp_y = ( ( image_height - 1 ) - (int)( flic_byte_index / image_width ) );
//
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_x: %d ( %d - ( %d * (int)( %d / %d ) ) )\n",
//                                                bmp_x,
//                                                flic_byte_index,
//                                                image_width,
//                                                flic_byte_index,
//                                                image_width);
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_y: %d ( ( %d - 1 ) - (int)( %d / %d ) )\n",
//                                                bmp_y,
//                                                image_height,
//                                                flic_byte_index,
//                                                image_width);
//
//
//            /*
//            bmp_byte_index = ( ( bmp_y ) + ( bmp_x * image_height ) );
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_byte_index: %d ( ( %d ) + ( %d * %d ) )\n",
//                                    bmp_byte_index,
//                                    bmp_y,
//                                    bmp_x,
//                                    image_height);
//            */
//            bmp_byte_index = ats_calculate_array_offset_from_column_major_to_row_major(itr_image_row, itr_image_column, image_height, image_width);
//
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_byte_index: %d ( %d * %d + %d )\n",
//                                                bmp_byte_index,
//                                                itr_image_row,
//                                                image_height,
//                                                itr_image_column);
//
//
//            // ptr_bmp_image_buffer[bmp_byte_index] = *(ptr_decoded_flic_frame_buffer + flic_byte_index);
//            *(ptr_bmp_image_buffer + bmp_byte_index) = *(ptr_decoded_flic_frame_buffer + flic_byte_index);
//            flic_baito = *(ptr_decoded_flic_frame_buffer + flic_byte_index);
//            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: flic_baito: %02X\n", flic_baito);
//
//        }
//    }


    /*
    * Fields to Populate:
    *   BMP_BITMAP_FILE_HEADER ->
    *     File Type Identifier
    *     File Size, in bytes
    *     Reserved Field 1
    *     Reserved Field 2
    *     Offset to Bitmap Pixel image_data_buffer
    *  BMP_BITMAP_INFO_HEADER ->
    *    Size of Info Header, in bytes
    *    Width, in pixels
    *    Height, in pixels
    *    Number of Planes
    *    Bits Per Pixel
    *    Compression Scheme
    *    Size of Bitmap, in bytes
    *    Horz. Resolution, in Pixels/Meter
    *    Vert. Resolution, in Pixels/Meter
    *    Number of Colors in Color-Table
    *    Number of Important Colors
    */

    unsigned int color_data_length;
    color_data_length = 256 * 4;  /* 256 colors, in 4 bytes each, for the Red, Green, Blue, and Reserved bytes */
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: color_data_length: %d\n", color_data_length);

    unsigned int headers_total_length;
    headers_total_length = BMP_BITMAP_FILE_HEADER_LENGTH + BMP_BITMAP_INFO_HEADER_LENGTH;
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: headers_total_length: %d\n", headers_total_length);

    unsigned int bmp_size;
    // bmp_size = bmp_image_buffer_size + color_data_length + headers_total_length; /* BMP File Size = Pixel image_data_buffer(Width * Height) + Color image_data_buffer(RGB * 4) + Header(14 + 40)*/
    bmp_size = element_count + color_data_length + headers_total_length; /* BMP File Size = Header(14 + 40) + Palette Data (RGB * 4) + Image Data (Width * Height) */
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_size: %d\n", bmp_size);


    /* if (BmpHead->WinInfo.BitCount != 24 || BmpHead->WinInfo.ClrUsed != 0) */
    /* BMP_BITMAP_FILE_HEADER: */
    bmp->bmp_bitmap_file_header->bfType = BMP_MAGIC;
    bmp->bmp_bitmap_file_header->bfSize = bmp_size;  /* 4294967296 - 1;  / * 2^32 * / */
    bmp->bmp_bitmap_file_header->bfReserved1 = 0;
    bmp->bmp_bitmap_file_header->bfReserved2 = 0;
    bmp->bmp_bitmap_file_header->bfOffBits = 14 + 40 + 1024;
    /* BMP_BITMAP_INFO_HEADER: */
    bmp->bmp_bitmap_info_header->biSize = 40;
    bmp->bmp_bitmap_info_header->biWidth = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width;
    bmp->bmp_bitmap_info_header->biHeight = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height;
    bmp->bmp_bitmap_info_header->biPlanes = 1;
    bmp->bmp_bitmap_info_header->biBitCount = 8;
    bmp->bmp_bitmap_info_header->biCompression = 0;
    // bmp->bmp_bitmap_info_header->biSizeImage = bmp_image_buffer_size; /* (4294967296 - 1) - (14 + 40) - (256 * 4);  / * 2^32 - Headers - Palette * / */
    bmp->bmp_bitmap_info_header->biSizeImage = element_count; /* (4294967296 - 1) - (14 + 40) - (256 * 4);  / * 2^32 - Headers - Palette * / */
    bmp->bmp_bitmap_info_header->biXPelsPerMeter = BMP_XPELS_PER_METER_DEFAULT;
    // bmp->bmp_bitmap_info_header->biXPelsPerMeter = 0;
    bmp->bmp_bitmap_info_header->biYPelsPerMeter = BMP_YPELS_PER_METER_DEFAULT;
    // bmp->bmp_bitmap_info_header->biYPelsPerMeter = 0;
    bmp->bmp_bitmap_info_header->biClrUsed = 256;  /* ~= "Use the maximum number of colors corresponding to the value of BitCount */
    // bmp->bmp_bitmap_info_header->biClrUsed = 0;  /* ~= "Use the maximum number of colors corresponding to the value of BitCount */
    bmp->bmp_bitmap_info_header->biClrImportant = 256;  /* ~= "NIU" */
    // bmp->bmp_bitmap_info_header->biClrImportant = 0;  /* ~= "NIU" */

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_file_header->bfType: %04X\n", bmp->bmp_bitmap_file_header->bfType);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_file_header->bfSize: %08X\n", bmp->bmp_bitmap_file_header->bfSize);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_file_header->bfReserved1: %04X\n", bmp->bmp_bitmap_file_header->bfReserved1);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_file_header->bfReserved2: %04X\n", bmp->bmp_bitmap_file_header->bfReserved2);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_file_header->bfOffBits: %08X\n", bmp->bmp_bitmap_file_header->bfOffBits);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biSize: %08X\n", bmp->bmp_bitmap_info_header->biSize);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biWidth: %08X\n", bmp->bmp_bitmap_info_header->biWidth);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biHeight: %08X\n", bmp->bmp_bitmap_info_header->biHeight);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biPlanes: %04X\n", bmp->bmp_bitmap_info_header->biPlanes);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biBitCount: %04X\n", bmp->bmp_bitmap_info_header->biBitCount);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biCompression: %08X\n", bmp->bmp_bitmap_info_header->biCompression);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biSizeImage: %08X\n", bmp->bmp_bitmap_info_header->biSizeImage);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biXPelsPerMeter: %08X\n", bmp->bmp_bitmap_info_header->biXPelsPerMeter);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biYPelsPerMeter: %08X\n", bmp->bmp_bitmap_info_header->biYPelsPerMeter);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biClrUsed: %08X\n", bmp->bmp_bitmap_info_header->biClrUsed);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp->bmp_bitmap_info_header->biClrImportant: %08X\n", bmp->bmp_bitmap_info_header->biClrImportant);

    /* TODO(JWB): add sanity check on header size and offset to image data */


    /* ******************* *
     *                     *
     *   END: MS BMP/DIB   *
     *                     *
     * ******************* */


    if (itr_entry_index == 0 && itr_frame_index == 0)
    {
        /* char * export_file_path; */
        char export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN000_FF0.BMP";
        FILE * ptr_stream_file_out;
        ptr_stream_file_out = fopen(export_file_path, "wb");

        char tmp_bmp_hdr_export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN000_FF0_thdr.BIN";
        FILE * tmp_bmp_hdr_ptr_stream_file_out;
        tmp_bmp_hdr_ptr_stream_file_out = fopen(tmp_bmp_hdr_export_file_path, "wb");

        char tmp_bmp_pal_export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN000_FF0_tpal.BIN";
        FILE * tmp_bmp_pal_ptr_stream_file_out;
        tmp_bmp_pal_ptr_stream_file_out = fopen(tmp_bmp_pal_export_file_path, "wb");


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, tmp_bmp_hdr_ptr_stream_file_out);\n");

        fwrite(&(bmp->bmp_bitmap_file_header->bfType), sizeof(bmp->bmp_bitmap_file_header->bfType), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfSize), sizeof(bmp->bmp_bitmap_file_header->bfSize), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved1), sizeof(bmp->bmp_bitmap_file_header->bfReserved1), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved2), sizeof(bmp->bmp_bitmap_file_header->bfReserved2), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfOffBits), sizeof(bmp->bmp_bitmap_file_header->bfOffBits), 1, tmp_bmp_hdr_ptr_stream_file_out);

        fwrite(&(bmp->bmp_bitmap_info_header->biSize), sizeof(bmp->bmp_bitmap_info_header->biSize), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biWidth), sizeof(bmp->bmp_bitmap_info_header->biWidth), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biHeight), sizeof(bmp->bmp_bitmap_info_header->biHeight), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biPlanes), sizeof(bmp->bmp_bitmap_info_header->biPlanes), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biBitCount), sizeof(bmp->bmp_bitmap_info_header->biBitCount), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biCompression), sizeof(bmp->bmp_bitmap_info_header->biCompression), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biSizeImage), sizeof(bmp->bmp_bitmap_info_header->biSizeImage), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biXPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biXPelsPerMeter), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biYPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biYPelsPerMeter), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrUsed), sizeof(bmp->bmp_bitmap_info_header->biClrUsed), 1, tmp_bmp_hdr_ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrImportant), sizeof(bmp->bmp_bitmap_info_header->biClrImportant), 1, tmp_bmp_hdr_ptr_stream_file_out);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, tmp_bmp_hdr_ptr_stream_file_out);\n");

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, ptr_stream_file_out);\n");

        fwrite(&(bmp->bmp_bitmap_file_header->bfType), sizeof(bmp->bmp_bitmap_file_header->bfType), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfSize), sizeof(bmp->bmp_bitmap_file_header->bfSize), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved1), sizeof(bmp->bmp_bitmap_file_header->bfReserved1), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved2), sizeof(bmp->bmp_bitmap_file_header->bfReserved2), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfOffBits), sizeof(bmp->bmp_bitmap_file_header->bfOffBits), 1, ptr_stream_file_out);

        fwrite(&(bmp->bmp_bitmap_info_header->biSize), sizeof(bmp->bmp_bitmap_info_header->biSize), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biWidth), sizeof(bmp->bmp_bitmap_info_header->biWidth), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biHeight), sizeof(bmp->bmp_bitmap_info_header->biHeight), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biPlanes), sizeof(bmp->bmp_bitmap_info_header->biPlanes), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biBitCount), sizeof(bmp->bmp_bitmap_info_header->biBitCount), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biCompression), sizeof(bmp->bmp_bitmap_info_header->biCompression), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biSizeImage), sizeof(bmp->bmp_bitmap_info_header->biSizeImage), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biXPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biXPelsPerMeter), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biYPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biYPelsPerMeter), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrUsed), sizeof(bmp->bmp_bitmap_info_header->biClrUsed), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrImportant), sizeof(bmp->bmp_bitmap_info_header->biClrImportant), 1, ptr_stream_file_out);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, ptr_stream_file_out);\n");


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, tmp_bmp_pal_ptr_stream_file_out);\n");
        fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, tmp_bmp_pal_ptr_stream_file_out);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, tmp_bmp_pal_ptr_stream_file_out);\n");

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);\n");
        fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);\n");


        // if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);\n");
        // fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);
        // if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);\n");

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);\n");
        fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);\n");

        fclose(ptr_stream_file_out);
    }

    if (itr_entry_index == 1 && itr_frame_index == 0)
    {
        /* char * export_file_path; */
        char export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN001_FF0.BMP";
        FILE * ptr_stream_file_out;
        ptr_stream_file_out = fopen(export_file_path, "wb");


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, ptr_stream_file_out);\n");

        fwrite(&(bmp->bmp_bitmap_file_header->bfType), sizeof(bmp->bmp_bitmap_file_header->bfType), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfSize), sizeof(bmp->bmp_bitmap_file_header->bfSize), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved1), sizeof(bmp->bmp_bitmap_file_header->bfReserved1), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfReserved2), sizeof(bmp->bmp_bitmap_file_header->bfReserved2), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_file_header->bfOffBits), sizeof(bmp->bmp_bitmap_file_header->bfOffBits), 1, ptr_stream_file_out);

        fwrite(&(bmp->bmp_bitmap_info_header->biSize), sizeof(bmp->bmp_bitmap_info_header->biSize), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biWidth), sizeof(bmp->bmp_bitmap_info_header->biWidth), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biHeight), sizeof(bmp->bmp_bitmap_info_header->biHeight), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biPlanes), sizeof(bmp->bmp_bitmap_info_header->biPlanes), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biBitCount), sizeof(bmp->bmp_bitmap_info_header->biBitCount), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biCompression), sizeof(bmp->bmp_bitmap_info_header->biCompression), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biSizeImage), sizeof(bmp->bmp_bitmap_info_header->biSizeImage), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biXPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biXPelsPerMeter), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biYPelsPerMeter), sizeof(bmp->bmp_bitmap_info_header->biYPelsPerMeter), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrUsed), sizeof(bmp->bmp_bitmap_info_header->biClrUsed), 1, ptr_stream_file_out);
        fwrite(&(bmp->bmp_bitmap_info_header->biClrImportant), sizeof(bmp->bmp_bitmap_info_header->biClrImportant), 1, ptr_stream_file_out);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(&(bmp->bmp_bitmap_file_header->), sizeof(bmp->bmp_bitmap_file_header->), 1, ptr_stream_file_out);\n");

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);\n");
        fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(bmp_palette_buffer, sizeof(unsigned char), BMP_PALETTE_SIZE, ptr_stream_file_out);\n");

        // if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);\n");
        // fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);
        // if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(bmp_image_buffer, sizeof(unsigned char), bmp_image_buffer_size, ptr_stream_file_out);\n");

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);\n");
        fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: fwrite(flipped_transposed_decoded_frame_buffer, sizeof(unsigned char), element_count, ptr_stream_file_out);\n");

        fclose(ptr_stream_file_out);
    }


    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_convert_flic_frame_to_bmp()\n");
}