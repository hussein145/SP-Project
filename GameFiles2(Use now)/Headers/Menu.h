#pragma once
#include "include.h"

struct Menu
{
	int level = 0;
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
	bool chenge_keyboard = 0;
	Texture handTex;
	RectangleShape hand;
	float display = 0;
	Text letter;
	void changeKeyMapping(int& action, Keyboard::Key newKey, Keyboard::Key &moveLeftKey, Keyboard::Key &moveRightKey, Keyboard::Key &jumpKey, Menu& menu9);
	void Hand_intilization();
	void MoveDown(int& selected, int choises);
	void MoveUp(int& selected, int choises);
	void menu1(RenderWindow& window, int& GameMode);
	void levels(RenderWindow& window);
	void Play_menu(RenderWindow& window, int& GameMode);
	void sound_options(RenderWindow& window);
	void options_menu1(RenderWindow& window);
	void player_controls(RenderWindow& window, Keyboard::Key& moveLeftKey, Keyboard::Key& moveRightKey, Keyboard::Key& jumpKey);
	void control_menu(RenderWindow& window);
	void options_menu(RenderWindow& window);
	void  credits(RenderWindow& window);
	void instructions(RenderWindow& window);
	void Pause(RenderWindow& window, Texture gametexture);
	string keyboardKeyToString(sf::Keyboard::Key key);
};
