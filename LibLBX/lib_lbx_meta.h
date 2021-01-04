#ifndef LIB_LBX_META_H
#define LIB_LBX_META_H

#include "lib_lbx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void populate_all_lbx_meta_data(LBX_DATA * lbx);
void populate_lbx_header_meta_data(LBX_DATA * lbx);
void populate_lbx_file_meta_data(LBX_DATA * lbx);
void populate_lbx_info_meta_data(LBX_DATA * lbx);
void populate_lbx_record_meta_data(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_META_H */
