#ifndef LIB_LBX_LBX_H
#define LIB_LBX_LBX_H

#include "lbx_defs.h"
#include "lbx_types.h"
//#include "lbx_record_type_flic.h"


struct s_LBX_HEADER_OFFSET_TABLE_ENTRY{
    lbx_uint32 begin;
};
typedef struct s_LBX_HEADER_OFFSET_TABLE_ENTRY LBX_HEADER_OFFSET_TABLE_ENTRY;

struct s_LBX_HEADER_OFFSET_TABLE{
    LBX_HEADER_OFFSET_TABLE_ENTRY entry[LBX_ENTRY_COUNT_MAXIMUM];
};
typedef struct s_LBX_HEADER_OFFSET_TABLE LBX_HEADER_OFFSET_TABLE;


struct s_LBX_HEADER_STRING_TABLE_ENTRY {
    char name[LBX_LENGTH_STRING_TABLE_ENTRY_NAME];
    char description[LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION];
};
typedef struct s_LBX_HEADER_STRING_TABLE_ENTRY LBX_HEADER_STRING_TABLE_ENTRY;

struct s_LBX_HEADER_STRING_TABLE{
    LBX_HEADER_STRING_TABLE_ENTRY entry[LBX_ENTRY_COUNT_MAXIMUM];
};
typedef struct s_LBX_HEADER_STRING_TABLE LBX_HEADER_STRING_TABLE;

struct s_LBX_HEADER {
    lbx_uint16 entry_count;
    lbx_uint16 magic;
    lbx_uint16 unknown;
    lbx_uint16 type;
    LBX_HEADER_OFFSET_TABLE * offset_table;
    LBX_HEADER_STRING_TABLE * string_table;
};
typedef struct s_LBX_HEADER LBX_HEADER;


#endif  /* LIB_LBX_LBX_H */
