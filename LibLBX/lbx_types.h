#ifndef LIB_LBX_LBX_TYPES_H
#define LIB_LBX_LBX_TYPES_H


typedef signed char         lbx_int8;
typedef unsigned char       lbx_uint8;

typedef signed short        lbx_int16;
typedef unsigned short      lbx_uint16;

#if defined(__LONG_IS_4_BYTE__)
typedef signed long         lbx_uint32;
typedef unsigned long        lbx_uint32;
#else
typedef signed int          lbx_int32;
typedef unsigned int        lbx_uint32;
#endif

typedef unsigned int lbx_size;



/* C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\i686-w64-mingw32\include\stdint.h */
/*
/ * 7.18.1.1  Exact-width integer types * /
typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned   uint32_t;
__MINGW_EXTENSION typedef long long  int64_t;
__MINGW_EXTENSION typedef unsigned long long   uint64_t;
*/

/* C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\i686-w64-mingw32\include\crtdefs.h */
/*
    typedef unsigned int size_t;
*/

#endif  /* LIB_LBX_LBX_TYPES_H */
