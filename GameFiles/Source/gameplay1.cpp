#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Sounds.h"
#include "Players.h"
#include "PowerUps.h"
#define N 500
using namespace sf;
using namespace std;

//int select = 0;
//PauseMenu pausemenu;
//Menu Pause1;
extern PowerUps* dropBag;
Menu menu;
Walls_And_Background background;
STAIRS Stairs;
Sounds sound;
Players player1; Players player2;
PowerUps Power;

RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Close | Style::Fullscreen);
int GameMode;
Clock clockk, clockk2;
float dt, dt2;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
void Intilize_Numbers()
{
	/*if (GameMode == 2) stairsNum = 200;
	else  stairsNum = 100;*/
}
//-------------------------------------------<<Main menu>>---------------------------------------------//
bool END = 1;
//---------------------------------------------<<powers>>---------------------------------------------------//
//struct PowerUps
//{
//	Sprite dropShape;		   // random powerup
//	//RectangleShape blockShape; // random block
//	int type;				   // drop type
//	int PowerUP_veolcity;
//}Power;
//Texture DropsTex[4];
//
//Sprite Drops[4]; // 0 walls inwards(heart)
//PowerUps* dropBag = new PowerUps[100];//stairsNum

//void generateDrop(Vector2f stair_position, bool check);
//void setDrops();
int strCnt = 0;

struct Gameclock
{
	Texture clo;
	Sprite cl;
	Texture clo2;
	Sprite cl2;
	float l = 0;
	Texture herry;
	Sprite herry2;
	bool f = 0;
}gameclock;
void setclock()
{
	gameclock.herry.loadFromFile("Assets\\Textures\\Hurry_Up.png");
	gameclock.herry2.setTexture(gameclock.herry);
	gameclock.herry2.setScale(0, 0);

	gameclock.clo.loadFromFile("Assets/Textures/clock2.png");
	gameclock.cl.setTexture(gameclock.clo);

	gameclock.clo2.loadFromFile("Assets/Textures/clock 1.png");
	gameclock.cl2.setTexture(gameclock.clo2);
	gameclock.cl2.setOrigin(9.5, 30);
	gameclock.cl2.setRotation(int(0));
	if (GameMode == 2) {
		gameclock.cl.setScale(1, 1);
		gameclock.cl2.setScale(1, 1);
		gameclock.cl.setPosition(0, 118);
		gameclock.cl2.setPosition(40, 180);
	}
	else {
		gameclock.cl.setScale(2, 2);
		gameclock.cl2.setScale(1.7, 1.7);
		gameclock.cl.setPosition(230, 118);
		gameclock.cl2.setPosition(315, 235);
	}
}
void update_clock()
{
	gameclock.l += 0.04f;
	gameclock.cl2.setRotation(int(gameclock.l) );

	gameclock.herry2.move(0, -550*dt);
	int end = int(gameclock.l) ;
	if (end % 360 != 0) {

		gameclock.f = true;

	}
	if (end % 360 == 0 && gameclock.f == true) {
		gameclock.herry2.setScale(2.5, 2.5);
		gameclock.herry2.setPosition(650, player1_View.getCenter().y + 540);

	}
}
struct MAP
{
	float Walls_velocity_y, Backgrond_Velocity_y, Stairs_velocity_y, view_velocity;
	//float Walls_velocity_x, Stairs_velocity_x;
	bool move = 0;
	int m = 1;
	void intilization()
	{
		setclock();
		background.intiliztion(GameMode, player1_View, player2_View);
		Stairs.intiliztion1(GameMode);
	}
	void update()
	{
		Stairs.updateStairs(GameMode, player1_View, player2_View);
		background.updateBackground_And_Walls(GameMode, player1_View, player2_View);
	}
	void Map_Motion()
	{
		if (player1.character.getPosition().y < 100 || player2.character.getPosition().y < 100)
			move = 1;
		if (move)
		{
			update_clock();

			for (int i = 0; i < 200; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity_y * dt);
				background.wallsRight[i].move(0, Walls_velocity_y * dt);
				background.wallsLeft[i].move(0, Walls_velocity_y * dt);
			}
			for (int i = 0; i <= Stairs.stairsNum; i++)
			{
				Stairs.stairs[i].move(0, Stairs_velocity_y * dt);
			}
			player2_View.move(0, -view_velocity * dt);
			player1_View.move(0, -view_velocity * dt);
		}
	}
};
void Set_ObjectsOnStairs()
{
	for (int i = 0; i < Stairs.stairsNum; i++)
	{
		Stairs.Strs10[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
		Stairs.strTxt[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
		dropBag[i].dropShape.setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y - 30);
	}
}
struct CameraView
{
	void view_insilization()
	{
		player1_View.setCenter(Vector2f(960, 540));
		if (GameMode == 2)
		{
			player2_View.setCenter(Vector2f(960, 540));
			player1_View.setViewport(FloatRect(0.f, 0.f, 0.49f, 1.f));
			player2_View.setViewport(FloatRect(0.5f, 0.f, 0.5f, 1.f));
		}
		else
		{
			player1_View.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
			player2_View.setViewport(FloatRect(0.f, 0.f, 0.f, 0.f));
		}
	}
	void SetView()
	{
		if (player1.character.getPosition().y < player1_View.getCenter().y - 340)
		{
			player1_View.setCenter(Vector2f(960, player1.character.getPosition().y + 340));
		}
		if (GameMode == 2 && player2.character.getPosition().y < player2_View.getCenter().y - 340)
		{
			player2_View.setCenter(Vector2f(960, player2.character.getPosition().y + 340));
		}
	}
};
//--------------------------------------------------------------------------------------------------
void reset()
{
	Stairs.StairPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.currstair = Stairs.updatestair = Stairs.Number_Of_Stair = 0;
	gameclock.l = 0;
	player1.Score = player1.curr_colission = 0;
	player2.Score = player2.curr_colission = 0;

	background.Curr_Background = background.Curr_walls = background.update_Background = background.update_wall_index = background.Difference_Between_bg = 0;
	END = background.player2_Out_of_Background = background.player2_Out_of_Walls = 1;
	delete[] dropBag;
	dropBag = nullptr;
	RectangleShape clear10;
	clear10.setSize(Vector2f(0, 0));
	fill(Stairs.Strs10, Stairs.Strs10 + strCnt, clear10);
	fill(begin(Stairs.stairs), end(Stairs.stairs), clear10);
	for (int i = 0; i < 200; i++) {
		Stairs.strTxt[i].setString("");
	}
	player1.droptype = -1;
	Power.skip = 0;
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
void DRAW(RenderWindow& window)
{
	window.setView(player2_View);
	for (int i = 0; i < 100; i++)
	{
		window.draw(background.bg[i]);
	}
	for (int i = 0; i < Stairs.stairsNum; i++)
	{
		window.draw(Stairs.stairs[i]);
		window.draw(Stairs.Strs10[i]);
		window.draw(Stairs.strTxt[i]);
		if (GameMode == 3)
		{
			window.draw(dropBag[i].dropShape);
		}
	}

	for (int i = 0; i < background.bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
	window.setView(player1_View);
	for (int i = 0; i < 100; i++)
	{
		window.draw(background.bg[i]);
	}
	window.draw(gameclock.herry2);
	for (int i = 0; i < Stairs.stairsNum; i++)
	{
		window.draw(Stairs.stairs[i]);
		window.draw(Stairs.Strs10[i]);
		window.draw(Stairs.strTxt[i]);
		if (GameMode == 3)
		{
			window.draw(dropBag[i].dropShape);
		}
	}

	for (int i = 0; i < background.bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
}

void collisions(Players &player)
{
	player.check_on_ground = false;
	if (player.velocity_y >= 0) {
		for (int i = 0; i < Stairs.stairsNum; i++)
		{
			if (player.character.getGlobalBounds().intersects(Stairs.stairs[i].getGlobalBounds()))
			{
				if (player.character.getPosition().y + 60 <= Stairs.stairs[i].getPosition().y)
				{
					player.character.setPosition(player.character.getPosition().x, Stairs.stairs[i].getPosition().y - 60);
					player.check_on_ground = true;

					if (player.curr_colission > i) {
						if ((player.curr_colission - i) <= 9) { // Fall from stair
							player.Score -= player.curr_colission - i;
						}
						else { // Jump and loop repeat itself
							player.Score += (Stairs.stairsNum - player.curr_colission) + i;
						}
					}
					else { // i > curr_colission (Normal Condition)
						player.Score += (i - player.curr_colission);
					}
					player.curr_colission = i;
					break;
				}
			}
		}
	}
}
void Gameplay()
{
	SoundBuffer buff;
	buff.loadFromFile("Assets//Sounds//jump.ogg");

	sound.music(1);
	Texture GameTexture;
	/*GameTexture.create(50, 50);*/

	//window.setFramerateLimit(60);
	// powerups
	dropBag = new PowerUps[Stairs.stairsNum];
	Power.setDrops();

	//player
	Texture tex1, tex2;
	tex1.loadFromFile("Assets/Textures/icytower1.png");
	tex2.loadFromFile("Assets/Textures/icytower2.png");
	player1.inti(tex1);
	player2.inti(tex2);
	//music(k);
	//Map
	MAP Map;
	CameraView view;

	//map insilization
	Map.intilization();

	//view insilization
	view.view_insilization();
	Clock TimeOfMove;
	//Time TimeOfMove;
	bool StartMoving = 0;
	bool StartReturning = 0;
	/*===========================<<Score>>=================================*/
	
	/*Font score_Tex;
	score_Tex.loadFromFile("Assets//Fonts//BrownieStencil-8O8MJ.ttf");
	Text score1, score2;*/
	/*score1.setFont(score_Tex);*/
	//score2.setFont(score_Tex);
	/*score.setCharacterSize(50);
	score.setPosition(240, 1000);*/
	clockk.restart();
	while (window.isOpen())
	{
		//cout << player1_View.getCenter().y << endl;
		dt = clockk.restart().asSeconds();
		//dt2 = clockk2.restart().asSeconds();
		/*if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			cout << pos.x << " " << pos.y << endl;
		}*/

		Event Play;
		while (window.pollEvent(Play))
		{
			if (Play.type == Event::Closed)
				window.close();
			if (Play.key.code == Keyboard::Escape)  //&& !menu.pressed
			{
				//pausedtime += TimeOfMove.getElapsedTime();
				//TimeOfMove.restart();
				Map.Backgrond_Velocity_y = Map.Walls_velocity_y = Map.Stairs_velocity_y = Map.view_velocity = Power.PowerUP_veolcity = 0;
				GameTexture.create(1920, 1080);
				GameTexture.update(window);
				menu.Pause(window, GameTexture);
				//TimeOfMove.restart();
				if (menu.exit)
				{
					menu.exit = 0;
					sound.music(0);
					//music(k);
					reset();
					return;
				}
			}
		}
		collisions(player1);
		collisions(player2);
		player1.score.setString("Score: " + to_string(player1.Score * 10));
		player2.score.setString("Score: " + to_string(player2.Score * 10));
		Set_ObjectsOnStairs();

		if (GameMode == 3)
		{
			Power.dropcollision();
			//clock
			if (!StartMoving)
			{
				TimeOfMove.restart();
			}
			Power.checkdrop(TimeOfMove, StartMoving, StartReturning);
			Power.resetPowerups();
		}
		Map.update();
		view.SetView();

		//map Motion
		Map.Map_Motion();
		Map.Backgrond_Velocity_y = 30.f;
		Map.Walls_velocity_y = 150.f;
		Map.Stairs_velocity_y = 70.0f;
		Map.view_velocity = 100;

		//motion of players
		player1.velocity_x = 0;
		player2.velocity_x = 0;

		//freeze game
		if (player1.character.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && player2.character.getPosition().y > player2_View.getCenter().y + 540))
		{
			Map.Backgrond_Velocity_y = Map.Walls_velocity_y = Map.Stairs_velocity_y = Map.view_velocity = Power.PowerUP_veolcity = 0;
			END = 0;
		}
		//cout << dt << endl;
		player1.Players_Motion(buff,Keyboard::A, Keyboard::D, Keyboard::Space);
		player2.Players_Motion(buff, Keyboard::Left, Keyboard::Right, Keyboard::Enter);
		player1.update();
		player2.update();

		window.clear();
		window.setView(player1_View);
		DRAW(window);
		if (GameMode == 2) {
			window.draw(player2.character);
		}
		window.draw(player1.character);

		window.setView(window.getDefaultView());
		//set position of clock then draw it
		/////////
		if (GameMode == 2) {
			gameclock.cl.setScale(1, 1);
			gameclock.cl2.setScale(1, 1);
			gameclock.cl.setPosition(0, 118);
			gameclock.cl2.setPosition(40, 180);
		}
		window.draw(gameclock.cl);
		window.draw(gameclock.cl2);
		window.draw(player1.score);

		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);
			//DRAW(window);
			window.draw(player1.character);
			window.draw(player2.character);

			window.setView(window.getDefaultView());
			//set position of clock then draw it
			/////////
			gameclock.cl.setPosition(950, 118);
			gameclock.cl2.setPosition(990, 180);
			window.draw(gameclock.cl);
			window.draw(gameclock.cl2);
			player2.score.setPosition(980, 990);
			window.draw(player2.score);
		}
		//cout << dt << endl;
		window.display();
	}
}
//-------------------------------------------------<<Menues>>---------------------------------------------------//
int main()
{
	//MainMenu
	menu.menu1(window, GameMode);
	//menu.Menues(window);
}