#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


struct Menu
{

	int pageNumber = 1000;
	bool resusme = 1;
	int shift = 60 * resusme;
	bool pressed = false;
	Text mainmenu[10];
	int selected = 0;
	Font font;
	int height = 1080;
	int choises;
	int positionOfHand = 60;
	Texture handTex;
	RectangleShape hand;

	void Hand_intilization();
	void MoveDown(int& selected, int choises);
	void MoveUp(int& selected, int choises);
	void menu1(RenderWindow &window, int &GameMode);
	void Play_menu(RenderWindow& window, int &GameMode);
	void options_menu1(RenderWindow& window);
	void options_menu(RenderWindow& window);
	void instructions(RenderWindow& window);

};
