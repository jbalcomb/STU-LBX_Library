
/* stdint.h */
typedef unsigned char   uint8_t;

/* Qt: qrgb.h */
typedef unsigned int QRgb;  /* RGB triplet */
/*
inline Q_DECL_CONSTEXPR QRgb qRgb(int r, int g, int b)// set RGB value
{ return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }

inline Q_DECL_CONSTEXPR QRgb qRgba(int r, int g, int b, int a)// set RGBA value
{ return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }
*/


/* Qt: qvector.h */
/*
class QVector
{
    ...
};
 */


/* ILSe - MoM-RTGT: QMoMLbx.h */
/* typedef QVector<QRgb> QMoMPalette; */
typedef QRgb MOMRTGT_QMoMPalette[255];
const uint8_t MOMRTGT_gTRANSPARENT_COLOR = 0;
const uint8_t MOMRTGT_gSHADOW_COLOR = 232;
const uint8_t MOMRTGT_gFIRST_BANNER_COLOR = 215;  /* Either 215 or 216. Apparently only 3 colors are actually used (216-218). */
const uint8_t MOMRTGT_gCOUNT_BANNER_COLOR = 4;


/* ILSe - MoM-RTGT: QMoMResources.h */
/*QMoMPalette m2_colorTable;*/  /* LBX Mgr keeps complaint about this having multiple definitions, but I don't see it, but, also, I don't actually know how this stuff works. */


/* ILSe - MoM-RTGT: MoMLbxBase.h */
/*
class MoMLbxBase
{
  ...
;}
*/
/*
https://www.google.com/search?q=C+language+can+you+put+a+function+in+a+struct&oq=C+language+can+you+put+a+function+in+a+struct&aqs=chrome..69i64j33i22i29i30.12918j0j7&sourceid=chrome&ie=UTF-8
|-> https://stackoverflow.com/questions/12642830/can-i-define-a-function-inside-a-c-structure#:~:text=No%2C%20you%20cannot%20define%20a,to%20the%20containing%20struct%20instance.&text=In%20C%20it%20is%20not,a%20method%20inside%20a%20struct%20.
*/
struct MoMLbxBase
{
    uint8_t* (*getRecord)(int);
};


QRgb qRgb(int r, int g, int b);
uint8_t* MoMLbxBase_getRecord(int RedNbr);
void createColorTable();
void convertLbxToPalette(const uint8_t* dataPalette, QMoMPalette colorTable);




/* Qt: qrgb.h
 * inline Q_DECL_CONSTEXPR QRgb qRgb(int r, int g, int b)// set RGB value
 * inline Q_DECL_CONSTEXPR QRgb qRgba(int r, int g, int b, int a)// set RGBA value*/
QRgb qRgb(int r, int g, int b)
{
    return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
};
QRgb qRgba(int r, int g, int b, int a)
{
    return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
};

/* ILSe - MoM-RTGT: MoMLbxBase.cpp
 * const uint8_t* MoMLbxBase::getRecord(size_t recordNr) const { ... };*/
uint8_t* MoMLbxBase_getRecord(int RecNbr)
{
    char * fontsLbxFile = "F:\\devel_data\\STU\\MoM131_LBX\\FONTS.LBX";
    LBX_DATA * lbx;
    /* lbx = malloc(sizeof(LBX_DATA)); */
    lbx = create_lbx_data(fontsLbxFile);
    lbx_open_file(lbx);
    lbx_load_header(lbx);

    return (uint8_t*)get_record_data(lbx, RecNbr);
};

void createColorTable()
{
    /* fontsLbxFile = m_game->getGameDirectory() + "/" + "FONTS.LBX"; */
    struct MoMLbxBase fontsLbx = { MoMLbxBase_getRecord };
    uint8_t* dataPalette = fontsLbx.getRecord(2);
    /*convertLbxToPalette(dataPalette, m2_colorTable);*/ /* see not in the .h ... LBX Mgr - multiple definitions */
}

/* ILSe - MoM-RTGT: ...\QMoMCommon\QMoMLbx.cpp */
void convertLbxToPalette(const uint8_t* dataPalette, QMoMPalette colorTable)
{
    int i;
    for (i = 0; i < 256; ++i)
    {
        colorTable[i] = qRgb(4 * dataPalette[3*i], 4 * dataPalette[3*i+1], 4 * dataPalette[3*i+2]);
    }

    /* Set transparent color */
    colorTable[gTRANSPARENT_COLOR] = qRgba(0, 0, 0, 0);
}
/*
 * i {0, 1, 2, ..., 253, 254, 255}
 *
 * coloTable[0] = qRgb( 4 * dataPalette[3 * 0], 4 * dataPalette[3 * 0 + 1], 4 * dataPalette[ 3 * 0 + 2] )
 * coloTable[0] = qRgb( 4 * dataPalette[0],     4 * dataPalette[1],         4 * dataPalette[2] )
 *
 * coloTable[1] = qRgb( 4 * dataPalette[3 * 1], 4 * dataPalette[3 * 1 + 1], 4 * dataPalette[ 3 * 1 + 2] )
 * coloTable[1] = qRgb( 4 * dataPalette[3],     4 * dataPalette[4],         4 * dataPalette[5] )
 *
 * coloTable[2] = qRgb( 4 * dataPalette[3 * 2], 4 * dataPalette[3 * 2 + 1], 4 * dataPalette[ 3 * 2 + 2] )
 * coloTable[2] = qRgb( 4 * dataPalette[6],     4 * dataPalette[7],         4 * dataPalette[8] )
 *
 * ...
 *
 * 256 * 3 = 768
 *
 * ...
 *
 * The fist 768 bytes of FONTS002.BIN are indeed all between 0 and 63.
 * However, the last 32 bytes are all 0.
 * And, 672 / 3 = 224.
 * So, that aligns with so many images having a 'palette_color_index' of 224.
 * It seems notable that those (all) have a 'palette_color_count of 20.
 * [There are also a bunch with 244 and 12.]
 *
 *  ...
 *
 *
 *
 */

