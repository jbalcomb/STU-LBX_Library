#include <malloc.h>         /* malloc(), realloc(); */
#include <string.h>         /* memcpy(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_record_palette.h"
#include "lib_lbx.h"
#include "lib_lbx_record.h"
#include "lib_lbx_load.h"
#include "per_game/MoM131/MoM131_palette.h"
#include "lib_lbx_record_flic.h"


//    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\PJHIGH\COLLOAD.C */
//    /*
//     Errcode pj_col_load(char *name, Cmap *cmap)
//     ...
//     if (size == OLD_SIZE && cmap->num_colors == COLORS)
//	     {
//	     if ((err = pj_read_ecode(fd, cmap->ctab, sizeof(cmap->ctab))) < Success)
//		     goto ERROR;
//	     pj_shift_cmap(cmap->ctab,cmap->ctab,COLORS*3);
//     */
//    Cmap *cmap;
//    cmap = malloc(sizeof(cmap));
//    cmap->num_colors = COLORS;
//    /*cmap->ctab = malloc(sizeof(cmap->ctab));*/
//    AA_pj_shift_cmap(cmap->ctab,cmap->ctab,COLORS*3);

void colormap_shift(unsigned char *src, unsigned char *dst, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        dst[i] = src[i] * 4;

        if (LBX_DEBUG_STRUGGLE_MODE)
        {
            if (i < 16 || i > 751)
            {
                printf("[%u] %u (0x%02X) %u (0x%02X)\n", i, src[i], src[i], dst[i], dst[i]);
            }

        }
    }
}


/*
 * drake178
 * MAGIC.EXE
 * seg020:000A
 * int __cdecl __far VGA_LoadPalette(int Palette_Index, int First_Color, int Last_Color)
 *
 * J:\STU-DASM\drake178\MAGIC.asm
 * line 40886
 */
char * LBX_Palette_Seg;
char * Font_FileName;
char * Palette_Color_Data;
char * Palette_Font_Colors;
char * Unused_Palette_Data;
char * Palette_Cursor_Data;
char * Shading_Colors;
/* int __cdecl __far VGA_LoadPalette(int Palette_Index, int First_Color, int Last_Color) */
int VGA_LoadPalette(int Palette_Index, int First_Color, int Last_Color)
{
    /*
    mov	ax, -1
    push	ax		; First_Color
    xor	ax, ax		; Logical Exclusive OR
    push	ax		; Palette_Index
    call	VGA_LoadPalette     ; loads	the specified palette (entry = index+2 in
			                    ; FONTS.LBX), sets font	0 with the default colors,
			                    ; and marks all	entries	in the DAC as changed
			                    ; could	be called specifying a first and last color,
			                    ; which	would skip the rest, but never is in MoM

    call	VGA_DAC_Write       ; writes any changed colors in the dynamic DAC
			                    ; allocation out to the	actual video DAC in two	sets
			                    ; of 128 colors	each, waiting after a vsync with each
			                    ; marks	all colors as unchanged	afterwards
     */

    // call LBXE_LoadReplace

}

/***
 * function to load a MoM131 palette record, by /palette number/
 * @param lbx_palette_file_path ~=?/+<palette_file_name=FONTS.LBX
 * @param lbx_palette_number ~=entry_index+2
 * @return unsigned char bytes of archive (GRAF) record entry
 */
unsigned char * liblbx_load_palette_record(char * lbx_palette_file_path, int lbx_palette_number)
{
    unsigned char * lbx_palette_record;
    int lbx_palette_entry_index;

    lbx_palette_entry_index = lbx_palette_number + 1;

    lbx_palette_record = liblbx_load_lbx_entry(lbx_palette_file_path, lbx_palette_entry_index);

    return lbx_palette_record;
}

unsigned char * liblbx_load_palette(char * lbx_palette_file_path, int lbx_palette_number)
{
    unsigned char * lbx_palette_record;
    lbx_palette_record = liblbx_load_palette_record(lbx_palette_file_path, lbx_palette_number);

    unsigned char * lbx_palette;
    lbx_palette = malloc(PALETTE_BYTE_COUNT);
    memcpy(lbx_palette, lbx_palette_record, PALETTE_BYTE_COUNT);

    colormap_shift(lbx_palette, lbx_palette, PALETTE_BYTE_COUNT);

    return lbx_palette;
}

void liblbx_export_palette(char * lbx_palette_file_path, int lbx_palette_number, char * export_palette_file_path_base)
{
    unsigned char * lbx_palette_record;
    lbx_palette_record = liblbx_load_palette_record(lbx_palette_file_path, lbx_palette_number);

    unsigned char * lbx_palette;
    lbx_palette = malloc(PALETTE_BYTE_COUNT);
    memcpy(lbx_palette, lbx_palette_record, PALETTE_BYTE_COUNT);

    colormap_shift(lbx_palette, lbx_palette, PALETTE_BYTE_COUNT);


    char * col_file_path;
    col_file_path = malloc(MAX_PATH);
    strcpy(col_file_path, export_palette_file_path_base);
    strcat(col_file_path, ".COL");

    printf("Out-putting... %s\n", col_file_path);
    FILE * file_col = fopen(col_file_path, "wb");
    fwrite(lbx_palette, 1, PALETTE_BYTE_COUNT, file_col);
    fclose(file_col);

    char * pal_file_path;
    pal_file_path = malloc(MAX_PATH);
    strcpy(pal_file_path, export_palette_file_path_base);
    strcat(pal_file_path, ".PAL");

    printf("Out-putting... %s\n", pal_file_path);
    FILE * file_pal = fopen(pal_file_path, "wb");
    fwrite(lbx_palette, 1, PALETTE_BYTE_COUNT, file_pal);
    fclose(file_pal);

    char * col_old_file_path;
    col_old_file_path = malloc(MAX_PATH);
    strcpy(col_old_file_path, export_palette_file_path_base);
    strcat(col_old_file_path, ".COL_OLD");

    printf("Out-putting... %s\n", col_old_file_path);
    FILE * file_col_old = fopen(col_old_file_path, "wb");
    fwrite(lbx_palette, 1, PALETTE_BYTE_COUNT, file_col_old);
    fclose(file_col_old);

    char * col_new_file_path;
    col_new_file_path = malloc(MAX_PATH);
    strcpy(col_new_file_path, export_palette_file_path_base);
    strcat(col_new_file_path, ".COL_NEW");

    printf("Out-putting... %s\n", col_new_file_path);
    FILE * file_col_new = fopen(col_new_file_path, "wb");

    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\STDTYPES.H */
    typedef unsigned char	UBYTE;
    typedef unsigned short	USHORT;
    typedef signed long 	LONG;
    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\VMAGICS.H */
#define CMAP_MAGIC		0xB123U     /* color map file */
#define CHUNKID_FIELDS \
	    LONG size;\
	    USHORT type
    typedef struct chunk_id {
        CHUNKID_FIELDS;
    } Chunk_id;
    typedef struct fat_chunk {
        CHUNKID_FIELDS;
        USHORT version;
    } Fat_chunk;
    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\CMAP.H */
#define COLORS 256
#define RGB_MAX 256
    typedef struct rgb3 {
        UBYTE r,g,b;
    } Rgb3;
    typedef struct colormap {
        LONG num_colors;
        Rgb3 ctab[COLORS];
    } Cmap;
    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\INC\PALCHUNK.H */
    typedef struct pal_chunk {
        Fat_chunk id;  /* Type is for file use, version is type of cmap data. */
        Rgb3 ctab[1];
    } Pal_chunk;
#define PAL_RGB256_VERS 0   /* only one type for now */
    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\PJHIGH\COLSAVE.C */
//    Errcode pj_col_save(char *name,Cmap *cmap)
//    /* Save color map file */
//    {
//        Errcode err;
//        Jfile fd;
//        if((fd = pj_create(name, JREADWRITE)) == JNONE)
//            return(pj_ioerr());
//        err = pj_write_palchunk(fd,cmap,CMAP_MAGIC);
//        pj_close(fd);
//        return(err);
//    }
    /* J:\STU\DBWD\developc\_AnimatorPro\Pristine-Pro\PJHIGH\PALWRITE.C */
//    Errcode pj_write_palchunk(Jfile fd, Cmap *cmap, SHORT id_type)
//    /* writes a palette chunk to the file input for the colormap input */
//    {
//        Errcode err;
//        LONG csize;
//        Fat_chunk id;
//        csize = (cmap->num_colors * sizeof(Rgb3));
//        id.type = id_type;
//        id.version = PAL_RGB256_VERS;
//        id.size = sizeof(id) + csize;
//        if((err = pj_write_ecode(fd,&id,sizeof(id))) < Success)
//            return(err);
//        return(pj_write_ecode(fd,cmap->ctab,csize));
//    }
    Cmap *cmap;
    SHORT id_type;
    LONG csize;
    Fat_chunk id;
    cmap = malloc(sizeof(Cmap));
    cmap->num_colors = COLORS;
    memcpy(cmap->ctab, lbx_palette, sizeof(cmap->ctab));
    id_type = CMAP_MAGIC;
    csize = (cmap->num_colors * sizeof(Rgb3));
    id.type = id_type;
    id.version = PAL_RGB256_VERS;
    id.size = sizeof(id) + csize;
    printf("(%u) (%d) (0x%02X)\n", id.type, id.type, id.type);
    printf("(%u) (%d) (0x%02X)\n", id.version, id.version, id.version);
    printf("(%lu) (%ld) (0x%02lX)\n", id.size, id.size, id.size);
    printf("(%lu) (%ld) (0x%02lX)\n", cmap->num_colors, cmap->num_colors, cmap->num_colors);
    printf("(%u) (%d) (0x%02X)\n", sizeof(Rgb3), sizeof(Rgb3), sizeof(Rgb3));

    fwrite(&id, 1, sizeof(id), file_col_new);
    fwrite(cmap->ctab, 1, csize, file_col_new);
    fclose(file_col_new);

}

void liblbx_load_palette_from_palettes_lbx_file(LBX_DATA * lbx)
{
    char * palettes_file_path;
    unsigned int tmp_str_len_directory_path;
    unsigned int tmp_str_len_palettes_file_name;
    LBX_DATA * palettes_lbx;

    tmp_str_len_directory_path = strlen(lbx->file->directory_path);
    tmp_str_len_palettes_file_name = strlen(palettes_file_name);
    palettes_file_path = malloc(tmp_str_len_directory_path + 1 + tmp_str_len_palettes_file_name + 1);
    strcpy(palettes_file_path, lbx->file->directory_path);
    strcpy(palettes_file_path, "/");
    strcpy(palettes_file_path, palettes_file_name);

    palettes_lbx = create_lbx_data(palettes_file_path);
    liblbx_open_file(palettes_lbx);
    lbx_load_header(palettes_lbx);

    liblbx_load_lbx_entry(palettes_file_path, 2);



}
void lbx_load_palette_all(void)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_load_palette_all()\n");

    int itr_palette_number;

    for (itr_palette_number = 0; itr_palette_number < 8; itr_palette_number++)
    {
        lbx_load_palette_by_number(itr_palette_number);
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_palette_all()\n");
}

/*LBX_PALETTE * lbx_load_palette_by_number(int palette_number)*/
lbx_uint8 * lbx_load_palette_by_number(int palette_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_load_palette_by_number()\n");

    /*
    LBX_PALETTE * lbx_palette;
    int entry_number;
    char * record_data;
    lbx_palette = malloc(LBX_PALETTE_SIZE);
    entry_number = palette_number + 2;
    record_data = liblbx_load_lbx_entry("FONTS.LBX", entry_number);
    memcpy(lbx_palette, record_data, LBX_PALETTE_SIZE);
    */

    /*LBX_PALETTE * lbx_palette;*/
    lbx_uint8 * lbx_palette;
    lbx_palette = MoM131_Palette_Emperato_8bpp;

    /*
    if (palette_number == 0)
    {
        realloc(g_PaletteNumberZero, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberZero, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 1)
    {
        realloc(g_PaletteNumberOne, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberOne, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 2)
    {
        realloc(g_PaletteNumberTwo, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberTwo, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 3)
    {
        realloc(g_PaletteNumberThree, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberThree, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 4)
    {
        realloc(g_PaletteNumberFour, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberFour, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 5)
    {
        realloc(g_PaletteNumberFive, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberFive, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 6)
    {
        realloc(g_PaletteNumberSix, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberSix, record_data, LBX_PALETTE_SIZE);
    }
    else if (palette_number == 7)
    {
        realloc(g_PaletteNumberSeven, LBX_PALETTE_SIZE);
        memcpy(g_PaletteNumberSeven, record_data, LBX_PALETTE_SIZE);
    }
    else
    {
        / * TODO(JWB): add ~= UNDEFINED_PALETTE * /
    }
    */

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_palette_by_number()\n");

    return lbx_palette;
}

/*LBX_PALETTE * lbx_load_palette_by_file_name(char * LbxFileName)*/
lbx_uint8 * lbx_load_palette_by_file_name(char * LbxFileName)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_load_palette_by_number()\n");

    int palette_number;

    /* TODO(JWB): figure out which files have images and which palette they use (e.g., Per ILSe, CONQUEST.LBX) */
    if (strcmp(LbxFileName, "LOAD.LBX") == 0) { palette_number = 1; }
    else if (strcmp(LbxFileName, "LOSE.LBX") == 0) { palette_number = 6; }
    else if (strcmp(LbxFileName, "MAIN.LBX") == 0) { palette_number = 2; }
    else if (strcmp(LbxFileName, "MAINSCRN.LBX") == 0) { palette_number = 2; }
    else if (strcmp(LbxFileName, "SPELLOSE.LBX") == 0) { palette_number = 6; }
    else if (strcmp(LbxFileName, "SPLMASTR.LBX") == 0) { palette_number = 4; }
    else if (strcmp(LbxFileName, "WIN.LBX") == 0) { palette_number = 5; }
    else if (strcmp(LbxFileName, "WIZLAB.LBX") == 0) { palette_number = 3; }
    else { palette_number = 0; }

    /* LBX_PALETTE * lbx_palette; */
    LBX_PALETTE * lbx_palette;
    int entry_number;
    char * record_data;

    /* lbx_palette = malloc(LBX_PALETTE_SIZE); */

    lbx_palette = lbx_load_palette_by_number(palette_number);

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_palette_by_number()\n");

    return lbx_palette;
}
