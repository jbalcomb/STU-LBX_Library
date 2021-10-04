#include "lib_lbx_unbrun.h"


#include <string.h>
/*#include "unbrun_.h"*/
#include "lib_lbx_unbrun.h"


static const VP_UBYTE *
VP_unbrun_copy(const VP_UBYTE *src, VP_UBYTE *dst)
{
    unsigned int lineopcount = *src++;

    for (; lineopcount > 0; lineopcount--) {
        int length = (VP_BYTE) *src++;

        if (length >= 0) {
            memset(dst, *src, length);
            src++;
            dst += length;
        }
        else {
            length = -length;
            memcpy(dst, src, length);
            src += length;
            dst += length;
        }
    }

    return src;
}


static const VP_UBYTE *
VP_unbrun_skip(const VP_UBYTE *src)
{
    unsigned int lineopcount = *src++;

    for (; lineopcount > 0; lineopcount--) {
        int length = (VP_BYTE) *src++;

        if (length >= 0) {
            src++;
        }
        else {
            length = -length;
            src += length;
        }
    }

    return src;
}


void
VP_unbrun(const VP_UBYTE *src, VP_UBYTE *dst, unsigned int linect)
{
    for (; linect > 0; linect--) {
        src = VP_unbrun_copy(src, dst);
        dst += VP_WIDTH;
    }
}
