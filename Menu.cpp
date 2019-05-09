#include "Menu.h"
#include "MenuItem.h"

extern "C" {
#include "libc.h"
}

Menu::Menu() {
	title = "";
}

Menu::Menu(const char *title) {
	this->title = title;
}

Menu::~Menu() {
}

void Menu::addMenuItem(const char *text) {
	contents.addItem(new MenuItem(text, nullptr));
}

void Menu::addMenuItem(const char *text, menu_callback callback) {
	contents.addItem(new MenuItem(text, callback));
}

void Menu::set_object_index(int index) {
	title_object = index;
}

int Menu::get_object_index() {
	return title_object;
}
