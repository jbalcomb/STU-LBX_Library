#ifndef LIB_LBX_DISPLAY_H
#define LIB_LBX_DISPLAY_H

#include "lib_lbx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void lbx_display_header(LBX_DATA * lbx_data);
void lbx_display_header_preamble(LBX_DATA * lbx);
void lbx_display_header_offset_table(LBX_DATA * lbx_data);
void lbx_display_header_string_table(LBX_DATA * lbx_data);

void display_lbx_meta_data(LBX_DATA * lbx);
void display_lbx_file_meta_data(LBX_DATA * lbx);
void display_lbx_record_meta_data(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_DISPLAY_H */
