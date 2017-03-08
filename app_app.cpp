#include "app_app.h"
#include "app_window.h"

void init_object(OBJECT *o) {
    //memset(o, 0, sizeof(OBJECT));
    o->ob_x = 0;
    o->ob_y = 0;
    o->ob_width = 0;
    o->ob_height = 0;
    o->ob_spec = (void *)0;
    o->ob_type = 0;
    o->ob_flags = 0;
    o->ob_state = 0;
    o->ob_next = -1;
    o->ob_head = -1;
    o->ob_tail = -1;
}

Application::Application() {

    // Clear window list
    for (int16_t i = 0; i < MAX_WINDOWS; i++)
        windows[i] = (Window *)NULL;
        
    quit_flag = false;
    
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
    
    OBJECT tree[15];
    for (int i = 0; i < 15; i++) {
        init_object(&tree[i]);
    }
    
    // ROOT
    tree[0].ob_type = 25 /* I_BOX */;
    tree[0].ob_width = 80;
    tree[0].ob_height = 25;
    tree[0].ob_head = 1;
    tree[0].ob_tail = 4;
    
    // THE BAR
    tree[1].ob_type = 20 /* G_BOX */;
    tree[1].ob_spec = (void *)0x1100;
    tree[1].ob_width = 80;
    tree[1].ob_height = 0x201;
    tree[1].ob_next = 4;
    tree[1].ob_head = 2;
    tree[1].ob_tail = 2;
    
    // THE ACTIVE
    tree[2].ob_type = 25 /* I_BOX */;
    tree[2].ob_x = 2;
    tree[2].ob_width = 10;
    tree[2].ob_height = 0x301;
    tree[2].ob_next = 1;
    tree[2].ob_head = 3;
    tree[2].ob_tail = 3;
    
    // menu 1 (DESK)
    tree[3].ob_type = 32 /* I_TITLE */;
    tree[3].ob_spec = (void *)"   DESK   ";
    tree[3].ob_width = 10;
    tree[3].ob_height = 0x301;
    tree[3].ob_next = 2;
   
    // THE SCREEN
    tree[4].ob_type = 25 /* I_BOX */;
    tree[4].ob_y = 0x301;
    tree[4].ob_width = 23;
    tree[4].ob_height = 8;
    tree[4].ob_head = 5;
    tree[4].ob_tail = 5;
    tree[4].ob_next = 0;

    // dropdown 1 (DESK)
    tree[5].ob_type = 20 /* G_BOX */;
    tree[5].ob_x = 2;
    tree[5].ob_y = 0;
    tree[5].ob_spec = (void *)0xff1100;
    tree[5].ob_width = 25;
    tree[5].ob_height = 8;
    tree[5].ob_next = 4;
    tree[5].ob_head = 6;
    tree[5].ob_tail = 13;
    
    // DESK menu items 6,7,8,9,10,11,12,13
    for (int i = 0; i < 8; i++) {
        tree[6 + i].ob_type = 28; // G_STRING
        tree[6 + i].ob_next = 6 + i + 1;
        tree[6 + i].ob_y = i;
        tree[6 + i].ob_width = 21;
        tree[6 + i].ob_height = 1;
    }
    tree[7].ob_state = 8;
    tree[13].ob_next = 5;
    
    tree[8].ob_spec = (void *)"~~~~~~~~~~~~~~~1";
    tree[9].ob_spec = (void *)"~~~~~~~~~~~~~~~2";
    tree[10].ob_spec = (void *)"~~~~~~~~~~~~~~~3";
    tree[11].ob_spec = (void *)"~~~~~~~~~~~~~~~4";            
    tree[12].ob_spec = (void *)"~~~~~~~~~~~~~~~5";
    tree[13].ob_spec = (void *)"~~~~~~~~~~~~~~~6";

    menu_bar(tree, MENU_SHOW);
}

Application::~Application() {
    //menu_bar(&menu_bar, MENU_HIDE);
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
    return (Window *)NULL;
}

// Event loop
void Application::run()
{
    int16_t msg[8];
    
    while (quit_flag == false) {
    
        //int16_t dummy[6];

        evnt_mesag(msg);
        //evnt_multi(0x10, 0, 0, 0, 0, 0, 0, 0, 0,
        //    0, 0, 0, 0, 0,
        //    msg, 
        //    0, 0, 
        //    &dummy[0], &dummy[1], &dummy[2], &dummy[3], &dummy[4], &dummy[5]);
            
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
        }
    }
}

int16_t Application::open_vwork(int16_t phys_handle)
{
    int16_t work_in[11];
    int16_t work_out[57];
    int16_t new_handle;
    int16_t i;

    work_in[0] = 2 + Getrez();
    for (i = 1; i < 10; i++) {
	    work_in[i] = 1;
    }
    work_in[10] = 2;
    new_handle = phys_handle;
    v_opnvwk(work_in, &new_handle, work_out);
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

// Exit the event loop and therefore end the application
void Application::quit() {
    quit_flag = true;
}

// Return the size of the desktop work area in rect
void Application::get_screen_size(RectXYWH *rect)
{
    wind_get(0, WF_WORKXYWH, &rect->x, &rect->y, &rect->w, &rect->h);
}


