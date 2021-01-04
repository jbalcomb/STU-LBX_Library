#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */

#include "lib_lbx_record_subrecord.h"
#include "lib_lbx.h"
#include "lib_lbx_types.h"
#include "lib_lbx_record.h"



int get_record_subrecord_count(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_record_subrecord_count()\n");

    int subrecord_count;
    char * tmp_record_data;
    int tmp_record_size;
    int tmp_subrecord_count;
    int tmp_subrecord_size;

    tmp_record_data = get_record_data(lbx, entry_number);

    tmp_record_size = get_record_size(lbx, entry_number);

    tmp_subrecord_count = *(uint16_t*)&tmp_record_data[0];
    tmp_subrecord_size = *(uint16_t*)&tmp_record_data[2];

    if (tmp_record_size < 4)
    {
        subrecord_count = -1;
    }
    else if (4 + tmp_subrecord_count * tmp_subrecord_size == tmp_record_size)
    {
        subrecord_count = tmp_subrecord_count;
    }
    else
    {
        subrecord_count = -1;
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_record_subrecord_count()\n");
    return subrecord_count;
}
