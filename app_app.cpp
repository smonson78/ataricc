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
    
    OBJECT tree[16];
    //for (int i = 0; i < 15; i++) {
    //    init_object(&tree[i]);
    //}
#if 0    
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
    tree[2].ob_y = 0;
    tree[2].ob_width = 15;
    tree[2].ob_height = 0x201;
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

    tree[6].ob_spec = (void *)"Something";
    tree[7].ob_spec = (void *)"-----";
    tree[8].ob_spec = (void *)"~~~~~~~~~~~~~~~1";
    tree[9].ob_spec = (void *)"~~~~~~~~~~~~~~~2";
    tree[10].ob_spec = (void *)"~~~~~~~~~~~~~~~3";
    tree[11].ob_spec = (void *)"~~~~~~~~~~~~~~~4";            
    tree[12].ob_spec = (void *)"~~~~~~~~~~~~~~~5";
    tree[13].ob_spec = (void *)"~~~~~~~~~~~~~~~6";
#endif

tree[0].ob_type = 20; //25;
tree[0].ob_next = -1;
tree[0].ob_head = 1;
tree[0].ob_tail = 5;
tree[0].ob_flags = 0;
tree[0].ob_state = 0;
tree[0].ob_x = 0x0;
tree[0].ob_y = 0x0;
tree[0].ob_width = 0x50;
tree[0].ob_height = 0x19;
tree[0].ob_spec = (void *)0x00000000;

tree[1].ob_type = 20;
tree[1].ob_next = 5;
tree[1].ob_head = 2;
tree[1].ob_tail = 2;
tree[1].ob_flags = 0;
tree[1].ob_state = 0;
tree[1].ob_x = 0x0;
tree[1].ob_y = 0x0;
tree[1].ob_width = 0x50;
tree[1].ob_height = 0x201;
tree[1].ob_spec = (void *)0x00001100;

tree[2].ob_type = 25;
tree[2].ob_next = 1;
tree[2].ob_head = 3;
tree[2].ob_tail = 4;
tree[2].ob_flags = 0;
tree[2].ob_state = 0;
tree[2].ob_x = 0x2;
tree[2].ob_y = 0x0;
tree[2].ob_width = 0xf;
tree[2].ob_height = 0x301;
tree[2].ob_spec = (void *)0x00000000;

tree[3].ob_type = 32;
tree[3].ob_next = 4;
tree[3].ob_head = -1;
tree[3].ob_tail = -1;
tree[3].ob_flags = 0;
tree[3].ob_state = 0;
tree[3].ob_x = 0x0;
tree[3].ob_y = 0x0;
tree[3].ob_width = 0x9;
tree[3].ob_height = 0x301;
tree[3].ob_spec = (void *)" Program";

tree[4].ob_type = 32;
tree[4].ob_next = 2;
tree[4].ob_head = -1;
tree[4].ob_tail = -1;
tree[4].ob_flags = 0;
tree[4].ob_state = 0;
tree[4].ob_x = 0x9;
tree[4].ob_y = 0x0;
tree[4].ob_width = 0x6;
tree[4].ob_height = 0x301;
tree[4].ob_spec = (void *)" File";

tree[5].ob_type = 25;
tree[5].ob_next = 0;
tree[5].ob_head = 6;
tree[5].ob_tail = 15;
tree[5].ob_flags = 0;
tree[5].ob_state = 0;
tree[5].ob_x = 0x0;
tree[5].ob_y = 0x301;
tree[5].ob_width = 0x17;
tree[5].ob_height = 0x8;
tree[5].ob_spec = (void *)0x00000000;

tree[6].ob_type = 20;
tree[6].ob_next = 15;
tree[6].ob_head = 7;
tree[6].ob_tail = 14;
tree[6].ob_flags = 0;
tree[6].ob_state = 0;
tree[6].ob_x = 0x2;
tree[6].ob_y = 0x0;
tree[6].ob_width = 0x15;
tree[6].ob_height = 0x8;
tree[6].ob_spec = (void *)0x00ff1100;

tree[7].ob_type = 28;
tree[7].ob_next = 8;
tree[7].ob_head = -1;
tree[7].ob_tail = -1;
tree[7].ob_flags = 0;
tree[7].ob_state = 0;
tree[7].ob_x = 0x0;
tree[7].ob_y = 0x0;
tree[7].ob_width = 0x15;
tree[7].ob_height = 0x1;
tree[7].ob_spec = (void *)"  Your message";

tree[8].ob_type = 28;
tree[8].ob_next = 9;
tree[8].ob_head = -1;
tree[8].ob_tail = -1;
tree[8].ob_flags = 0;
tree[8].ob_state = 8;
tree[8].ob_x = 0x0;
tree[8].ob_y = 0x1;
tree[8].ob_width = 0x15;
tree[8].ob_height = 0x1;
tree[8].ob_spec = (void *)"---------------------";

tree[9].ob_type = 28;
tree[9].ob_next = 10;
tree[9].ob_head = -1;
tree[9].ob_tail = -1;
tree[9].ob_flags = 0;
tree[9].ob_state = 0;
tree[9].ob_x = 0x0;
tree[9].ob_y = 0x2;
tree[9].ob_width = 0x15;
tree[9].ob_height = 0x1;
tree[9].ob_spec = (void *)"  Desk Accessory 1  ";

tree[10].ob_type = 28;
tree[10].ob_next = 11;
tree[10].ob_head = -1;
tree[10].ob_tail = -1;
tree[10].ob_flags = 0;
tree[10].ob_state = 0;
tree[10].ob_x = 0x0;
tree[10].ob_y = 0x3;
tree[10].ob_width = 0x15;
tree[10].ob_height = 0x1;
tree[10].ob_spec = (void *)"  Desk Accessory 2";

tree[11].ob_type = 28;
tree[11].ob_next = 12;
tree[11].ob_head = -1;
tree[11].ob_tail = -1;
tree[11].ob_flags = 0;
tree[11].ob_state = 0;
tree[11].ob_x = 0x0;
tree[11].ob_y = 0x4;
tree[11].ob_width = 0x15;
tree[11].ob_height = 0x1;
tree[11].ob_spec = (void *)"  Desk Accessory 3";

tree[12].ob_type = 28;
tree[12].ob_next = 13;
tree[12].ob_head = -1;
tree[12].ob_tail = -1;
tree[12].ob_flags = 0;
tree[12].ob_state = 0;
tree[12].ob_x = 0x0;
tree[12].ob_y = 0x5;
tree[12].ob_width = 0x15;
tree[12].ob_height = 0x1;
tree[12].ob_spec = (void *)"  Desk Accessory 4";

tree[13].ob_type = 28;
tree[13].ob_next = 14;
tree[13].ob_head = -1;
tree[13].ob_tail = -1;
tree[13].ob_flags = 0;
tree[13].ob_state = 0;
tree[13].ob_x = 0x0;
tree[13].ob_y = 0x6;
tree[13].ob_width = 0x15;
tree[13].ob_height = 0x1;
tree[13].ob_spec = (void *)"  Desk Accessory 5";

tree[14].ob_type = 28;
tree[14].ob_next = 6;
tree[14].ob_head = -1;
tree[14].ob_tail = -1;
tree[14].ob_flags = 0;
tree[14].ob_state = 0;
tree[14].ob_x = 0x0;
tree[14].ob_y = 0x7;
tree[14].ob_width = 0x15;
tree[14].ob_height = 0x1;
tree[14].ob_spec = (void *)"  Desk Accessory 6";

tree[15].ob_type = 20;
tree[15].ob_next = 5;
tree[15].ob_head = 16;
tree[15].ob_tail = 16;
tree[15].ob_flags = 0;
tree[15].ob_state = 0;
tree[15].ob_x = 0xb;
tree[15].ob_y = 0x0;
tree[15].ob_width = 0x7;
tree[15].ob_height = 0x1;
tree[15].ob_spec = (void *)0x00ff1100;

    if (rsrc_load("TEST.RSC"))
    {
        form_alert(1, "[1][Resource loaded][ OK ]");
    }
    
    OBJECT *menu;
    rsrc_gaddr(0, 0, &menu);


    graf_mouse(256, (MFORM*)NULL);
    menu_bar(menu, MENU_SHOW);
    graf_mouse(257, (MFORM*)NULL);
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


