#ifndef LIB_LBX_RECORD_TYPE_H
#define LIB_LBX_RECORD_TYPE_H

#include "lib_lbx.h"


/* Inhibit C++ name-mangling for lib_lbx functions, but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int is_record_type_empty(LBX_DATA * lbx, unsigned int entry_number);

int liblbx_deduce_lbx_record_type(LBX_DATA * lbx, unsigned char * record_data, unsigned int record_size, char * file_name, unsigned int entry_index);

int get_record_type(LBX_DATA * lbx, unsigned int entry_number);


#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_RECORD_TYPE_H */
