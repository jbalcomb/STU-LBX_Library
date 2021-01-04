#ifndef LIB_LBX_UTIL_H
#define LIB_LBX_UTIL_H

#include "lib_lbx.h"
#include "lib_lbx_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint16_t lbx_read_2byte_le(FILE * file_stream);
uint32_t lbx_read_4byte_le(FILE * file_stream);

void lbx_file_path_and_file_name(LBX_DATA * lbx);
void lbx_file_name_base(LBX_DATA * lbx);

size_t lbx_file_size_via_seek(FILE * file_stream);

void lbx_earliest_timestamp_via_stat(LBX_DATA * lbx);

int lbx_compute_crc32_char_buffer(char * char_buffer_in, size_t char_buffer_length, unsigned long int * crc32_out);
int lbx_compute_crc32_file(FILE * file_stream, unsigned long int * crc32_out);
unsigned long lbx_compute_crc32(unsigned long crc32_in, const void * buf, size_t bufLen);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_UTIL_H */
