#include "app_app.h"
#include "app_window.h"

Window *Application::find_window_by_handle(int16_t h)
{
    for (uint16_t i = 0; i < MAX_WINDOWS; i++) {
        if (windows[i] && windows[i]->handle == h) {
            return windows[i];
        }
    }
    form_alert(1, "[1][Crapped out][ OK ]");
    return (Window *)NULL;
}

void Application::event_handler()
{
    int16_t quit = 0;
    int16_t msg[8];
    
    while (!quit) {

        evnt_mesag(msg);
        Event e = (Event)msg[0];
        
        // Find the window that owns the event
        Window *w;
        switch (e) {
        case WM_REDRAW:
        case WM_NEWTOP:
        case WM_TOPPED:
        case WM_FULLED:
        case WM_SIZED:
        case WM_MOVED:
            w = find_window_by_handle(msg[3]);
            break;
        default:
            break;
        }
        
        switch (e) {
        case WM_REDRAW:
            w->redraw(screen_vhandle,
                msg[4], msg[5], msg[6], msg[7]);
            break;
        case WM_NEWTOP:
        case WM_TOPPED:
            w->topped();
            break;
        case WM_CLOSED:
            quit = 1; // any window closed - quit
            break;
        case WM_FULLED:
            w->fulled();
            break;
        case WM_SIZED:
            w->size(msg[4], msg[5], msg[6], msg[7]);
            break;
        case WM_MOVED:
            w->size(msg[4], msg[5], msg[6], msg[7]);
            break;
        }
    }
}

