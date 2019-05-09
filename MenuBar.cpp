#include "MenuBar.h"

extern "C" {
#include "aes.h"
#include "libc.h"
}

#include "app.h"
#include "LinkedListNode.h"

MenuBar::MenuBar() {
	object_array = nullptr;
	callbacks_array = nullptr;
}

MenuBar::~MenuBar() {
	if (object_array) {
		delete[] object_array;
		delete[] callbacks_array;
	}
}

/* This function is massive. It would be good to make it a compile-time option. */
// NOTE see Atari Compendium for more info
void MenuBar::buildObjectArray(Application *app) {
	// count: 3 + menus (title objects) + 1 + menus + total menuitems
	uint16_t count = 4;
	for (smonson::LinkedListNode<Menu> *n = contents.getHead(); n; n = n->getNext()) {
		Menu *item = n->getItem();
		count += 2;
		count += item->getContents()->findLength();
	}
	object_array = new OBJECT[count];
	callbacks_array = new menu_callback[count];
	memset(callbacks_array, 0, sizeof(callbacks_array) * sizeof(menu_callback));

	int menu_x[contents.findLength()];

	uint16_t width = app->get_screen_width();
	uint16_t char_height = app->get_char_height();

	/* Build required base menu structure */
	// ROOT - should be width and height of the screen
	new_object2(app, &object_array[0], OBJ_IBOX, (void *)0,
		0, 0, 0,
		width, 0, 200); // FIXME: hard-coded height
	object_array[0].ob_next = -1;
	object_array[0].ob_head = 1;

	// THE BAR
	new_object2(app, &object_array[1], OBJ_GBOX, (void *)0x1100,
		0, 0, 0,
		width, 1, 2); // height of font plus 2 pixels
	object_array[1].ob_head = 2;
	object_array[1].ob_tail = 2;

	// Do the ACTIVE (object_array[2]) after this bit so we'll know how wide it is

	// Add menu titles
	int o = 3, i = 0;
	int menu_start_x = 0;
	int total_menu_width = 0;
	smonson::LinkedListNode<Menu> *n;
	for (n = contents.getHead(); n; n = n->getNext()) {
		Menu *item = n->getItem();
		int width = strlen(item->getTitle()) * 8;
		total_menu_width += width;
		menu_x[i] = menu_start_x;
		o = 3 + i;
		new_object(&object_array[o], OBJ_GTITLE, (void *)item->getTitle(),
				menu_start_x, 0, width, char_height + 3);
		menu_start_x += width;
		object_array[o].ob_next = o + 1;
		object_array[o].ob_head = -1;
		object_array[o].ob_tail = -1;

		i++;
	}

	// fill in THE ACTIVE - height of font, width of menu titles
	new_object2(app, &object_array[2], OBJ_IBOX, (void *)0,
		2 * 8, 0, 0, // x, y
		total_menu_width, 1, 0);  // width, height
	object_array[2].ob_next = 1;
	object_array[2].ob_head = 3;
	object_array[2].ob_tail = o; // update pointer from ACTIVE to the last menu title

	// update last menu title's 'next' pointer to point back to ACTIVE
	object_array[o].ob_next = 2;
	o++;

	// THE SCREEN
	int i_screen = o;
	int screen_width = 0;
	int screen_height = 0;

	new_object(&object_array[i_screen], OBJ_IBOX, (void *)0, 0,
		char_height + 3, width, 8 * char_height);
	object_array[i_screen].ob_next = 0;
	int i_menu = o + 1;
	object_array[i_screen].ob_head = i_menu; // FIXME: if menus are present. pointer to menus

	object_array[0].ob_tail = o; // update ROOT pointer
	object_array[1].ob_next = o; // update BAR pointer

	// Walk the menu list again to add the drop-down part of the menus
	i = 0;
	for (n = contents.getHead(); n; n = n->getNext()) {
		// i_menu is from 6... then 15
		Menu *item = n->getItem();

		o++;
		i_menu = o;

		// The box around the drop-down part of the menu
		new_object(&object_array[i_menu], OBJ_GBOX, (void *)0xff1100,
				menu_x[i] + (2 * 8), 0, 0, 0);
		object_array[i_menu].ob_head = i_menu + 1; // the first menu item in the list
		object_array[i_menu].ob_tail = -1;
		object_array[i_screen].ob_tail = o; // update pointer from SCREEN

		// Add menu items
		smonson::LinkedListNode<MenuItem> *s;
		int j = 0;
		int max_width = 0;
		int o_start = o;
		for (s = item->getContents()->getHead(); s; s = s->getNext()) {
			MenuItem *subItem = s->getItem();
			int width = strlen(subItem->getText()) * 8;
			o++;
			new_object(&object_array[o], OBJ_GSTRING, (void *)subItem->getText(),
					0, j * char_height, width, char_height);
			object_array[o].ob_next = o + 1;
			object_array[o].ob_head = -1;
			object_array[o].ob_tail = -1;
			object_array[i_screen].ob_tail = o; // update tail pointer from SCREEN to the current item

			callbacks_array[o] = subItem->getAction();

			if (max_width < width)
				max_width = width;

			j++;
		}
		// Update size and pointers for this menu group
		object_array[i_menu].ob_width = max_width; // width, height of drop-down box
		object_array[i_menu].ob_height = j * char_height;
		object_array[i_menu].ob_next = o + 1; // pointer to next menu
		object_array[i_menu].ob_tail = o; // tail of menu's list points to last item
		object_array[o].ob_next = i_menu; // last next pointer goes back to menu

		// Update widths
		o = o_start;
		for (s = item->getContents()->getHead(); s; s = s->getNext()) {
			o++;
			object_array[o].ob_width = max_width;
		}

		// keep track of max width/height
		screen_width = (object_array[i_menu].ob_x + object_array[i_menu].ob_width) > screen_width ?
				(object_array[i_menu].ob_x + object_array[i_menu].ob_width) : screen_width;
		screen_height = object_array[i_menu].ob_width > screen_height ?
				object_array[i_menu].ob_width : screen_height;
		i++;
	}
	object_array[i_screen].ob_tail = i_menu; // tail of SCREEN's list
	object_array[i_menu].ob_next = i_screen; // last pointer back to SCREEN

	// max size of SCREEN
	object_array[i_screen].ob_width = screen_width;
	object_array[i_screen].ob_height = screen_height;
}

OBJECT *MenuBar::get_object_array() {
	return object_array;
}

void MenuBar::addMenu(Menu *menu) {
	contents.addItem(menu);
}

void MenuBar::do_callback(uint16_t menu, uint16_t item) {
	if (callbacks_array[item]) {
		callbacks_array[item]();
	}
}

void MenuBar::new_object2(Application *app, OBJECT *o, uint16_t type, void *spec, uint16_t x,
	uint16_t y_lines, uint16_t y_pixels, uint16_t width,
	uint16_t height_lines, uint16_t height_pixels) {
	uint16_t char_height = app->get_char_height();
	o->ob_type = type;
	o->ob_flags = 0;
	o->ob_state = 0;
	o->ob_spec = spec;
	o->ob_x = x;
	o->ob_y = (y_lines * char_height) + y_pixels;
	o->ob_width = width;
	o->ob_height = (height_lines * char_height) + height_pixels;
}
