#include "app_app.h"
#include "app_window.h"

Application::Application() {

    // Clear window list
    for (int16_t i = 0; i < MAX_WINDOWS; i++)
        windows[i] = (Window *)NULL;
    
    app_id = appl_init();
    if (app_id == -1) {
	    Cconws("*** Initialization error.\n");
	    Cconws("Press any key to continue.\n");
	    Cconin();
	    exit(1);
    }
    
    // Change mouse from busy-bee into pointer
    graf_mouse(0, (MFORM*)NULL);

    screen_phandle = graf_handle(&gr_wchar, &gr_hchar, &gr_wbox, &gr_hbox);
    screen_vhandle = open_vwork(screen_phandle);
}

Application::~Application() {
    v_clsvwk(screen_vhandle);
    appl_exit();
}

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
    
        //int16_t dummy[6];

        evnt_mesag(msg);
        //evnt_multi(0x10, 0, 0, 0, 0, 0, 0, 0, 0,
        //    0, 0, 0, 0, 0,
        //    msg, 
        //    0, 0, 
        //    &dummy[0], &dummy[1], &dummy[2], &dummy[3], &dummy[4], &dummy[5]);
            
        WM_Event e = (WM_Event)msg[0];
        
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

int16_t Application::open_vwork(int16_t phys_handle)
{
    int16_t work_in[11];
    int16_t work_out[57];
    int16_t new_handle;
    int16_t i;

    for (i = 0; i < 10; i++) {
	    work_in[i] = 1;
    }
    work_in[10] = 2;
    new_handle = phys_handle;
    v_opnvwk(work_in, &new_handle, work_out);
    return new_handle;
}

void Application::add_window(Window *w) {

    // Keep track of the given window
    for (int16_t i = 0; i < MAX_WINDOWS; i++) {
        if (!windows[i]) {
            windows[i] = w;
            return;
        }
    }
    
    // FIXME: handle error
}


