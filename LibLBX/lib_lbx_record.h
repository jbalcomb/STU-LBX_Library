#ifndef LIB_LBX_RECORD_H
#define LIB_LBX_RECORD_H

#include "lib_lbx.h"

/* Inhibit C++ name-mangling for lib_lbx functions, but not for system calls. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char * get_record_data(LBX_DATA * lbx, unsigned int entry_number);
unsigned int get_record_size(LBX_DATA * lbx, unsigned int entry_number);
unsigned long int get_record_checksum_crc32(LBX_DATA * lbx, unsigned int entry_number);
char * get_record_file_name_base(LBX_DATA * lbx, unsigned int entry_number);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_RECORD_H */
