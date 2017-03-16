#include "Menu.h"
#include "MenuItem.h"

Menu::Menu() {
	title = "";
}

Menu::Menu(const char *title) {
	this->title = title;
}

Menu::~Menu() {
}

void Menu::addMenuItem(const char *text, menu_callback callback) {
	contents.addItem(new MenuItem(text, callback));
}

