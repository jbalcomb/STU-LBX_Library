
/* F:\Development_OPC\momrtgt-code\QMoMDialogs\DialogLbxEditor.cpp */



bool DialogLbxEditor::decodeGlyph(const std::vector<uint8_t>& data, int fontIndex, int characterIndex, int left, int top, QMoMImagePtr& image)
{
    if (data.size() < sizeof(MoMFontsStyleData))
        return false;
    const MoMFontsStyleData* fontsData = reinterpret_cast<const MoMFontsStyleData*>(&data[0]);
    const uint8_t* ptrGlyphData = &data[0] + fontsData->m_allGlyphOffsets[fontIndex].m_glyphOffsets[characterIndex];
    const uint8_t* ptrEndData = &data[0] + data.size();
    if (ptrGlyphData > ptrEndData)
    {
        qDebug() << "Failed to decode glyph" << characterIndex << "in font" << fontIndex << ": offset glyph after end of data";
        return false;
    }

    int x = left;
    int y = top;
    for (int line = 0; (line < fontsData->m_allCharacterWidths[fontIndex].m_characterWidths[characterIndex]) && (ptrGlyphData < ptrEndData); ptrGlyphData++)
    {
        // Decode pixel
        uint8_t code = *ptrGlyphData;
        if (code < 0x80)
        {
            uint8_t nrPixels = (code >> 4);
            uint8_t colorIndex = (code & 0x0F);
            if (image->format() == QImage::Format_Mono)
            {
                colorIndex = 0;
            }
            while (nrPixels-- > 0)
            {
                image->setPixel(x, y, colorIndex);
                y++;
            }
        }
        else if (code == 0x80)
        {
            x++;
            line++;
            y = top;
        }
        else if (code <= 0x8F)
        {
            y += (code - 0x80);
        }
        else
        {
            qDebug() << "Failed to decode glyph" << characterIndex << "in font" << fontIndex << ": code" << (int)code << "out of range";
            return false;
        }
    }

    return true;
}

void DialogLbxEditor::exportFont(size_t lbxIndex, const QString& directory)
{
    MoM::MoMLbxBase::eRecordType recordType = m_lbx.getRecordType(lbxIndex);
    if (recordType != MoM::MoMLbxBase::TYPE_font)
        return;
    std::vector<uint8_t> data;
    if (!m_lbx.getRecord(lbxIndex, data))
        return;
    if (data.size() < sizeof(MoMFontsStyleData))
        return;
    const MoMFontsStyleData* fontsData = reinterpret_cast<const MoMFontsStyleData*>(&data[0]);

    // For each font
    for (int fontIndex = 0; fontIndex < 8; ++fontIndex)
    {
        // For each glyph
        for (int ch = 0x20; ch < 0x7E; ++ch)
        {
            int characterIndex = ch - 0x20;

            // include 1 free line left and right
            int width = 2 + fontsData->m_allCharacterWidths[fontIndex].m_characterWidths[characterIndex];
            int height = 2 + fontsData->m_allFontHeights[fontIndex];

            // Create bitmap
            QMoMImagePtr image(new QImage(width, height, QImage::Format_Indexed8));
            QVector<QRgb> colorTable = QMoMResources::instance().getColorTable();
            colorTable.resize(256);
            colorTable[255] = qRgb(255, 255, 255);
            image->setColorTable(colorTable);
            image->fill(255);

            // Decode glyph
            if (!decodeGlyph(data, fontIndex, characterIndex, 1, 1, image))
            {
                (void)QMessageBox::warning(this,
                    tr("Export font"),
                    tr("Failed to decode glyph %0 in font %1").arg(characterIndex).arg(fontIndex));
                //break;
            }

            // Scale image
            image = QMoMImagePtr(new QImage(image->scaled(width * 2, height * 2, Qt::IgnoreAspectRatio, Qt::FastTransformation)));

            // Construct save filename
            QString fileTitle = QString("Font%0-%1").arg(fontIndex).arg(ch, 2, 16, QChar('0'));
            QString charStr = QString("%0").arg((QChar)ch);
            if (charStr.contains(QRegExp("[0-9A-Za-z]")))
            {
                fileTitle = fileTitle + "-" + charStr;
            }
            QFileInfo fileInfoPng(QDir(directory), fileTitle + ".png");

            // Save bitmap
            if (!image->save(fileInfoPng.absoluteFilePath()))
            {
                (void)QMessageBox::warning(this,
                    tr("Export font"),
                    tr("Failed to save font character as '%0'").arg(fileInfoPng.absoluteFilePath()));
                break;
            }
        }
    }
}




void DialogLbxEditor::processFont(int lbxIndex)
{
    MoM::MoMLbxBase::eRecordType recordType = m_lbx.getRecordType(lbxIndex);
    if (recordType != MoM::MoMLbxBase::TYPE_font)
        return;
    std::vector<uint8_t> data;
    if (!m_lbx.getRecord(lbxIndex, data))
        return;
    if (data.size() < sizeof(MoMFontsStyleData))
        return;

    m_lbxAnimations[lbxIndex].clear();

    const MoMFontsStyleData* fontsData = reinterpret_cast<const MoMFontsStyleData*>(&data[0]);

    QVector<QRgb> colorTable(13);
    for (int i = 1; i < 13; ++i)
    {
        colorTable[i] = qRgb(73 * (24 - 6 + i) / 24, 56 * (24 - 6 + i) / 24, 36 * (24 - 6 + i) / 24);
    }
    colorTable[0] = qRgb(148, 105, 48);

    for (int fontIndex = 0; fontIndex < 8; ++fontIndex)
    {
        QString text = constructComboBoxTitle(lbxIndex, fontIndex);

        int height = fontsData->m_allFontHeights[fontIndex];
        int width = 0;
        for (int ch = 0x20; ch < 0x7E; ++ch)
        {
            int characterIndex = ch - 0x20;
            width += fontsData->m_allCharacterWidths[fontIndex].m_characterWidths[characterIndex] + fontsData->m_allHorizontalSpacings[fontIndex];
        }
        qDebug("Font %d has height %d width %d lineSpacing %d at 0x%04X"
               , fontIndex, height, width, fontsData->m_allLineSpacings[fontIndex], fontsData->m_allGlyphOffsets[fontIndex].m_glyphOffsets[0]);

        QMoMImagePtr image(new QImage(width, height, QImage::Format_Indexed8));
        image->setColorTable(colorTable);
        image->fill(0);

        int x = 0;
        int y = 0;
        for (int ch = 0x20; ch < 0x7E; ++ch)
        {
            int characterIndex = ch - 0x20;
//            qDebug("Glyph data for '%c' at 0x%04X", ch, fontsData->m_allGlyphOffsets[fontIndex][characterIndex]);

            if (!decodeGlyph(data, fontIndex, characterIndex, x, y, image))
            {
                break;
            }

            x += fontsData->m_allCharacterWidths[fontIndex].m_characterWidths[characterIndex] + fontsData->m_allHorizontalSpacings[fontIndex];
        }

        m_lbxAnimations[lbxIndex].append(image);
    }
    m_lbxAnimations[lbxIndex].scale(2.0);
}
