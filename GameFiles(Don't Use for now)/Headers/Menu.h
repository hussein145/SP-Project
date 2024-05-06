#pragma once
#include "include.h"

struct Menu
{
	bool exit = 0;
	int pageNumber = 1000;
	int shift = 60;
	Text mainmenu[10];
	int selected = 0;
	Font font;
	int height = 1080;
	int choises;
	int positionOfHand = 60;
	bool play_again = 0;
	int x = 40;
	Texture handTex;
	RectangleShape hand;
	void Hand_intilization();
	void MoveDown(int& selected, int choises);
	void MoveUp(int& selected, int choises);
	void menu1(RenderWindow& window, int& GameMode);
	void levels(RenderWindow& window);
	void Play_menu(RenderWindow& window, int& GameMode);
	void sound_options(RenderWindow& window);
	void options_menu1(RenderWindow& window);
	void options_menu(RenderWindow& window);
	void instructions(RenderWindow& window);
	void Pause(RenderWindow& window, Texture gametexture);
};