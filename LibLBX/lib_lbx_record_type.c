#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <string.h> /* strncpy() */

#include "lib_lbx_record_type.h"
#include "lib_lbx.h"
#include "lib_lbx_types.h"
#include "lib_lbx_record.h"
#include "lib_lbx_record_subrecord.h"
#include "lib_lbx_record_display.h"


int is_record_type_empty(LBX_DATA * lbx, unsigned int entry_number)
{
    int is_record_type_empty;
    unsigned int tmp_record_size;

    tmp_record_size = get_record_size(lbx, entry_number);

    if (tmp_record_size == 0) {
        is_record_type_empty = 1;
    } else {
        is_record_type_empty = 0;
    }

    return is_record_type_empty;
}


int liblbx_deduce_lbx_record_type(LBX_DATA * lbx, unsigned char * record_data, unsigned int record_size, char * file_name, unsigned int entry_index)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: liblbx_deduce_lbx_record_type()\n");

    int have_record_type;
    int record_type;
    int tmp_subrecord_count;

    record_type = LBX_RECORD_TYPE_UNKNOWN;
    have_record_type = 0;


    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_size: %d\n", record_size);

    /*
     * Empty
     */
    if (have_record_type != 1)
    {
        if (record_size == 0)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: record_size == 0\n");
            record_type =  LBX_RECORD_TYPE_EMPTY;
            have_record_type = 1;
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_EMPTY\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping EMPTY...\n");
    }


    /*
     * Font
     */
    /* TODO(JWB): make this not use hard-coded file name and entry number */
    if (have_record_type != 1)
    {
        if (strcmp(lbx->file->file_name, "FONTS.LBX") == 0)
        {
            if (entry_index < 2)
            {
                record_type = LBX_RECORD_TYPE_FONT;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_FONT\n");
            }
            if (entry_index >= 2)
            {
                record_type = LBX_RECORD_TYPE_PALETTE;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_PALETTE\n");
            }
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_FONT\n");
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_PALETTE\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping FONT...\n");
    }

    /*
     * Custom
     */
    if (have_record_type != 1)
    {
        if (record_size < 4)
        {
            record_type =  LBX_RECORD_TYPE_CUSTOM;
            have_record_type = 1;
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_CUSTOM\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping CUSTOM...\n");
    }

    if (have_record_type != 1)
    {
        /*
     * All the checks after this point require the record_data
     */
        /*record_data = get_record_data(lbx, entry_index);*/

        lbx_uint16 bytes_1to2 = *(lbx_uint16*)&record_data[0];
        lbx_uint16 bytes_3to4 = *(lbx_uint16*)&record_data[2];
        lbx_uint16 bytes_5to6 = *(lbx_uint16*)&record_data[4];
        lbx_uint16 bytes_7to8 = *(lbx_uint16*)&record_data[6];

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[0,1]: %d\n", bytes_1to2);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[2,3]: %d\n", bytes_3to4);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[4,5]: %d\n", bytes_5to6);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[6,7]: %d\n", bytes_7to8);


        /*
         * Array
         */
        if (have_record_type != 1)
        {
            /*tmp_subrecord_count = get_record_subrecord_count(lbx, entry_index);*/
            if (4 + bytes_1to2 * bytes_3to4 == record_size)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Sub-Record Count: %d\n", bytes_1to2);
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Sub-Record Size: %d\n", bytes_3to4);
                record_type = LBX_RECORD_TYPE_ARRAY;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_ARRAY\n");
            }
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping ARRAY...\n");
        }

        /*
         * Image
         */
        if (have_record_type != 1)
        {
            if ((bytes_1to2 >= 3) && (bytes_1to2 <= 320) && (bytes_3to4 >= 3) && (bytes_3to4 <= 200))
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Frame Width: %d\n", bytes_1to2);
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Frame Height: %d\n", bytes_3to4);

                if (bytes_7to8 == 1)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Frame Count: %d\n", bytes_7to8);
                    /* record_type = LBX_RECORD_TYPE_IMAGE; */
                    record_type = LBX_RECORD_TYPE_FLIC;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Frame Count: %d\n", bytes_7to8);
                    /* record_type = LBX_RECORD_TYPE_ANIMATION; */
                    record_type = LBX_RECORD_TYPE_FLIC;
                    have_record_type = 1;
                }
            }
            else
            {
                /*
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_IMAGE\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_ANIMATION\n");
                */
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_FLIC\n");
            }
        }

        /*
         * Sound
         */
        if (have_record_type != 1)
        {
            if (bytes_1to2 == LBX_SOUND_MAGIC)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_magic == LBX_SOUND_MAGIC\n");
                record_type = LBX_RECORD_TYPE_SOUND_UNKNOWN;
                have_record_type = 1;

                if (bytes_3to4 == LBX_SOUND_XMIDI_TYPE_MAGIC)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_XMIDI_TYPE_MAGIC\n");
                    record_type = LBX_RECORD_TYPE_SOUND_XMIDI;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_XMIDI\n");
                }
                if (bytes_3to4 == LBX_SOUND_VOC_TYPE_MAGIC)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_VOC_TYPE_MAGIC\n");
                    record_type = LBX_RECORD_TYPE_SOUND_VOC;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_VOC\n");
                }
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_XMIDI\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_VOC\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_UNKNOWN\n");
            }
        }

        /*
     * Driver
     */
        if (have_record_type != 1)
        {
            char ail_digpak_magic[7];
            strncpy(ail_digpak_magic, &record_data[3], 6);
            ail_digpak_magic[6] = 0;
            char ail_ail_magic[43];
            strncpy(ail_ail_magic, &record_data[2], 42);
            ail_ail_magic[42] = 0;

            if (strcmp(ail_digpak_magic, LBX_AIL_DIGPAK_DRIVER_MAGIC_STRING) == 0)
            {
                record_type = LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER\n");
            }
            if (strcmp(ail_ail_magic, LBX_AIL_AIL_DRIVER_MAGIC_STRING) == 0)
            {
                record_type = LBX_RECORD_TYPE_AIL_AIL_DRIVER;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_AIL_AIL_DRIVER\n");
            }
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping IMAGE, ANIMATION, SOUND_XMIDI, SOUND_VOC, SOUND_UNKNOWN, AIL_DIGPAK_DRIVER, AIL_AIL_DRIVER...\n");
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: record_type: %d\n", record_type);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: liblbx_deduce_lbx_record_type()\n");
    return record_type;
}


int get_record_type(LBX_DATA * lbx, unsigned int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_type()\n");

    int have_record_type;
    int record_type;
    int tmp_record_size;
    int tmp_subrecord_count;
    char * record_data;

    tmp_record_size = 0;

    record_type = LBX_RECORD_TYPE_UNKNOWN;
    have_record_type = 0;

    tmp_record_size = get_record_size(lbx, entry_number);

    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_record_size: %d\n", tmp_record_size);

    /*
     * Empty
     */
    if (have_record_type != 1)
    {
        if (tmp_record_size == 0)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_record_size == 0\n");
            record_type =  LBX_RECORD_TYPE_EMPTY;
            have_record_type = 1;
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_EMPTY\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping EMPTY...\n");
    }


    /*
     * Font
     */
    if (have_record_type != 1)
    {
        if (strcmp(lbx->file->file_name, "FONTS.LBX") == 0)
        {
            if (entry_number < 2)
            {
                record_type = LBX_RECORD_TYPE_FONT;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_FONT\n");
            }
            if (entry_number >= 2)
            {
                record_type = LBX_RECORD_TYPE_PALETTE;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_PALETTE\n");
            }
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_FONT\n");
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_PALETTE\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping FONT...\n");
    }

    /*
     * Custom
     */
    if (have_record_type != 1)
    {
        if (tmp_record_size < 4)
        {
            record_type =  LBX_RECORD_TYPE_CUSTOM;
            have_record_type = 1;
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_CUSTOM\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping CUSTOM...\n");
    }

    /*
     * Array
     */
    if (have_record_type != 1)
    {
        tmp_subrecord_count = get_record_subrecord_count(lbx, entry_number);
        if (tmp_subrecord_count > 0)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_subrecord_count > 0\n");
            record_type = LBX_RECORD_TYPE_ARRAY;
            have_record_type = 1;
        }
        else
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_ARRAY\n");
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping ARRAY...\n");
    }

    if (have_record_type != 1)
    {
        /*
     * All the checks after this point require the record_Data
     */
        record_data = get_record_data(lbx, entry_number);

        uint16_t bytes_1to2 = *(uint16_t*)&record_data[0];
        uint16_t bytes_3to4 = *(uint16_t*)&record_data[2];
        uint16_t bytes_5to6 = *(uint16_t*)&record_data[4];
        uint16_t bytes_7to8 = *(uint16_t*)&record_data[6];

        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[0,1]: %d\n", bytes_1to2);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[2,3]: %d\n", bytes_3to4);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[4,5]: %d\n", bytes_5to6);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Bytes[6,7]: %d\n", bytes_7to8);

        /*
         * Image
         */
        if (have_record_type != 1)
        {
            if ((bytes_1to2 >= 3) && (bytes_1to2 <= 320) && (bytes_3to4 >= 3) && (bytes_3to4 <= 200))
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_1to2: %d\n", bytes_1to2);
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_3to4: %d\n", bytes_3to4);

                if (bytes_7to8 == 1)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_5to6: %d\n", bytes_5to6);
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_7to8: %d\n", bytes_7to8);
                    /* record_type = LBX_RECORD_TYPE_IMAGE; */
                    record_type = LBX_RECORD_TYPE_FLIC;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_5to6: %d\n", bytes_5to6);
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: bytes_7to8: %d\n", bytes_7to8);
                    /* record_type = LBX_RECORD_TYPE_ANIMATION; */
                    record_type = LBX_RECORD_TYPE_FLIC;
                    have_record_type = 1;
                }
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_IMAGE\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_ANIMATION\n");
            }
        }

        /*
         * Sound
         */
        if (have_record_type != 1)
        {
            if (bytes_1to2 == LBX_SOUND_MAGIC)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_magic == LBX_SOUND_MAGIC\n");
                record_type = LBX_RECORD_TYPE_SOUND_UNKNOWN;
                have_record_type = 1;

                if (bytes_3to4 == LBX_SOUND_XMIDI_TYPE_MAGIC)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_XMIDI_TYPE_MAGIC\n");
                    record_type = LBX_RECORD_TYPE_SOUND_XMIDI;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_XMIDI\n");
                }
                if (bytes_3to4 == LBX_SOUND_VOC_TYPE_MAGIC)
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_VOC_TYPE_MAGIC\n");
                    record_type = LBX_RECORD_TYPE_SOUND_VOC;
                    have_record_type = 1;
                }
                else
                {
                    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_VOC\n");
                }
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_XMIDI\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_VOC\n");
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_SOUND_UNKNOWN\n");
            }
        }

        /*
     * Driver
     */
        if (have_record_type != 1)
        {
            char ail_digpak_magic[7];
            strncpy(ail_digpak_magic, &record_data[3], 6);
            ail_digpak_magic[6] = 0;
            char ail_ail_magic[43];
            strncpy(ail_ail_magic, &record_data[2], 42);
            ail_ail_magic[42] = 0;

            if (strcmp(ail_digpak_magic, LBX_AIL_DIGPAK_DRIVER_MAGIC_STRING) == 0)
            {
                record_type = LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_AIL_DIGPAK_DRIVER\n");
            }
            if (strcmp(ail_ail_magic, LBX_AIL_AIL_DRIVER_MAGIC_STRING) == 0)
            {
                record_type = LBX_RECORD_TYPE_AIL_AIL_DRIVER;
                have_record_type = 1;
            }
            else
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: NOT LBX_RECORD_TYPE_AIL_AIL_DRIVER\n");
            }
        }
    }
    else
    {
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: Skipping IMAGE, ANIMATION, SOUND_XMIDI, SOUND_VOC, SOUND_UNKNOWN, AIL_DIGPAK_DRIVER, AIL_AIL_DRIVER...\n");
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: record_type: %d\n", record_type);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_type()\n");
    return record_type;
}
