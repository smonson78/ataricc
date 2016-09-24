extern "C" {
#include <aes.h>
#include <aes_window.h>
#include <tos.h>
#include <stdint.h>
#include <libc.h>
}

#include "app_app.h"
#include "app_window.h"

Window::Window() {
    isopen = false;
    maximised = false;
    handle = wind_create(WIND_BASIC, 0, 0, 640, 400);
}

void Window::update() {
    // Calculate work area from window dimensions
    wind_calc(WC_WORK, WIND_BASIC,
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
        wind_set(handle, WF_CURRXYWH, x, y, w, h);
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
    int16_t x1, y1, x2, y2;

    // horizontal
    x1 = max(dst[0], src[0]);
    x2 = min(dst[0] + dst[2], src[0] + src[2]);
    dst[0] = x1;
    dst[2] = max(0, x2 - x1);

    // vertical
    y1 = max(dst[1], src[1]);
    y2 = min(dst[1] + dst[3], src[1] + src[3]);
    dst[1] = y1;
    dst[3] = max(0, y2 - y1);
}

// Redraw part of the window contents
void Window::redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h) 
{
    // Disable updates
    graf_mouse(M_OFF, (MFORM *)NULL);
    wind_update(BEG_UPDATE);

    // set clipping rectangle to updated area
    int16_t cliprect[4];
    cliprect[0] = x;
    cliprect[1] = y;
    cliprect[2] = w;
    cliprect[3] = h;
    
    // Get first rectangle
    int16_t r[4];
    wind_get(handle, WF_FIRSTXYWH, &r[0], &r[1], &r[2], &r[3]);

    // If rectangle has height or width
    while (r[2] || r[3]) {

        // Intersect with repaintable area
        intersect_xywh(r, cliprect);
        
        if (r[2] && r[3]) {

            // set clipping rectangle to current rectangle
            int16_t temp[4];
            temp[0] = r[0];
            temp[1] = r[1];
            temp[2] = r[0] + r[2] - 1;
            temp[3] = r[1] + r[3] - 1;
            vs_clip(vhandle, 1, temp);
            
            draw(vhandle, temp);
        }
        
        // Get next rectangle
        wind_get(handle, WF_NEXTXYWH, &r[0], &r[1], &r[2], &r[3]);
    }
    
    // Enable updates
    wind_update(END_UPDATE);
    graf_mouse(M_ON, (MFORM *)NULL);
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

void Window::settitle(const char *t) {
    title = t;
    wind_set(handle, WF_NAME, (int32_t)t >> 16, (int32_t)t & 0xFFFF, 0, 0);
}

void Window::open() {
    update();
    wind_open(handle, dimensions[0], dimensions[1], 
        dimensions[2], dimensions[3]);
    isopen = true;
}

void Window::close() {
}

// Draw client area
void Window::draw(int16_t vhandle, int16_t rect[])
{
    // Set draw mode=REPLACE, fill style=solid
    vswr_mode(vhandle, 1);
	vsf_interior(vhandle, 1);

    // Paint white
    vsf_color(vhandle, 0);
    //vr_recfl(vhandle, temp);
    v_bar(vhandle, rect);
}

void Window::set_app(Application *a)
{
    app = a;
}



