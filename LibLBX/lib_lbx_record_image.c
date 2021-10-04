#include <malloc.h>         /* malloc(), realloc(); */
#include <stdlib.h>         /* exit(), itoa(), splitpath(); EXIT_FAILURE, EXIT_SUCCESS; */
#include <string.h>         /* memcpy(), memset(), strcpy(), strncpy(), strlen(); */

#include "lib_lbx_record_image.h"
#include "lbx_record_type_flic.h"
#include "lib_lbx.h"
#include "lib_lbx_record.h"
#include "lib_lbx_util.h"

/*
QMoMPalette m_colorTable;
...
const QMoMPalette& getColorTable()
	{
		return m_colorTable;
	}
...
// Create bitmap
            QMoMImagePtr image(new QImage(width, height, QImage::Format_Indexed8));
            QVector<QRgb> colorTable = QMoMResources::instance().getColorTable();
            colorTable.resize(256);
            colorTable[255] = qRgb(255, 255, 255);
            image->setColorTable(colorTable);
image->fill(255);
...
bool convertLbxToImages(const uint8_t* data, size_t size, const QMoMPalette& defaultColorTable, QMoMAnimation& images, const std::string& context)
...
QMoMPalette colorTable(defaultColorTable);
...
bool QMoMResources::createColorTable()
{
    if (m_game.isNull())
        return false;
    m_colorTable.resize(256);
    std::string fontsLbxFile = m_game->getGameDirectory() + "/" + "FONTS.LBX";
    MoM::MoMLbxBase fontsLbx;
    if (!fontsLbx.load(fontsLbxFile))
        return false;

    uint8_t* dataPalette = fontsLbx.getRecord(2);
    MoM::convertLbxToPalette(dataPalette, m_colorTable);

    return true;
}
...
void QMoMResources::setGame(const QMoMGamePtr& game)
{
    if (game.data() != m_game.data())
    {
//        qDebug() << getDateTimeStr() << ">QMoMResources::setGame() begin";
        m_game = game;
        m_wizardsExe.reset();

        (void)createColorTable();

 */


void create_lbx_image_record(LBX_FLIC_RECORD_HEADER * lbx_image_record)
{
    /*LBX_FLIC_RECORD_HEADER * lbx_image_record;*/
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: lbx_image_record = (LBX_FLIC_RECORD_HEADER *)malloc(sizeof *lbx_image_record);\n");
    lbx_image_record = malloc(sizeof *lbx_image_record);
    if (lbx_image_record == NULL)
    {
        printf("FAILURE: lbx_image_record = (LBX_FLIC_RECORD_HEADER *)malloc(%u);\n", sizeof *lbx_image_record);
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: lbx_image_record = (LBX_FLIC_RECORD_HEADER *)malloc(sizeof *lbx_image_record);\n");

}

void destroy_lbx_image_record(LBX_FLIC_RECORD_HEADER * lbx_image_record)
{
    free(lbx_image_record);
    lbx_image_record = NULL;
}


LBX_FLIC_INFO_HEADER * get_lbx_image_header(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_lbx_image_header()\n");

    LBX_FLIC_INFO_HEADER * lbx_image_header;
    char * record_data;

    record_data = get_record_data(lbx, entry_number);

    lbx_image_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));

    lbx_image_header->frame_width = *(lbx_uint16 *) &record_data[0];
    lbx_image_header->frame_height = *(lbx_uint16 *) &record_data[2];
    lbx_image_header->current_frame = *(lbx_uint16 *) &record_data[4];
    lbx_image_header->frame_count = *(lbx_uint16 *) &record_data[6];
    lbx_image_header->loop_frame = *(lbx_uint16 *) &record_data[8];
    lbx_image_header->emm_handle = *(lbx_uint8 *) &record_data[10];
    lbx_image_header->emm_logical_page = *(lbx_uint8 *) &record_data[11];
    lbx_image_header->emm_data_offset = *(lbx_uint16 *) &record_data[12];
    lbx_image_header->palette_info_offset = *(lbx_uint16 *) &record_data[14];
    lbx_image_header->unknown = *(lbx_uint16 *) &record_data[16];

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_lbx_image_header()\n");

    return lbx_image_header;
}

LBX_FLIC_PALETTE_HEADER * get_lbx_image_custom_palette_header(LBX_DATA * lbx, int entry_number)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: get_lbx_image_custom_palette_header()\n");

    LBX_FLIC_INFO_HEADER * lbx_image_header;
    LBX_FLIC_PALETTE_HEADER * lbx_image_custom_palette_header;
    char * record_data;

    record_data = get_record_data(lbx, entry_number);

    lbx_image_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));

    lbx_image_header->frame_width = *(lbx_uint16 *) &record_data[0];
    lbx_image_header->frame_height = *(lbx_uint16 *) &record_data[2];
    lbx_image_header->current_frame = *(lbx_uint16 *) &record_data[4];
    lbx_image_header->frame_count = *(lbx_uint16 *) &record_data[6];
    lbx_image_header->loop_frame = *(lbx_uint16 *) &record_data[8];
    lbx_image_header->emm_handle = *(lbx_uint8 *) &record_data[10];
    lbx_image_header->emm_logical_page = *(lbx_uint8 *) &record_data[11];
    lbx_image_header->emm_data_offset = *(lbx_uint16 *) &record_data[12];
    lbx_image_header->palette_info_offset = *(lbx_uint16 *) &record_data[14];
    lbx_image_header->unknown = *(lbx_uint16 *) &record_data[16];

    if (lbx_image_header->palette_info_offset == 0) {
        if (LBX_DEBUG_MODE) printf("DEBUG: No custom palette contained here-in.\n");
        lbx_image_custom_palette_header = NULL;
    }
    else
    {
        lbx_image_custom_palette_header = malloc(sizeof(LBX_FLIC_PALETTE_HEADER));

        lbx_image_custom_palette_header->palette_offset = *(lbx_uint16*)&record_data[lbx_image_header->palette_info_offset + 0];
        lbx_image_custom_palette_header->palette_color_index = *(lbx_uint16*)&record_data[lbx_image_header->palette_info_offset + 2];
        lbx_image_custom_palette_header->palette_color_count = *(lbx_uint16*)&record_data[lbx_image_header->palette_info_offset + 4];
    }

    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: get_lbx_image_custom_palette_header()\n");

    return lbx_image_custom_palette_header;
}

void process_lbx_image_single_frame_flic(const lbx_uint8 * dst, lbx_uint8 * src)
{

}

void lbx_load_image_record(LBX_FLIC_RECORD_HEADER * image_record, char * image_record_data)
{
    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: BEGIN: lbx_load_image_record()\n");

    LBX_FLIC_INFO_HEADER * lbx_image_info_header;
    LBX_FLIC_PALETTE_HEADER * lbx_image_palette_header;
    LBX_FLIC_FRAME_OFFSET_TABLE * lbx_image_frame_offset_table;
    /*LBX_PALETTE * lbx_palette;*/
    lbx_uint8 * lbx_image_palette;
    lbx_uint8 * lbx_image_frame;


    LBX_FLIC_PALETTE_HEADER * lbx_image_custom_palette_header;



    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: image_record->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));\n");
    image_record->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));
    if (image_record->lbx_flic_info_header == NULL)
    {
        printf("FAILURE: image_record->lbx_flic_info_header = malloc(%u);\n", sizeof(LBX_FLIC_INFO_HEADER));
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: image_record->lbx_flic_info_header = malloc(sizeof(LBX_FLIC_INFO_HEADER));\n");



    image_record->lbx_flic_info_header->frame_width = *(lbx_uint16 *) &image_record_data[0];
    image_record->lbx_flic_info_header->frame_height = *(lbx_uint16 *) &image_record_data[2];
    image_record->lbx_flic_info_header->current_frame = *(lbx_uint16 *) &image_record_data[4];
    image_record->lbx_flic_info_header->frame_count = *(lbx_uint16 *) &image_record_data[6];
    image_record->lbx_flic_info_header->loop_frame = *(lbx_uint16 *) &image_record_data[8];
    image_record->lbx_flic_info_header->emm_handle = *(lbx_uint8 *) &image_record_data[10];
    image_record->lbx_flic_info_header->emm_logical_page = *(lbx_uint8 *) &image_record_data[11];
    image_record->lbx_flic_info_header->emm_data_offset = *(lbx_uint16 *) &image_record_data[12];
    image_record->lbx_flic_info_header->palette_info_offset = *(lbx_uint16 *) &image_record_data[14];
    image_record->lbx_flic_info_header->unknown = *(lbx_uint16 *) &image_record_data[16];

    if (image_record->lbx_flic_info_header->palette_info_offset == 0) {
        if (LBX_DEBUG_MODE) printf("DEBUG: No custom palette contained here-in.\n");
        lbx_image_custom_palette_header = NULL;
    }
    else
    {



        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: image_record->lbx_flic_palette_header = malloc(sizeof(LBX_FLIC_PALETTE_HEADER));\n");
        image_record->lbx_flic_palette_header = malloc(sizeof(LBX_FLIC_PALETTE_HEADER));
        if (image_record->lbx_flic_info_header == NULL)
        {
            printf("FAILURE: image_record->lbx_flic_palette_header = malloc(%u);\n", sizeof(LBX_FLIC_PALETTE_HEADER));
            exit(EXIT_FAILURE);
        }
        if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: image_record->lbx_flic_palette_header = malloc(sizeof(LBX_FLIC_PALETTE_HEADER));\n");

        image_record->lbx_flic_palette_header->palette_offset = *(lbx_uint16*)&image_record_data[image_record->lbx_flic_info_header->palette_info_offset + 0];
        image_record->lbx_flic_palette_header->palette_color_index = *(lbx_uint16*)&image_record_data[image_record->lbx_flic_info_header->palette_info_offset + 2];
        image_record->lbx_flic_palette_header->palette_color_count = *(lbx_uint16*)&image_record_data[image_record->lbx_flic_info_header->palette_info_offset + 4];
    }



    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: image_data_decoded_buffer = (char *)malloc(flic->width * flic->height);\n");
    char * image_data_decoded_buffer;
    image_data_decoded_buffer = (char *)malloc(image_record->lbx_flic_info_header->frame_width * image_record->lbx_flic_info_header->frame_height);
    if (image_data_decoded_buffer == NULL)
    {
        printf("FAILURE: image_data_decoded_buffer = (char *)malloc(%d);\n", image_record->lbx_flic_info_header->frame_width * image_record->lbx_flic_info_header->frame_height);
        exit(EXIT_FAILURE);
    }
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: image_data_decoded_buffer = (char *)malloc(flic->width * flic->height);\n");



    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: BEGIN: memset(image_data_decoded_buffer, 211, flic->width * flic->height);\n");
    memset(image_data_decoded_buffer, 211, image_record->lbx_flic_info_header->frame_width * image_record->lbx_flic_info_header->frame_height);
    if (LBX_DEBUG_STRUGGLE_MODE) printf("DEBUG: END: memset(image_data_decoded_buffer, 211, flic->width * flic->height);\n");



    char * ptr_image_data_decoded_buffer;
    ptr_image_data_decoded_buffer = image_data_decoded_buffer;


    if (LBX_DEBUG_VERBOSE_MODE) printf("DEBUG: END: lbx_load_image_record()\n");
}