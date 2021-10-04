#ifndef LIB_LBX_RECORD_IMAGE_H
#define LIB_LBX_RECORD_IMAGE_H

#include "lib_lbx.h"
#include "lbx_record_type_flic.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

LBX_FLIC_INFO_HEADER * get_lbx_image_header(LBX_DATA * lbx, int entry_number);
LBX_FLIC_PALETTE_HEADER * get_lbx_image_custom_palette_header(LBX_DATA * lbx, int entry_number);
void lbx_load_image_record(LBX_FLIC_RECORD_HEADER * image_record, char * image_record_data);

#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_RECORD_IMAGE_H */
