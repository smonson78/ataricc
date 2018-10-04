#include "MenuBar.h"

extern "C" {
#include "aes.h"
#include "libc.h"
}

#include "LinkedListNode.h"

MenuBar::MenuBar(uint16_t char_height) {
	this->char_height = char_height;
}

MenuBar::~MenuBar() {
}

/* This function is massive. It would be good to make it a compile-time option. */
OBJECT *MenuBar::buildObjectArray() {
	OBJECT *p = new OBJECT[30];

	int menu_x[contents.findLength()];

	/* Build required base menu structure */
	// ROOT
	new_object2(&p[0], OBJ_IBOX, (void *)0,
		0, 0, 0,
		80 * 8, 25, 0);
	p[0].ob_next = -1;
	p[0].ob_head = 1;

	// THE BAR
	new_object2(&p[1], OBJ_GBOX, (void *)0x1100, 0, 0, 0, 80 * 8, 16, 2);
	p[1].ob_head = 2;
	p[1].ob_tail = 2;

	// Do the ACTIVE (p[2]) after this bit so we'll know how wide it is

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
		new_object(&p[o], OBJ_GTITLE, (void *)item->getTitle(),
				menu_start_x, 0, width, 16 + 3);
		menu_start_x += width;
		p[o].ob_next = o + 1;
		p[o].ob_head = -1;
		p[o].ob_tail = -1;

		i++;
	}

	// fill in THE ACTIVE
	new_object(&p[2], OBJ_IBOX, (void *)0, 2 * 8, 0, total_menu_width, 16 + 3);
	p[2].ob_next = 1;
	p[2].ob_head = 3;
	p[2].ob_tail = o; // update pointer from ACTIVE to the last menu title

	// update last menu title's 'next' pointer to point back to ACTIVE
	p[o].ob_next = 2;
	o++;

	// THE SCREEN
	int i_screen = o;
	int screen_width = 0;
	int screen_height = 0;

	new_object(&p[i_screen], OBJ_IBOX, (void *)0, 0, 16 + 3, 80 * 8, 8 * 16);
	p[i_screen].ob_next = 0;
	int i_menu = o + 1;
	p[i_screen].ob_head = i_menu; // FIXME: if menus are present. pointer to menus

	p[0].ob_tail = o; // update ROOT pointer
	p[1].ob_next = o; // update BAR pointer

	// Walk the menu list again to add the drop-down part of the menus
	i = 0;
	for (n = contents.getHead(); n; n = n->getNext()) {
		// i_menu is from 6... then 15
		Menu *item = n->getItem();

		o++;
		i_menu = o;

		// The box around the drop-down part of the menu
		new_object(&p[i_menu], OBJ_GBOX, (void *)0xff1100,
				menu_x[i] + (2 * 8), 0, 0, 0);
		p[i_menu].ob_head = i_menu + 1;
		p[i_menu].ob_tail = -1;
		p[i_screen].ob_tail = o; // update pointer from SCREEN

		// Add menu items
		smonson::LinkedListNode<MenuItem> *s;
		int j = 0;
		int max_width = 0;
		int o_start = o;
		for (s = item->getContents()->getHead(); s; s = s->getNext()) {
			MenuItem *subItem = s->getItem();
			int width = strlen(subItem->getText()) * 8;
			o++;
			new_object(&p[o], OBJ_GSTRING, (void *)subItem->getText(),
					0, j * 16, width, 1 * 16);
			p[o].ob_next = o + 1;
			p[o].ob_head = -1;
			p[o].ob_tail = -1;
			p[i_screen].ob_tail = o; // update pointer from SCREEN

			if (max_width < width)
				max_width = width;

			j++;
		}

		// Update widths
		o = o_start;
		for (s = item->getContents()->getHead(); s; s = s->getNext()) {
			o++;
			p[o].ob_width = max_width;
		}

		p[i_menu].ob_width = max_width; // width, height of drop-down box
		p[i_menu].ob_height = j * 16;
		p[i_menu].ob_next = o + 1; // pointer to next menu
		p[i_menu].ob_tail = o; // tail of menu's list
		p[o].ob_next = i_menu; // last pointer back to menu

		// keep track of max width/height
		screen_width = (p[i_menu].ob_x + p[i_menu].ob_width) > screen_width ?
				(p[i_menu].ob_x + p[i_menu].ob_width) : screen_width;
		screen_height = p[i_menu].ob_width > screen_height ?
				p[i_menu].ob_width : screen_height;
		i++;
	}
	p[i_screen].ob_tail = i_menu; // tail of SCREEN's list
	p[i_menu].ob_next = i_screen; // last pointer back to SCREEN

	// max size of SCREEN
	p[i_screen].ob_width = screen_width;
	p[i_screen].ob_height = screen_height;

	o++;

	return p;
}

void MenuBar::addMenu(Menu *menu) {
	contents.addItem(menu);
}

void MenuBar::new_object2(OBJECT *o, uint16_t type, void *spec, uint16_t x,
	uint16_t y_lines, uint16_t y_pixels, uint16_t width,
	uint16_t height_lines, uint16_t height_pixels) {
	o->ob_type = type;
	o->ob_flags = 0;
	o->ob_state = 0;
	o->ob_spec = spec;
	o->ob_x = x;
	o->ob_y = (y_lines * char_height) + y_pixels;
	o->ob_width = width;
	o->ob_height = (height_lines * char_height) * height_pixels;
}
