#ifndef LIB_LBX_LBX_DEFS_H
#define LIB_LBX_LBX_DEFS_H

#define LBX_FILE_EXTENSION "LBX"
#define LBX_MAGIC 0xFEAD                                /* (Little-Endian Bytes: 0xAD 0xFE) */
#define LBX_SOUND_MAGIC 0xDEAF                          /* Little-Endian Bytes: 0xAF 0xDE */ /* DEAFh = 57007d; AFDEh = 45022; DEh = 222d; AFh = 175d */
#define LBX_SOUND_XMIDI_MAGIC 0xDEAF0001                /* Little-Endian Bytes: 0xAF 0xDE 0x01 0x00 */
#define LBX_SOUND_VOC_MAGIC 0xDEAF0002                  /* Little-Endian Bytes: 0xAF 0xDE 0x02 0x00 */
#define LBX_SOUND_XMIDI_TYPE_MAGIC 0x0001               /* Little-Endian Bytes: 0x01 0x00 */
#define LBX_SOUND_VOC_TYPE_MAGIC 0x0002                 /* Little-Endian Bytes: 0x02 0x00 */
#define LBX_AIL_DRIVER_MAGIC 0x002D
#define LBX_AIL_AIL_DRIVER_MAGIC_STRING "Copyright (C) 1991,1992 Miles Design, Inc."
#define LBX_AIL_DIGPAK_DRIVER_MAGIC_STRING "DIGPAK"
#define AIL_MAGIC_LENGTH 42
#define DIGPAK_MAGIC_LENGTH 6

/* TODO(JWB): Organize these notes and move them to the documentation/wiki */
/* 43 6F 70 79 72 69 67 68 74 20 28 43 29 20 31 39 39 31 2C 31 39 39 32 20 4D 69 6C 65 73 20 44 65 73 69 67 6E 2C 20 49 6E 63 2E */
/*  C  o  p  y  r  i  g  h  t     (  C  )     1  9  9  1  ,  1  9  9  2     M  i  l  e  s     D  e  s  i  g  n  ,     I  n  c  . */
/* 44 49 47 50 41 4B */
/*  D  I  G  P  A  K" */
/* SNDDRV.LBX SNDDRV001 ADV/DRV	AIL2/A214_D1/PCSPKR.ADV */
/*
#define XMIDI_DRVR 3        / * equates for drvr_desc.drvr_type values    * /
#define DSP_DRVR 2

typedef struct
{
    unsigned min_API_version;
    unsigned drvr_type;
    char data_suffix[4];
    void far *dev_name_table;
    int default_IO;
    int default_IRQ;
    int default_DMA;
    int default_DRQ;
    int service_rate;
    unsigned display_size;
}
drvr_desc;
 */

#define LBX_ENTRY_COUNT_MAXIMUM 125                     /* (512 - 8) = 504 / 4 = 126 - 1 = 125 */
#define LBX_OFFSET_TABLE_MAXIMUM 126                    /* (512 - 8) = 504 / 4 = 126 */
#define LBX_OFFSET_TO_HEADER_PREAMBLE 0x00              /* BOF+0; */
#define LBX_OFFSET_TO_OFFSET_TABLE 0x08                 /* BOF+8; */
#define LBX_OFFSET_TO_STRING_TABLE 0x0200               /* BOF+512; 512 = (8 + ((4 * 126) + 4)) */

#define LBX_LENGTH_HEADER_DEFAULT 512                   /* Bytes (0x0200) (As seen, in MAGIC.EXE Dasm) */
#define LBX_LENGTH_HEADER_PREAMBLE_DEFAULT 8            /* Bytes (0x08) */
#define LBX_LENGTH_HEADER_OFFSET_TABLE_DEFAULT 504      /* Bytes (0x01F8) */
#define LBX_LENGTH_OFFSET_TABLE_ENTRY 4                 /* Bytes */
#define LBX_LENGTH_STRING_TABLE_ENTRY 32                /* Bytes */
#define LBX_LENGTH_STRING_TABLE_ENTRY_NAME 9            /* Bytes */
#define LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION 23    /* Bytes */
#define LBX_HEADER_BUFFER_SIZE 512                      /* Bytes */
#define LBX_READ_BUFFER_CHUNK_SIZE 32768                /* Bytes (32 KB) (As seen, in MAGIC.EXE Dasm) */

#define LBX_IMAGE_DATA_OFFSET_TABLE_OFFSET_DEFAULT 18   /* Bytes (0x10) (As seen, in MAIN.LBX, Entry 0) */
#define LBX_LENGTH_IMAGE_FRAME_OFFSET_TABLE_ENTRY 4     /* Bytes */

#endif  /* LIB_LBX_LBX_DEFS_H */
