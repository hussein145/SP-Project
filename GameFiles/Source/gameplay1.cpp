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
#include "GameClock.h"
#define N 500
using namespace sf;
using namespace std;

//int select = 0;
//PauseMenu pausemenu;
//Menu Pause1;
Menu menu;
Walls_And_Background background;
STAIRS Stairs;
Sounds sound;
Players player1; Players player2;
PowerUps Power;
GameClock gameclock;


RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Close | Style::Fullscreen);
int GameMode;
Clock clockk, clockk2;
float dt, dt2;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
void Intilize_Numbers()
{
	if (GameMode == 2) {
		Stairs.stairsNum = 200;
		background.bgNums = 40;
	}
	else {
		Stairs.stairsNum = 50;
		background.bgNums = 20;
	}
}
bool END = 1;
int strCnt = 0;
extern bool pressed;
struct MAP
{
	float Walls_velocity_y, Backgrond_Velocity_y, Stairs_velocity_y, view_velocity;
	//float Walls_velocity_x, Stairs_velocity_x;
	bool move = 0;
	void intilization()
	{
		Stairs.intiliztion1(GameMode);
		background.intiliztion(GameMode, player1_View, player2_View);
		gameclock.setclock();
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

		gameclock.update_clock(view_velocity, move);
		if (move)
		{
			for (int i = 0; i < background.bgNums; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity_y * dt);
				background.wallsRight[i].move(0, Walls_velocity_y * dt);
				background.wallsLeft[i].move(0, Walls_velocity_y * dt);
			}
			for (int i = 0; i < Stairs.stairsNum; i++)
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
		Power.dropBag[i].dropShape.setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y - 30);
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
	gameclock.f = 0;
	player1.Score = player1.curr_colission = 0;
	player2.Score = player2.curr_colission = 0;

	background.Curr_Background = background.Curr_walls = background.update_Background = background.update_wall_index = background.Difference_Between_bg = 0;
	END = background.player2_Out_of_Background = background.player2_Out_of_Walls = 1;
	delete[] Power.dropBag;
	Power.dropBag = nullptr;

	delete[] Stairs.stairs;
	Stairs.stairs = nullptr;

	delete[] Stairs.Strs10;
	Stairs.Strs10 = nullptr;

	delete[] Stairs.strTxt;
	Stairs.strTxt = nullptr;

	delete[] background.bg;
	background.bg = nullptr;

	delete[] background.wallsLeft, background.wallsRight;
	background.wallsLeft = background.wallsRight = nullptr;

	player1.droptype = -1;
	Power.skip = 0;
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
void CountScore(Players& player, int i)
{
	if (player.curr_colission > i) {
		if ((player.curr_colission - i) <= 9) { // Fall from stair
			player.Score -= player.curr_colission - i;
			player.cnt = 1;
		}
		else { // Jump and loop repeat itself
			player.cnt = (Stairs.stairsNum - player.curr_colission) + i;
			player.Score += (Stairs.stairsNum - player.curr_colission) + i;
		}
	}
	else { // i > curr_colission (Normal Condition)
		player.cnt = (i - player.curr_colission);
		player.Score += (i - player.curr_colission);
	}
	player.curr_colission = i;
}
void collisions(Players& player)
{
	player.check_on_ground = false;
	if (player.velocity_y >= 0) {
		for (int i = 0; i < Stairs.stairsNum; i++)
		{
			if (player.character.getGlobalBounds().intersects(Stairs.stairs[i].getGlobalBounds()))
			{
				if (player.character.getPosition().y + 25 <= Stairs.stairs[i].getPosition().y)
				{
					player.character.setPosition(player.character.getPosition().x, Stairs.stairs[i].getPosition().y - 60);
					player.check_on_ground = true;
					CountScore(player, i);
					break;
				}
			}
		}
	}
}
void DRAW()
{
	for (int i = 0; i < background.bgNums; i++)
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
			window.draw(Power.dropBag[i].dropShape);
		}
	}
	for (int i = 0; i < background.bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
}
void DRAW_View1()
{
	if (GameMode == 2) {
		window.draw(player2.character);
	}
	window.draw(player1.character);
	window.setView(window.getDefaultView());
	gameclock.power.setFillColor({ 180,3,3 });
	gameclock.power.setPosition(295, 558);
	//set position of clock then draw it
	/////////
	if (GameMode == 2) {
		gameclock.cl.setScale(1, 1);
		gameclock.cl2.setScale(1, 1);
		gameclock.cl.setPosition(0, 118);
		gameclock.cl2.setPosition(40, 180);
		gameclock.star.setPosition(5, 350);
		player1.compo.setPosition(35, 360);
		player1.score.setPosition(30, 990);
		gameclock.power.setPosition(32.5, 338);
	}
	window.draw(gameclock.cl);
	window.draw(gameclock.cl2);
	window.draw(player1.score);
	window.draw(gameclock.power);
	window.draw(gameclock.star);
	gameclock.star.setPosition(230, 550);
	window.draw(player1.compo);
}
void DRAW_View2()
{
	gameclock.power2.setFillColor({ 180,3,3 });
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
	gameclock.power2.setPosition(982, 338);
	window.draw(gameclock.power2);
	window.draw(gameclock.star2);
	gameclock.star2.setPosition(950, 350);
	player2.compo.setPosition(980, 360);
	window.draw(player2.compo);
}
void Gameplay()
{
	Intilize_Numbers();
	Stairs.stairs = new RectangleShape[Stairs.stairsNum];
	Stairs.Strs10 = new RectangleShape[Stairs.stairsNum];
	Stairs.strTxt = new Text[Stairs.stairsNum];

	background.bg = new RectangleShape[background.bgNums];
	background.wallsLeft = new RectangleShape[background.bgNums];
	background.wallsRight = new RectangleShape[background.bgNums];

	Power.dropBag = new PowerUps[Stairs.stairsNum];

	SoundBuffer buff;
	buff.loadFromFile("Assets//Sounds//jump.ogg");

	sound.music(1);
	Texture GameTexture;

	float mapspeed = 0, addmapspeed = 0;

	MAP Map;
	CameraView view;

	// powerups
	Power.setDrops();

	//map insilization
	Map.intilization();

	//player
	extern int PLayer1;
	extern int PLayer2;

	Texture tex1, tex2;
	tex1.loadFromFile("Assets/Textures/icytower1.png");
	tex2.loadFromFile("Assets/Textures/icytower2.png");
	if (PLayer1 == 0)
		player1.inti(tex1);
	else if (PLayer1 == 1)
		player1.inti(tex2);


	if (PLayer2 == 0)
		player2.inti(tex2);
	else if (PLayer2 == 1)
		player2.inti(tex2);

	float resize = 0, resize2 = 0;

	//music(k);



	//view insilization
	view.view_insilization();
	Clock TimeOfMove;
	//Time TimeOfMove;
	bool StartMoving = 0;
	bool StartReturning = 0;
	int x = 0, y = 0, disapp = 0,disapp2;

	Map.Backgrond_Velocity_y = 20.0f;
	Map.Walls_velocity_y = 120.0f;
	Map.Stairs_velocity_y = 50.0f;
	Map.view_velocity = 80.0f;
	while (window.isOpen())
	{
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
			if (END ? (Play.key.code == Keyboard::Escape && !pressed) : (Play.type == Event::KeyPressed && !pressed))  //&& !menu.pressed
			{
				pressed = true;
				GameTexture.create(1920, 1080);
				GameTexture.update(window);
				menu.Pause(window, GameTexture);
				clockk.restart();
				//TimeOfMove.restart();
				if (menu.exit)
				{
					menu.exit = 0;
					sound.music(0);
					reset();
					return;
				}

				if (menu.exit)
				{
					menu.exit = 0;
					sound.music(0);
					reset();
					return;
				}
			}
			if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}
		}
		
			if (x > 0 && x != disapp)
				resize = GameMode == 2 ?103: 203;
			else if (x == 0)
			{
				resize = 0; disapp = 0;
			}

			if (resize > 0)
			{
				gameclock.power.setOrigin(0, gameclock.power.getSize().y);
				gameclock.power.setSize({ GameMode==2? 18.f: 35.f, resize });
				resize -= GameMode == 2 ? .25 : .5;
			}
			else
				gameclock.power.setSize({ 0,0 });

			disapp = x;
		
			//-------------------------------------------------------------------------------

			if (y > 0 && y != disapp2)
				resize2 = 103;
			else if (y == 0)
			{
				resize2 = 0; disapp2 = 0;
			}

			if (resize2 > 0)
			{
				gameclock.power2.setOrigin(0, gameclock.power2.getSize().y);
				gameclock.power2.setSize({ 18.f, resize2 });
				resize2 -= .25;
			}
			else
				gameclock.power2.setSize({ 0,0 });

			disapp2 = y;

		dt = clockk.restart().asSeconds();
		dt2 = clockk2.restart().asSeconds();
		collisions(player1);
		collisions(player2);
		player1.score.setString("Score: " + to_string(player1.Score * 10));
		player2.score.setString("Score: " + to_string(player2.Score * 10));
		if (player1.cnt != 1)
		{
			x += player1.cnt;
			player1.cnt = 0;
			player1.Max_Compo = max(x, player1.Max_Compo);
		}
		else {
			x = 0;
		}
		player1.compo.setString(to_string(x));

		if (player2.cnt > 1 || player2.cnt == 0)
		{
			y += player2.cnt;
			player2.Max_Compo = max(y, player2.Max_Compo);
			player2.compo.setString(to_string(y));
		}
		else {
			y = 0;
		}
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

			if (player1.droptype == 3)
			{
				mapspeed = 100.f;
				addmapspeed = 7;
				Map.view_velocity += mapspeed;
				player1.droptype = -1;
			}
			if (addmapspeed <= 0)
			{
				Map.view_velocity -= mapspeed;
				mapspeed = 0;
				addmapspeed = 0;
			}
			else
			{
				addmapspeed -= 0.01;
			}


			if (player1.droptype != 0)
				Power.resetPowerups();
		}
		Map.update();
		view.SetView();

		//map Motion
		Map.Map_Motion();

		//freeze game
		if (player1.character.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && player2.character.getPosition().y > player2_View.getCenter().y + 540))
		{
			Map.move = 0;
			END = 0;
		}
		//cout << dt << endl;
		player1.Players_Motion(buff, Keyboard::A, Keyboard::D, Keyboard::Space);
		player2.Players_Motion(buff, Keyboard::Left, Keyboard::Right, Keyboard::Numpad0);
		player1.update();
		player2.update();
		if (x == 0||resize==0)
		{
			gameclock.star.setScale(0, 0);
			player1.compo.setCharacterSize(0);
		}
		if (y == 0 || resize2 == 0)
		{
			gameclock.star2.setScale(0, 0);
			player2.compo.setCharacterSize(0);
		}
		/*====================================================DRAW=================================*/
		window.clear();
		window.setView(player1_View);
		DRAW();
		DRAW_View1();
		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);
			DRAW();
			DRAW_View2();
		}
		window.display();
	}
}
//-------------------------------------------------<<Menues>>---------------------------------------------------//
int main()
{
	window.setFramerateLimit(120);
	//MainMenu
	menu.menu1(window, GameMode);
	//menu.Menues(window);
}
