#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <string.h>
#include <vector>
#include <math.h>
#define N 500
using namespace sf;
using namespace std;

Menu menu;
RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Fullscreen);
int GameMode;
Clock clockk, clockk2;
float dt, dt2;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
int stairsNum = 100, bgNums = 200;
void Intilize_Numbers()
{
	/*if (GameMode == 2) stairsNum = 200;
	else  stairsNum = 100;*/
}
//-------------------------------------------<<Main menu>>---------------------------------------------//
bool END = 1;
//---------------------------------------------<<Players>>---------------------------------------------------//
struct sprite {
	Sprite player1;
	RectangleShape player2;
	Texture texture;
	float velocity_x;
	float velocity_y;
	float x;
	bool check_on_ground;
	int gravity = -1;
	bool pree;
	bool pree2;
	int reflectionR;
	int reflectionL;
	const float Ground = 900;
	const float Right_wall = 1500;
	const float Left_wall = 450;
	int droptype = -1;
	void inti(Texture& texture)
	{
		player1.setTexture(texture);
		player1.setPosition(500, 500);
		player1.setTextureRect(IntRect(0, 0, 50, 60));
		player1.setOrigin(25, 30);
		player1.setScale(2.4, 2.4);
		//player2
		player2.setSize(Vector2f(100, 100));
		player2.setPosition(450, 500);
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
			x += 0.09f;
			player1.setTextureRect(IntRect(50 * (int)(x), 60, 50, 60));
		}
		if (velocity_x < 0)
		{
			player1.setScale(-2.4, 2.4);
			x += 0.09f;
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
	void Players_Motion()
	{

		if (reflectionL <= 0 && reflectionR <= 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (pree2 && !pree)
				{
					clockk2.restart();
					dt2 = 0;
				}
				velocity_x = 7 * dt2;
				pree = true;
				pree2 = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (pree && !pree2)
				{
					clockk2.restart();
					dt2 = 0;
				}
				velocity_x = -7 * dt2;
				pree2 = true;
				pree = false;
			}
			if (velocity_x == 0)
			{
				x += 0.04f;
				player1.setTextureRect(IntRect(50 * int(x), 0, 50, 60));
				clockk2.restart();
				pree = false;
				pree2 = false;
				reflectionR = 0;
				reflectionL = 0;
			}
			/*if(check_on_ground && velocity_x == 0)
				dt2 = 0;*/

		}
		else
		{
			if (reflectionL > 0)
			{
				velocity_x = reflectionL;
				reflectionL--;
			}
			if (reflectionR > 0)
			{
				velocity_x = -reflectionR;
				reflectionR--;
			}
			pree = false;
			pree2 = false;
		}

		if (velocity_y > 0 || !check_on_ground)
		{
			//velocity_y = 3;
			player1.setTextureRect(IntRect(50 * 3, 60 * 2, 50, 60));
		}

		if (check_on_ground)
		{
			//cout << "hu" << endl;
			velocity_y = 0;
		}
		else
		{
			velocity_y += 0.05;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && check_on_ground)
		{
			//cout << dt << endl;
			velocity_y -= 5.f;
			//velocity_y -= 5.f * (int(dt2) ? float(dt2)*100 : 1);
			check_on_ground = false;
		}
		//cout << velocity_y << endl;

		if (player1.getPosition().x > Right_wall)
		{
			player1.setPosition(Right_wall - 5, player1.getPosition().y);
			reflectionR = abs(velocity_x) - 2;
		}
		if (player1.getPosition().x < Left_wall)
		{
			player1.setPosition(Left_wall + 5, player1.getPosition().y);
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
PowerUps* dropBag = new PowerUps[stairsNum];

void generateDrop(Vector2f stair_position, bool check);
void setDrops();
//---------------------------------------------<<GameBackground & Stairs>>------------------------------------//
struct BackGround {
	Texture backGround, wallTexture;

	RectangleShape bg[N];
	RectangleShape wallsLeft[N], wallsRight[N];

	int Curr_Background = 0, Curr_walls = 0;
	int update_Background = 0, update_wall_index = 0, Difference_Between_bg = 0;

	int LeftWall_Pos_x, RightWalls_Pos_x, bg_width, floor_width;
	int Walls_Width = 160;

	bool player2_Out_of_Walls = 1;
	bool player2_Out_of_Background = 1;

	void intiliztion()
	{

		backGround.loadFromFile("Assets/Textures/BackGround game1.png");
		wallTexture.loadFromFile("Assets/Textures/wall1.png");
		//background
		if (GameMode == 2)
		{
			LeftWall_Pos_x = 0, RightWalls_Pos_x = 1920;
			bg_width = 1920, floor_width = 1920;
		}
		else
		{
			LeftWall_Pos_x = 240, RightWalls_Pos_x = 1680;
			bg_width = 1420, floor_width = 1420;
		}
		for (Curr_Background = 0; Curr_Background < bgNums; Curr_Background++)
		{
			Curr_walls = Curr_Background;
			wallsLeft[Curr_walls].setTexture(&wallTexture);
			wallsLeft[Curr_walls].setSize(Vector2f(Walls_Width, 1080));
			wallsLeft[Curr_walls].setPosition(LeftWall_Pos_x, -Difference_Between_bg);

			wallsRight[Curr_walls].setTexture(&wallTexture);
			wallsRight[Curr_walls].setSize(Vector2f(Walls_Width, 1080));
			wallsRight[Curr_walls].setScale(-1, 1);
			wallsRight[Curr_walls].setPosition(RightWalls_Pos_x, -Difference_Between_bg);

			bg[Curr_Background].setTexture(&backGround);
			bg[Curr_Background].setSize(Vector2f(bg_width, 1080));
			bg[Curr_Background].setPosition(LeftWall_Pos_x, -Difference_Between_bg);
			Difference_Between_bg += 1080;
		}
		Curr_Background--;
	}
	void updateBackground_And_Walls()
	{
		if (GameMode == 2) // 2player
		{
			if (bg[update_Background].getPosition().y >= player2_View.getCenter().y + 540)
				player2_Out_of_Background = 1;
			else
				player2_Out_of_Background = 0;
		}
		if (bg[update_Background].getPosition().y >= player1_View.getCenter().y + 540 && player2_Out_of_Background)
		{
			bg[update_Background].setPosition(Vector2f(LeftWall_Pos_x, bg[Curr_Background].getPosition().y - 1080));
			Curr_Background = update_Background;
			update_Background++;

		}
		if (GameMode == 2) // 2player
		{
			if (wallsLeft[update_wall_index].getPosition().y >= player2_View.getCenter().y + 540)
				player2_Out_of_Walls = 1;
			else
				player2_Out_of_Walls = 0;
		}
		if (wallsLeft[update_wall_index].getPosition().y >= player1_View.getCenter().y + 540 && player2_Out_of_Walls)
		{
			wallsLeft[update_wall_index].setPosition(Vector2f(LeftWall_Pos_x, wallsLeft[Curr_walls].getPosition().y - 1080));
			wallsRight[update_wall_index].setPosition(Vector2f(RightWalls_Pos_x, wallsLeft[Curr_walls].getPosition().y - 1080));
			Curr_walls = update_wall_index;
			update_wall_index++;
		}
		update_Background %= (bgNums - 1);
		update_wall_index %= (bgNums - 1);

	}
}background;
void strnum();
int strCnt = 0;
int Number_Of_Stair = 0;

int distanceOfMove = 0;
struct STAIRS {
	RectangleShape stairs[N];
	Texture stairTexture[3], floorTexture[3];

	//positions
	Vector2f StairPosition;
	//sizes
	Vector2f size_Of_Stair;
	int floor_width;

	//limit of stairs positions
	int RightLimit;

	//counters
	int heightBetweenStair = 0;
	int currstair = 0, updatestair = 0;
	int Stairs_OF_EachFloor = 50;

	//stairs intiliztion
	void StairsTextures()
	{
		if (Number_Of_Stair >= 100 && Number_Of_Stair < 200)
		{
			stairTexture[1].loadFromFile("Assets/Textures/Stair2.png");
			stairs[currstair].setTexture(&stairTexture[1]);
		}
		else if (Number_Of_Stair >= 200 && Number_Of_Stair < 300)
		{
			stairTexture[2].loadFromFile("Assets/Textures/Stair3.png");
			stairs[currstair].setTexture(&stairTexture[2]);
		}
	}
	void FloorTextures() {
		if (Number_Of_Stair >= 100 && Number_Of_Stair < 200)
		{
			floorTexture[1].loadFromFile("Assets/Textures/floor2.png");
			stairs[currstair].setTexture(&floorTexture[1]);
		}
		else if (Number_Of_Stair >= 200 && Number_Of_Stair < 300)
		{
			floorTexture[2].loadFromFile("Assets/Textures/floor3.png");
			stairs[currstair].setTexture(&floorTexture[2]);
		}
	}
	void intiliztion()
	{
		Intilize_Numbers();
		if (GameMode == 2)
		{
			background.LeftWall_Pos_x = 0, background.RightWalls_Pos_x = 1920;
			background.bg_width = 1920, floor_width = 1920;
		}
		else
		{
			background.LeftWall_Pos_x = 240, background.RightWalls_Pos_x = 1680;
			background.bg_width = 1420, floor_width = 1420;
		}

		//stairs & floors
		srand(static_cast<unsigned>(time(NULL)));
		for (currstair = 0; currstair < stairsNum; currstair++)
		{
			if (currstair % Stairs_OF_EachFloor == 0) //50
			{
				//cout << currstair << endl;
				floorTexture[0].loadFromFile("Assets/Textures/floor.png");
				stairs[currstair].setTexture(&floorTexture[0]);
				FloorTextures();
				stairs[currstair].setSize(Vector2f(floor_width, 50));
				stairs[currstair].setOrigin(floor_width / 2, 0);
				stairs[currstair].setPosition(Vector2f(background.LeftWall_Pos_x + floor_width / 2, 955 - heightBetweenStair));
				heightBetweenStair += 205;
			}
			else
			{
				stairTexture[0].loadFromFile("Assets/Textures/Stair.png");
				stairs[currstair].setTexture(&stairTexture[0]);
				StairsTextures();
				////SET SIZE
				size_Of_Stair = Vector2f((rand() % 300 + 200), 60);
				stairs[currstair].setSize(size_Of_Stair);
				stairs[currstair].setOrigin(size_Of_Stair.x / 2, 0);
				//1680                       240    =   1440                  size stair         (480)                 1440                   240
				RightLimit = (background.RightWalls_Pos_x - background.Walls_Width) - stairs[currstair].getSize().x - (1920 - (background.RightWalls_Pos_x - background.Walls_Width));

				////SET POSITION
				StairPosition = Vector2f((rand() % RightLimit) + (background.LeftWall_Pos_x + background.Walls_Width + stairs[currstair].getSize().x / 2), 955 - heightBetweenStair);
				stairs[currstair].setPosition(StairPosition);

				heightBetweenStair += 205;
			}
			strnum();
			if (GameMode == 3)
			{
				generateDrop(stairs[currstair].getPosition(), 1);
			}
			Number_Of_Stair++;
		}
		currstair--;

	}
	void updateStairs()
	{
		heightBetweenStair = 205;
		RightLimit = ((background.RightWalls_Pos_x - distanceOfMove) - background.Walls_Width) - stairs[updatestair].getSize().x - (1920 - ((background.RightWalls_Pos_x - distanceOfMove) - background.Walls_Width));
		bool player2_Notexist = 1;
		if (GameMode == 2)
		{
			if (stairs[updatestair].getPosition().y > player2_View.getCenter().y + 540)
				player2_Notexist = 1;
			else
				player2_Notexist = 0;
		}

		//if (currstair == stairsNum)
		//{
		//	updatestair = 0;
		//	//currstair = 0;
		//}

		if (stairs[updatestair].getPosition().y > player1_View.getCenter().y + 540 && player2_Notexist)
		{

			if (updatestair % Stairs_OF_EachFloor == 0) //50
			{
				StairPosition = (Vector2f(background.LeftWall_Pos_x + floor_width / 2, stairs[currstair].getPosition().y - heightBetweenStair));
				currstair = updatestair;
				FloorTextures();
			}
			else
			{
				StairPosition = Vector2f(rand() % RightLimit + (background.LeftWall_Pos_x + background.Walls_Width + distanceOfMove + stairs[updatestair].getSize().x / 2), stairs[currstair].getPosition().y - heightBetweenStair);
				currstair = updatestair;
				StairsTextures();
			}

			stairs[updatestair].setPosition(StairPosition);
			//powerups
			//currstair = updatestair;
			updatestair++;
			updatestair %= stairsNum;
			strnum();
			if (GameMode == 3)
			{
				generateDrop(StairPosition, 0);
			}
			//heightBetweenStair += 205;
			Number_Of_Stair++;
		}
	}
}Stairs;

RectangleShape Strs10[N];
Text strTxt[N];
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
	float Walls_velocity_x, Stairs_velocity_x;
	bool move = 0;

	void intilization()
	{
		setclock();
		background.intiliztion();
		Stairs.intiliztion();
	}
	void update()
	{
		Stairs.updateStairs();
		background.updateBackground_And_Walls();
	}
	void Map_Motion()
	{
		if (players.player1.getPosition().y < 100 || players.player2.getPosition().y < 100)
			move = 1;
		if (move)
		{
			update_clock();
			/*for (int i = 0; i < stairsNum; i++)
			{
				Strs10[i].move(0, Stairs_velocity_y * dt);
				strTxt[i].move(0, Stairs_velocity_y * dt);
			}*/
			/*for (int i = 0; i < stairsNum; i++)
				dropBag[i].dropShape.move(0, Stairs_velocity_y * dt);*/

			for (int i = 0; i < bgNums; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity_y * dt);
				background.wallsRight[i].move(0, Walls_velocity_y * dt);
				background.wallsLeft[i].move(0, Walls_velocity_y * dt);
			}
			for (int i = 0; i <= stairsNum; i++)
			{
				Stairs.stairs[i].move(0, Stairs_velocity_y * dt);
			}
			player2_View.move(0, -view_velocity * dt);
			player1_View.move(0, -view_velocity * dt);
		}
	}
};
void strnum() {
	if (Number_Of_Stair % 10 == 0) {
		RectangleShape numberedStr;
		Text strNumTxt;
		numberedStr.setPosition(Stairs.stairs[Stairs.currstair].getPosition().x, Stairs.stairs[Stairs.currstair].getPosition().y + 30);
		numberedStr.setSize(Vector2f(50, 50));
		numberedStr.setOrigin(numberedStr.getSize().x / 2, 0);

		strNumTxt.setFillColor(Color::White);
		strNumTxt.setCharacterSize(20);
		strNumTxt.setString(to_string(Number_Of_Stair));
		//strNumTxt.setOrigin(strNumTxt.getScale().x/2, strNumTxt.getScale().y);
		strNumTxt.setPosition(numberedStr.getPosition().x, numberedStr.getPosition().y + 15);
		Strs10[Stairs.currstair] = numberedStr;
		strTxt[Stairs.currstair] = strNumTxt;
	}
}
void Set_ObjectsOnStairs()
{
	for (int i = 0; i < stairsNum; i++)
	{
		Strs10[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
		strTxt[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
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

	int x = rand() % 5 + 4;
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
		for (int i = 0; i < stairsNum; i++)
		{
			if (players.player1.getGlobalBounds().intersects(dropBag[i].dropShape.getGlobalBounds()))
			{
				players.droptype = dropBag[i].type;
				dropBag[i].dropShape.setScale(0, 0);///////////Stairs.currstair
			}
		}
}
float velocity_x = 20;
void checkdrop(Clock& timerOfMove, bool& start, bool& StartReturning)
{
	if (players.droptype == 0)
	{
		distanceOfMove = 100;
		skip = 1;
		start = 1;
		if (timerOfMove.getElapsedTime().asSeconds() <= 5)
		{
			for (int i = 0; i < stairsNum; i++)
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
			distanceOfMove = 0;
		}
	}
	else if (players.droptype == 1)
	{

	}
	else if (players.droptype == 2)
	{

	}
}
//--------------------------------------------------------------------------------------------------
void reset()
{
	Stairs.StairPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.currstair = Number_Of_Stair = 0;
	Stairs.heightBetweenStair = 0;
	gameclock.l = 0;

	background.Curr_Background = background.Curr_walls = background.update_Background = background.update_wall_index = background.Difference_Between_bg = 0;
	END = background.player2_Out_of_Background = background.player2_Out_of_Walls = 1;
	delete[] dropBag;
	dropBag = nullptr;
	RectangleShape clear10;
	clear10.setSize(Vector2f(0, 0));
	fill(Strs10, Strs10 + strCnt, clear10);
	fill(begin(Stairs.stairs), end(Stairs.stairs), clear10);
	for (int i = 0; i < 200; i++) {
		strTxt[i].setString("");
	}
	players.droptype = -1;
	skip = 0;
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
void DRAW()
{
	Texture Block_texture;
	Block_texture.loadFromFile("Assets/Textures/strnum.png");
	Font Gfont;
	Gfont.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	for (int i = 0; i < bgNums; i++)
	{
		window.draw(background.bg[i]);
	}
	for (int i = 0; i < stairsNum; i++)
	{
		window.draw(Stairs.stairs[i]);
		Strs10[i].setTexture(&Block_texture);
		strTxt[i].setFont(Gfont);
		window.draw(Strs10[i]);
		window.draw(strTxt[i]);
		if (GameMode == 3)
		{
			window.draw(dropBag[i].dropShape);
		}
	}

	for (int i = 0; i < bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
}
void Gameplay()
{
	//window.setFramerateLimit(60);
	// powerups
	dropBag = new PowerUps[stairsNum];
	setDrops();

	//player
	Texture tex;
	tex.loadFromFile("Assets/Textures/icytower1.png");
	players.inti(tex);

	//Map
	MAP Map;
	CameraView view;

	//map insilization
	Map.intilization();

	//view insilization
	view.view_insilization();
	//////////////////////////////////////////
	Clock TimeOfMove, TimeOfReturn;
	bool StartMoving = 0;
	bool StartReturning = 0;
	//////////////////////////////////////////////
	while (window.isOpen())
	{
		/*if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			cout << pos.x << " " << pos.y << endl;
		}*/
		//--------------------------collisions----------------------------//
		players.check_on_ground = false;
		if (players.velocity_y >= 0) {
			for (int i = 0; i < stairsNum; i++)
			{
				if (players.player1.getGlobalBounds().intersects(Stairs.stairs[i].getGlobalBounds()))
				{
					if (players.player1.getPosition().y + 60 <= Stairs.stairs[i].getPosition().y)
					{
						players.player1.setPosition(players.player1.getPosition().x, Stairs.stairs[i].getPosition().y - 60);
						players.check_on_ground = true;
						//players.velocity_y = Map.Stairs_velocity * dt;
					}
				}
			}
		}
		dt = clockk.restart().asSeconds();
		dt2 = clockk2.getElapsedTime().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape) && !menu.pressed)
			{
				//pageNumber = 500;
				menu.pressed = true;
				menu.pageNumber = 500;
				window.setView(window.getDefaultView());
				reset();
				////////////////////////////////////////////////////////////
				////////////////
				return;
			}
			/*if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}*/
		}
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

		players.Players_Motion();
		players.update();

		window.clear();
		window.setView(player1_View);
		DRAW();
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

		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);
			DRAW();
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
	//MainMenu;
	menu.menu1(window, GameMode);

}