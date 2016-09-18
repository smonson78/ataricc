extern "C" {
#include <tos.h>
#include <aes.h>
#include <aes_window.h>
#include <libc.h>
}

#include "app_app.h"

int main(int argc, char **argv)
{
    Application app;
	
	Window simon;
	simon.settitle("Smonson");
	app.add_window(&simon);

	Window simon2;
	simon2.settitle("Not-smonson");
	app.add_window(&simon2);

	simon.open();
	simon2.open();

    // Main loop	
    app.event_handler();
  
    form_alert(1, "[1][Thanks!][ OK ]");
  
	return 0;
}
