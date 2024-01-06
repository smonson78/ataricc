#ifndef MENUBAR_H_
#define MENUBAR_H_

extern "C" {
	#include <stdint.h>
#include "aes_object.h"
}
#include "Menu.h"
#include "LinkedList.h"

#include "Menu.h"
#include "MenuItem.h"

class Application;

class MenuBar {

public:
	MenuBar();
	virtual ~MenuBar();
	void addMenu(Menu *menu);
	void buildObjectArray(Application *app);
	void do_callback(uint16_t menu, uint16_t item);
	OBJECT *get_object_array();

private:
	OBJECT *object_array;
	menu_callback *callbacks_array;
	smonson::LinkedList<Menu> contents;
	void new_object2(Application *app, OBJECT *o, uint16_t type, void *spec, uint16_t x,
		uint16_t y_lines, uint16_t y_pixels, uint16_t width,
		uint16_t height_lines, uint16_t height_pixels);
};

#endif
