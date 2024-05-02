#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Sounds.h"
using namespace std;
using namespace sf;
int PLayer1 = 0;
int PLayer2 = 0;
extern bool END;
bool pressed = false;
extern Sounds sound;
menu_Bg_and_Face menu_UI;
void Gameplay();
void Menu::Hand_intilization()
{
	handTex.loadFromFile("Assets/Textures/hand.png");
	hand.setTexture(&handTex);
	hand.setSize(Vector2f(100, 70));
	hand.setPosition(1140, 580);
}
void Menu::MoveDown(int& selected, int choises)
{
	if (selected < choises)
	{
		mainmenu[selected].setFillColor(Color::Black);
		hand.setPosition(hand.getPosition().x, hand.getPosition().y + positionOfHand);
		selected++;
		if (selected == choises)
		{
			selected = 0;
			hand.setPosition(hand.getPosition().x, hand.getPosition().y - (choises * positionOfHand));
		}
		mainmenu[selected].setFillColor(Color{ 255,204,0 });
	}
}
void Menu::MoveUp(int& selected, int choises)
{
	if (selected > -1)
	{

		mainmenu[selected].setFillColor(Color::Black);
		hand.setPosition(hand.getPosition().x, hand.getPosition().y - positionOfHand);
		selected--;
		if (selected == -1)
		{
			selected = choises - 1;
			hand.setPosition(hand.getPosition().x, hand.getPosition().y + (positionOfHand * choises));
		}
		mainmenu[selected].setFillColor(Color{ 255,204,0 });

	}
}
void  Menu::menu1(RenderWindow& window, int& GameMode)
{
	Menu men1;
	sound.LoadMusic();
	sound.music(0);
	men1.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	enternameTX.loadFromFile("Assets/Textures/entername.png");
	enternameSP.setTexture(enternameTX);
	enternameSP.setPosition(500, 450);
	enternameSP.setScale(2, 2);
	playernamefont.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");

	playerNameText.setFont(playernamefont);
	playerNameText.setCharacterSize(24);
	playerNameText.setFillColor(sf::Color::Black);
	playerNameText.setPosition(570, 690);

	if (resusme) men1.mainmenu[0 + resusme].setFillColor(Color::Black);
	else   men1.mainmenu[0 + resusme].setFillColor(Color{ 255,204,0 });

	men1.choises = 6 + resusme;
	men1.mainmenu[0].setFont(men1.font);
	men1.mainmenu[0].setFillColor(Color{ 255,204,0 });
	men1.mainmenu[0].setString("Resume");
	men1.mainmenu[0].setCharacterSize(50);
	men1.mainmenu[0].setPosition(Vector2f(1250, men1.height / 2 + 40));

	men1.mainmenu[0 + resusme].setFont(men1.font);
	men1.mainmenu[0 + resusme].setString("Play Game");
	men1.mainmenu[0 + resusme].setCharacterSize(50);
	men1.mainmenu[0 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 40 + shift));

	men1.mainmenu[1 + resusme].setFont(men1.font);
	men1.mainmenu[1 + resusme].setFillColor(Color::Black);
	men1.mainmenu[1 + resusme].setString("Instructions");
	men1.mainmenu[1 + resusme].setCharacterSize(50);
	men1.mainmenu[1 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 100 + shift));

	men1.mainmenu[2 + resusme].setFont(men1.font);
	men1.mainmenu[2 + resusme].setFillColor(Color::Black);
	men1.mainmenu[2 + resusme].setString("Profile");
	men1.mainmenu[2 + resusme].setCharacterSize(50);
	men1.mainmenu[2 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 160 + shift));

	men1.mainmenu[3 + resusme].setFont(men1.font);
	men1.mainmenu[3 + resusme].setFillColor(Color::Black);
	men1.mainmenu[3 + resusme].setString("High Score");
	men1.mainmenu[3 + resusme].setCharacterSize(50);
	men1.mainmenu[3 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 220 + shift));

	men1.mainmenu[4 + resusme].setFont(men1.font);
	men1.mainmenu[4 + resusme].setFillColor(Color::Black);
	men1.mainmenu[4 + resusme].setString("Options");
	men1.mainmenu[4 + resusme].setCharacterSize(50);
	men1.mainmenu[4 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 280 + shift));

	men1.mainmenu[5 + resusme].setFont(men1.font);
	men1.mainmenu[5 + resusme].setFillColor(Color::Black);
	men1.mainmenu[5 + resusme].setString("Exit");
	men1.mainmenu[5 + resusme].setCharacterSize(50);
	men1.mainmenu[5 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 340 + shift));
	menu_UI.back_ground(window);
	men1.Hand_intilization();

	while (window.isOpen())
	{
		if (pageNumber == 1000)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::KeyPressed)

				{
					if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z)
					{
						playername.push_back('A' + event.key.code);

					}
					else if (event.key.code == Keyboard::BackSpace)
					{
						playername.pop_back();
					}
					else if (event.key.code == Keyboard::Space)
					{
						playername.push_back(' ');
					}


					if (event.key.code == Keyboard::Enter)
					{
						if (!boolenter)
						{

							enternameSP.setPosition(-1000, -1000);
							playerNameText.setPosition(-1000, -1000);
							infile = 1;
							boolenter = 1;

						}
					}

				}
				playerNameText.setString(playername);
				if (infile)
				{
					if (event.key.code == Keyboard::Escape && !pressed && men1.selected != 5 + resusme)
					{
						sound.change_option_Sound();
						men1.mainmenu[men1.selected].setFillColor(Color::Black);
						men1.selected = 5 + resusme;
						men1.mainmenu[5 + resusme].setFillColor(Color{ 255,204,0 });
						men1.hand.setPosition(1140, 890 + shift);
						pressed = true;
					}
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Down)
						{
							sound.change_option_Sound();

							men1.MoveDown(men1.selected, men1.choises);
						}
						if (event.key.code == Keyboard::Up)
						{
							sound.change_option_Sound();
							//so.play();
							men1.MoveUp(men1.selected, men1.choises);
						}
						if (event.key.code == Keyboard::Enter || event.key.code == Keyboard::Escape && !pressed && men1.selected == 5 + resusme)
						{
							sound.select_option_Sound();
							if (men1.selected == 5 + resusme)
								pageNumber = -1;
							if (men1.selected == 0 + resusme)
							{
								Play_menu(window, GameMode);
							}
							if (men1.selected == 4 + resusme)
								options_menu(window);
							if (men1.selected == 1 + resusme)
								instructions(window);
						}
					}
					if (!Keyboard::isKeyPressed(Keyboard::Escape))
					{
						pressed = false;
					}

				}
			}
		}
		menu_UI.FaceMotion(window);
		if (pageNumber == -1)
		{
			window.close();
			break;
		}


		window.clear();
		window.draw(menu_UI.bg);
		window.draw(menu_UI.face);
		for (int i = 0; i < men1.choises; i++)
		{
			window.draw(men1.mainmenu[i]);
		}
		window.draw(men1.hand);
		window.draw(enternameSP);
		window.draw(playerNameText);
		window.display();
	}
}
void  Menu::Play_menu(RenderWindow& window, int& GameMode)
{
	Menu menu2;
	menu2.Hand_intilization();
	menu2.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu2.choises = 4;

	menu2.mainmenu[0].setFont(menu2.font);
	menu2.mainmenu[0].setString("Single");
	menu2.mainmenu[0].setCharacterSize(50);
	menu2.mainmenu[0].setFillColor(Color{ 255,204,0 });
	menu2.mainmenu[0].setPosition(Vector2f(1250, menu2.height / 2 + 40));

	menu2.mainmenu[1].setFont(menu2.font);
	menu2.mainmenu[1].setString("Multi");
	menu2.mainmenu[1].setCharacterSize(50);
	menu2.mainmenu[1].setFillColor(Color::Black);
	menu2.mainmenu[1].setPosition(Vector2f(1250, menu2.height / 2 + 100));

	menu2.mainmenu[2].setFont(menu2.font);
	menu2.mainmenu[2].setString("PowerUps");
	menu2.mainmenu[2].setCharacterSize(50);
	menu2.mainmenu[2].setFillColor(Color::Black);
	menu2.mainmenu[2].setPosition(Vector2f(1250, menu2.height / 2 + 160));

	menu2.mainmenu[3].setFont(menu2.font);
	menu2.mainmenu[3].setString("Back");
	menu2.mainmenu[3].setCharacterSize(50);
	menu2.mainmenu[3].setFillColor(Color::Black);
	menu2.mainmenu[3].setPosition(Vector2f(1250, menu2.height / 2 + 220));

	pageNumber = 500;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
			{
				sound.select_option_Sound();
				if (menu2.selected == 3) {
					pageNumber = 1000;
					pressed = true;
					return;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape) && menu2.selected != 3 && !pressed)
			{
				sound.change_option_Sound();
				menu2.mainmenu[menu2.selected].setFillColor(Color::Black);
				menu2.selected = 3;
				menu2.mainmenu[3].setFillColor(Color{ 255,204,0 });
				menu2.hand.setPosition(1140, 760);
				pressed = true;
			}
			if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down) {
					sound.change_option_Sound();
					menu2.MoveDown(menu2.selected, menu2.choises);
				}
				if (event.key.code == Keyboard::Up) {
					sound.change_option_Sound();
					menu2.MoveUp(menu2.selected, menu2.choises);
				}
				//cout << Enter_Game << endl;
				if (event.key.code == Keyboard::Enter)
				{
					sound.select_option_Sound();
					if (menu2.selected == 0)   GameMode = 1;
					if (menu2.selected == 1)   GameMode = 2;
					if (menu2.selected == 2)   GameMode = 3;
					Gameplay();
				}
			}
		}
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		window.draw(menu_UI.face);
		for (int i = 0; i < menu2.choises; i++)
		{
			window.draw(menu2.mainmenu[i]);
		}
		window.draw(menu2.hand);

		window.display();
	}
}
void  Menu::options_menu1(RenderWindow& window)
{
	Menu menu5;
	menu5.Hand_intilization();
	menu5.positionOfHand = 110;
	menu5.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu5.choises = 3;

	menu5.mainmenu[0].setFont(menu5.font);
	menu5.mainmenu[0].setFillColor(Color{ 255,204,0 });
	menu5.mainmenu[0].setString("Player1 \n Charchters <>");
	menu5.mainmenu[0].setCharacterSize(50);
	menu5.mainmenu[0].setPosition(Vector2f(1250, menu5.height / 2 + 40));

	menu5.mainmenu[1].setFont(menu5.font);
	menu5.mainmenu[1].setFillColor(Color::Black);
	menu5.mainmenu[1].setString("Player2 \n Charchters <>");
	menu5.mainmenu[1].setCharacterSize(50);
	menu5.mainmenu[1].setPosition(Vector2f(1250, menu5.height / 2 + 150));

	menu5.mainmenu[2].setFont(menu5.font);
	menu5.mainmenu[2].setFillColor(Color::Black);
	menu5.mainmenu[2].setString("Back");
	menu5.mainmenu[2].setCharacterSize(50);
	menu5.mainmenu[2].setPosition(Vector2f(1250, menu5.height / 2 + 260));

	Texture pl1;
	pl1.loadFromFile("Assets/Textures/icytower1.png");

	Texture pl2;
	pl2.loadFromFile("Assets/Textures/icytower2.png");

	Sprite player1;
	Sprite player2;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				sound.change_option_Sound();
				menu5.MoveDown(menu5.selected, menu5.choises);
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				sound.change_option_Sound();
				menu5.MoveUp(menu5.selected, menu5.choises);
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) && menu5.selected != 2&& !pressed)
			{
				sound.change_option_Sound();
				menu5.mainmenu[menu5.selected].setFillColor(Color::Black);
				menu5.selected = 2;
				menu5.mainmenu[2].setFillColor(Color{ 255,204,0 });
				menu5.hand.setPosition(1140, 800);
				pressed = true;
			}
			if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape&& !pressed))
			{
				sound.select_option_Sound();
				if (menu5.selected == 2) {
					return;
				}
			}
			if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}

			if (menu5.selected == 0)
			{
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					if (PLayer1 > 0)
						PLayer1--;
					else
						PLayer1 = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if (PLayer1 < 1)
						PLayer1++;
					else
						PLayer1 = 0;
				}
			}
			else if (menu5.selected == 1)
			{
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					if (PLayer2 > 0)
						PLayer2--;
					else
						PLayer2 = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if (PLayer2 < 1)
						PLayer2++;
					else
						PLayer2 = 0;
				}
			}
		}
		if (PLayer1 == 0)
		{
			player1.setTexture(pl1);
		}
		else if (PLayer1 == 1)
		{
			player1.setTexture(pl2);
		}
		if (PLayer2 == 1)
		{
			player2.setTexture(pl1);
		}
		else if (PLayer2 == 0)
		{
			player2.setTexture(pl2);
		}
		player1.setTextureRect(IntRect(0, 0, 50, 60));
		player1.setScale(2.4, 2.4);
		player1.setPosition(1650, menu5.height / 2);
		player2.setTextureRect(IntRect(0, 0, 50, 60));
		player2.setScale(2.4, 2.4);
		player2.setPosition(1650, menu5.height / 2 + 150);
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		for (int i = 0; i < menu5.choises; i++)
		{
			window.draw(menu5.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu5.hand);
		window.draw(player1);
		window.draw(player2);
		window.display();
	}
}
void  Menu::options_menu(RenderWindow& window)
{
	Menu menu4;
	menu4.Hand_intilization();
	menu4.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu4.choises = 3;

	menu4.mainmenu[0].setFont(menu4.font);
	menu4.mainmenu[0].setFillColor(Color{ 255,204,0 });
	menu4.mainmenu[0].setString("GFX Options");
	menu4.mainmenu[0].setCharacterSize(50);
	menu4.mainmenu[0].setPosition(Vector2f(1250, menu4.height / 2 + 40));

	menu4.mainmenu[1].setFont(menu4.font);
	menu4.mainmenu[1].setFillColor(Color::Black);
	menu4.mainmenu[1].setString("Sound options");
	menu4.mainmenu[1].setCharacterSize(50);
	menu4.mainmenu[1].setPosition(Vector2f(1250, menu4.height / 2 + 100));

	menu4.mainmenu[2].setFont(menu4.font);
	menu4.mainmenu[2].setFillColor(Color::Black);
	menu4.mainmenu[2].setString("Back");
	menu4.mainmenu[2].setCharacterSize(50);
	menu4.mainmenu[2].setPosition(Vector2f(1250, menu4.height / 2 + 160));
	//hand.setPosition(1155, 600);
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down) {
					sound.change_option_Sound();
					menu4.MoveDown(menu4.selected, menu4.choises);
				}
				if (event.key.code == Keyboard::Up) {
					sound.change_option_Sound();
					menu4.MoveUp(menu4.selected, menu4.choises);
				}
				if (event.key.code == Keyboard::Escape && !pressed && menu4.selected != 2)
				{
					sound.change_option_Sound();
					menu4.mainmenu[menu4.selected].setFillColor(Color::Black);
					menu4.selected = 2;
					menu4.mainmenu[2].setFillColor(Color{ 255,204,0 });
					menu4.hand.setPosition(1140, 700);
					pressed = true;
				}
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
				{
					sound.select_option_Sound();
					if (menu4.selected == 0)  options_menu1(window);
					if (menu4.selected == 2) {
						pageNumber = 1000;
						pressed = true;
						return;
					}
				}
			}
		}
		if (!Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pressed = false;
		}
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		for (int i = 0; i < menu4.choises; i++)
		{
			window.draw(menu4.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu4.hand);
		window.display();
	}
}
void  Menu::instructions(RenderWindow& window)
{

	Texture instr;
	instr.loadFromFile("Assets/Textures/instructions.png");
	Sprite instructions;
	instructions.setTexture(instr);
	instructions.setScale(2.4, 1.83);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			sound.select_option_Sound();
			pageNumber = 1000;
			pressed = true;
			return;
		}
		window.clear();
		window.draw(instructions);
		window.display();
	}
}
void Menu::Pause(RenderWindow& window, Texture gametexture)
{
	Menu Pause1;
	Pause1.choises = END + 2;
	//Pause1.c = 3;
	//if (!font.loadFromFile("arial.ttf")) {}
	if (END)
		Pause1.mainmenu[0 + END].setFillColor(Color::Black);
	else  
		Pause1.mainmenu[0 + END].setFillColor(Color{ 255,204,0 });

	Pause1.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	Pause1.mainmenu[0].setFont(Pause1.font);
	Pause1.mainmenu[0].setFillColor(Color{ 255,204,0 });
	Pause1.mainmenu[0].setString("resume");
	Pause1.mainmenu[0].setCharacterSize(70);
	Pause1.mainmenu[0].setPosition(670, 200);

	Pause1.mainmenu[0+END].setFont(Pause1.font);
	Pause1.mainmenu[0+END].setString("Play Again");
	Pause1.mainmenu[0+END].setCharacterSize(70);
	Pause1.mainmenu[0+END].setPosition(670, END?300:200);

	Pause1.mainmenu[1+END].setFont(Pause1.font);
	Pause1.mainmenu[1+END].setFillColor(sf::Color::Black);
	Pause1.mainmenu[1+END].setString("Exit");
	Pause1.mainmenu[1+END].setCharacterSize(70);
	Pause1.mainmenu[1+END].setPosition(670, END?400:300);

	RectangleShape photo2;
	photo2.setSize(Vector2f(1920, 1080));
	photo2.setFillColor(Color(0, 0, 0, 100));

	Sprite game;
	game.setTexture(gametexture);

	Texture txx;
	txx.loadFromFile("Assets/Textures/Pausemenu.png");

	Sprite pausemenu;
	pausemenu.setTexture(txx);
	pausemenu.setPosition(600, 150);
	pausemenu.setScale(1.5,1.8);
	Pause1.Hand_intilization();
	Pause1.hand.setPosition(560, 200);
	Pause1.positionOfHand = 100;

	//pressed = true;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up) {
					sound.change_option_Sound();
					Pause1.MoveUp(Pause1.selected, Pause1.choises);
					//break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					sound.change_option_Sound();
					Pause1.MoveDown(Pause1.selected, Pause1.choises);
					//break;
				}
				if (event.key.code == Keyboard::Escape && !pressed && Pause1.selected != 1 + END)
				{
					sound.change_option_Sound();
					Pause1.mainmenu[Pause1.selected].setFillColor(Color::Black);
					Pause1.selected = 1 + END;
					Pause1.mainmenu[1 + END].setFillColor(Color{ 255,204,0 });
					Pause1.hand.setPosition(560, END ? 400 : 300);
					pressed = true;
				}
				if (event.key.code == sf::Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed)) {
					sound.select_option_Sound();
					if (Pause1.selected == -1 + END) {
						return;
					}
					if (Pause1.selected == 0+END) {

					}
					if (Pause1.selected == 1+END) {
						window.setView(window.getDefaultView());
						exit = 1;
						return;
					}
				}
				if (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					pressed = false;
				}
			}
		}
		window.clear();
		window.draw(game);
		window.draw(photo2);
		window.draw(pausemenu);
		for (int i = 0; i < Pause1.choises; i++) {
			window.draw(Pause1.mainmenu[i]);
		}
		window.draw(Pause1.hand);
		window.display();
	}
}

//void Menu::Menues(RenderWindow& window)
//{
//	while (window.isOpen())
//	{
//		if () {
//			Play_menu();
//		}
//		else if () {
//
//		}
//		else if{
//
//		}
//		else if () {
//
//		}
//	}
//}
