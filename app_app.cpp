#include "app_app.h"
#include "app_window.h"

Window *Application::find_window_by_handle(int16_t h)
{
    for (uint16_t i = 0; i < MAX_WINDOWS; i++) {
        if (windows[i] && windows[i]->handle == h) {
            return windows[i];
        }
    }
    return (Window *)NULL;
}

void Application::event_handler()
{
    int16_t quit = 0;
    int16_t msg[8];
    int16_t rect[4];
    
    // (Re)draw contents of all open windows
    for (int16_t i = 0; i < MAX_WINDOWS; i++) {
        if (windows[i]) {
            windows[i]->redraw(screen_vhandle);
        }
    }
    
    while (!quit) {

        evnt_mesag(msg);
        
        // Find the window that owns the event
        Window *w;
        switch (msg[0]) {
        case 20:
        case 21:
        case 22:
        case 23:
        case 28:
        case 27:
            w = find_window_by_handle(msg[3]);
        }
        
        switch (msg[0]) {
        case 20: // WM_REDRAW
            w->redraw(screen_vhandle);
            break;
        case 21: // WM_TOPPED
            wind_set(msg[3], 10 /* WF_TOP */, 0, 0, 0, 0);
            break;
        case 22: // WM_CLOSED
            //if (msg[3] == window)
            quit = 1;
            break;
        case 23: // WM_FULLED
            // get size of widow 0 (desktop)
            wind_get(0, 4, &rect[0], &rect[1], &rect[2], &rect[3]);
            w->size(rect[0], rect[1], rect[2], rect[3]);
            w->redraw(screen_vhandle);
            break;
        case 28: // WM_MOVED
            w->size(msg[4], msg[5], msg[6], msg[7]);
            w->redraw(screen_vhandle);
            break;
        case 27: // WM_SIZED
            w->size(msg[4], msg[5], msg[6], msg[7]);
            w->redraw(screen_vhandle);
            break;
        }
    }
}

