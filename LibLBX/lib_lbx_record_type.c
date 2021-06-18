
#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <string.h> /* strncpy() */
#include "lib_lbx_record_type.h"
#include "lib_lbx.h"
#include "lib_lbx_types.h"
#include "lib_lbx_record.h"
#include "lib_lbx_record_subrecord.h"

int get_record_type(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_type()\n");

    int have_record_type;
    int record_type;
    int tmp_record_size;
    int tmp_subrecord_count;
    char * record_data;

    record_type = LBX_RECORD_TYPE_UNKNOWN;
    have_record_type = 0;

    tmp_record_size = get_record_size(lbx, entry_number);

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
    }

    /*
     * Custom
     */
    if (have_record_type != 1)
    {
        if (tmp_record_size < 4)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: tmp_record_size < 4\n");
            record_type =  LBX_RECORD_TYPE_CUSTOM;
            have_record_type = 1;
        }
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
    }

    /*
     * Sound
     */
    if (have_record_type != 1)
    {
        record_data = get_record_data(lbx, entry_number);
        uint16_t sound_record_magic = *(uint16_t*)&record_data[0];
        uint16_t sound_record_type_magic = *(uint16_t*)&record_data[2];
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_magic: %d\n", sound_record_magic);
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic: %d\n", sound_record_type_magic);
        if (sound_record_magic == LBX_SOUND_MAGIC)
        {
            if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_magic == LBX_SOUND_MAGIC\n");

            if (sound_record_type_magic == LBX_SOUND_XMIDI_TYPE_MAGIC)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_XMIDI_TYPE_MAGIC\n");
                record_type = LBX_RECORD_TYPE_SOUND_XMIDI;
                have_record_type = 1;
            }
            else if (sound_record_type_magic == LBX_SOUND_VOC_TYPE_MAGIC)
            {
                if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: sound_record_type_magic == LBX_SOUND_VOC_TYPE_MAGIC\n");
                record_type = LBX_RECORD_TYPE_SOUND_VOC;
                have_record_type = 1;
            }
            else
            {
                record_type = LBX_RECORD_TYPE_SOUND_UNKNOWN;
                have_record_type = 1;
            }
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
        if (strcmp(ail_ail_magic, LBX_AIL_AIL_DRIVER_MAGIC_STRING) == 0)
        {
            record_type = LBX_RECORD_TYPE_AIL_AIL_DRIVER;
            have_record_type = 1;
        }
    }

    /*
     * Font
     */
    if (have_record_type != 1)
    {
        if (strcmp(lbx->meta->meta_file_name, "FONTS.LBX") == 0)
        {
            if (entry_number < 2)
            {
                record_type = LBX_RECORD_TYPE_FONT;
                have_record_type = 1;
            }
            if (entry_number >= 2)
            {
                record_type = LBX_RECORD_TYPE_PALETTE;
                have_record_type = 1;
            }
        }
    }

    /*
     * Image
     */
    if (have_record_type != 1)
    {
        uint16_t image_height = *(uint16_t*)&record_data[0];
        uint16_t image_width = *(uint16_t*)&record_data[2];
        if ((image_height >= 3) && (image_height <= 320) && (image_width >= 3) && (image_width <= 200))
        {
            record_type = LBX_RECORD_TYPE_IMAGES;
            have_record_type = 1;
        }
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_type()\n");
    return record_type;
}
