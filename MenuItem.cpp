#include "MenuItem.h"
extern "C" {
#include <libc.h>
}

MenuItem::MenuItem(const char *text, menu_callback action) {
	this->text = text;
	this->action = action;
}

MenuItem::~MenuItem() {
}

