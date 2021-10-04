#ifndef LIB_LBX_LOAD_H
#define LIB_LBX_LOAD_H


#include "lib_lbx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void liblbx_load_lbx(LBX_DATA * lbx);
void lbx_unload_lbx_file(LBX_DATA * lbx);
unsigned char * liblbx_load_lbx_entry(char * lbx_file_path, int lbx_entry_index);

#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_LOAD_H */
