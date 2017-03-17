#include "MenuBar.h"

extern "C" {
#include "aes.h"
#include "libc.h"
}

#include "LinkedListNode.h"

MenuBar::MenuBar() {
}

MenuBar::~MenuBar() {
}

OBJECT *MenuBar::buildObjectArray() {
	OBJECT *p = new OBJECT[30];

	int menu_x[contents.findLength()];

	/* Build required base menu structure */
	// ROOT
	new_object(&p[0], OBJ_IBOX, (void *)0, 0, 0, 80 * 8, 25 * 16);
	p[0].ob_next = -1;
	p[0].ob_head = 1;

	// THE BAR
	new_object(&p[1], OBJ_GBOX, (void *)0x1100, 0, 0, 80 * 8, 16 + 2);
	p[1].ob_head = 2;
	p[1].ob_tail = 2;

	// THE ACTIVE
	// FIXME: width should be total width of all menus
	new_object(&p[2], OBJ_IBOX, (void *)0, 2 * 8, 0, 30 * 8, 16 + 3);
	p[2].ob_next = 1;
	p[2].ob_head = 3;
	p[2].ob_tail = -1;

	// Add menu titles
	int o = 3, i = 0;
	int menu_start_x = 2 * 8;
	smonson::LinkedListNode<Menu> *n;
	for (n = contents.getHead(); n; n = n->getNext()) {
		Menu *item = n->getItem();
		int width = strlen(item->getTitle()) * 8;
		menu_x[i] = menu_start_x;
		o = 3 + i;
		new_object(&p[o], OBJ_GTITLE, (void *)item->getTitle(),
				// give it 15 chars width for now
				menu_start_x, 0, width, 16 + 3);
		menu_start_x += width;
		p[o].ob_next = o + 1;
		p[o].ob_head = -1;
		p[o].ob_tail = -1;
		p[2].ob_tail = o; // update pointer from ACTIVE

		i++;
	}
	// update last pointer to point back to ACTIVE
	p[o].ob_next = 2;
	o++;

	// THE SCREEN (5)
	// FIXME: shrink to fit menus
	int i_screen = o;

	new_object(&p[i_screen], OBJ_IBOX, (void *)0, 0, 16 + 3, 80 * 8, 8 * 16);
	p[i_screen].ob_next = 0;
	int i_menu = o + 1;
	p[i_screen].ob_head = i_menu; // FIXME: if present. pointer to menus

	p[0].ob_tail = o; // update ROOT pointer
	p[1].ob_next = o; // update BAR pointer

	// Walk the menu list again to add the drop-down part of the menus
	i = 0;
	for (n = contents.getHead(); n; n = n->getNext()) {
		// i_menu is from 6... then 15
		Menu *item = n->getItem();

		o++;
		i_menu = o;
		new_object(&p[i_menu], OBJ_GBOX, (void *)0xff1100,
				menu_x[i] + (2 * 8), 0, 0, 0);
		p[i_menu].ob_head = i_menu + 1;
		p[i_menu].ob_tail = -1;
		p[i_screen].ob_tail = o; // update pointer from ACTIVE

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
			p[i_screen].ob_tail = o; // update pointer from ACTIVE

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
		i++;
	}
	p[i_screen].ob_tail = i_menu; // tail of SCREEN's list
	p[i_menu].ob_next = i_screen; // last pointer back to SCREEN

	o++;
	//printf("Menu size: %d\n", o);


//	menu_bar(p, MENU_SHOW);
	return p;
}


void MenuBar::addMenu(Menu *menu) {
	contents.addItem(menu);
}
