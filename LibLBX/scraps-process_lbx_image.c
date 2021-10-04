
            LBX_IMAGE_HEADER * lbx_image_header;

            lbx_image_header = (LBX_IMAGE_HEADER *) malloc(sizeof(LBX_IMAGE_HEADER));

            lbx_image_header->width = *(lbx_uint16 *) &record_data[0];
            lbx_image_header->height = *(lbx_uint16 *) &record_data[2];
            lbx_image_header->compression = *(lbx_uint16 *) &record_data[4];
            lbx_image_header->frame_count = *(lbx_uint16 *) &record_data[6];
            lbx_image_header->frame_delay = *(lbx_uint16 *) &record_data[8];
            lbx_image_header->flags = *(lbx_uint16 *) &record_data[10];
            lbx_image_header->reserved = *(lbx_uint16 *) &record_data[12];
            lbx_image_header->palette_info_offset = *(lbx_uint16 *) &record_data[14];
            lbx_image_header->unknown = *(lbx_uint16 *) &record_data[16];

            int lbx_image_header_length;
            lbx_image_header_length = record_data[0] - record_data[14];
            if (LBXMGR_DEBUG_MODE) printf("DEBUG: lbx_image_header_length: %u\n", lbx_image_header_length);

            if (lbx_image_header->palette_info_offset == 0) {
                if (LBXMGR_DEBUG_MODE) printf("DEBUG: No custom palette contained here-in.\n");
                if (LBXMGR_DEBUG_MODE) printf("DEBUG: palette_info_header_length: DNE\n");
            }
            else
            {
                LBX_IMAGE_CUSTOM_PALETTE_HEADER * lbx_image_custom_palette_header;

                lbx_image_custom_palette_header = (LBX_IMAGE_CUSTOM_PALETTE_HEADER *) malloc(
                        sizeof(LBX_IMAGE_CUSTOM_PALETTE_HEADER));

                lbx_image_custom_palette_header->palette_offset = *(lbx_uint16 *) &record_data[lbx_image_header->palette_info_offset + 0];
                lbx_image_custom_palette_header->palette_color_index = *(lbx_uint16 *) &record_data[lbx_image_header->palette_info_offset + 2];
                lbx_image_custom_palette_header->palette_color_count = *(lbx_uint16 *) &record_data[lbx_image_header->palette_info_offset + 4];

                int palette_info_header_length;
                palette_info_header_length = lbx_image_custom_palette_header->palette_offset - lbx_image_header_length;
                if (LBXMGR_DEBUG_MODE) printf("DEBUG: palette_info_header_length: %u\n", palette_info_header_length);

                fseek(lbx->file_stream, lbx_image_custom_palette_header->palette_offset, SEEK_SET);

                int itr_palette_color_count;
                for (itr_palette_color_count = 0; itr_palette_color_count < lbx_image_custom_palette_header->palette_color_count; itr_palette_color_count++)
                {
                    lbx_palette[lbx_image_custom_palette_header->palette_color_index + itr_palette_color_count] =  *(lbx_uint8 *) &record_data[lbx_image_custom_palette_header->palette_offset + itr_palette_color_count];
                }
            }

            if (lbx_image_header->frame_count == 1)
            {
                lbx_int32 offset_to_image_data_offset_table;
                offset_to_image_data_offset_table = LBX_IMAGE_DATA_OFFSET_TABLE_OFFSET_DEFAULT;
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: offset_to_image_data_offset_table: %04X (%u)\n", offset_to_image_data_offset_table, offset_to_image_data_offset_table);

                lbx_int32 frame_data_offset_begin;
                frame_data_offset_begin = *(lbx_int32 *) &record_data[offset_to_image_data_offset_table];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: frame_data_offset_begin: %04X (%u)\n", frame_data_offset_begin, frame_data_offset_begin);

                lbx_int32 frame_data_offset_end;
                frame_data_offset_end = *(lbx_int32 *) &record_data[offset_to_image_data_offset_table + LBX_LENGTH_IMAGE_FRAME_OFFSET_TABLE_ENTRY];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: frame_data_offset_end: %04X (%u)\n", frame_data_offset_end, frame_data_offset_end);

                /*
                lbx_uint32 frame_offset_table[2];
                int itr_frame_offset_table;
                for (itr_frame_offset_table = 0; itr_frame_offset_table < lbx_image_header->frame_count + 1; itr_frame_offset_table++)
                {
                    frame_offset_table[itr_frame_offset_table] = *(lbx_uint32 *) &record_data[offset_to_image_data_offset_table * itr_frame_offset_table];
                }
                */



                // frame_data_offset_begin
                // frame_data_offset_end
                // frame_data_offset_end - frame_data_offset_begin

                /* ******************************* *
                 *                                 *
                 *   BEGIN: LBX IMAGE Frame Data   *
                 *                                 *
                 * ******************************* */

                /* starting at line 356 in F:\Development_OPC\momrtgt-code\QMoMCommon\QMoMLbx.cpp */
                /*
                 * "Should be 01 for first frame, and either 00 (incremental), or 01 (complete) for the following frames"
                 * if lbx_chunk_type = 1
                 */
                /*
                 * AKA
                 * ...
                 * 12    FLI_LC           Byte-oriented delta compression
                 * ...
                 * 15    FLI_BRUN         Byte run length compression
                 *
                 */
                char lbx_chunk_type;
                lbx_chunk_type = *(char *) &record_data[frame_data_offset_begin];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx_chunk_type: %04X (%d)\n", lbx_chunk_type, lbx_chunk_type);

                /*
                // struct GCC_PACKED fli_chunk
                //	   {
                //	   LONG size;
                //	   WORD type;
                //	   };
                // ...
                // uncompfli(f, frame, colors)
                //   Vscreen *f;
                //   struct fli_frame *frame;
                //   int colors;	/ * update color registers? * /
                // {
                // ...
                // char *c;
                // struct fli_chunk *chunk;
                // c = (char *)(frame+1);
                // chunk = (struct fli_chunk *)c;
                // ...
                switch (lbx_chunk_type)
                {
                    case LBX_FLI_LC:
                        //unlccomp((const UBYTE *)(chunk+1), f->p);
                        break;
                    case LBX_FLI_BRUN:
                        //unbrun((const UBYTE *)(chunk+1), f->p, f->h);
                        // void unbrun(const UBYTE *src, UBYTE *dst, unsigned int linect);

                        break;
                    default:
                        break;
                }
                */



                /* ********************* *
                 *                       *
                 *   BEGIN: Decode RLE   *
                 *                       *
                 * ********************* */



                /*
                   FLI_LC Chunks
                   This is the most common, and alas, most complex chunk.
                   The first WORD (16 bits) is the number of lines starting from the top of the screen that are the same as the previous frame.
                   (If there is motion only on the bottom line of screen you'd have a 199 here.)
                   The next WORD is the number of lines that do change.
                   Next there is the data for the changing lines themselves.
                   Each line is compressed individually (which makes it much easier to play back the FLI 1/4 size among other things.)
                   The first byte of a compressed line is the number of packets in this line.
                   If the line is unchanged from the last frame this is zero.
                   The format of an individual packet is:
                       skip_count    size_count    data
                   The skip count is a single byte.
                   If more than 255 pixels are to be skipped it must be broken into 2 packets.
                   The size-count is also a byte.
                   If it is positive then that many bytes of data follow, and are copied to the screen.
                   If it's negative a single byte follows, and is repeated -skip_count times.

                   FLI_BRUN  Chunks
                    These are much like FLI_LC chunks without the skips.
                    They start immediately with the data for the first line,
                      and go line by line from there.
                    The first byte contains the number of packets in that line.
                    The format for a packet is: [size_count, data]
                    If size_count is positive
                      the data consists of a single byte
                      which is repeated size_count times.
                    If size_count is negative
                      there is -size_count bytes of data
                      which is copied to the screen.
                 */

                /*
                 * In the VP/ANI source code, "line count" is the height  i.e., not as in (horizontal) lines on the screen, but (vertical) columns.
                 *
                 * So, line_count decrements from h to 0...
                 *    while calling unbrun_copy(), without line_count
                 *    then incrementing 'dst' by WIDTH (AKA 320)
                 * There is no check for {0x00, 0x80, 0xFF}
                 *
                 * ...
                 * I'm still not getting something here...
                 * The outer most loop is the image width. e.g., 320 for a 'full-screen' image.
                 * ?So, they are to be 320 FLIC_LC chunks?
                 *   while < WIDTH
                 * The first WORD (16 bits) (?signed?) is the number of lines to skip AKA that are the same as the previous frame,
                 *   which is some case is a FLIC_BLACK frame - ? the default /frame 0/ ?
                 * The second WORD (16 bits) (?signed?) is the number of lines to change.
                 * Then comes the line change data...
                 * ... ? "...each line is compressed individually..." ?
                 * Line:
                 * 1B number of packets in this line - 0 if unchanged from previous frame
                 * Packet:
                 * 1B skip_count
                 * 1B size_count - positive: 'copy n bytes 1 time'; negative: 'copy 1 byte n times'
                 *
                 *
                 */

                char obsolete_operation_count_byte1;
                obsolete_operation_count_byte1 = *(char *) &record_data[frame_data_offset_begin + 0];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: obsolete_operation_count_byte1: %02X (%d)\n", obsolete_operation_count_byte1, obsolete_operation_count_byte1);

                char br_packet_size_count1;
                br_packet_size_count1 = *(char *) &record_data[frame_data_offset_begin + 1];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: br_packet_size_count1: %02X (%d)\n", br_packet_size_count1, br_packet_size_count1);

                char br_packet_data1;
                br_packet_data1 = *(char *) &record_data[frame_data_offset_begin + 2];
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: br_packet_data1: %02X (%d)\n", br_packet_data1, br_packet_data1);

                int is_begin_line;
                is_begin_line = 0;
                int is_end_line;
                is_end_line = 0;

                int byte_run_line_length;
                byte_run_line_length = lbx_image_header->width;

                int image_lines;
                image_lines = lbx_image_header->height;

                int itr_image_lines;
                itr_image_lines = lbx_image_header->height;

                char * ptr_record_data;
                ptr_record_data = record_data;
                ptr_record_data = ptr_record_data + frame_data_offset_begin;

                char obsolete_operation_count_byte;
                char br_packet_size_count;
                int br_packet_size_count_uchar;













                int cnt_encoded_byte_length;
                cnt_encoded_byte_length = 0;
                int cnt_decoded_byte_length;
                cnt_decoded_byte_length = 0;

                /*
                 * Width, Columns,
                 * Height, Rows,
                 */
                while (--itr_image_lines >= 0)
                {
                    if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: Decoding BRUN Line %d\n", lbx_image_header->height - itr_image_lines);

                    is_begin_line = 1;

                    br_packet_size_count = 0;

                    if (is_begin_line == 1)
                    {
                        obsolete_operation_count_byte = *ptr_record_data;
                        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: obsolete_operation_count_byte: %02X (%d)\n", obsolete_operation_count_byte, obsolete_operation_count_byte);
                        ptr_record_data = ptr_record_data + 1;
                        cnt_encoded_byte_length = cnt_encoded_byte_length + 1;
                    }

                    br_packet_size_count = *ptr_record_data;
                    if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: br_packet_size_count: %02X (%d)\n", br_packet_size_count, br_packet_size_count);
                    ptr_record_data = ptr_record_data + 1;
                    cnt_encoded_byte_length = cnt_encoded_byte_length + 1;

                    /* J:\STU\DBWD\developc\_AnimatorPro\src\COMMON\unbrun_.c */
                    /* static const UBYTE * unbrun_copy(const UBYTE *src, UBYTE *dst) */

                    if (br_packet_size_count >= 0)  /* positive: repeat 1 byte n times */
                    {
                        /* J:\STU-EduMat\_FileFormats\FLIC\__Dr Dobbs Journal 199303 - contains FLIC ASC and ARC\9303\flic_arc\PCCLONE.C */
                        /* screen_repeat_one(s, x, y, *cpt++, psize); */

                        if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: repeating %02X, %d times\n", *ptr_record_data, br_packet_size_count);
                        memset(ptr_image_data_decoded_buffer, *ptr_record_data, br_packet_size_count);
                        ptr_record_data = ptr_record_data + 1;                                                  /* advance the next byte ion the RLE data */
                        ptr_image_data_decoded_buffer = ptr_image_data_decoded_buffer + br_packet_size_count;   /* advance as many bytes as were set */
                        cnt_encoded_byte_length = cnt_encoded_byte_length + 1;
                        cnt_decoded_byte_length = cnt_decoded_byte_length + br_packet_size_count;
                    }
                    else  /* negative: copy n bytes 1 time */
                    {
                        /* J:\STU-EduMat\_FileFormats\FLIC\__Dr Dobbs Journal 199303 - contains FLIC ASC and ARC\9303\flic_arc\PCCLONE.C */
                        /*screen_copy_seg(s, x, y, (Pixel far *)cpt, psize);*/

                        /* ~= absolute value; just switching the sign, on a known negative number */
                        /*br_packet_size_count = -br_packet_size_count;*/
                        /*br_packet_size_count = (char)(br_packet_size_count * -1);*/
                        /*br_packet_size_count = (unsigned)-br_packet_size_count;*/
                        /*br_packet_size_count = abs(br_packet_size_count);*/
                        /*br_packet_size_count = (br_packet_size_count^-(br_packet_size_count < 0)) + (br_packet_size_count < 0);*/
                        /*br_packet_size_count_uchar = (unsigned char)br_packet_size_count;*/
                        /*if (br_packet_size_count == 0x80)*/
                        /*if (br_packet_size_count == 0b10000000)*/
                        /*if (br_packet_size_count == -128)*/
                        /*if (br_packet_size_count == -0x80)*/
                        if (br_packet_size_count == -128) /* -128, (signed) char */
                        {
                            if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: ERMAHGERD It's Negative One-Twenty-Eight!!\n");
                            /*br_packet_size_count = 128;*/
                            br_packet_size_count_uchar = (unsigned char)br_packet_size_count;
                            if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: br_packet_size_count_uchar: %02X (%d)\n", br_packet_size_count_uchar, br_packet_size_count_uchar);

                            if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: copying %d bytes (%02X...)\n", br_packet_size_count_uchar, *ptr_record_data);
                            memcpy(image_data_decoded_buffer, ptr_record_data, br_packet_size_count_uchar);               /* copy the prescribed number of bytes */
                            ptr_record_data = ptr_record_data + br_packet_size_count_uchar;                               /* advance as many bytes as were copied */
                            ptr_image_data_decoded_buffer = ptr_image_data_decoded_buffer + br_packet_size_count_uchar;   /* advance as many bytes as were copied */
                            cnt_encoded_byte_length = cnt_encoded_byte_length + br_packet_size_count_uchar;
                            cnt_decoded_byte_length = cnt_decoded_byte_length + br_packet_size_count_uchar;
                        }
                        else /* {-127, ..., -1} */
                        {
                            /*if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: copying %d bytes (%X...)\n", br_packet_size_count, *ptr_record_data);*/
                            /*if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: copying %d bytes (%X...)\n", (unsigned)((br_packet_size_count<0)?-br_packet_size_count:br_packet_size_count), *ptr_record_data);*/
                            br_packet_size_count = -br_packet_size_count;
                            if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: copying %d bytes (%02X...)\n", br_packet_size_count, *ptr_record_data);
                            memcpy(image_data_decoded_buffer, ptr_record_data, br_packet_size_count);               /* copy the prescribed number of bytes */
                            ptr_record_data = ptr_record_data + br_packet_size_count;                               /* advance as many bytes as were copied */
                            ptr_image_data_decoded_buffer = ptr_image_data_decoded_buffer + br_packet_size_count;   /* advance as many bytes as were copied */
                            cnt_encoded_byte_length = cnt_encoded_byte_length + br_packet_size_count_uchar;
                            cnt_decoded_byte_length = cnt_decoded_byte_length + br_packet_size_count_uchar;
                        }
                    }
                    if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: cnt_encoded_byte_length: %02X (%d)\n", cnt_encoded_byte_length, cnt_encoded_byte_length);
                    if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: cnt_decoded_byte_length: %02X (%d)\n", cnt_decoded_byte_length, cnt_decoded_byte_length);
                }



                /* ********************* *
                 *                       *
                 *   BEGIN: Decode RLE   *
                 *                       *
                 * ********************* */




                /* ***************************** *
                 *                               *
                 *   END: LBX IMAGE Frame Data   *
                 *                               *
                 * ***************************** */




                /* J:\STU\DBWD\developc\_AnimatorPro\src\V\fli.c */
                /*
                     #include "unbrun_.h"
                     unbrun((const UBYTE *)(chunk+1), f->p, f->h);
                */
                /* J:\STU\DBWD\developc\_AnimatorPro\src\V\Makefile.tc */
                /*
                   	..\COMMON\unbrun_.obj
                */
                /* J:\STU\DBWD\developc\_AnimatorPro\src\COMMON\unbrun_.h */
                /*
                   / * Function: unbrun
                     *
                     *  Decompress 1st frame full size.
                     *
                     *  src - compressed source.  See FLI.DOC for details.
                     *  dst - byte plane to decompress onto.
                     *  linect - number of lines of screen (always 320 now.)
                     * /
                   extern void unbrun(const UBYTE *src, UBYTE *dst, unsigned int linect);
                */




                /* ********************* *
                 *                       *
                 *   BEGIN: MS BMP/DIB   *
                 *                       *
                 * ********************* */

                /* Image image_data_buffer Buffer Size, General Equation:
                 *     (Image Width * Image Height * Bytes Per Pixel)
                */






                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp_image_bytes_buffer = (char *)malloc(pixel_data_length);\n");
                char * bmp_image_bytes_buffer;
                bmp_image_bytes_buffer = (char *)malloc(pixel_data_length);
                if (bmp_image_bytes_buffer == nullptr)
                {
                    printf("FAILURE: bmp_image_bytes_buffer = (char *)malloc(%d);\n", pixel_data_length);
                    exit(EXIT_FAILURE);
                }
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp_image_bytes_buffer = (char *)malloc(pixel_data_length);\n");



                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: [findme]\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



                /*
                char * ptr;
                for (int x_coord = 0; x_coord < lbx_image_header->width; ++x_coord)
                {
                    for (int y_coord = 0; y_coord < lbx_image_header->height; ++y_coord)
                    {
                        image.setPixel(x_coord, y_coord, *ptr);
                        ptr++;
                    }
                }
                */

































                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp_file->bmp_bitmap_file_header = (BMP_BITMAP_FILE_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n");
                bmp_file->bmp_bitmap_file_header = (BMP_BITMAP_FILE_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));
                if (bmp_file == nullptr)
                {
                    printf("bmp_file->bmp_bitmap_file_header = (BMP_BITMAP_FILE_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n", sizeof(BMP_BITMAP_FILE_HEADER));
                    exit(EXIT_FAILURE);
                }
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp_file->bmp_bitmap_file_header = (BMP_BITMAP_FILE_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n");



                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: bmp_file->bmp_bitmap_info_header = (BMP_BITMAP_INFO_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n");
                bmp_file->bmp_bitmap_info_header = (BMP_BITMAP_INFO_HEADER *)malloc(sizeof(BMP_BITMAP_INFO_HEADER));
                if (bmp_file == nullptr)
                {
                    printf("FAILURE: bmp_file->bmp_bitmap_info_header = (BMP_BITMAP_INFO_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n", sizeof(BMP_BITMAP_FILE_HEADER));
                    exit(EXIT_FAILURE);
                }
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: bmp_file->bmp_bitmap_info_header = (BMP_BITMAP_INFO_HEADER *)malloc(sizeof(BMP_BITMAP_FILE_HEADER));\n");



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
                /* if (BmpHead->WinInfo.BitCount != 24 || BmpHead->WinInfo.ClrUsed != 0) */
                /* BMP_BITMAP_FILE_HEADER: */
                bmp_file->bmp_bitmap_file_header->bfType = BMP_MAGIC;
                bmp_file->bmp_bitmap_file_header->bfSize = bmp_file_size;  /* 4294967296 - 1;  / * 2^32 * / */
                bmp_file->bmp_bitmap_file_header->bfReserved1 = 0;
                bmp_file->bmp_bitmap_file_header->bfReserved2 = 0;
                bmp_file->bmp_bitmap_file_header->bfOffBits = 14 + 40 + 1024;
                /* BMP_BITMAP_INFO_HEADER: */
                bmp_file->bmp_bitmap_info_header->biSize = 40;
                bmp_file->bmp_bitmap_info_header->biWidth = 320;
                bmp_file->bmp_bitmap_info_header->biHeight = 200;
                bmp_file->bmp_bitmap_info_header->biPlanes = 1;
                bmp_file->bmp_bitmap_info_header->biBitCount = 8;
                bmp_file->bmp_bitmap_info_header->biCompression = 0;
                bmp_file->bmp_bitmap_info_header->biSizeImage = pixel_data_length; /* (4294967296 - 1) - (14 + 40) - (256 * 4);  / * 2^32 - Headers - Palette * / */
                bmp_file->bmp_bitmap_info_header->biXPelsPerMeter = BMP_XPELS_PER_METER_DEFAULT;
                bmp_file->bmp_bitmap_info_header->biYPelsPerMeter = BMP_YPELS_PER_METER_DEFAULT;
                bmp_file->bmp_bitmap_info_header->biClrUsed = 256;  /* ~= "Use the maximum number of colors corresponding to the value of BitCount */
                bmp_file->bmp_bitmap_info_header->biClrImportant = 256;  /* ~= "NIU" */

                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_file_header->bfType: %04X\n", bmp_file->bmp_bitmap_file_header->bfType);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_file_header->bfSize: %08X\n", bmp_file->bmp_bitmap_file_header->bfSize);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_file_header->bfReserved1: %04X\n", bmp_file->bmp_bitmap_file_header->bfReserved1);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_file_header->bfReserved2: %04X\n", bmp_file->bmp_bitmap_file_header->bfReserved2);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_file_header->bfOffBits: %08X\n", bmp_file->bmp_bitmap_file_header->bfOffBits);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biSize: %08X\n", bmp_file->bmp_bitmap_info_header->biSize);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biWidth: %08X\n", bmp_file->bmp_bitmap_info_header->biWidth);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biHeight: %08X\n", bmp_file->bmp_bitmap_info_header->biHeight);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biPlanes: %04X\n", bmp_file->bmp_bitmap_info_header->biPlanes);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biBitCount: %04X\n", bmp_file->bmp_bitmap_info_header->biBitCount);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biCompression: %08X\n", bmp_file->bmp_bitmap_info_header->biCompression);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biSizeImage: %08X\n", bmp_file->bmp_bitmap_info_header->biSizeImage);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biXPelsPerMeter: %08X\n", bmp_file->bmp_bitmap_info_header->biXPelsPerMeter);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biYPelsPerMeter: %08X\n", bmp_file->bmp_bitmap_info_header->biYPelsPerMeter);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biClrUsed: %08X\n", bmp_file->bmp_bitmap_info_header->biClrUsed);
                if (LBXMGR_DEBUG_STRUGGLE_MODE) printf("DEBUG: bmp_file->bmp_bitmap_info_header->biClrImportant: %08X\n", bmp_file->bmp_bitmap_info_header->biClrImportant);





                //BITMAPFILEHEADER fileHeader;
                //BITMAPINFOHEADER infoHeader;

                //FILE *fp;
                int downToUp = 1; // 1: 下から上にデータが並ぶ（通常） 0: 逆転（上から下）  // 1: image_data_buffer is lined up from bottom to top (normal) 0: Reverse (top to bottom)
                unsigned char * image_data_buffer; // イメージデータを格納する領域  // Area for storing image data
                unsigned int image_data_buffer_size;// イメージのバイトサイズ  // Image byte image_data_buffer_size

                int w, h, image_width, image_height; // カウンタ、縦横値の保存場所  // Counter, storage location of vertical and horizontal values
                int image_line_size; // 横一列ぶんのデータのバイト数  // Number of bytes of data in a horizontal row
                unsigned char * image_line_data_buffer; // 横一列ぶんのデータの領域  // A horizontal row of data area

                // 縦横サイズの確認
                // Confirmation of vertical and horizontal image_data_buffer_size
                image_width = bmp_file->bmp_bitmap_info_header->biWidth;
                image_height = bmp_file->bmp_bitmap_info_header->biHeight;
                /*debugMsg("width = %d, height = %d\n", infoHeader.biWidth, infoHeader.biHeight);*/
                if (image_height < 0) { // もし height が負の数の場合、それは「上から下」に向けてデータが並んでいることを意味する。
                    downToUp = 0;
                    image_height *= -1;
                    /*debugMsg("(up to down scanned data)\n");*/
                }

                // ファイル先頭から所定位置までスキップしてビットマップデータ部分にジャンプ
                // Skip from the beginning of the file to the specified position and jump to the bitmap data part
                /*fseek(fp, bmp_file->bmp_bitmap_file_header->bfOffBits, SEEK_SET);*/

                // 画像サイズの計算
                // Image image_data_buffer_size calculation
                int bytes_per_pixel = bmp_file->bmp_bitmap_info_header->biBitCount / 8; // 画素あたりのバイト数を出しておく  // Get the number of bytes per pixel
                image_data_buffer_size = image_width * image_height * bytes_per_pixel; // メモリサイズ  // Memory image_data_buffer_size
                image_data_buffer = (unsigned char *)malloc(image_data_buffer_size);
                if (image_data_buffer == NULL) {
                    /*errorMsg("cannot alocate memory for the picture (%d bytes)\n", image_data_buffer_size);*/
                    return 1;
                }
                /*debugMsg("image_data_buffer %p (%d bytes allocated)\n", image_data_buffer, image_data_buffer_size);*/

                // ラインごとに読むための準備
                // 横 1 ラインのバイト数を求める（4バイトアライメント必須なので width * pixSize にパディングが有り得る）
                // Preparing to read line by line
                // side 1 Find the number of bytes in a line（4 Because byte alignment is essential width * pixSize Can have padding）
                image_line_size = image_width * bytes_per_pixel; // とりあえず一行あたりの最低バイト数を求めておく  // For the time being, find the minimum number of bytes per line
                if ((image_line_size % 4) != 0)
                {
                    image_line_size = ((image_line_size / 4) + 1) * 4; // 境界ピッタリでなければ 4byte 境界にあわせる  // If it's not perfect for the boundary 4byte Align with boundaries
                }
                // debugMsg("image_line_size = %d\n", image_line_size);
                // ラインバッファを用意
                // Prepare a line buffer
                image_line_data_buffer = (unsigned char *)malloc(image_line_size);
                if (image_data_buffer == NULL) {
                    /*errorMsg("cannot alocate memory for line buffer (%d bytes)\n", image_line_size);*/
                    return 1;
                }




                /*
                lbx_uint8 * lbx_uint8_buffer;
                lbx_uint8 lbx_uint8_buffer_length;
                lbx_uint8 lbx_uint8_buffer_element_size;
                lbx_uint8 lbx_uint8_buffer_element_count;

                display_lbx_uint8_array_as_hexadecimal(lbx_uint8_buffer, lbx_uint8_buffer_length, lbx_uint8_buffer_element_size, lbx_uint8_buffer_element_count);
                */





                /* Meh. BMP stores RGB as BGR... */
                /* So. Convert LBX RGB Palette to MS BMP/DIB xBGR Palette... */

                /*
                 * FUU... I suck so hard at this sort of thing - just no mental frame-work... High-IQ Moron?
                 * ...
                 * itr Color Count ... times something, plus something...
                 * ...
                 * bmp_bgrx_quad[0] = 0
                 * bmp_bgrx_quad[1] = lbx_palette[2]
                 * bmp_bgrx_quad[2] = lbx_palette[1]
                 * bmp_bgrx_quad[3] = lbx_palette[0]
                 * ...
                 * bmp_bgrx_quad[4] = 0
                 * bmp_bgrx_quad[5] = lbx_palette[5]
                 * bmp_bgrx_quad[6] = lbx_palette[4]
                 * bmp_bgrx_quad[7] = lbx_palette[3]
                 * ...
                 * bmp_bgrx_quad[8] = 0
                 * bmp_bgrx_quad[9] = lbx_palette[2]
                 * bmp_bgrx_quad[10] = lbx_palette[1]
                 * bmp_bgrx_quad[11] = lbx_palette[0]
                 * ...
                 * ...
                 * itr Color Count = 0
                 *  0 = 0 + 0 ... (0 * 4) + 0
                 *  1 = 0 + 1 ... (0 * 4) + 1       2 = (0 * 4) + 2 ... (0 * 4) + (-itr + 2)
                 *  2 = 0 + 2 ... (0 * 4) + 2       1 = (0 * 4) + 1 ... (0 * 4) + (-itr + 1)
                 *  3 = 0 + 3 ... (0 * 4) + 3       0 = (0 * 4) + 0 ... (0 * 4) + (-itr + 0)
                 * ...
                 * itr Color Count = 1
                 *  4 = 1 + 0 ... (1 * 4) + 0
                 *  5 = 1 + 1 ... (1 * 4) + 1       5 = (1 * 4) + 1 ... (1 * 4) + (-itr + 2)
                 *  6 = 1 + 2 ... (1 * 4) + 2       4 = (1 * 4) + 0 ... (1 * 4) + (-itr + 1)
                 *  7 = 1 + 3 ... (1 * 4) + 3       3 = (1 * 4) - 1 ... (1 * 4) + (-itr + 0)
                 * ...
                 * itr Color Count = 2
                 *  8 = 2 + 0 ... (2 * 4) + 0
                 *  9 = 2 + 1 ... (2 * 4) + 1       8 = (2 * 4) + 0 ... (2 * 4) + (-itr + 2)
                 * 10 = 2 + 2 ... (2 * 4) + 2       7 = (2 * 4) - 1 ... (2 * 4) + (-itr + 1)
                 * 11 = 2 + 3 ... (2 * 4) + 3       6 = (2 * 4) - 2 ... (2 * 4) + (-itr + 0)
                 * ...
                 * ...
                 * Next up, {0,1023} by 226's...
                 *
                 */
