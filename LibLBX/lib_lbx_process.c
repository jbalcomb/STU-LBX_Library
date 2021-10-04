
#include <stdio.h>  /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */

#include "lib_lbx_process.h"
#include "lib_lbx.h"
#include "lib_lbx_display.h"
#include "lib_lbx_util.h"



int lbx_process_records(LBX_DATA * lbx)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: lbx_process_records()\n");

    int itr_entry_count;

    for (itr_entry_count = 0; itr_entry_count < lbx->header->entry_count; itr_entry_count++)
    {
        /* lbx->records->entry[itr_entry_count].size = lbx->header->offset_table->entry[itr_entry_count + 1].begin - lbx->header->offset_table->entry[itr_entry_count].begin; */

        /*
         * Record Type
         *
         * ..if type = ARRAY {  }
         */

        if (lbx->meta->records->entry[itr_entry_count].type == LBX_RECORD_TYPE_SOUND_XMIDI)
        {

        }

    }

    if (LBX_DEBUG_MODE) printf("DEBUG: END: lbx_process_records()\n");
    return 0;
}
