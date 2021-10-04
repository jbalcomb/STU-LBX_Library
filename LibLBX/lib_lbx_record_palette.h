#ifndef LIB_LBX_RECORD_PALETTE_H
#define LIB_LBX_RECORD_PALETTE_H

#ifndef LBX_RECORD_TYPE_PALETTE_H
#include "lbx_record_type_palette.h"
#endif  /* LBX_RECORD_TYPE_PALETTE_H */

#define PALETTE_COLOR_COUNT 256
#define PALETTE_BYTE_COUNT 768

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void colormap_shift(unsigned char *src, unsigned char *dst, unsigned int n);
unsigned char * liblbx_load_palette_record(char * lbx_palette_file_path, int lbx_palette_number);
unsigned char * liblbx_load_palette(char * lbx_palette_file_path, int lbx_palette_number);
void liblbx_export_palette(char * lbx_palette_file_path, int lbx_palette_number, char * export_palette_file_path_base);
void lbx_load_palette_all(void);
/*LBX_PALETTE * lbx_load_palette_by_number(int palette_number);*/
lbx_uint8 * lbx_load_palette_by_number(int palette_number);
/*LBX_PALETTE * lbx_load_palette_by_file_name(char * LbxFileName);*/
lbx_uint8 * lbx_load_palette_by_file_name(char * LbxFileName);

#ifdef __cplusplus
}
#endif


#endif  /* LIB_LBX_RECORD_PALETTE_H */
