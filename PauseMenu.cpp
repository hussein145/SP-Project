#include "PauseMenu.h"
#include "Menu.h"
#include "menu_Bg_and_Face.h"
#include <SFML/Graphics.hpp> 
#include<SFML/Audio.hpp> 
#include<SFML/System.hpp> 
#include<SFML/Window.hpp> 
#include<iostream> 
#include<time.h>
using namespace sf;
using namespace std;
PauseMenu::PauseMenu(float width, float hight)
{
	//if (!font.loadFromFile("arial.ttf")) {}
	font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::Blue);
	mainmenu[0].setString("continue");
	mainmenu[0].setCharacterSize(90);
	mainmenu[0].setPosition(150, 100);

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(sf::Color::White);
	mainmenu[1].setString("resume");
	mainmenu[1].setCharacterSize(90);
	mainmenu[1].setPosition(150, 300);

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(sf::Color::White);
	mainmenu[2].setString("exit");
	mainmenu[2].setCharacterSize(90);
	mainmenu[2].setPosition(150, 500);

	mainmenuselected = 0;
}

PauseMenu::~PauseMenu()
{

}
void PauseMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(mainmenu[i]);
	}
}
void PauseMenu::movedown() {
	if (mainmenuselected + 1 <= Max_main_menu) {
		mainmenu[mainmenuselected].setFillColor(sf::Color::White);
		mainmenuselected++;
		if (mainmenuselected == 3) {
			mainmenuselected = 0;
		}
		mainmenu[mainmenuselected].setFillColor(sf::Color::Blue);
	}
}
//move up
void PauseMenu::moveup() {
	if (mainmenuselected - 1 >= -1) {
		mainmenu[mainmenuselected].setFillColor(sf::Color::White);
		mainmenuselected--;
		if (mainmenuselected == -1) {
			mainmenuselected = 2;
		}
		mainmenu[mainmenuselected].setFillColor(sf::Color::Blue);
	}
}

