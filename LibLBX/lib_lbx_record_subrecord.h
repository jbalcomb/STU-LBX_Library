
/*
 * MoM-RTGT
 * DialogLbxEditor.cpp
 * DialogLbxEditor::processPalette()
 * // FONTS.LBX palette records can have an additional raw cursor image at offset 0x500
    const size_t offsetRawImages = 0x500;
    if (data.size() >= 0x500)
...
 // LBX has data column by column: reverse x and y


 loadPaletteForFile(const QString &filename)
{
    m_colorTable.clear();

    QFileInfo fileInfo(filename);
    QString gameDirectory = fileInfo.absoluteDir().absolutePath();
    QString filetitle = fileInfo.fileName();
    int lbxIndex = 0;

    // CONQUEST???
    if (0 == filetitle.compare("LOAD.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 3;
    }
    else if (0 == filetitle.compare("MAINSCRN.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 4;
    }
    else if (0 == filetitle.compare("WIZLAB.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 5;
    }
    else if (0 == filetitle.compare("SPLMASTR.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 6;
    }
    else if (0 == filetitle.compare("WIN.LBX", Qt::CaseInsensitive))
    {
        lbxIndex = 7;
    }
    else if ((0 == filetitle.compare("LOSE.LBX", Qt::CaseInsensitive))
             || (0 == filetitle.compare("SPELLOSE.LBX", Qt::CaseInsensitive)))
    {
        lbxIndex = 8;
    }
    else
    {
        lbxIndex = 2;
    }



 uint8_t* dataPalette = fontsLbx.getRecord(lbxIndex);
    MoM::convertLbxToPalette(dataPalette, m_colorTable);


 */


#ifndef LIB_LBX_RECORD_SUB_H
#define LIB_LBX_RECORD_SUB_H

#include "lib_lbx.h"


/*
 * LBX Array Type Structure
 * 4 byte header
 * (2) 16-bit
 *
 */
struct LBX_ARRAY_HEADER {
    int element_count;
    int element_size;
};
struct LBX_ARRAY_MEMBER_HELP {
    char member[1048];
    char name[24];
    char contents[1024];
};

/*
 * HELP000.BIN
 * D9 00 C8 00 00 00 01 00 00 00 00 00 00 00 00 00
 * 217 x 200
 * HELP001.BIN
 * D9 00 17 00 00 00 01 00 00 00 00 00 00 00 00 00
 * 217 x 23
 *
 */
struct LBX_PICTURE_HEADER {
    int image_height;
    int image_width;
};

int get_record_subrecord_count(LBX_DATA * lbx, int entry_number);

#endif  /* LIB_LBX_RECORD_SUB_H */
