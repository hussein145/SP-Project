#include "Menu.h"
#include "menu_Bg_and_Face.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

menu_Bg_and_Face menu_UI;
void Gameplay();
void Menu:: Hand_intilization()
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
		hand.setPosition(1140, hand.getPosition().y + positionOfHand);
		selected++;
		if (selected == choises)
		{
			selected = 0;
			hand.setPosition(1140, 580);
		}
		mainmenu[selected].setFillColor(Color{ 255,204,0 });
	}
}
void Menu::MoveUp(int& selected, int choises)
{
	if (selected > -1)
	{

		mainmenu[selected].setFillColor(Color::Black);
		hand.setPosition(1140, hand.getPosition().y - positionOfHand);
		selected--;
		if (selected == -1)
		{
			selected = choises - 1;
			hand.setPosition(1140, hand.getPosition().y + (positionOfHand * choises));
		}
		mainmenu[selected].setFillColor(Color{ 255,204,0 });

	}
}
void  Menu::menu1(RenderWindow &window, int &GameMode)
{
	Menu men1;
	men1.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");

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
				if (event.key.code == Keyboard::Escape && !pressed && men1.selected != 5 + resusme)
				{
					men1.mainmenu[men1.selected].setFillColor(Color::Black);
					men1.selected = 5 + resusme;
					men1.mainmenu[5 + resusme].setFillColor(Color{ 255,204,0 });
					men1.hand.setPosition(1140, 890 + shift);
					pressed = true;
				}

				if (event.key.code == Keyboard::Escape && !pressed && men1.selected == 5 + resusme)
				{
					window.close();
				}
				if (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					pressed = false;
				}
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Down)
						men1.MoveDown(men1.selected, men1.choises);
					if (event.key.code == Keyboard::Up)
						men1.MoveUp(men1.selected, men1.choises);
					if (event.key.code == Keyboard::Enter)
					{

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
		window.display();
	}
}
void  Menu::Play_menu(RenderWindow& window, int &GameMode)
{
	Menu menu2;
	menu2.Hand_intilization();
	menu2.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	menu2.choises = 3;

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

	pageNumber = 500;
	while (window.isOpen())
	{
		Event event;

		if (Keyboard::isKeyPressed(Keyboard::Escape) && !pressed)
		{
			pageNumber = 1000;
			pressed = true;
			break;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pressed = false;
		}
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down)
					menu2.MoveDown(menu2.selected, menu2.choises);
				if (event.key.code == Keyboard::Up)
					menu2.MoveUp(menu2.selected, menu2.choises);
				//cout << Enter_Game << endl;
				if (event.key.code == Keyboard::Enter)
				{
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
	Menu menu4;
	menu4.Hand_intilization();
	int charcter = 0;
	Font font;
	font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	Text t1;

	t1.setFont(font);
	t1.setString("change charcter <> ");
	t1.setCharacterSize(70);
	t1.setPosition(10, 10);
	t1.setFillColor(Color{ 255,204,0 });
	t1.setPosition(650, 460);


	Texture Bl;
	Bl.loadFromFile("Assets/Textures/Stair.png");

	Sprite Block;
	Block.setTexture(Bl);

	Block.setScale(.8, 1);
	Block.setPosition(1245, 550);

	Texture pl1;
	pl1.loadFromFile("Assets/Textures/Dude_Monster.png");

	Texture pl2;
	pl2.loadFromFile("Assets/Textures/Owlet_Monster.png");
	Texture pl3;
	pl3.loadFromFile("Assets/Textures/Pink_Monster.png");

	Sprite player;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (charcter > 0)
					charcter--;
				else
					charcter = 2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (charcter < 2)
					charcter++;
				else
					charcter = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pageNumber = 1000;
				return;
			}

		}
		menu_UI.FaceMotion(window);
		if (charcter == 0)
		{
			player.setTexture(pl1);
			player.setScale(3, 3);
			player.setPosition(1250, 440);
		}
		else if (charcter == 1)
		{
			player.setTexture(pl2);
			player.setScale(3, 3);
			player.setPosition(1250, 440);
		}
		else if (charcter == 2)
		{
			player.setTexture(pl3);
			player.setScale(3, 3);
			player.setPosition(1250, 440);
		}
		window.clear();
		window.draw(menu_UI.bg);
		window.draw(menu_UI.face);
		window.draw(t1);
		window.draw(Block);
		window.draw(player);
		window.display();
	}
}
void  Menu::options_menu(RenderWindow& window)
{
	Menu menu4;
	menu4.Hand_intilization();
	menu4.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
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
				if (event.key.code == Keyboard::Down)
					menu4.MoveDown(menu4.selected, menu4.choises);
				if (event.key.code == Keyboard::Up)
					menu4.MoveUp(menu4.selected, menu4.choises);
				if (event.key.code == Keyboard::Escape && !pressed && menu4.selected != 2)
				{
					menu4.mainmenu[menu4.selected].setFillColor(Color::Black);
					menu4.selected = 2;
					menu4.mainmenu[2].setFillColor(Color{ 255,204,0 });
					menu4.hand.setPosition(1140, 700);
					pressed = true;
				}
				if (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					pressed = false;
				}
				if (event.key.code == Keyboard::Enter)
				{
					if (menu4.selected == 0)  options_menu1(window);
					if (menu4.selected == 2) {
						pageNumber = 1000;
						return;
					}
				}
			}
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
			pageNumber = 1000;
			return;
		}
		window.clear();
		window.draw(instructions);
		window.display();
	}
}
void Menu::Pause(RenderWindow& window)
{
	Menu Pause1;
	Pause1.choises = 3;
	//Pause1.c = 3;
	//if (!font.loadFromFile("arial.ttf")) {}
	Pause1.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	Pause1.mainmenu[0].setFont(Pause1.font);
	Pause1.mainmenu[0].setFillColor(Color{ 255,204,0 });
	Pause1.mainmenu[0].setString("continue");
	Pause1.mainmenu[0].setCharacterSize(90);
	Pause1.mainmenu[0].setPosition(800, 100);

	Pause1.mainmenu[1].setFont(Pause1.font);
	Pause1.mainmenu[1].setFillColor(sf::Color::Black);
	Pause1.mainmenu[1].setString("resume");
	Pause1.mainmenu[1].setCharacterSize(90);
	Pause1.mainmenu[1].setPosition(800, 300);

	Pause1.mainmenu[2].setFont(Pause1.font);
	Pause1.mainmenu[2].setFillColor(sf::Color::Black);
	Pause1.mainmenu[2].setString("exit");
	Pause1.mainmenu[2].setCharacterSize(90);
	Pause1.mainmenu[2].setPosition(800, 500);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up) {
					Pause1.MoveUp(Pause1.selected, 3);
					//break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					Pause1.MoveDown(Pause1.selected, 3);
					//break;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					if (Pause1.selected == 0) {
						return;
					}
					if (Pause1.selected == 1) {

					}
					if (Pause1.selected == 2) {
						window.setView(window.getDefaultView());
						exit = 1;
						return;
					}
				}
			}
			//window.clear();
			for (int i = 0; i < 3; i++) {
				window.draw(Pause1.mainmenu[i]);
			}
			window.display();
		}
		if (exit)
			break;
		//----------------------------------------//
		////pageNumber = 500;
		//menu.pressed = true;
		//menu.pageNumber = 500;
		//reset();
		//////////////////////////////////////////////////////////////
		//////////////////
		//return;

		//mainmenuselected = 0;
	}
}
