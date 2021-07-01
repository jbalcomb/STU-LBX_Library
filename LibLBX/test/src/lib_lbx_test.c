#include <malloc.h>         /* malloc(), realloc(); */
#include <stdlib.h>         /* itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), strcat(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_test.h"

#include "../lib_lbx_record_flic.h"



void test()
{
    LBX_DATA * lbx;

    lbx->header->entry_count = 0x01;
    lbx->header->magic = 0xFEAD;
    lbx->header->unknown = 0x00;
    lbx->header->type = 0x00;

    char * frame_data_decoded;
    frame_data_decoded = malloc(64000);

    char * frame_data_encoded;
    frame_data_encoded = malloc(12275);
    char * ptr_frame_data_encoded;
    ptr_frame_data_encoded = frame_data_encoded;
    *ptr_frame_data_encoded = 0x01;
    ptr_frame_data_encoded++;
    *ptr_frame_data_encoded = 0x80;
    ptr_frame_data_encoded++;
    *ptr_frame_data_encoded = 0x0B;
    ptr_frame_data_encoded++;
    *ptr_frame_data_encoded = 0x09;
    ptr_frame_data_encoded++;
    *ptr_frame_data_encoded = 0x00;

    frame_data_encoded[0] = 0x01;
    frame_data_encoded[1] = 0x80;
    frame_data_encoded[2] = 0x0B;
    frame_data_encoded[3] = 0x09;
    frame_data_encoded[4] = 0x00;

    frame_data_encoded[12275] = 0xBB;


    int bad_baito;
    bad_baito = 0x80;
    char good_baito;
    good_baito = *(char *)&bad_baito;
    char AL_baito;
    AL_baito = (bad_baito & 0xFF);
    char mc_baito;
    memcpy(&mc_baito, (char *)&bad_baito, 1);
    char mc_baito_3;
    memcpy(&mc_baito_3, (char *)&bad_baito + 3, 1);
    char mc_baito_2;
    memcpy(&mc_baito_2, (char *)&bad_baito + 2, 1);
    char mc_baito_1;
    memcpy(&mc_baito_1, (char *)&bad_baito + 1, 1);
    char mc_baito_0;
    memcpy(&mc_baito_0, (char *)&bad_baito + 0, 1);
    char id_baito;
    id_baito = (char) bad_baito;
    printf("bad_baito: %d\n", bad_baito);
    printf("good_baito: %d\n", good_baito);
    printf("AL_baito: %d\n", AL_baito);
    printf("mc_baito: %d\n", mc_baito);
    printf("mc_baito_3: %d\n", mc_baito_3);
    printf("mc_baito_2: %d\n", mc_baito_2);
    printf("mc_baito_1: %d\n", mc_baito_1);
    printf("mc_baito_0: %d\n", mc_baito_0);
    printf("id_baito: %d\n", id_baito);

    exit(EXIT_SUCCESS);


    liblbx_decompress_flic_rle_record_data(lbx);

}

