#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_record_flic.h"
#include "lib_lbx_record_palette.h"


/* J:\STU\DBWD\developc\_AnimatorPro\src\PJ\rastlib\cmapshif.c */
/*#include "cmap.h"*/

/* function: pj_shift_cmap */
void
AA_pj_shift_cmap(const AA_UBYTE *src, AA_UBYTE *dst, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        dst[i] = src[i] * 4;
}
void
AA_pj_shift_cmap_meh(unsigned char *src, unsigned char *dst, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        dst[i] = src[i] * 4;
        if (i < 48 || i > 719)
        {
            printf("[%u] %u (0x%02X) %u (0x%02X)\n",
                   i,
                   src[i],
                   src[i],
                   dst[i],
                   dst[i]);
        }
    }
}


/*!
 * loads FLIC Frame structure for each frame_raw
 * @param lbx
 */
void liblbx_load_lbx_record_flic_frame_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_load_lbx_record_flic_frame_data()\n");

    int itr_entry_index;
    lbx_uint16 itr_frame_index;
    lbx_uint32 tmp_frame_size;
    lbx_uint32 tmp_frame_data_size;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++)
    {


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%u].headers->flic->lbx_flic_frames = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAMES_DATA));
        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames = malloc(sizeof(LBX_FLIC_FRAMES_DATA));
        if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames == NULL)
        {
            printf("FAILURE: lbx->record->entry[%u].headers->flic->lbx_flic_frames = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAMES_DATA));
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%u].headers->flic->lbx_flic_frames = malloc(%u);\n", itr_entry_index, sizeof(LBX_FLIC_FRAMES_DATA));


        for (itr_frame_index = 0; itr_frame_index < lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count; itr_frame_index++)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frame_offset_table->entry[%d].begin: %u\n", itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index].begin);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frame_offset_table->entry[%d].begin: %u\n", itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index + 1].begin);

            tmp_frame_size = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index + 1].begin - lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index].begin;
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_frame_size: %u\n", tmp_frame_size);


            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_raw = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);
            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_raw = malloc(tmp_frame_size);
            if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_raw == NULL)
            {
                printf("FAILURE: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_raw = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);
                exit(EXIT_FAILURE);
            }
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_raw = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);

            /*
            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame_raw[itr_frame_index].frame_raw
            fseek(lbx->file->file_stream, lbx->header->offset_table->entry[itr_entry_index].begin, SEEK_SET);
            fread(lbx->record->entry[itr_entry_index].record_buffer, 1, lbx->record->entry[itr_entry_index].size, lbx->file->file_stream);
            */
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->header->offset_table->entry[%d].begin: %u (0x%2X)\n", itr_entry_index, lbx->header->offset_table->entry[itr_entry_index].begin, lbx->header->offset_table->entry[itr_entry_index].begin);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frame_offset_table->entry[%d].begin: %u (0x%2X)\n", itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index].begin, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index].begin);
            lbx_uint32 tmp_offset_to_lbx_record_flic_frame_data = lbx->header->offset_table->entry[itr_entry_index].begin + lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frame_offset_table->entry[itr_frame_index].begin;
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d]: tmp_offset_to_lbx_record_flic_frame_data: %u (0x%2X)\n", itr_entry_index, itr_frame_index, tmp_offset_to_lbx_record_flic_frame_data, tmp_offset_to_lbx_record_flic_frame_data);
            fseek(lbx->file->file_stream, tmp_offset_to_lbx_record_flic_frame_data, SEEK_SET);
            fread(lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_raw, 1, tmp_frame_size, lbx->file->file_stream);

            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type = *(lbx_uint16 *) &lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_raw[0];
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_header.frame_type: %u (0x%2X)\n", itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type);

            // tmp_frame_data_size = tmp_frame_size - sizeof(lbx_uint16);
            tmp_frame_data_size = tmp_frame_size - 1;
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_frame_data_size: %u (0x%02X)\n", tmp_frame_data_size, tmp_frame_data_size);

            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_data = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_data_size);
            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data = malloc(tmp_frame_data_size);
            if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data == NULL)
            {
                printf("FAILURE: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_data = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_data_size);
                exit(EXIT_FAILURE);
            }
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame_raw[%d].frame_data = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_data_size);

            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data_size = tmp_frame_data_size;

            memcpy(
                    lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data,
                    &lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_raw[0 + sizeof(lbx_uint8)],
                    lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data_size
                    );

        }

    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_load_lbx_record_flic_frame_data()\n");
}

/*!
 * frame_type = 1
 * @param lbx
 */
void liblbx_decompress_flic_rle_record_data(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_decompress_flic_rle_record_data()\n");

    /*lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame_raw[itr_frame_index].frame_header.frame_type*/
    /* if frame_type = 1 */

//    int itr_entry_index = 0;
//    int itr_frame_index =0;
    unsigned int itr_entry_index;
    unsigned int itr_frame_index;
    unsigned int itr_frame_data;

    lbx_uint16 tmp_frame_count;
    lbx_uint16 tmp_frame_height;
    lbx_uint16 tmp_frame_width;

    lbx_uint32 tmp_frame_data_size;

    for (itr_entry_index = 0; itr_entry_index < lbx->header->entry_count; itr_entry_index++) {

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: THIS ENTRY: %u\n", itr_entry_index);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].record_file_name_base: %s\n", itr_entry_index, lbx->record->entry[itr_entry_index].record_file_name_base);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].size: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].size);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].type: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].type);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->have_loaded_flic_header: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].headers->have_loaded_flic_header);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_info_header->frame_count: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count);

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_info_header->frame_height: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_info_header->frame_width: %u\n", itr_entry_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width);
        // lbx->record[itr_entry_index].entry->
        // lbx->record->entry[itr_entry_index].
        // lbx->record[%d].entry->
        // lbx->record->entry[%u].
        // lbx->record[%u].entry->
        // lbx->record->entry[%u].
        // lbx->record->entry[%d].
        // lbx->record->entry[%u].
        
        
        tmp_frame_height = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height;
        tmp_frame_width = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width;
        lbx_size tmp_frame_size;

        tmp_frame_size = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height *
                         lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width;
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_frame_size: %u\n", tmp_frame_size);

        tmp_frame_count = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_count;


        /* ******************** *
         *                      *
         *   BEGIN: Frame Loop  *
         *                      *
         * ******************** */

        for (itr_frame_index = 0; itr_frame_index < tmp_frame_count; itr_frame_index++) {

            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame[%u].decoded_frame_buffer = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);
            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer = malloc(tmp_frame_size);
            if (lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer == NULL) {
                printf("FAILURE: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame[%u].decoded_frame_buffer = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);
                exit(EXIT_FAILURE);
            }
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame[%u].decoded_frame_buffer = malloc(%u);\n", itr_entry_index, itr_frame_index, tmp_frame_size);


            unsigned char *ptr_decoded_frame_buffer;
            ptr_decoded_frame_buffer = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer;

            //memset(lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, 0, tmp_frame_size);
            /* Set all colors to RED for debugging purposes */
            //memset(lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, 211, tmp_frame_size);
            //memset(lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, 203, tmp_frame_size);
            memset(lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer, 207, tmp_frame_size);
            // Magenta #FF00FF 255,0,255
            /* 320x200 = 64000 pixels, RGB = 3 bytes per pixel; 64,000 * 3 = 192,000 bytes; */
//            int itr_decoded_frame_buffer_color;
//            for (itr_decoded_frame_buffer_color = 0; itr_decoded_frame_buffer_color <= tmp_frame_size;)
//            {
//                *ptr_decoded_frame_buffer = 255;
//                ptr_decoded_frame_buffer++;
//                *ptr_decoded_frame_buffer = 0;
//                ptr_decoded_frame_buffer++;
//                *ptr_decoded_frame_buffer = 255;
//                ptr_decoded_frame_buffer++;
//
//                itr_decoded_frame_buffer_color =  itr_decoded_frame_buffer_color + 3;
//            }

            ptr_decoded_frame_buffer = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer;


//            // lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette = lbx_load_palette_by_number(2);
//            lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_palette = liblbx_load_palette(g_palette_file_path, EMPERATO);


            tmp_frame_data_size = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data_size;
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: lbx->record->entry[%u].headers->flic->lbx_flic_frames->frame[%u].frame_data_size: %u;\n", itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data_size);



//    int len_frame_data_baito = snprintf(NULL, 0, "0x%02X", *(((char *) &lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data) + 0));
//    char * str_frame_data_baito = malloc(len_frame_data_baito);
//    for (itr_frame_data = 0; itr_frame_data < tmp_frame_data_size; itr_frame_data++)
//    {
//        snprintf(str_frame_data_baito, len_frame_data_baito, "0x%02X", *(((char *) &lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data) + itr_frame_data));
//        printf("str_frame_data_baito[%d]: %s\n", itr_frame_data, str_frame_data_baito);
//
//    }
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_frame_data: %d;\n", itr_frame_data);
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: len_frame_data_baito: %d;\n", len_frame_data_baito);
//    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: str_frame_data_baito: %s;\n", str_frame_data_baito);

            int nth_bit_index; //to store bit
            nth_bit_index = 8;
            unsigned char bit_mask_zero = 0x00;
            unsigned char bitmask_negative_one_twenty_eight = 0x80;
            unsigned char bitmask_negative_one = 0xFF;

            unsigned char *ptr_tmp_flic_frame_data_encoded_buffer;
            ptr_tmp_flic_frame_data_encoded_buffer = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_data;

            unsigned char frame_data_baito;
            unsigned char rle_packet_operation_code;

            int rle_packet_index;
            rle_packet_index = 0;

            int column_index_maximum;
            column_index_maximum = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_width - 1;
            int itr_column_index;
            int row_index_maximum;
            row_index_maximum = lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_info_header->frame_height - 1;
            int itr_row_index;

            unsigned char copy_sequence_count;
            int itr_copy_sequence_count;

            unsigned char packet_byte_count;
            unsigned char sequence_byte_count;
            unsigned char delta_byte_count;
            int itr_packet_byte_count;
            int itr_sequence_byte_count;

            int repeat_byte_count;
            int int_repeat_byte_count;

            unsigned char sequence_baito;
            unsigned char repeat_baito;

            int delta_balance;

            int encoded_buffer_index;
            encoded_buffer_index = 0;
            int decoded_buffer_index;
            decoded_buffer_index = 0;

            /* TODO(JWB): refactor this like FLIC Lib, where the copy and decode operations are separate functions, with (*dst,*src) */
            for (itr_column_index = 0; itr_column_index <= column_index_maximum; itr_column_index++) {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Image Column: [%d of %d]\n", itr_column_index, column_index_maximum);
                itr_row_index = 0;

                frame_data_baito = *ptr_tmp_flic_frame_data_encoded_buffer;
                /*if (LBX_DEBUG_STRUGGLE_MODE) printf("frame_data_baito[%d]: %02X\n", encoded_buffer_index, frame_data_baito);*/
                ptr_tmp_flic_frame_data_encoded_buffer++;
                encoded_buffer_index++;

                /* TODO(JWB): capture the first byte of every frame in every FLIC in every LBX */

                /*
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bit_mask_zero (%d & %d): %d;\n", frame_data_baito, bit_mask_zero, (frame_data_baito & bit_mask_zero));
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bitmask_negative_one_twenty_eight (%d & %d): %d;\n", frame_data_baito, bitmask_negative_one_twenty_eight, (frame_data_baito & bitmask_negative_one_twenty_eight));
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bitmask_negative_one (%d & %d): %d;\n", frame_data_baito, bitmask_negative_one, (frame_data_baito & bitmask_negative_one));
                / * (NUM & (1<<nth_bit_index)) * /
                //checking bit status
                if(frame_data_baito & (1 << nth_bit_index))
                    printf("Bit number %d is SET in number %d.\n", nth_bit_index, frame_data_baito);
                else
                    printf("Bit number %d is not SET in number %d.\n", nth_bit_index, frame_data_baito);
                */

                /* RLE Packet Operation Code {0x00, 0x80, 0xFF} */
                if (frame_data_baito == 0x00) {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("The RLE Operation Code is 0x00 - Copy Sequence.\n");
                    rle_packet_operation_code = frame_data_baito;

//                    copy_sequence_count = *ptr_tmp_flic_frame_data_encoded_buffer;
//                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: copy_sequence_count: 5u (%02X)\n", copy_sequence_count, copy_sequence_count);
//                    ptr_tmp_flic_frame_data_encoded_buffer++;
//                    encoded_buffer_index++;

                    packet_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: packet_byte_count: %u (%02X)\n", packet_byte_count, packet_byte_count);
                    ptr_tmp_flic_frame_data_encoded_buffer++;
                    encoded_buffer_index++;

//                    for (itr_copy_sequence_count = 0; itr_copy_sequence_count < copy_sequence_count; itr_copy_sequence_count++) {
//                        *ptr_decoded_frame_buffer = *ptr_tmp_flic_frame_data_encoded_buffer;
//                        ptr_tmp_flic_frame_data_encoded_buffer++;
//                        encoded_buffer_index++;
//                        ptr_decoded_frame_buffer++;
//                        decoded_buffer_index++;
//                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);
//                        itr_row_index++;
//                    }
//                    rle_packet_index++;

                    for (itr_packet_byte_count = 0; itr_packet_byte_count < packet_byte_count;) {
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_packet_byte_count: %d [packet_byte_count: %u]\n", itr_packet_byte_count, packet_byte_count);

                        sequence_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sequence_byte_count: %u (%02X)\n", sequence_byte_count, sequence_byte_count);
                        ptr_tmp_flic_frame_data_encoded_buffer++;
                        encoded_buffer_index++;
                        itr_packet_byte_count++;

                        delta_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: delta_byte_count: %u (%02X)\n", delta_byte_count, delta_byte_count);
                        ptr_tmp_flic_frame_data_encoded_buffer++;
                        encoded_buffer_index++;
                        itr_packet_byte_count++;

                        if (delta_byte_count != 0) {
                            ptr_decoded_frame_buffer = ptr_decoded_frame_buffer + delta_byte_count;
                            decoded_buffer_index = decoded_buffer_index + delta_byte_count;
                            itr_row_index = itr_row_index + delta_byte_count;
                            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: decoded_buffer_index: %u\n", decoded_buffer_index);
                        }

                        for (itr_sequence_byte_count = 0; itr_sequence_byte_count < sequence_byte_count; itr_sequence_byte_count++) {
                            sequence_baito = *ptr_tmp_flic_frame_data_encoded_buffer;
                            ptr_tmp_flic_frame_data_encoded_buffer++;
                            encoded_buffer_index++;

                            *ptr_decoded_frame_buffer = sequence_baito;
                            ptr_decoded_frame_buffer++;
                            decoded_buffer_index++;

                            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);
                            itr_row_index++;
                        }

                        itr_packet_byte_count = itr_packet_byte_count + sequence_byte_count;
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_packet_byte_count: %d [packet_byte_count: %u]\n", itr_packet_byte_count, packet_byte_count);
                    }


                } else if (frame_data_baito == 0x80) {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("The RLE Operation Code is 0x80 - Decode Sequence.\n");
                    rle_packet_operation_code = frame_data_baito;
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: rle_packet_operation_code: %u (%02X)\n", rle_packet_operation_code, rle_packet_operation_code);

                    packet_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: packet_byte_count: %u (%02X)\n", packet_byte_count, packet_byte_count);
                    ptr_tmp_flic_frame_data_encoded_buffer++;
                    encoded_buffer_index++;

                    for (itr_packet_byte_count = 0; itr_packet_byte_count < packet_byte_count;) {
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_packet_byte_count: %d [packet_byte_count: %u]\n", itr_packet_byte_count, packet_byte_count);

                        sequence_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sequence_byte_count: %u (%02X)\n", sequence_byte_count, sequence_byte_count);
                        ptr_tmp_flic_frame_data_encoded_buffer++;
                        encoded_buffer_index++;
                        itr_packet_byte_count++;

                        delta_byte_count = *ptr_tmp_flic_frame_data_encoded_buffer;
                        if (LBX_DEBUG_STRUGGLE_MODE)
                            printf("DEBUG: delta_byte_count: %u (%02X)\n", delta_byte_count, delta_byte_count);
                        ptr_tmp_flic_frame_data_encoded_buffer++;
                        encoded_buffer_index++;
                        itr_packet_byte_count++;

                        if (delta_byte_count != 0) {
                            ptr_decoded_frame_buffer = ptr_decoded_frame_buffer + delta_byte_count;
                            decoded_buffer_index = decoded_buffer_index + delta_byte_count;
                            itr_row_index = itr_row_index + delta_byte_count;
                            if (LBX_DEBUG_STRUGGLE_MODE)
                                printf("DEBUG: decoded_buffer_index: %u\n", decoded_buffer_index);
                        }

                        for (itr_sequence_byte_count = 0; itr_sequence_byte_count < sequence_byte_count;) {
                            sequence_baito = *ptr_tmp_flic_frame_data_encoded_buffer;
                            ptr_tmp_flic_frame_data_encoded_buffer++;
                            encoded_buffer_index++;

                            if (sequence_baito >= 224) {
                                itr_sequence_byte_count = itr_sequence_byte_count + 2;

                                repeat_byte_count = sequence_baito - 223;

                                repeat_baito = *ptr_tmp_flic_frame_data_encoded_buffer;
                                ptr_tmp_flic_frame_data_encoded_buffer++;
                                encoded_buffer_index++;

                                if (LBX_DEBUG_STRUGGLE_MODE)
                                    printf("DEBUG: Copy x%u: %02X\n", repeat_byte_count, repeat_baito);

                                for (int_repeat_byte_count = 0;
                                     int_repeat_byte_count < repeat_byte_count; int_repeat_byte_count++) {
                                    *ptr_decoded_frame_buffer = repeat_baito;
                                    ptr_decoded_frame_buffer++;
                                    decoded_buffer_index++;
                                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);
                                    itr_row_index++;
                                }
                            } else {
                                itr_sequence_byte_count = itr_sequence_byte_count + 1;

                                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Copy 1: %02X\n", sequence_baito);
                                *ptr_decoded_frame_buffer = sequence_baito;
                                ptr_decoded_frame_buffer++;
                                decoded_buffer_index++;
                                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);
                                itr_row_index++;
                            }

                        }

                        itr_packet_byte_count = itr_packet_byte_count + sequence_byte_count;
                        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_packet_byte_count: %d [packet_byte_count: %u]\n", itr_packet_byte_count, packet_byte_count);
                    }

                    rle_packet_index++;
                } else if (frame_data_baito == 0xFF) {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("The RLE Operation Code is 0xFF - Skip.\n");
                    rle_packet_index++;
                    itr_row_index = row_index_maximum;
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);
                } else {
                    printf("ERROR: Unknown RLE Operation Code! [file: %s entry: %u frame: %u type: %u baito: 0x%0X]\n", lbx->file->file_name, itr_entry_index, itr_frame_index, lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].frame_header.frame_type, frame_data_baito);
                }

                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: itr_row_index: %d\n", itr_row_index);

//        /* Short-Circuit */
//        if (encoded_buffer_index >= 200)
//        {
//            break;
//        }

                delta_balance = row_index_maximum - (itr_row_index - 1);
                if (LBX_DEBUG_STRUGGLE_MODE)
                    printf("DEBUG: Delta Balance: %d (%d - %d)\n", delta_balance, row_index_maximum, itr_row_index);
                /* Assumption of delta for balance of column */
                ptr_decoded_frame_buffer = ptr_decoded_frame_buffer + delta_balance;
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: decoded_buffer_index: %u\n", decoded_buffer_index);
                decoded_buffer_index = decoded_buffer_index + delta_balance;
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: decoded_buffer_index: %u\n", decoded_buffer_index);

//        if (decoded_buffer_index != (200 + (itr_column_index * 200)))
//        {
//            exit(EXIT_FAILURE);
//        }
            }
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: ALL DONE!!\n");
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: rle_packet_index: %d\n", rle_packet_index);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: encoded_buffer_index: %d\n", encoded_buffer_index);
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: decoded_buffer_index: %d\n", decoded_buffer_index);



            if (itr_entry_index == 0 && itr_frame_index == 0)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: TRUE: if (itr_entry_index == 0 && itr_frame_index == 0)\n");
                /* char * export_file_path; */
                char export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN000_FF0.BIN";
                FILE *ptr_stream_file_out;
                ptr_stream_file_out = fopen(export_file_path, "wb");
                if (ptr_stream_file_out == NULL)
                {
                    printf("FAILURE: fopen(%s, \"wb\");\n", export_file_path);
                    exit(EXIT_FAILURE);
                }
                fwrite(
                        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer,
                        sizeof(*lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer),
                        decoded_buffer_index,
                        ptr_stream_file_out
                        );
                fclose(ptr_stream_file_out);
            }

            if (itr_entry_index == 1 && itr_frame_index == 0)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: TRUE: if (itr_entry_index == 1 && itr_frame_index == 0)\n");
                /* char * export_file_path; */
                char export_file_path[] = "C:\\Development\\STU-LBX_Library\\docs\\MAIN001_FF0.BIN";
                FILE *ptr_stream_file_out;
                ptr_stream_file_out = fopen(export_file_path, "wb");
                if (ptr_stream_file_out == NULL)
                {
                    printf("FAILURE: fopen(%s, \"wb\");\n", export_file_path);
                    exit(EXIT_FAILURE);
                }
                fwrite(
                        lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer,
                        sizeof(*lbx->record->entry[itr_entry_index].headers->flic->lbx_flic_frames->frame[itr_frame_index].decoded_frame_buffer),
                        decoded_buffer_index, ptr_stream_file_out
                        );
                fclose(ptr_stream_file_out);
            }

            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NEXT FRAME!!\n");
        }

        /* ******************** *
         *                      *
         *   END: Frame Loop    *
         *                      *
         * ******************** */


        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NEXT ENTRY!!\n");
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_decompress_flic_rle_record_data()\n");
}