#include "app.h"
#include "app_window.h"

Application::Application() {
    // Clear window list
    for (int16_t i = 0; i < MAX_WINDOWS; i++)
        windows[i] = nullptr;

    // No menu bar
    current_menubar = nullptr;

    quit_flag = false;


    app_id = appl_init();
    if (app_id == -1) {
	    Cconws("*** Initialization error.\n");
	    Cconws("Press any key to continue.\n");
	    Cconin();
	    exit(1);
    }

    // Change mouse from busy-bee into pointer
    graf_mouse(0, nullptr);

    // Current video mode
    screen_mode = Getrez();

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
        Window *w = windows[i];
        if (w && w->handle == h) {
            return w;
        }
    }
    form_alert(1, "[1][AES error:|Requested window handle doesn't exist.][ OK ]");
    return nullptr;
}

// Event loop
void Application::run()
{
    int16_t msg[8];

    while (quit_flag == false) {
        evnt_mesag(msg);
        WM_Event e = (WM_Event)msg[0];
        Window *w;

        switch (e) {
        case WM_REDRAW:
            w = find_window_by_handle(msg[3]);
            w->redraw(screen_vhandle,
                msg[4], msg[5], msg[6], msg[7]);
            break;
        case WM_NEWTOP:
        case WM_TOPPED:
            w = find_window_by_handle(msg[3]);
            w->event_topped();
            break;
        case WM_CLOSED:
            w = find_window_by_handle(msg[3]);
            w->event_closed();
            break;
        case WM_FULLED:
            w = find_window_by_handle(msg[3]);
            w->event_fulled();
            break;
        case WM_SIZED:
            w = find_window_by_handle(msg[3]);
            w->size(msg[4], msg[5], msg[6], msg[7]);
            break;
        case WM_MOVED:
            w = find_window_by_handle(msg[3]);
            w->size(msg[4], msg[5], msg[6], msg[7]);
            break;
        case MN_SELECTED:
            if (current_menubar) {
                //const char *buf = "[1][Menu selected X X!][ OK ]";
                //((char *)buf)[18] = '0' + msg[3];
                //((char *)buf)[20] = '0' + msg[4];
                //form_alert(1, buf);
                //if (msg[4] == 16) // object index of menu item selected
                //    quit();
                current_menubar->do_callback(msg[3], msg[4]);
                menu_tnormal(current_menubar->get_object_array(), msg[3], 1);
            }
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

    work_in[0] = 2 + screen_mode;
    for (i = 1; i < 10; i++) {
	    work_in[i] = 1;
    }
    work_in[10] = 2;
    new_handle = phys_handle;
    v_opnvwk(work_in, &new_handle, work_out);
    screen_width = work_out[0] + 1;
    screen_height = work_out[1] + 1;
    return new_handle;
}

// Add a Window to the application
void Application::add_window(Window *w) {

    // Keep a reference to the application in the window, so that events
    // in the window can easily access application data.
    w->set_app(this);

    // Keep track of the given window
    for (int16_t i = 0; i < MAX_WINDOWS; i++) {
        if (!windows[i]) {
            windows[i] = w;
            return;
        }
    }

    form_alert(1, "[1][Out of windows!][ OK ]");
    quit();
}

void Application::add_menubar(MenuBar *mb) {
  // Construct the object array for this menu bar
  current_menubar = mb;
  current_menubar->buildObjectArray(this);

  // Attach the menu bar to the screen
  menu_bar(current_menubar->get_object_array(), MENU_SHOW);
}

// Exit the event loop and therefore end the application
void Application::quit() {
    quit_flag = true;
}

// Return the size of the desktop work area in rect
void Application::get_screen_size(RectXYWH *rect)
{
    wind_get(0, WF_WORKXYWH, &rect->x, &rect->y, &rect->w, &rect->h);
}

uint16_t Application::get_char_height() {
  if (screen_mode == 2)
    return 16;
  return 8;
}

uint16_t Application::get_screen_width() {
  if (screen_mode == 0)
    return 320;
  return 640;
}
