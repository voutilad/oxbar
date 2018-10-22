#ifndef XINFO_H
#define XINFO_H

#include <sys/types.h>

#include <xcb/xcb.h>
#include <cairo/cairo.h>
#include <pango/pango-font.h>

/* pango font wraper */
typedef struct xfont {
   char                 *ufont;  /* user-specified font string unchanged */
   PangoFontDescription *pfont;  /* pango font loaded from that string   */
   int                   height; /* derived font height (in pixels)      */
} xfont_t;

xfont_t *xfont_init(const char *const font_description);
void xfont_free(xfont_t *xf);

/* x display info - this is readonly info about our x display */
typedef struct xdisp {
   uint32_t              display_width;
   uint32_t              display_height;
   xcb_connection_t     *con;
   xcb_screen_t         *root_screen;
   xcb_visualtype_t     *root_visual;
} xdisp_t;

xdisp_t *xdisp_init();
void xdisp_free(xdisp_t *x);

/* xcb window & cairo wrapper */
typedef struct xwin_settings {
   char *bgcolor;    /* background color of window                   */
   char *wname;      /* name of window for window manager            */
   int   x, y;       /* (x,y) pixel coordinates of top-left corner   */
   int   w, h;       /* (width,height) pixel dimensions of window    */
} xwin_settings_t;

typedef struct xwin {
   xwin_settings_t  *settings;
   xdisp_t          *xdisp;      /* x display server                    */
   xcb_drawable_t    window;     /* oxbar xwindow                       */
   cairo_surface_t  *surface;    /* core ciaro surface mapped to X      */
   cairo_t          *cairo;      /* core ciaro object for rendering     */
} xwin_t;

xwin_t *xwin_init(
   xdisp_t    *xdisp,
   xwin_settings_t *settings);
void xwin_free(xwin_t *w);
void xwin_push(xwin_t *w);
void xwin_pop(xwin_t *w);

/* a universal method to translate colors to components */
void hex2rgba(const char *s, double *r, double *g, double *b, double *a);

#endif
