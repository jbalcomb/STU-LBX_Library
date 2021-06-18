#include <stdio.h>          /* fclose(), fopen(), fread(), fwrite(), printf(); FILE */
#include <stdlib.h>         /* itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* strcat(), strcpy(), strncpy(), strlen(); */

#include <sys/stat.h>       /* fstat(); stat; */
#include <time.h>           /* ctime(), localtime(), strftime(), time(); time_t, struct tm; */

#include "lib_lbx_util.h"

uint16_t lbx_read_2byte_le(FILE * file_stream)
{
    uint16_t result;
    result  = fgetc(file_stream);
    result |= fgetc(file_stream) << 8;
    return result;
}

uint32_t lbx_read_4byte_le(FILE * file_stream)
{
    uint32_t result;
    result  = fgetc(file_stream);
    result |= fgetc(file_stream) << 8;
    result |= fgetc(file_stream) << 16;
    result |= fgetc(file_stream) << 24;
    return result;
}

void lbx_file_path_and_file_name(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_file_path_and_file_name()\n");

    char tmp_windows_splitpath_drive[MAX_DRIVE];
    char tmp_windows_splitpath_dir[MAX_DIR];
    char tmp_windows_splitpath_fname[MAX_FNAME];
    char tmp_windows_splitpath_ext[MAX_EXT];
    char * tmp_file_path;
    char * tmp_file_name;

    _splitpath(lbx->meta->meta_file_path,
               tmp_windows_splitpath_drive,
               tmp_windows_splitpath_dir,
               tmp_windows_splitpath_fname,
               tmp_windows_splitpath_ext);

    tmp_file_path = malloc(sizeof(char) * (strlen(tmp_windows_splitpath_drive) + strlen(tmp_windows_splitpath_dir) + 1));
    strcpy(tmp_file_path, tmp_windows_splitpath_drive);
    strcat(tmp_file_path, tmp_windows_splitpath_dir);

    tmp_file_name = malloc(sizeof(char) * (strlen(tmp_windows_splitpath_fname) + strlen(tmp_windows_splitpath_ext) + 1));
    strcpy(tmp_file_name, tmp_windows_splitpath_fname);
    strcat(tmp_file_name, tmp_windows_splitpath_ext);

    lbx->meta->meta_file_path = tmp_file_path;
    lbx->meta->meta_file_name = tmp_file_name;

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_file_path_and_file_name()\n");
}


void lbx_file_name_base(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_file_name_base()\n");

    int itr_file_name_in;

    lbx->meta->meta_file_name_base = malloc(sizeof(char) * (strlen(lbx->meta->meta_file_name) + 1));
    strcpy(lbx->meta->meta_file_name_base, lbx->meta->meta_file_name);

    for (itr_file_name_in = 0; lbx->meta->meta_file_name_base[itr_file_name_in] != 0; itr_file_name_in++)
    {
        if (lbx->meta->meta_file_name[itr_file_name_in] == '.')
        {
            lbx->meta->meta_file_name_base[itr_file_name_in] = '\0';
            lbx->meta->meta_file_name_base[itr_file_name_in + 1] = '\0';
        }
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_file_name_base()\n");
}

size_t lbx_file_size_via_seek(FILE * file_stream)
{
    if (LBX_DEBUG_MODE) printf("DEBUG: BEGIN: lbx_file_size_via_seek()\n");

    size_t tmp_pos;
    size_t file_size_seek;

    tmp_pos = ftell(file_stream);

    fseek(file_stream, 0, SEEK_END);
    file_size_seek = ftell(file_stream);

    fseek(file_stream, tmp_pos, SEEK_SET);

    if (LBX_DEBUG_MODE) printf("DEBUG: END: lbx_file_size_via_seek()\n");
    return file_size_seek;
}

void lbx_earliest_timestamp_via_stat(LBX_DATA * lbx)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_earliest_timestamp_via_stat()\n");

    time_t tmp_st_atime;        /* time of last access */
    time_t tmp_st_mtime;        /* time of last modification */
    time_t tmp_st_ctime;        /* time of last status change */
    /* time_t tmp_st_birthtime;    / * time of creation * / */

    struct stat file_stat_buf;

    fstat(fileno(lbx->file_stream), &file_stat_buf);

    if (LBX_DEBUG_STRUGGLE_MODE) printf(" File access time %s", ctime(&file_stat_buf.st_atime));
    if (LBX_DEBUG_STRUGGLE_MODE) printf(" File modify time %s", ctime(&file_stat_buf.st_mtime));
    if (LBX_DEBUG_STRUGGLE_MODE) printf("File changed time %s", ctime(&file_stat_buf.st_ctime));
    /* if (LBX_DEBUG_STRUGGLE_MODE) printf("File birth time %s", ctime(&file_stat_buf.st_birthtime)); */

    tmp_st_atime = file_stat_buf.st_atime;
    tmp_st_mtime = file_stat_buf.st_mtime;
    tmp_st_ctime = file_stat_buf.st_ctime;
    /* tmp_st_birthtime = file_stat_buf.st_birthtime; */

    if (LBX_DEBUG_STRUGGLE_MODE) printf(" File access time %s", ctime(&tmp_st_atime));
    if (LBX_DEBUG_STRUGGLE_MODE) printf(" File modify time %s", ctime(&tmp_st_mtime));
    if (LBX_DEBUG_STRUGGLE_MODE) printf("File changed time %s", ctime(&tmp_st_ctime));
    /* if (LBX_DEBUG_STRUGGLE_MODE) printf("File birth time %s", ctime(&tmp_st_birthtime)); */

    if (&tmp_st_atime < &tmp_st_mtime)
    {
        lbx->meta->earliest_timestamp = file_stat_buf.st_atime;
    }
    else
    {
        lbx->meta->earliest_timestamp = file_stat_buf.st_mtime;
    }
    if (file_stat_buf.st_ctime < lbx->meta->earliest_timestamp)
    {
        lbx->meta->earliest_timestamp = file_stat_buf.st_ctime;
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: ctime(lbx->meta->earliest_timestamp): %s\n", ctime(&lbx->meta->earliest_timestamp));

    char iso8601_buf[sizeof "0000-00-00T00:00:00Z"];
    strftime(iso8601_buf, sizeof iso8601_buf, "%FT%TZ", gmtime(&lbx->meta->earliest_timestamp));

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_earliest_timestamp_via_stat()\n");
}

/*
 * http://csbruce.com/software/crc32.c
 * |-> https://www.drdobbs.com/database/file-verification-using-crc/184408765
 *
 */

/*----------------------------------------------------------------------------*\
 *  CRC-32 version 2.0.0 by Craig Bruce, 2006-04-29.
 *
 *  This program generates the CRC-32 values for the files named in the
 *  command-line arguments.  These are the same CRC-32 values used by GZIP,
 *  PKZIP, and ZMODEM.  The lbx_compute_crc32_buffer() can also be detached and
 *  used independently.
 *
 *  THIS PROGRAM IS PUBLIC-DOMAIN SOFTWARE.
 *
 *  Based on the byte-oriented implementation "File Verification Using CRC"
 *  by Mark R. Nelson in Dr. Dobb's Journal, May 1992, pp. 64-67.
 *
 *  v1.0.0: original release.
 *  v1.0.1: fixed printf formlbx.
 *  v1.0.2: fixed something else.
 *  v1.0.3: replaced CRC constant table by generator function.
 *  v1.0.4: reformatted code, made ANSI C.  1994-12-05.
 *  v2.0.0: rewrote to use memory buffer & static table, 2006-04-29.
\*----------------------------------------------------------------------------*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

/*----------------------------------------------------------------------------*\
 *  Local functions
\*----------------------------------------------------------------------------*/

/*
static int Crc32_ComputeFile( FILE *file, unsigned long *outCrc32 );

static unsigned long lbx_compute_crc32_buffer( unsigned long inCrc32, const void *buf,
                                       size_t bufLen );
*/

/*----------------------------------------------------------------------------*\
 *  NAME:
 *     main() - main function for CRC-32 generation
 *  DESCRIPTION:
 *     Computes the CRC-32 value for the set of files named in the command-
 *     line arguments.
 *  ARGUMENTS:
 *     argc - command-line-argument count
 *     argv - command-line-argument strings
 *  RETURNS:
 *     err - 0 on success or executes exit(1) on error
 *  ERRORS:
 *     - file errors
\*----------------------------------------------------------------------------*/

/*
int main( int argc, const char *argv[] )
{
}
*/

/*----------------------------------------------------------------------------*\
 *  NAME:
 *     Crc32_ComputeFile() - compute CRC-32 value for a file
 *  DESCRIPTION:
 *     Computes the CRC-32 value for an opened file.
 *  ARGUMENTS:
 *     file - file pointer
 *     outCrc32 - (out) result CRC-32 value
 *  RETURNS:
 *     err - 0 on success or -1 on error
 *  ERRORS:
 *     - file errors
\*----------------------------------------------------------------------------*/

int lbx_compute_crc32_char_buffer(char * char_buffer_in, size_t char_buffer_length, unsigned long int * crc32_out)
{
#   define CRC_BUFFER_SIZE  8192
    unsigned char buf[CRC_BUFFER_SIZE];
    /* size_t bufLen; */

    int chunk_size;
    int chunk_count;
    int chunk_remainder;
    int pos_char_buffer_in;
    int itr_chunk_count;

    chunk_size = CRC_BUFFER_SIZE;
    chunk_count = (int)(char_buffer_length / chunk_size);
    chunk_remainder = (int)(char_buffer_length - (chunk_count * chunk_size));

    pos_char_buffer_in = 0;
    itr_chunk_count = 0;

    /** accumulate crc32 from file **/
    *crc32_out = 0;
    while (itr_chunk_count <= chunk_count)
    {
        if (itr_chunk_count == chunk_count)
        {
            chunk_size = chunk_remainder;
        }

        memcpy(buf, char_buffer_in + pos_char_buffer_in, sizeof(char) * chunk_size);

        *crc32_out = lbx_compute_crc32(*crc32_out, buf, chunk_size);

        itr_chunk_count = itr_chunk_count + 1;
        pos_char_buffer_in = pos_char_buffer_in + chunk_size;
    }

    return(0);
}

int lbx_compute_crc32_file(FILE * file_stream, unsigned long int * crc32_out)
{
#   define CRC_BUFFER_SIZE  8192
    unsigned char buf[CRC_BUFFER_SIZE];
    size_t bufLen;

    size_t tmp_pos;
    tmp_pos = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    /** accumulate crc32 from file **/
    *crc32_out = 0;
    while (1)
    {
        bufLen = fread(buf, 1, CRC_BUFFER_SIZE, file_stream );
        if (bufLen == 0)
        {
            if (ferror(file_stream))
            {
                fprintf( stderr, "error reading file\n" );
                goto ERR_EXIT;
            }
            break;
        }
        *crc32_out = lbx_compute_crc32(*crc32_out, buf, bufLen);
    }

    fseek(file_stream, tmp_pos, SEEK_SET);

    return( 0 );

    /** error exit **/
    ERR_EXIT:
    return( -1 );
}

/*----------------------------------------------------------------------------*\
 *  NAME:
 *     lbx_compute_crc32_buffer() - computes the CRC-32 value of a memory buffer
 *  DESCRIPTION:
 *     Computes or accumulates the CRC-32 value for a memory buffer.
 *     The 'crc32_in' gives a previously accumulated CRC-32 value to allow
 *     a CRC to be generated for multiple sequential buffer-fuls of data.
 *     The 'crc32_in' for the first buffer must be zero.
 *  ARGUMENTS:
 *     crc32_in - accumulated CRC-32 value, must be 0 on first call
 *     buf     - buffer to compute CRC-32 value for
 *     bufLen  - number of bytes in buffer
 *  RETURNS:
 *     crc32 - computed CRC-32 value
 *  ERRORS:
 *     (no errors are possible)
\*----------------------------------------------------------------------------*/
/* static unsigned long lbx_compute_crc32(unsigned long crc32_in, const void * buf, size_t bufLen) */
unsigned long lbx_compute_crc32(unsigned long crc32_in, const void * buf, size_t bufLen)
{
    static const unsigned long crcTable[256] = {
            0x00000000,0x77073096,0xEE0E612C,0x990951BA,0x076DC419,0x706AF48F,0xE963A535,
            0x9E6495A3,0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988,0x09B64C2B,0x7EB17CBD,
            0xE7B82D07,0x90BF1D91,0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE,0x1ADAD47D,
            0x6DDDE4EB,0xF4D4B551,0x83D385C7,0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC,
            0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5,0x3B6E20C8,0x4C69105E,0xD56041E4,
            0xA2677172,0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B,0x35B5A8FA,0x42B2986C,
            0xDBBBC9D6,0xACBCF940,0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59,0x26D930AC,
            0x51DE003A,0xC8D75180,0xBFD06116,0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F,
            0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924,0x2F6F7C87,0x58684C11,0xC1611DAB,
            0xB6662D3D,0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A,0x71B18589,0x06B6B51F,
            0x9FBFE4A5,0xE8B8D433,0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818,0x7F6A0DBB,
            0x086D3D2D,0x91646C97,0xE6635C01,0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E,
            0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457,0x65B0D9C6,0x12B7E950,0x8BBEB8EA,
            0xFCB9887C,0x62DD1DDF,0x15DA2D49,0x8CD37CF3,0xFBD44C65,0x4DB26158,0x3AB551CE,
            0xA3BC0074,0xD4BB30E2,0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB,0x4369E96A,
            0x346ED9FC,0xAD678846,0xDA60B8D0,0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9,
            0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086,0x5768B525,0x206F85B3,0xB966D409,
            0xCE61E49F,0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4,0x59B33D17,0x2EB40D81,
            0xB7BD5C3B,0xC0BA6CAD,0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A,0xEAD54739,
            0x9DD277AF,0x04DB2615,0x73DC1683,0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8,
            0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1,0xF00F9344,0x8708A3D2,0x1E01F268,
            0x6906C2FE,0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7,0xFED41B76,0x89D32BE0,
            0x10DA7A5A,0x67DD4ACC,0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5,0xD6D6A3E8,
            0xA1D1937E,0x38D8C2C4,0x4FDFF252,0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B,
            0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60,0xDF60EFC3,0xA867DF55,0x316E8EEF,
            0x4669BE79,0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236,0xCC0C7795,0xBB0B4703,
            0x220216B9,0x5505262F,0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04,0xC2D7FFA7,
            0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D,0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A,
            0x9C0906A9,0xEB0E363F,0x72076785,0x05005713,0x95BF4A82,0xE2B87A14,0x7BB12BAE,
            0x0CB61B38,0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21,0x86D3D2D4,0xF1D4E242,
            0x68DDB3F8,0x1FDA836E,0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777,0x88085AE6,
            0xFF0F6A70,0x66063BCA,0x11010B5C,0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45,
            0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2,0xA7672661,0xD06016F7,0x4969474D,
            0x3E6E77DB,0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0,0xA9BCAE53,0xDEBB9EC5,
            0x47B2CF7F,0x30B5FFE9,0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6,0xBAD03605,
            0xCDD70693,0x54DE5729,0x23D967BF,0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94,
            0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D };
    unsigned long crc32;
    unsigned char *byteBuf;
    size_t i;

    /** accumulate crc32 for buffer **/
    crc32 = crc32_in ^ 0xFFFFFFFF;
    byteBuf = (unsigned char*) buf;
    for (i=0; i < bufLen; i++) {
        crc32 = (crc32 >> 8) ^ crcTable[ (crc32 ^ byteBuf[i]) & 0xFF ];
    }
    return( crc32 ^ 0xFFFFFFFF );
}

/*----------------------------------------------------------------------------*\
 *  END OF MODULE: crc32.c
\*----------------------------------------------------------------------------*/
