#ifndef LIB_LBX_UTIL_H
#define LIB_LBX_UTIL_H

#include <stdio.h>

#include "lib_lbx.h"
#include "lib_lbx_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint16_t liblbx_read_2byte_le(FILE * file_stream);
uint32_t liblbx_read_4byte_le(FILE * file_stream);

/* char * convert_number_to_string_with_padding(int number, int length); */
char * liblbx_convert_entry_index_to_string(int entry_number, int string_length);

void liblbx_directory_path_and_file_name(LBX_DATA * lbx);
void liblbx_file_name_base(LBX_DATA * lbx);

size_t liblbx_file_size_via_seek(FILE * file_stream);

void liblbx_earliest_timestamp_via_stat(LBX_DATA * lbx);

int liblbx_compute_crc32_char_buffer(char * char_buffer_in, size_t char_buffer_length, unsigned long int * crc32_out);
int liblbx_compute_crc32_file(FILE * file_stream, unsigned long int * crc32_out);
unsigned long liblbx_compute_crc32(unsigned long crc32_in, const void * buf, size_t bufLen);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_LBX_UTIL_H */
