#ifndef LIB_LBX_PROCESS_RECORD_H
#define LIB_LBX_PROCESS_RECORD_H

#include "lib_lbx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void liblbx_load_lbx_record_headers(LBX_DATA * lbx);
void liblbx_process_lbx_records(LBX_DATA * lbx);
void process_lbx_record(char * lbx);

#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_PROCESS_RECORD_H */
