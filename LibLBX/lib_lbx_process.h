#ifndef LIB_LBX_PROCESS_H
#define LIB_LBX_PROCESS_H

#include "lib_lbx.h"

/* Inhibit C++ name-mangling for lib_lbx functions, but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int lbx_process_records(LBX_DATA * lbx);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_PROCESS_H */
