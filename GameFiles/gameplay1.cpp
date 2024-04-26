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

RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Close | Style::Fullscreen);
int GameMode;
Clock clockk, clockk2;
float dt, dt2;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
/* bgNums = 200;*/



void Intilize_Numbers()
{
	/*if (GameMode == 2) stairsNum = 200;
	else  stairsNum = 100;*/
}
//-------------------------------------------<<Main menu>>---------------------------------------------//
bool END = 1;
//---------------------------------------------<<Players>>---------------------------------------------------//
struct sprite {
	int Score = 0;
	Sprite player1;
	RectangleShape player2;
	Texture texture;
	float velocity_x;
	float velocity_y;
	float x;
	bool check_on_ground = 1;
	int gravity = -1;
	bool pree;
	bool pree2;
	int reflectionR;
	int reflectionL;
	const float Ground = 900;
	const float Right_wall = 1500;
	const float Left_wall = 450;
	int droptype = -1;
	float incspeed = 1, addspeed = 0, superjump = 1, addsuperjump = 0;
	void inti(Texture& texture)
	{
		player1.setTexture(texture);
		player1.setPosition(500, 850);
		player1.setTextureRect(IntRect(0, 0, 50, 60));
		player1.setOrigin(25, 30);
		player1.setScale(2.4, 2.4);
		//player2
		player2.setSize(Vector2f(100, 100));
		player2.setPosition(450, 400);
		velocity_x = 0;
		velocity_y = 0;
		x = 0;
		check_on_ground = 0;
		pree = false;
		pree2 = false;
		reflectionR = 0;
		reflectionL = 0;
	}
	void update()
	{
		player1.move(velocity_x, velocity_y);
		if (velocity_x > 0)
		{
			player1.setScale(2.4, 2.4);
			x += 0.005f;
			player1.setTextureRect(IntRect(50 * (int)(x), 60, 50, 60));
		}
		if (velocity_x < 0)
		{
			player1.setScale(-2.4, 2.4);
			x += 0.008f;
			player1.setTextureRect(IntRect(50 * (int)(x), 60, 50, 60));
		}
		if (velocity_y < 0)
		{
			player1.setTextureRect(IntRect(0, 60 * 2, 50, 60));
		}
		else if (velocity_y < 0 && Keyboard::isKeyPressed(Keyboard::Right))
		{
			player1.setTextureRect(IntRect(50, 60 * 2, 50, 60));
		}
		if (x > 3.9)
			x = 0;
	}

	Sound so4;
	void Players_Motion(SoundBuffer& buff) {
		if (reflectionL <= 0 && reflectionR <= 0) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (pree2 && !pree) {
					clockk2.restart();
					dt2 = 0;
				}
				velocity_x = 700 * dt;
				pree = true;
				pree2 = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (pree && !pree2) {
					clockk2.restart();
					dt2 = 0;
				}
				velocity_x = -700 * dt;
				pree2 = true;
				pree = false;
			}
			if (velocity_x == 0 && velocity_y == 0) {
				x += 0.009f;
				player1.setTextureRect(IntRect(50 * int(x), 0, 50, 60));
				clockk2.restart();
				dt2 = 0;
				pree = false;
				pree2 = false;
				reflectionR = 0;
				reflectionL = 0;
			}
			/*if(check_on_ground && velocity_x == 0)
				dt2 = 0;*/
		}
		else {
			if (reflectionL > 0) {
				velocity_x = reflectionL;
				reflectionL--;
			}
			if (reflectionR > 0) {
				velocity_x = -reflectionR;
				reflectionR--;
			}
			pree = false;
			pree2 = false;
		}

		if (velocity_y > 0 || !check_on_ground) {
			player1.setTextureRect(IntRect(50 * 3, 60 * 2, 50, 60));
		}

		if (check_on_ground) {
			velocity_y = 0;
		}
		else {
			velocity_y += 4.f*dt;
		}
		/*if (!check_on_ground) {
			velocity_y += 1.f * dt;*/
		//}
		if (Keyboard::isKeyPressed(Keyboard::Space) && check_on_ground) {
			velocity_y -= 2 + addsuperjump;
			check_on_ground = false;
			so4.setBuffer(buff);
			so4.play();
			cout << dt << endl;
		}
		//cout << velocity_y << endl;

		if (player1.getPosition().x > background.RightWalls_Pos_x - background.Walls_Width)
		{
			player1.setPosition(background.RightWalls_Pos_x - background.Walls_Width - 5, player1.getPosition().y);
			reflectionR = abs(velocity_x) - 2;
		}
		if (player1.getPosition().x < background.LeftWall_Pos_x + background.Walls_Width)
		{
			player1.setPosition(background.LeftWall_Pos_x + background.Walls_Width + 5, player1.getPosition().y);
			reflectionL = abs(velocity_x) - 2;
		}
	}
}players;
//---------------------------------------------<<powers>>---------------------------------------------------//
struct PowerUps
{
	Sprite dropShape;		   // random powerup
	//RectangleShape blockShape; // random block
	int type;				   // drop type
	int PowerUP_veolcity;
}Power;
Texture DropsTex[4];

Sprite Drops[4]; // 0 walls inwards(heart)
PowerUps* dropBag = new PowerUps[100];//stairsNum

void generateDrop(Vector2f stair_position, bool check);
void setDrops();
//---------------------------------------------<<GameBackground & Stairs>>------------------------------------//
int strCnt = 0;

struct Gameclock
{
	Texture clo;
	Sprite cl;
	Texture clo2;
	Sprite cl2;
	float l = 0;
}gameclock;
void setclock()
{
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
	gameclock.l += .08;
	gameclock.cl2.setRotation(int(gameclock.l) * 2);
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
		if (players.player1.getPosition().y < 100 || players.player2.getPosition().y < 100)
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
		}
	}
	void SetView()
	{
		if (players.player1.getPosition().y < player1_View.getCenter().y - 340)
		{
			player1_View.setCenter(Vector2f(960, players.player1.getPosition().y + 340));
		}
		if (GameMode == 2 && players.player2.getPosition().y < player2_View.getCenter().y - 340)
		{
			player2_View.setCenter(Vector2f(960, players.player2.getPosition().y + 340));
		}
	}
};
//------------------------------------------------<<powerups>>-------------------------------------------//
Clock addtimer;
void setDrops()
{
	DropsTex[0].loadFromFile("Assets//Textures//heart.png");
	DropsTex[1].loadFromFile("Assets//Textures//speed.png");
	DropsTex[2].loadFromFile("Assets//Textures//superjump.png");
	DropsTex[3].loadFromFile("Assets//Textures//danger.png");
	for (size_t i = 0; i < 4; i++)
	{
		Drops[i].setTexture(DropsTex[i]);
		Drops[i].setOrigin(Drops[i].getScale().x / 2, Drops[i].getScale().y / 2);
	}
	Drops[0].setScale(0.15, 0.15);
	Drops[1].setScale(0.15, 0.15);
	Drops[2].setScale(0.15, 0.15);
	Drops[3].setScale(0.15, 0.15);
}
void generateDrop(Vector2f stair_position, bool check)
{
	float timee;
	if (check)
		timee = addtimer.getElapsedTime().asMilliseconds();
	else
		timee = addtimer.getElapsedTime().asSeconds();

	int x = rand() % 5 + 2;
	if (timee >= x)
	{
		int indexDrop = rand() % 4;
		//PowerUps Powerup;
		Power.dropShape = Drops[indexDrop];
		Power.dropShape.setPosition(stair_position.x, stair_position.y - 30);
		Power.type = indexDrop;
		dropBag[Stairs.currstair] = Power;
		addtimer.restart();
	}
}
bool skip = 0;
void dropcollision()
{
	if (!skip)
		for (int i = 0; i < Stairs.stairsNum; i++)
		{
			if (players.player1.getGlobalBounds().intersects(dropBag[i].dropShape.getGlobalBounds()))
			{
				players.droptype = dropBag[i].type;
				dropBag[i].dropShape.setScale(0, 0);
			}
		}
}
float velocity_x = 20;
void checkdrop(Clock& timerOfMove, bool& start, bool& StartReturning)
{
	if (players.droptype == 0)
	{
		Stairs.distanceOfMove = 100;
		skip = 1;
		start = 1;
		if (timerOfMove.getElapsedTime().asSeconds() <= 5)
		{
			for (int i = 0; i < Stairs.stairsNum; i++)
			{
				if (Stairs.stairs[i].getPosition().x > 960)
					Stairs.stairs[i].move(-velocity_x * dt, 0);
				else if (Stairs.stairs[i].getPosition().x < 960)
					Stairs.stairs[i].move(velocity_x * dt, 0);

				background.wallsLeft[i].move(velocity_x * dt, 0);
				background.wallsRight[i].move(-velocity_x * dt, 0);
			}
			gameclock.cl.move(velocity_x * dt, 0);
			gameclock.cl2.move(velocity_x * dt, 0);
		}
		else if (timerOfMove.getElapsedTime().asSeconds() > 5 && timerOfMove.getElapsedTime().asSeconds() < 8)
		{
			velocity_x = 0;
		}
		else if (timerOfMove.getElapsedTime().asSeconds() >= 8)
		{
			StartReturning = 1;
			velocity_x = -20;
			timerOfMove.restart();
		}
		if (timerOfMove.getElapsedTime().asSeconds() >= 5 && StartReturning)
		{
			StartReturning = 0;
			players.droptype = -1;
			start = 0;
			velocity_x = 20;
			skip = 0;
			Stairs.distanceOfMove = 0;
		}
	}
	else if (players.droptype == 1)
	{
		players.addsuperjump = 3;
		players.superjump = 1.5;
	}
	else if (players.droptype == 2)
	{
		players.addspeed = 7;
		players.incspeed = 2;
	}
}
//--------------------------------------------------------------------------------------------------
void reset()
{
	Stairs.StairPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.currstair = Stairs.updatestair = Stairs.Number_Of_Stair = 0;
	Stairs.heightBetweenStair = 0;
	gameclock.l = 0;
	players.Score = 0;

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
	players.droptype = -1;
	skip = 0;
}
void resetPowerups()
{
	if (players.addspeed <= 0) {
		players.addspeed = 0;
		players.incspeed = 1;
	}
	else {
		players.addspeed -= 0.01;
		players.droptype = -1;
	}
	if (players.addsuperjump <= 0) {
		players.addsuperjump = 0;
		players.superjump = 1;
	}
	else {
		players.addsuperjump -= 0.001;
		players.droptype = -1;
	}
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
void DRAW(RenderWindow& window)
{
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
	setDrops();

	//player
	Texture tex;
	tex.loadFromFile("Assets/Textures/icytower1.png");
	players.inti(tex);
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
	int curr_colission = 0;
	Font score_Tex;
	score_Tex.loadFromFile("Assets//Fonts//BrownieStencil-8O8MJ.ttf");
	Text score;
	score.setFont(score_Tex);
	score.setCharacterSize(50);
	score.setPosition(240, 1000);
	while (window.isOpen())
	{
		dt = clockk.restart().asSeconds();
		dt2 = clockk2.getElapsedTime().asSeconds();
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
		//--------------------------collisions----------------------------//
		/*if (dt2 > 10)
		{
			dt2 = 10;
			cout << " hussein" << endl;
		}*/
		players.check_on_ground = false;
		if (players.velocity_y >= 0) {
			for (int i = 0; i < Stairs.stairsNum; i++)
			{
				if (players.player1.getGlobalBounds().intersects(Stairs.stairs[i].getGlobalBounds()))
				{
					if (players.player1.getPosition().y + 60 <= Stairs.stairs[i].getPosition().y)
					{
						players.player1.setPosition(players.player1.getPosition().x, Stairs.stairs[i].getPosition().y - 60);
						players.check_on_ground = true;

						if (curr_colission > i) {
							if ((curr_colission - i) <= 9) { // Fall from stair
								players.Score -= curr_colission - i;
							}
							else { // Jump and loop repeat itself
								players.Score += (Stairs.stairsNum - curr_colission) + i;
							}
						}
						else { // i > curr_colission (Normal Condition)
							players.Score += (i - curr_colission);
						}

						curr_colission = i;
					}
				}
			}
		}

		score.setString("Score: " + to_string(players.Score * 10));
		Set_ObjectsOnStairs();

		if (GameMode == 3)
		{
			dropcollision();
			//clock
			if (!StartMoving)
			{
				TimeOfMove.restart();
			}
			checkdrop(TimeOfMove, StartMoving, StartReturning);
			resetPowerups();
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
		players.velocity_x = 0;
		//players.velocity_y = 0;

		//freeze game
		if (players.player1.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && players.player2.getPosition().y > player2_View.getCenter().y + 540))
		{
			Map.Backgrond_Velocity_y = Map.Walls_velocity_y = Map.Stairs_velocity_y = Map.view_velocity = Power.PowerUP_veolcity = 0;
			END = 0;
		}

		players.Players_Motion(buff);
		players.update();

		window.clear();
		window.setView(player1_View);
		DRAW(window);
		if (GameMode == 2) {
			window.draw(players.player2);
		}
		window.draw(players.player1);

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
		window.draw(score);

		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);
			DRAW(window);
			window.draw(players.player1);
			window.draw(players.player2);

			window.setView(window.getDefaultView());
			//set position of clock then draw it
			/////////
			gameclock.cl.setPosition(950, 118);
			gameclock.cl2.setPosition(990, 180);
			window.draw(gameclock.cl);
			window.draw(gameclock.cl2);

		}
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
