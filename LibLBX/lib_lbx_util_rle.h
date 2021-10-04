#ifndef LIB_LBX_UTIL_RLE_H
#define LIB_LBX_UTIL_RLE_H

#include "lbx_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void decompress_lbx_new_frame_line_compressed_flic_frame(lbx_uint8 * dst, lbx_uint8 * src);
void decompress_lbx_delta_frame_line_compressed_flic_frame(lbx_uint8 * dst, lbx_uint8 * src);
void process_lbx_image_frame_data(lbx_uint8 * dst, lbx_uint8 * src);

#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_UTIL_RLE_H */
