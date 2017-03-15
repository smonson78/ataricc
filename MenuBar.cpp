#include "MenuBar.h"

MenuBar::MenuBar() {
}

MenuBar::~MenuBar() {
}

void MenuBar::addMenu(Menu *menu) {
	contents.addItem(menu);
}
