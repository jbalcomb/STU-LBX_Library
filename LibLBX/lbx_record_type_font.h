#ifndef LBX_TYPE_FONT_H
#define LBX_TYPE_FONT_H

/* F:\Development_OPC\momrtgt-code\QMoMDialogs\DialogLbxEditor.cpp */
/* F:\Development_OPC\momrtgt-code\MoMModel\MoMTemplate.h */

typedef struct PACKED_STRUCT // MoMFontsCharacterWidths
{
    int8_t      m_characterWidths[0x60];
} MoMFontsCharacterWidths;

typedef struct PACKED_STRUCT // MoMFontsGlyphOffsets
{
    uint16_t    m_glyphOffsets[0x60];
} MoMFontsGlyphOffsets;

typedef struct PACKED_STRUCT // MoMFontsStyleData
{
    uint8_t     m_Unk_0000[0x0010];             // 0000
    int16_t     m_curFontHeight;                // 0010
    uint8_t     m_Unk_0012[0x0036];             // 0012
    int16_t     m_curHorizontalSpacing;         // 0048
    int8_t      m_curCharacterWidths[0x60];     // 004A
    uint16_t    m_curGlyphOffsets[0x60];        // 00AA
    int16_t     m_allFontHeights[8];            // 016A
    int16_t     m_allHorizontalSpacings[8];     // 017A
    int16_t     m_allLineSpacings[8];           // 018A
    MoMFontsCharacterWidths m_allCharacterWidths[8];// 019A
    MoMFontsGlyphOffsets    m_allGlyphOffsets[8];   // 049A

    uint8_t     m_glyphData[1];                 // 0A9A
    // SIZE 4574
} MoMFontsStyleData;

#endif  /* LBX_TYPE_FONT_H */
