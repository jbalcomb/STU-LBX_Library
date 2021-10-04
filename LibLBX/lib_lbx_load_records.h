#ifndef LIB_LBX_LOAD_RECORDS_H
#define LIB_LBX_LOAD_RECORDS_H

#include "lib_lbx.h"

/* Inhibit C++ name-mangling for lib_lbx functions, but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void liblbx_populate_lbx_record_file_name_base(LBX_DATA * lbx);
void liblbx_load_lbx_record_data(LBX_DATA * lbx);
void liblbx_populate_lbx_record_type(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_LOAD_RECORDS_H */
