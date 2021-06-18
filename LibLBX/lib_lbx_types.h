#ifndef LIB_LBX_TYPES_H
#define LIB_LBX_TYPES_H

// #include <crtdefs.h>        /* size_t; */

typedef unsigned char BINARY_FILE_BYTE;


/* SEE: Borland C++ 3.0: .\BORLANDC\CRTL\RTLINC\RULES.H */

/*      Precise types for portability and clarity of intent.

- chars are for strings or text (16 bits for Oriental or video buffers)
- ordinals are for indexes and offsets
- cardinals count how many of something
- integers can be negative
- bitsets are for bits, unknown patterns, and binary trickery
*/
typedef     signed char     lbx_int8;
typedef     short           lbx_int16;
/* typedef long         lbx_int32; */
typedef     int             lbx_int32;


/* SEE: Borland C++ 3.0: .\BORLANDC\INCLUDE\WINDOWS.H  */
#ifndef BYTE
typedef unsigned char       BYTE;
#endif
#ifndef CHAR
typedef char				CHAR;
#endif
#ifndef SHORT
typedef short				SHORT;
#endif
#ifndef WORD
typedef unsigned short      WORD;
#endif
#ifndef DWORD
/* typedef unsigned long       DWORD; */
typedef unsigned int       DWORD;
#endif


/*
    SEE: Borland C++ 3.0: .\BORLANDC\INCLUDE\WINDOWS.H
*/
/*
    SEE: Animator Pro: .\Animator-Pro\Pristine-Pro\INC\STDTYPES.H
        BYTE, UBYTE, etc is to keep code portable between different compilers
        where especially 'int' can mean different things.
*/

/* typedef unsigned char       LBX_BYTE; */
typedef signed char 	LBX_BYTE;
typedef unsigned char	LBX_UBYTE;
typedef char				LBX_CHAR;
/* typedef short				LBX_SHORT; */
typedef signed short	LBX_SHORT;
typedef unsigned short	LBX_USHORT;
typedef unsigned short      LBX_WORD;
/* typedef unsigned long       DWORD; */
typedef unsigned int       LBX_DWORD;
typedef signed long 	LBX_LONG;
typedef unsigned long	LBX_ULONG;
typedef double			LBX_FLOAT;
typedef LBX_UBYTE		   *LBX_PTR;


/* SEE: Borland C++ 3.0: .\BORLANDC\INCLUDE\WINDOWS.H  */
#ifndef BYTE
typedef unsigned char       BYTE;
#endif
#ifndef CHAR
typedef char				CHAR;
#endif
#ifndef SHORT
typedef short				SHORT;
#endif
#ifndef WORD
typedef unsigned short      WORD;
#endif
#ifndef DWORD
/* typedef unsigned long       DWORD; */
typedef unsigned int       DWORD;
#endif

/* SEE: libpng-1.5.4 pngconf.h */
#if defined(INT_MAX) && (INT_MAX > 0x7ffffffeL)
typedef unsigned int lbx_uint_32;
typedef int lbx_int_32;
#else
typedef unsigned long lbx_uint_32;
typedef long lbx_int_32;
#endif
typedef unsigned short lbx_uint_16;
typedef short lbx_int_16;
typedef unsigned char lbx_byte;
#ifdef LBX_NO_SIZE_T
typedef unsigned int lbx_size_t;
#else
/* crtdefs.h: typedef unsigned int size_t; */
typedef unsigned int lbx_size_t;
#endif
#define lbx_sizeof(x) (sizeof (x))

/* C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\i686-w64-mingw32\include\crtdefs.h
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#undef size_t
#ifdef _WIN64
__MINGW_EXTENSION typedef unsigned __int64 size_t;
#else
typedef unsigned int size_t;
#endif / * _WIN64 * /
#endif / * _SIZE_T_DEFINED * /
*/

/* SEE: C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\i686-w64-mingw32\include\crtdefs.h */
/*
 * #ifndef _SIZE_T_DEFINED
 * #define _SIZE_T_DEFINED
 * #undef size_t
 * #ifdef _WIN64
 * __MINGW_EXTENSION typedef unsigned __int64 size_t;
 * #else
 * typedef unsigned int size_t;
 * #endif / * _WIN64 * /
 * #endif / * _SIZE_T_DEFINED * /
*/

/* SEE: stdint.h */
/* /usr/include/sys/types.h */
/* /usr/include/stdio.h */
typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned   uint32_t;
/* typedef long long  int64_t; */
/* typedef unsigned long long   uint64_t; */

#endif  /* LIB_LBX_TYPES_H */
