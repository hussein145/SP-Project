//#pragma once
//using namespace std;
//using namespace sf;
//
//struct Menu
//{
//	bool exit = 0;
//
//	int pageNumber = 0;
//	bool resusme = 1;
//	int shift = 60 * resusme;
//	Text mainmenu[10];
//	int selected = 0;
//	Font font;
//	int height = 1080;
//	int choises;
//	int positionOfHand = 60;
//	bool infile = 0;
//	bool boolenter = 0;
//	Texture handTex;
//	RectangleShape hand;
//	Texture enternameTX;
//	Sprite enternameSP;
//	Font playernamefont;
//	Text playerNameText;
//	string playername;
//	void Hand_intilization();
//	void MoveDown(int& selected, int choises);
//	void MoveUp(int& selected, int choises);
//	void menu1();
//	void Play_menu();
//	//void options_menu1(RenderWindow& window);
//	void options_menu();
//	void instructions();
//	//void Pause(RenderWindow& window, Texture gametexture);
//	//void Menues(RenderWindow& window);
//	void GameMenu();
//	void intilize();
//};