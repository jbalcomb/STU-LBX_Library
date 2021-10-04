#ifndef LIB_LBX_RECORD_FLIC_H
#define LIB_LBX_RECORD_FLIC_H

#include "lib_lbx.h"

/* Inhibit C++ name-mangling for lib_lbx functions, but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void
AA_pj_shift_cmap(const AA_UBYTE *src, AA_UBYTE *dst, unsigned int n);
void
AA_pj_shift_cmap_meh(unsigned char *src, unsigned char *dst, unsigned int n);

void liblbx_decompress_flic_rle_record_data(LBX_DATA * lbx);
void liblbx_load_lbx_record_flic_frame_data(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_RECORD_FLIC_H */
