#pragma once
#define Max_main_menu 3
#include<sfml\Graphics.hpp>
class PauseMenu
{
public:
	PauseMenu(float width, float hight);
	//int sum(int x, int y);
	void draw(sf::RenderWindow& Window);
	void moveup();
	void movedown();
	//void selected(int t);
	int pressed() {
		return mainmenuselected;

	}

	~PauseMenu();
private:
	int mainmenuselected;
	sf::Font font;
	sf::Text mainmenu[Max_main_menu];
};
