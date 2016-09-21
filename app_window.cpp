extern "C" {
#include <aes.h>
#include <aes_window.h>
#include <tos.h>
#include <stdint.h>
#include <libc.h>
}

#include "app_window.h"

void Window::update() {
    // Find visible area
    wind_calc(1 /* WC_WORK */,
        0x2F,
        dimensions[0], dimensions[1], dimensions[2], dimensions[3],
        &visible[0], &visible[1], &visible[2], &visible[3]);
}

void Window::size(int16_t x, int16_t y, int16_t w, int16_t h) {
    dimensions[0] = x;
    dimensions[1] = y;
    dimensions[2] = w;
    dimensions[3] = h;
    update();

    if (isopen) {
        //graf_mouse(256 /* M_OFF */, (MFORM *)NULL);
        //wind_update(1);
        wind_set(handle, WF_CURRXYWH, x, y, w, h);
        //wind_update(0);
        //graf_mouse(257 /* M_ON */, (MFORM *)NULL);
    }

}

int16_t min(int16_t a, int16_t b)
{
    if (a < b)
        return a;
    return b;
}

int16_t max(int16_t a, int16_t b)
{
    if (a > b)
        return a;
    return b;
}

void intersect_xywh(int16_t *dst, int16_t *src)
{
    int16_t x1, y1, w, h;

    // horizontal
    if (dst[0] < src[0]) {
        x1 = src[0];
        w = min(
            max((dst[0] + dst[2]) - src[0], 0), 
            src[2]
        );
    } else {
        x1 = dst[0];
        w = min(
            max((src[0] + src[2]) - dst[0], 0),
            dst[2]
        );
    }

    // vertical
    if (dst[1] < src[1]) {
        y1 = src[1];
        h = min(
            max((dst[1] + dst[3]) - src[1], 0),
            src[3]
        );
    } else {
        y1 = dst[1];
        h = min(
            max((src[1] + src[3]) - dst[1], 0),
            dst[3]
        );
    }

    dst[0] = x1;
    dst[1] = y1;
    dst[2] = w;
    dst[3] = h;
}

// Redraw only part of the window contents
void Window::redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h) 
{
    // Disable updates
    graf_mouse(256 /* M_OFF */, (MFORM *)NULL);
    wind_update(1);

    // Set draw mode=REPLACE
    vswr_mode(vhandle, 1);
  
	// solid colour mode
	vsf_interior(vhandle, 1);
	
    // Colour 0 (white)
	vsf_color(vhandle, 0);
	
    // set clipping rectangle to updated area
    int16_t cliprect[4]; // vs_clip takes CORNERS not WxH
    cliprect[0] = x;
    cliprect[1] = y;
    cliprect[2] = w;
    cliprect[3] = h;
    
    // Get first rectangle
    int16_t r[4];
    wind_get(handle, WF_FIRSTXYWH, &r[0], &r[1], &r[2], &r[3]);

    // Only proceed if rectangle has height and width
    while (r[2] && r[3]) {

        // Limit to only the visible and changed area
        intersect_xywh(r, cliprect);
        
        if (r[2] && r[3]) {
            int16_t temp[4];

            // set clipping rectangle to current drawing rectangle
            temp[0] = r[0];
            temp[1] = r[1];
            temp[2] = (r[0] + r[2]) - 1;
            temp[3] = (r[1] + r[3]) - 1;
            vs_clip(vhandle, 1, temp);

            // Paint white - e.g. fill in client area with whatever.
        	vsf_color(vhandle, 0);
            vr_recfl(vhandle, temp);
        }
        
        // Get next rectangle
        wind_get(handle, WF_NEXTXYWH, &r[0], &r[1], &r[2], &r[3]);
    }
    
    // Reenable updates
    wind_update(0);
    graf_mouse(257 /* M_ON */, (MFORM *)NULL);
}

// Topped as in brought to top (focused)
void Window::topped()
{
    if (isopen) {
        wind_set(handle, WF_TOP, 0, 0, 0, 0);
    }
}

void Window::fulled()
{
    // get size of window 0 (desktop)
    int16_t rect[4];
    wind_get(0, WF_WORKXYWH, &rect[0], &rect[1], &rect[2], &rect[3]);
    size(rect[0], rect[1], rect[2], rect[3]);
}
