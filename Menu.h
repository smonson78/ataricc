#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu();
	Menu(const char *title);
	//void addMenuItem(const char *text, menu_callback callback);
	virtual ~Menu();
	const char *getTitle() {
		return title;
	}
private:
	const char *title;
	Menu *next;
};

#endif
