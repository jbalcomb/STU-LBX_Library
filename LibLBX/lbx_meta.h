#ifndef LIB_LBX_LBX_META_H
#define LIB_LBX_LBX_META_H

struct s_LBX_RECORD_META_DATA_ENTRY {
    /* char * record_file_name_base; */  /* MAGIC.LBX -> MAGIC<entry_number> ... {.BIN, .C, .CSV, .HEX, etc.; .FLI, .TXT, .VOC, .XMI, etc.}*/
    /* char record_file_name_base[MAX_FNAME]; */         /* File Name Base + nnn + '\0' */
    char * meta_record_file_name_base;

    int meta_entry_number;
    char * entry_number_string;

    /* char * entry_name; */
    char entry_name[LBX_LENGTH_STRING_TABLE_ENTRY_NAME];
    /* char * entry_description; */
    char entry_description[LBX_LENGTH_STRING_TABLE_ENTRY_DESCRIPTION];

    int meta_type;
    char * type_string;
    char * type_description_string;

    int meta_size;
    char * size_string;

    int offset_bod;
    int offset_bod_string;
    int offset_bod_string_dec;
    int offset_bod_string_hex;
    int offset_eod;
    int offset_eod_string;
    int offset_eod_string_dec;
    int offset_eod_string_hex;

    unsigned long int record_checksum_crc32;
    char * record_checksum_crc32_string;
    unsigned long int record_checksum_md5;
    char * record_checksum_md5_string;
    unsigned long int record_checksum_sha1;
    char * record_checksum_sha1_string;
    unsigned long int record_checksum_sha256;
    char * record_checksum_sha256_string;

    /*
     * Sub-Record
     */
    int has_subrecords;

    int subrecord_count;
    char * subrecord_count_string;

    char * subrecord_attributes;
    /*
     * Array, Picture, Sound
     * Array: Element Count, Element Size
     * Picture: Height, Width
     * Sound:
     *
     * */

};
typedef struct s_LBX_RECORD_META_DATA_ENTRY LBX_RECORD_META_DATA_ENTRY;

struct s_LBX_RECORD_META_DATA {
    LBX_RECORD_META_DATA_ENTRY entry[LBX_ENTRY_COUNT_MAXIMUM];
};
typedef struct s_LBX_RECORD_META_DATA LBX_RECORD_META_DATA;

struct s_LBX_META_DATA {

    /* LBX Header */
    lbx_uint16 entry_count;
    char * entry_count_string_dec;
    char * entry_count_string_hex;
    lbx_uint16 magic;
    char * magic_string_dec;
    char * magic_string_hex;
    lbx_uint16 unknown;
    char * unknown_string_dec;
    char * unknown_string_hex;
    lbx_uint16 type;
    char * type_string_dec;
    char * type_string_hex;

    /* LBX File */
    char * meta_file_path;
    char * meta_directory_path;
    char * meta_file_name;
    char * meta_file_name_base;
    int file_size_seek;
    char * file_size_seek_string;
    int file_size_stat;
    char * file_size_stat_string;
    int file_size;
    char * file_size_string;
    time_t earliest_timestamp;
    char * earliest_timestamp_string;
    long unsigned int file_checksum_crc32;
    char * file_checksum_crc32_string;
    long unsigned int file_checksum_md5;
    char * file_checksum_md5_string;
    long unsigned int file_checksum_sha1;
    char * file_checksum_sha1_string;
    long unsigned int file_checksum_sha256;
    char * file_checksum_sha256_string;

    /* LBX Research Information */
    int offset_bod;
    char * offset_bod_string_dec;
    char * offset_bod_string_hex;
    int offset_eod;
    char * offset_eod_string_dec;
    char * offset_eod_string_hex;

    int equal_eod_eof;
    char * equal_eod_eof_string;

    int header_length;
    char * header_length_string_dec;
    char * header_length_string_hex;
    int header_length_total;
    char * header_length_total_string_dec;
    char * header_length_total_string_hex;
    int header_length_used;
    char * header_length_used_string_dec;
    char * header_length_used_string_hex;
    int header_padding_length;
    char * header_padding_length_string_dec;
    char * header_padding_length_string_hex;

    int header_padding_length_total;
    int header_padding_length_used;

    int has_string_table;
    char * has_string_table_string;
    int string_table_length;
    char * string_table_length_string;
    int string_table_entry_count;
    char * string_table_entry_count_string;

    int equal_header_padding_length_string_table_length;
    char * equal_header_padding_length_string_table_length_string;

    int record_size_minimum;
    char * record_size_minimum_string;
    int record_size_maximum;
    char * record_size_maximum_string;
    int record_size_average;
    char * record_size_average_string;
    int empty_record_count;
    char * empty_record_count_string;

    LBX_RECORD_META_DATA * records;

};
typedef struct s_LBX_META_DATA LBX_META_DATA;

#endif  /* LIB_LBX_LBX_META_H */
