extern "C" {
#include <aes.h>
#include <aes_window.h>
#include <tos.h>
#include <stdint.h>
}

#include "app_window.h"

void Window::redraw(int16_t vhandle) 
{
    int16_t rect[4];

    // Get extent of visible area
    wind_get(handle, 4, // WF_WORKXYWH
        &rect[0], &rect[1], &rect[2], &rect[3]);

    // Set draw mode=REPLACE
    vswr_mode(vhandle, 1);
    
    // Calculate new x,y,w,h from rect corners
    int16_t rect2[4];
    rect2[0] = rect[0];
    rect2[1] = rect[1];
    rect2[2] = rect[0] + rect[2] - 1;
    rect2[3] = rect[1] + rect[3] - 1;
    
	vsf_color(vhandle, 0); // colour 0
    vr_recfl(vhandle, rect2);
}

// Redraw only part of the window contents
void Window::redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h) 
{
    redraw(vhandle);
}
