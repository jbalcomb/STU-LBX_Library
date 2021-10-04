#ifndef LIB_LBX_RECORD_DISPLAY_H
#define LIB_LBX_RECORD_DISPLAY_H

#include "lib_lbx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void liblbx_display_lbx_record_file_name_base(LBX_DATA * lbx);
void liblbx_display_lbx_record_type(LBX_DATA * lbx);
void liblbx_display_lbx_record_headers_long(LBX_DATA * lbx);
void liblbx_display_lbx_record_headers_wide(LBX_DATA * lbx);

void liblbx_display_lbx_record_flic_header(LBX_DATA * lbx);

void display_lbx_flic_header(LBX_DATA * lbx, unsigned int entry_number);
void display_lbx_image_custom_palette_header(LBX_DATA * lbx, unsigned int entry_number);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_RECORD_DISPLAY_H */
