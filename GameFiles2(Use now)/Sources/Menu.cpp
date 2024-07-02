#include "Menu.h"
#include "menu_Bg_and_Face.h"
#include "Sounds.h"
#include "FileSave.h"

int P_M_Sound = 100;	//change option,effects(hurry up,.....);
int P_M_Music = 100;	//background,game;
int PLayer1 = 0;
int PLayer2 = 0;
extern bool END;
bool pressed = true;
bool esc_button = true;
extern Sounds sound;
extern FileSave File;
extern user_data user[5];
extern Vector2f window_size;
extern int GameMode;

bool waitingForKey = false;
int actionToChange;

extern Keyboard::Key moveLeftKey;
extern Keyboard::Key moveRightKey;
extern Keyboard::Key jumpKey;

extern Keyboard::Key moveLeftKey2;
extern Keyboard::Key moveRightKey2;
extern Keyboard::Key jumpKey2;

menu_Bg_and_Face menu_UI;
Event event;
void Gameplay();

void Menu::changeKeyMapping(int& action, Keyboard::Key newKey, Keyboard::Key &moveLeftKey, Keyboard::Key &moveRightKey, Keyboard::Key &jumpKey, Menu &menu9) {
	if (action == 0) {
		moveLeftKey = newKey;
	}
	else if (action == 1) {
		moveRightKey = newKey;
	}
	else if (action == 2) {
		jumpKey = newKey;
	}
	//letter.setString(keyboardKeyToString(newKey));
}

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
	//sound.LoadMusic();
	sound.music(0);
	men1.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");

	men1.choises = 7;
	men1.mainmenu[0].setString("Play Game");
	men1.mainmenu[1].setString("Instructions");
	men1.mainmenu[2].setString("Change Profile");
	men1.mainmenu[3].setString("High Score");
	men1.mainmenu[4].setString("Options");
	men1.mainmenu[5].setString("Credits");
	men1.mainmenu[6].setString("Exit");
	x = 40;
	for (int i = 0; i < men1.choises; i++)
	{
		if (!i)
			men1.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else
			men1.mainmenu[i].setFillColor(Color::Black);
		men1.mainmenu[i].setFont(men1.font);
		men1.mainmenu[i].setCharacterSize(50);
		men1.mainmenu[i].setPosition(Vector2f(1250, men1.height / 2 + x));
		x += 60;
	}
	menu_UI.back_ground(window);
	men1.Hand_intilization();
	File.EnterName();


	pressed = false;
	while (window.isOpen())
	{
		if (pageNumber == 1000)
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				File.TypeYourName();
				if (File.infile)
				{
					if (event.type == Event::KeyReleased) {
						pressed = false;
					}

					if (event.type == Event::KeyPressed && !pressed) {
						pressed = true;
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
						if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && men1.selected == 6))
						{
							esc_button = 1;
							sound.select_option_Sound();
							if (men1.selected == 6)
								pageNumber = -1;
							if (men1.selected == 0)
							{
								Play_menu(window, GameMode);
							}
							if (men1.selected == 2)
							{
								File.erase = 1;
								File.SaveName = File.playername;
								File.EnterName();
							}
							if (men1.selected == 4)
								options_menu(window);
							if (men1.selected == 1)
								instructions(window);
							if (men1.selected == 5)
								credits(window);
							if (men1.selected == 3)
							{
								File.highscore(window);
							}
						}
						if (event.key.code == Keyboard::Escape) {
							sound.change_option_Sound();
							men1.mainmenu[men1.selected].setFillColor(Color::Black);
							men1.selected = 6;
							men1.mainmenu[6].setFillColor(Color{ 255,204,0 });
							men1.hand.setPosition(1140, 890 + shift);
						}
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
		window.draw(File.enternameSP);
		window.draw(File.playerNameText);
		if (File.boolenter && display < 4) {
			window.draw(File.profile);
			display += 0.02;
		}
		else if (!File.boolenter)
			display = 0;
		window.draw(File.welcome);
		window.display();
	}
}
void Menu::levels(RenderWindow& window) {
	Menu menu7;
	menu7.Hand_intilization();
	menu7.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu7.choises = 4;
	File.search(File.playername);
	//cout << File.index << endl;
	x = 40;
	for (int i = 0; i < menu7.choises; i++)
	{
		if (!i)
			menu7.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else
			menu7.mainmenu[i].setFillColor(Color::Black);
		menu7.mainmenu[i].setFont(menu7.font);
		menu7.mainmenu[i].setCharacterSize(50);
		menu7.mainmenu[i].setPosition(Vector2f(1250, menu7.height / 2 + x));
		x += 60;
	}
	menu7.mainmenu[0].setString("Level 2");
	menu7.mainmenu[1].setString("Level 3");
	menu7.mainmenu[2].setString("Level 4");
	menu7.mainmenu[3].setString("Back");
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyReleased) {
				pressed = false;
			}
			if (event.type == Event::KeyPressed && !pressed)
			{
				pressed = true;
				if (event.key.code == Keyboard::Down) {
					sound.change_option_Sound();
					menu7.MoveDown(menu7.selected, menu7.choises);
				}
				if (event.key.code == Keyboard::Up) {
					sound.change_option_Sound();
					menu7.MoveUp(menu7.selected, menu7.choises);
				}
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && menu7.selected == 3))
				{
					sound.select_option_Sound();
					GameMode = 1;
					if (menu7.selected == 0 && user[File.index].highest_stair >= 50) {
						level = 2;
						Gameplay();
					}
					else if (menu7.selected == 1 && user[File.index].highest_stair >= 100) {
						level = 3;
						Gameplay();
					}
					else if (menu7.selected == 2 && user[File.index].highest_stair >= 150) {
						level = 4;
						Gameplay();
					}
					//cout << File.index << endl;
					if (File.index == -1)
						level = 0;

					if (menu7.selected == 3) {
						pageNumber = 500;
						pressed = 0;
						return;
					}
				}
				if (event.key.code == Keyboard::Escape && menu7.selected != 3)
				{
					sound.change_option_Sound();
					menu7.mainmenu[menu7.selected].setFillColor(Color::Black);
					menu7.selected = 3;
					menu7.mainmenu[3].setFillColor(Color{ 255,204,0 });
					menu7.hand.setPosition(1140, 760);
				}
			}
		}
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		for (int i = 0; i < menu7.choises; i++)
		{
			window.draw(menu7.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu7.hand);
		if (play_again) {
			Gameplay();
			window.clear();
		}
		window.draw(File.welcome);
		window.display();
	}

}
void  Menu::Play_menu(RenderWindow& window, int& GameMode)
{
	Menu menu2;
	menu2.Hand_intilization();
	menu2.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu2.choises = 5;
	x = 40;
	for (int i = 0; i < menu2.choises; i++)
	{
		if (!i)
			menu2.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else
			menu2.mainmenu[i].setFillColor(Color::Black);
		menu2.mainmenu[i].setFont(menu2.font);
		menu2.mainmenu[i].setCharacterSize(50);
		menu2.mainmenu[i].setPosition(Vector2f(1250, menu2.height / 2 + x));
		x += 60;
	}
	menu2.mainmenu[0].setString("Single");
	menu2.mainmenu[1].setString("Multi");
	menu2.mainmenu[2].setString("PowerUps");
	menu2.mainmenu[3].setString("Levels");
	menu2.mainmenu[4].setString("Back");

	pageNumber = 500;
	while (window.isOpen())
	{
		level = 0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyReleased) {
				pressed = false;
			}
			if (event.type == Event::KeyPressed && !pressed) {
				pressed = true;
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && menu2.selected == 4))
				{
					sound.select_option_Sound();
					if (menu2.selected == 3) {
						levels(window);
					}
					if (menu2.selected == 4) {
						pageNumber = 1000;
						return;
					}
				}
				if (event.key.code == Keyboard::Escape && menu2.selected != 4)
				{
					sound.change_option_Sound();
					menu2.mainmenu[menu2.selected].setFillColor(Color::Black);
					menu2.selected = 4;
					menu2.mainmenu[4].setFillColor(Color{ 255,204,0 });
					menu2.hand.setPosition(1140, 820);

				}
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
					if (menu2.selected < 3)       Gameplay();
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

		if (play_again) {
			Gameplay();
			window.clear();
		}
		window.draw(File.welcome);
		window.display();
	}
}
void  Menu::sound_options(RenderWindow& window) {
	Menu menu6;
	menu6.Hand_intilization();
	menu6.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu6.choises = 3;
	x = 40;
	for (int i = 0; i < menu6.choises; i++)
	{
		if (!i) menu6.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else   menu6.mainmenu[i].setFillColor(Color::Black);
		menu6.mainmenu[i].setFont(menu6.font);
		menu6.mainmenu[i].setCharacterSize(50);
		menu6.mainmenu[i].setPosition(Vector2f(1250, menu6.height / 2 + x));
		x += 60;
	}
	menu6.mainmenu[0].setString("Sound - \t\t\t\t\t +");
	menu6.mainmenu[1].setString("Music  - \t\t\t\t\t +");
	menu6.mainmenu[2].setString("Back");
	RectangleShape Sound(Vector2f(P_M_Sound * 3, 40));
	Sound.setFillColor({ 180,3,3 });
	Sound.setPosition(1400, menu6.height / 2 + 55);

	RectangleShape Music(Vector2f(P_M_Music * 3, 40));
	Music.setFillColor({ 180,3,3 });
	Music.setPosition(1400, menu6.height / 2 + 115);

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
					menu6.MoveDown(menu6.selected, menu6.choises);
				}
				if (event.key.code == Keyboard::Up) {
					sound.change_option_Sound();
					menu6.MoveUp(menu6.selected, menu6.choises);
				}
				if (event.key.code == Keyboard::Escape && !pressed && menu6.selected != 2)
				{
					sound.change_option_Sound();
					menu6.mainmenu[menu6.selected].setFillColor(Color::Black);
					menu6.selected = 2;
					menu6.mainmenu[2].setFillColor(Color{ 255,204,0 });
					menu6.hand.setPosition(1140, 700);
					pressed = true;
				}
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
				{
					sound.select_option_Sound();
					if (menu6.selected == 2) {
						pressed = true;
						return;
					}
				}
				if (menu6.selected == 0)
				{
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						if (P_M_Sound > 0)
							P_M_Sound -= 10;
						else
							P_M_Sound = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						if (P_M_Sound < 100)
							P_M_Sound += 10;
						else
							P_M_Sound = 100;
					}
					Sound.setSize(Vector2f(P_M_Sound * 3, 40));
					sound.so.setVolume(P_M_Sound);
					sound.so2.setVolume(P_M_Sound);
					sound.so4.setVolume(P_M_Sound);
					sound.so5.setVolume(P_M_Sound);
					sound.so6.setVolume(P_M_Sound);
					sound.so7.setVolume(P_M_Sound);
					sound.so8.setVolume(P_M_Sound);
					sound.so9.setVolume(P_M_Sound);
					sound.so10.setVolume(P_M_Sound);
					sound.so11.setVolume(P_M_Sound);
					sound.so12.setVolume(P_M_Sound);
					sound.so13.setVolume(P_M_Sound);
				}
				else if (menu6.selected == 1)
				{
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						if (P_M_Music > 0)
							P_M_Music -= 10;
						else
							P_M_Music = 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						if (P_M_Music < 100)
							P_M_Music += 10;
						else
							P_M_Music = 100;
					}
				}
				Music.setSize(Vector2f(P_M_Music * 3, 40));
				sound.bgmusic.setVolume(P_M_Music);
			}
		}
		if (!Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pressed = false;
		}
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		window.draw(Sound);
		window.draw(Music);
		for (int i = 0; i < menu6.choises; i++)
		{
			window.draw(menu6.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu6.hand);
		window.draw(File.welcome);
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
	x = 40;
	for (int i = 0; i < menu5.choises; i++)
	{
		if (!i) menu5.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else   menu5.mainmenu[i].setFillColor(Color::Black);
		menu5.mainmenu[i].setFont(menu5.font);
		menu5.mainmenu[i].setPosition(Vector2f(1250, menu5.height / 2 + x));
		menu5.mainmenu[i].setCharacterSize(50);
		x += 110;
	}
	menu5.mainmenu[0].setString("Player1 \n Charchters <>");
	menu5.mainmenu[1].setString("Player2 \n Charchters <>");
	menu5.mainmenu[2].setString("Back");
	const int players = 5;

	Texture pl[players];
	pl[0].loadFromFile("Assets/Textures/icytower1.png");
	pl[1].loadFromFile("Assets/Textures/icytower2.png");
	pl[2].loadFromFile("Assets/Textures/icy_demon1.png");
	pl[3].loadFromFile("Assets/Textures/SpiderMan.png");
	pl[4].loadFromFile("Assets/Textures/Hurry_Potter.png");

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
			if (Keyboard::isKeyPressed(Keyboard::Escape) && menu5.selected != 2 && !pressed)
			{
				sound.change_option_Sound();
				menu5.mainmenu[menu5.selected].setFillColor(Color::Black);
				menu5.selected = 2;
				menu5.mainmenu[2].setFillColor(Color{ 255,204,0 });
				menu5.hand.setPosition(1140, 800);
				pressed = true;
			}
			if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
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
						PLayer1 = players - 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if (PLayer1 < players - 1)
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
						PLayer2 = players - 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if (PLayer2 < players - 1)
						PLayer2++;
					else
						PLayer2 = 0;
				}
			}
		}
		if (PLayer1 == 0)
		{
			player1.setTexture(pl[0]);
		}
		else if (PLayer1 == 1)
		{
			player1.setTexture(pl[1]);
		}

		else if (PLayer1 == 2)
		{
			player1.setTexture(pl[2]);
		}
		else if (PLayer1 == 3)
		{
			player1.setTexture(pl[3]);
		}
		else if (PLayer1 == 4)
		{
			player1.setTexture(pl[4]);
		}

		if (PLayer2 == 1)
		{
			player2.setTexture(pl[0]);
		}
		else if (PLayer2 == 0)
		{
			player2.setTexture(pl[1]);
		}
		else if (PLayer2 == 2)
		{
			player2.setTexture(pl[2]);
		}
		else if (PLayer2 == 3)
		{
			player2.setTexture(pl[3]);
		}
		else if (PLayer2 == 4)
		{
			player2.setTexture(pl[4]);
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
		window.draw(File.welcome);
		window.display();
	}
}
void  Menu::player_controls(RenderWindow& window, Keyboard::Key &moveLeftKey, Keyboard::Key &moveRightKey, Keyboard::Key &jumpKey)
{
	Menu menu9;
	menu9.Hand_intilization();
	menu9.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu9.choises = 4;
	x = 40;
	for (int i = 0; i < menu9.choises; i++)
	{
		if (!i) menu9.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else   menu9.mainmenu[i].setFillColor(Color::Black);
		menu9.mainmenu[i].setFont(menu9.font);
		menu9.mainmenu[i].setCharacterSize(50);
		menu9.mainmenu[i].setPosition(Vector2f(1250, menu9.height / 2 + x));
		x += 60;
	}
	menu9.mainmenu[3].setString("Back");
	letter.setFillColor(Color::Black);
	letter.setFont(menu9.font);
	letter.setCharacterSize(50);
	letter.setPosition(Vector2f(840, 580));
	bool draw = 0;

	RectangleShape photo2;
	photo2.setSize(Vector2f(1920, 1080));
	photo2.setFillColor(Color(0, 0, 0, 100));

	Texture direction[3];
	direction[0].loadFromFile("Assets/Textures/left.png");
	direction[1].loadFromFile("Assets/Textures/right.png");
	direction[2].loadFromFile("Assets/Textures/jump.png");

	Sprite LRJ;
	LRJ.setScale(1.8, 1.8);
	LRJ.setPosition(450, 450);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyReleased){
				pressed = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down && !waitingForKey) {
					sound.change_option_Sound();
					menu9.MoveDown(menu9.selected, menu9.choises);
				}
				if (event.key.code == Keyboard::Up && !waitingForKey) {
					sound.change_option_Sound();
					menu9.MoveUp(menu9.selected, menu9.choises);
				}
				/*========================================================================*/
				if (event.key.code == Keyboard::Escape && !pressed && menu9.selected != 3 &&!waitingForKey){
					sound.change_option_Sound();
					menu9.mainmenu[menu9.selected].setFillColor(Color::Black);
					menu9.selected = 3;
					menu9.mainmenu[3].setFillColor(Color{ 255,204,0 });
					menu9.hand.setPosition(1140, 760);
					draw = 0;
					pressed = true;
				}
				/*========================================================================*/
				if (event.type == Event::KeyPressed)
				{
					if (event.type == Event::KeyReleased) {
						pressed = 0;
					}
					if (event.key.code == Keyboard::Enter && !waitingForKey && !pressed)
					{
						//letter.setString("----");
						pressed = 1;
						sound.select_option_Sound();
						if (menu9.selected != 3) {
							LRJ.setTexture(direction[menu9.selected]);
							waitingForKey = 1;
							draw = 1;
						}
						else {
							return;
						}
					}
					else if (event.key.code == Keyboard::Enter && !pressed) {
						draw = 0;
						waitingForKey = 0;
					}
					//----------------------------------------------
					if (event.key.code != Keyboard::Enter && waitingForKey && menu9.selected == 0) {
						actionToChange = menu9.selected;
						menu9.changeKeyMapping(actionToChange, event.key.code, moveLeftKey, moveRightKey, jumpKey, menu9);
					}
					if (event.key.code != Keyboard::Enter && waitingForKey && menu9.selected == 1)
					{
						actionToChange = menu9.selected;
						menu9.changeKeyMapping(actionToChange, event.key.code, moveLeftKey, moveRightKey, jumpKey, menu9);
					}
					if (event.key.code != Keyboard::Enter && waitingForKey && menu9.selected == 2)
					{
						actionToChange = menu9.selected;
						menu9.changeKeyMapping(actionToChange, event.key.code, moveLeftKey, moveRightKey, jumpKey, menu9);
					}
					letter.setString(keyboardKeyToString(event.key.code));
					//---------------------------------------------
				}
			}
		}
		menu9.mainmenu[0].setString("Left : " + keyboardKeyToString(moveLeftKey));
		menu9.mainmenu[1].setString("Right : " + keyboardKeyToString(moveRightKey));
		menu9.mainmenu[2].setString("Jump : " + keyboardKeyToString(jumpKey));
		menu_UI.FaceMotion(window);
		window.clear();
		window.draw(menu_UI.bg);
		for (int i = 0; i < menu9.choises; i++)
		{
			window.draw(menu9.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu9.hand);
		window.draw(File.welcome);
		//cout << draw << endl;
		if (draw == 1)
		{
			window.draw(photo2);
			window.draw(LRJ);
			window.draw(letter);
		}
		window.display();
	}
}
void  Menu::control_menu(RenderWindow& window)
{
	Menu menu8;
	menu8.Hand_intilization();
	menu8.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu8.choises = 3;
	x = 40;
	for (int i = 0; i < menu8.choises; i++)
	{
		if (!i) menu8.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else   menu8.mainmenu[i].setFillColor(Color::Black);
		menu8.mainmenu[i].setFont(menu8.font);
		menu8.mainmenu[i].setCharacterSize(50);
		menu8.mainmenu[i].setPosition(Vector2f(1250, menu8.height / 2 + x));
		x += 60;
	}
	menu8.mainmenu[0].setString("Player 1 ");
	menu8.mainmenu[1].setString("Player 2");
	menu8.mainmenu[2].setString("Back");

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
					menu8.MoveDown(menu8.selected, menu8.choises);
				}
				if (event.key.code == Keyboard::Up) {
					sound.change_option_Sound();
					menu8.MoveUp(menu8.selected, menu8.choises);
				}
				if (event.key.code == Keyboard::Escape && !pressed && menu8.selected != 2)
				{
					sound.change_option_Sound();
					menu8.mainmenu[menu8.selected].setFillColor(Color::Black);
					menu8.selected = 2;
					menu8.mainmenu[2].setFillColor(Color{ 255,204,0 });
					menu8.hand.setPosition(1140, 700);
					pressed = true;
				}
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
				{
					sound.select_option_Sound();
					if (menu8.selected == 0)  player_controls(window, moveLeftKey, moveRightKey, jumpKey);
					if (menu8.selected == 1)  player_controls(window, moveLeftKey2, moveRightKey2, jumpKey2);
					if (menu8.selected == 2) {
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
		for (int i = 0; i < menu8.choises; i++)
		{
			window.draw(menu8.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu8.hand);
		window.draw(File.welcome);
		window.display();
	}
}
void  Menu::options_menu(RenderWindow& window)
{
	Menu menu4;
	menu4.Hand_intilization();
	menu4.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	menu4.choises = 4;
	x = 40;
	for (int i = 0; i < menu4.choises; i++)
	{
		if (!i) menu4.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else   menu4.mainmenu[i].setFillColor(Color::Black);
		menu4.mainmenu[i].setFont(menu4.font);
		menu4.mainmenu[i].setCharacterSize(50);
		menu4.mainmenu[i].setPosition(Vector2f(1250, menu4.height / 2 + x));
		x += 60;
	}
	menu4.mainmenu[0].setString("GFX Options");
	menu4.mainmenu[1].setString("Sound options");
	menu4.mainmenu[2].setString("Controls");
	menu4.mainmenu[3].setString("Back");

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
				if (event.key.code == Keyboard::Escape && !pressed && menu4.selected != 3)
				{
					sound.change_option_Sound();
					menu4.mainmenu[menu4.selected].setFillColor(Color::Black);
					menu4.selected = 3;
					menu4.mainmenu[3].setFillColor(Color{ 255,204,0 });
					menu4.hand.setPosition(1140, 760);
					pressed = true;
				}
				if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
				{
					sound.select_option_Sound();
					if (menu4.selected == 0)  options_menu1(window);
					if (menu4.selected == 1)  sound_options(window);
					if (menu4.selected == 2)   control_menu(window);
					if (menu4.selected == 3) {
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
		window.draw(File.welcome);
		window.display();
	}
}
void  Menu::credits(RenderWindow& window)
{
	Texture cre;
	cre.loadFromFile("Assets/Textures/credits7.png");
	Sprite credits;
	credits.setTexture(cre);
	//credits.setPosition(200, 0);
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
		window.draw(credits);
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

//=================================================<<PAUSE MENU>>=========================================================//
void Menu::Pause(RenderWindow& window, Texture gametexture)
{
	Menu Pause1, option;
	Pause1.choises = END + 3;
	option.choises = 3;
	option.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	Pause1.font.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");
	x = 200;
	for (int i = 0; i < Pause1.choises; i++)
	{
		if (!i) Pause1.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else  Pause1.mainmenu[i].setFillColor(Color::Black);
		Pause1.mainmenu[i].setFont(Pause1.font);
		Pause1.mainmenu[i].setCharacterSize(70);
		Pause1.mainmenu[i].setPosition(670, x);
		x += 100;
	}
	x = 200;
	for (int i = 0; i < option.choises; i++)
	{
		if (!i) option.mainmenu[i].setFillColor(Color{ 255,204,0 });
		else  option.mainmenu[i].setFillColor(Color::Black);
		option.mainmenu[i].setFont(option.font);
		option.mainmenu[i].setCharacterSize(70);
		option.mainmenu[i].setPosition(670, x);
		x += 100;
	}
	Pause1.mainmenu[0].setString("resume");
	Pause1.mainmenu[0 + END].setString("Play Again");
	Pause1.mainmenu[1 + END].setString("Sound Option");
	Pause1.mainmenu[2 + END].setString("Exit");

	option.mainmenu[0].setString("Sound - \t\t\t   +");
	option.mainmenu[1].setString("Music  - \t\t\t   +");
	option.mainmenu[2].setString("Back");


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
	pausemenu.setScale(1.7, 2.2);
	Pause1.Hand_intilization();
	Pause1.hand.setPosition(560, 200);
	Pause1.positionOfHand = 100;


	option.Hand_intilization();
	option.hand.setPosition(560, 200);
	option.positionOfHand = 100;

	RectangleShape Sound(Vector2f(P_M_Sound * 3, 40));
	Sound.setFillColor({ 180,3,3 });
	Sound.setPosition(885, 220);

	RectangleShape Music(Vector2f(P_M_Music * 3, 40));
	Music.setFillColor({ 180,3,3 });
	Music.setPosition(885, 320);

	bool op = false;
	//pressed = true;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (!op) {
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
					if (event.key.code == Keyboard::Escape && !pressed && Pause1.selected != 2 + END)
					{
						sound.change_option_Sound();
						Pause1.mainmenu[Pause1.selected].setFillColor(Color::Black);
						Pause1.selected = 2 + END;
						Pause1.mainmenu[2 + END].setFillColor(Color{ 255,204,0 });
						Pause1.hand.setPosition(560, END ? 500 : 400);
						pressed = true;
					}
					if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed)) {
						sound.select_option_Sound();
						if (Pause1.selected == -1 + END) {
							return;
						}
						if (Pause1.selected == 0 + END) {
							play_again = 1;
							exit = 1;
							return;
						}
						if (Pause1.selected == 1 + END) {
							op = true;
						}
						if (Pause1.selected == 2 + END) {
							window.setView(window.getDefaultView());
							play_again = 0;
							exit = 1;
							return;
						}
					}

					if (!Keyboard::isKeyPressed(Keyboard::Escape))
					{
						pressed = false;
					}
				}
				else if (op)
				{
					if (event.key.code == sf::Keyboard::Up) {
						sound.change_option_Sound();
						option.MoveUp(option.selected, option.choises);
						//break;
					}
					if (event.key.code == sf::Keyboard::Down) {
						sound.change_option_Sound();
						option.MoveDown(option.selected, option.choises);
						//break;
					}
					if (event.key.code == Keyboard::Escape && !pressed && option.selected != 2)
					{
						sound.change_option_Sound();
						option.mainmenu[option.selected].setFillColor(Color::Black);
						option.selected = 2;
						option.mainmenu[2].setFillColor(Color{ 255,204,0 });
						option.hand.setPosition(560, 400);
						pressed = true;
					}
					if (event.key.code == Keyboard::Enter || (event.key.code == Keyboard::Escape && !pressed))
					{
						sound.select_option_Sound();
						if (option.selected == 2) {
							pressed = true;
							op = false;
						}
					}
					if (option.selected == 0)
					{
						if (event.key.code == sf::Keyboard::Left)
						{
							if (P_M_Sound > 0)
								P_M_Sound -= 10;
							else
								P_M_Sound = 0;
						}
						if (event.key.code == sf::Keyboard::Right)
						{
							if (P_M_Sound < 100)
								P_M_Sound += 10;
							else
								P_M_Sound = 100;
						}
						Sound.setSize(Vector2f(P_M_Sound * 3, 40));
						sound.so.setVolume(P_M_Sound);
						sound.so2.setVolume(P_M_Sound);
						sound.so4.setVolume(P_M_Sound);
						sound.so5.setVolume(P_M_Sound);
						sound.so6.setVolume(P_M_Sound);
						sound.so7.setVolume(P_M_Sound);
						sound.so8.setVolume(P_M_Sound);
						sound.so9.setVolume(P_M_Sound);
						sound.so10.setVolume(P_M_Sound);
						sound.so11.setVolume(P_M_Sound);
						sound.so12.setVolume(P_M_Sound);
						sound.so13.setVolume(P_M_Sound);
					}
					else if (option.selected == 1)
					{
						if (event.key.code == Keyboard::Left)
						{
							if (P_M_Music > 0)
								P_M_Music -= 10;
							else
								P_M_Music = 0;
						}
						if (event.key.code == Keyboard::Right)
						{
							if (P_M_Music < 100)
								P_M_Music += 10;
							else
								P_M_Music = 100;
						}
					}
					Music.setSize(Vector2f(P_M_Music * 3, 40));
					sound.bgmusic.setVolume(P_M_Music);


					if (!Keyboard::isKeyPressed(Keyboard::Escape))
					{
						pressed = false;
					}
				}

			}
		}
		window.clear();
		window.draw(game);
		window.draw(photo2);
		window.draw(pausemenu);
		if (!op) {
			for (int i = 0; i < Pause1.choises; i++) {
				window.draw(Pause1.mainmenu[i]);
			}
			window.draw(Pause1.hand);
		}
		else
		{
			for (int i = 0; i < option.choises; i++) {
				window.draw(option.mainmenu[i]);
			}
			window.draw(option.hand);
			window.draw(Sound);
			window.draw(Music);
		}
		window.display();
	}
}
