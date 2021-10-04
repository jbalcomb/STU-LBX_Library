#ifndef LIB_LBX_UNBRUN_H
#define LIB_LBX_UNBRUN_H



/* J:\STU\DBWD\developc\_AnimatorPro\src\COMMON\jimk0.h */

#ifndef JIMK0_H
#define JIMK0_H

typedef char VP_BYTE;
typedef unsigned char VP_UBYTE;
typedef short VP_WORD;
typedef unsigned short VP_UWORD;

#if defined(__TURBOC__)
typedef long VP_LONG;
typedef unsigned long VP_ULONG;
#else
typedef int VP_LONG;
typedef unsigned int VP_ULONG;
#endif

#endif /* JIMK0_H */


#ifndef JIMK_H
#define JIMK_H



/* J:\STU\DBWD\developc\_AnimatorPro\src\V\jimk.h */

/*#include <stdio.h>*/
/*#include "jimk0.h"*/

/* -------------  BASIC  DEFINES ----------------- */

#define VP_TRUE 1
#define VP_FALSE 0

#ifndef VP_NULL
#define VP_NULL ((void *)0)
#endif /* NULL */


typedef unsigned char *VP_PLANEPTR;


#define VP_XMAX 320
#define VP_BPR 320
#define VP_YMAX 200
#define VP_WIDTH 320
#define VP_HEIGHT 200
#define VP_DEPTH 8
#define VP_COLORS 256
#define VP_SCREEN_SIZE (BPR*HEIGHT)
#define VP_VGA_SCREEN ((void *)0xa0000000)
#define VP_CH_WIDTH 6
#define VP_CH_HEIGHT 8


/* size of a buffer big enough to hold a worst case FLI frame_raw */
#define VP_CBUF_SIZE (64000L+3*COLORS+256+16+sizeof(struct vscreen) )


/* This structure is your basic blitter food.  A rectangular image
   with associated color map. */


struct VP_vcel
{
    VP_WORD x, y;	/* upper left corner in screen coordinates */
    VP_UWORD w, h;	/* width, height */
    VP_UWORD bpr;	/* bytes per row of image p */
    VP_PLANEPTR p;	/* These is my pixels */
    VP_UBYTE *cmap;	/* These is my colors */
    VP_UWORD ix;	/* where in sequence we are (ignored) */
};
typedef struct VP_vcel VP_Vcel;
extern VP_Vcel *VP_cel;
extern VP_Vcel *VP_alloc_cel(), *VP_clone_cel();


/* This structure is something we can draw on.  A superset of Vcel
   (and keep it that way or things break!)  */
struct VP_vscreen
{
    VP_WORD x, y;	/* upper left corner in screen coordinates */
    VP_UWORD w, h;	/* width, height */
    VP_UWORD bpr;	/* bytes per row of image p */
    VP_PLANEPTR p;	/* Starts on segment boundary */
    VP_UBYTE *cmap;
    VP_UWORD ix;	/* where in sequence we are */
};
typedef struct VP_vscreen VP_Video_form;
typedef struct VP_vscreen VP_Vscreen;
extern VP_Vscreen VP_vf,VP_uf;
extern VP_Vscreen *VP_zoom_form, *VP_render_form, *VP_cursor_form, *VP_alt_form;
extern VP_Vscreen *VP_alloc_big_screen(),*VP_alloc_screen(), *VP_clone_screen();


#endif /* JIMK_H */



/* J:\STU\DBWD\developc\_AnimatorPro\src\COMMON\unbrun_.h */

#ifndef UNBRUN_H
#define UNBRUN_H

/* #include "jimk.h" */


/* Function: unbrun
 *
 *  Decompress 1st frame_raw full size.
 *
 *  src - compressed source.  See FLI.DOC for details.
 *  dst - byte plane to decompress onto.
 *  linect - number of lines of screen (always 320 now.)
 */
extern void VP_unbrun(const VP_UBYTE *src, VP_UBYTE *dst, unsigned int linect);

#endif /* UNBRUN_H */



#endif  /* LIB_LBX_UNBRUN_H */
