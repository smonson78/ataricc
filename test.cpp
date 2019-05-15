
extern "C" {
#include <gemdos.h>
#include <libc.h>
}

#include "app.h"
#include "LinkedListNode.h"

class SmonsonWindow : public Window {

    void draw(int16_t vhandle, int16_t rect[]) {
        // Disable updates
        graf_mouse(M_OFF, nullptr);
        wind_update(BEG_UPDATE);

        vsf_color(vhandle, 1);
        v_bar(vhandle, rect);
        vsf_color(vhandle, 0);
        // Clip to drawable area
        vs_clip(vhandle, 1, rect);
        v_ellipse(vhandle,
            (visible[0] + visible[2] / 2),
            (visible[1] + visible[3] / 2),
            visible[2] / 2,
            visible[3] / 2
        );

        // Enable updates
        wind_update(END_UPDATE);
        graf_mouse(M_ON, nullptr);
    }

    public:
    void event_resized() {
    }

    void event_closed() {
        int16_t response = form_alert(1,
            "[2][Are you sure you want to quit?]"
            "[ NO | YES ]");
        if (response == 2)
            app->quit();
    }

    void about() {
      form_alert(1,
          "[1][|Smonson was filmed in front of|a live studio audience.]"
          "[ OK ]");
    }
    ~SmonsonWindow() {
    }
};
/*
void recurse_print(OBJECT *b, int start)
{
	OBJECT *o = &b[start];
	printf("%d - type %d -->%d [%d .. %d] \n",
		start, o->ob_type,
		o->ob_next, o->ob_head, o->ob_tail);
	if (o->ob_head != -1) {
		int n = o->ob_head;
		while (n != start) {
			recurse_print(b, n);
			n = b[n].ob_next;
		}
	}
}
*/

Application app;
SmonsonWindow simon;
MenuBar *menubar;
Menu *programMenu;
Menu *fileMenu;

void open_callback() {
  char path[200];
  char name[13];
  int16_t result;
  fsel_input(path, name, &result);

  char msg[80];
  sprintf(msg, "[2][You selected: %s][ Thanks! ]", name);
  form_alert(1, msg);
}

void quit_callback() {
  simon.event_closed();
}

void about_callback() {
  simon.about();
}

void get_menubar() {
  menubar = new MenuBar();
  programMenu = new Menu(" Smonson ");
  fileMenu = new Menu(" File ");
  menubar->addMenu(programMenu);
  menubar->addMenu(fileMenu);

  programMenu->addMenuItem("  About...  ", about_callback);
  programMenu->addMenuItem("  First");
  programMenu->addMenuItem("  Second");
  programMenu->addMenuItem("  Third");
  programMenu->addMenuItem("  Fourth");
  programMenu->addMenuItem("  Fifth  ");
  programMenu->addMenuItem("  Sixth  ");
  programMenu->addMenuItem("  Seventh  ");
  programMenu->addMenuItem("  Eighth");
/*
  smonson::LinkedListNode<MenuItem> *n;
  printf("Program menu has %d items in it\n", programMenu->getContents()->findLength());
  for (n = programMenu->getContents()->getHead(); n; n = n->getNext()) {
		MenuItem *item = n->getItem();
    printf("--> %s\n", item->getText());
  }
*/


  fileMenu->addMenuItem("  Open", open_callback);
  fileMenu->addMenuItem("  Close");
  fileMenu->addMenuItem("---------");
  fileMenu->addMenuItem("  Quit", quit_callback);
}

int main(int argc, char **argv)
{
  // Reset terminal
  //printf("\x1b");
  //printf("E\n\n\n--start--\n");

  //printf("Hello!\n%d %p %s %x\n", 123, buf, "greetings", 255);
  //sprintf(buf, "Hello!\n%d %p %s %x\n", 123, buf, "greetings", 255);
  //printf("\n[%s]", buf);
  //Cconin();

	simon.setstyle(WIND_BASIC);
	simon.settitle("Smonson");
	simon.size(20, 20, 150, 60);
	app.add_window(&simon);

	/*Window *simon2 = new Window();
	app.add_window(simon2);
	simon2->setstyle(WIND_NAME|WIND_MOVER);
	simon2->settitle("Not-smonson");
	simon2->size(100, 70, 150, 60);

	simon2->open();*/

	simon.open();

  get_menubar();
  app.add_menubar(menubar);

	//recurse_print(menubar->get_object_array(), 0);

  // Main loop
  app.run();
  //delete simon2;

  return 0;
}
