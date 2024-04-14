#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <string.h>
#include <vector>
#include <math.h>
#define N 500
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Fullscreen);
Clock clockk;
float dt;
int GameMode;
bool pressed = false;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
int pageNumber = 1000;
int stairsNum = 200, bgNums = 200;
void Intilize_Numbers()
{
	/*if (GameMode == 2) stairsNum = 200;
	else  stairsNum = 100;*/
}
//---------------------------------------------<<Powerups>>--------------------------------------//
struct PowerUps
{
	Sprite dropShape;		   // random powerup
	//RectangleShape blockShape; // random block
	int type;				   // drop type
	int PowerUP_veolcity;
}Power;
Texture DropsTex[4];
vector<PowerUps> dropBag;
Sprite Drops[4];
Clock addtimer, deletetimer;
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
	float time;
	if (check)
		time = addtimer.getElapsedTime().asMilliseconds();
	else
		time = addtimer.getElapsedTime().asSeconds();
	//cout << addtimer.getElapsedTime().asMilliseconds() << endl;
	if (time >= rand() % 5 + 1)
	{
		
		int indexDrop = rand() % 4;
		PowerUps Powerup;
		Powerup.dropShape = Drops[indexDrop];
		Powerup.dropShape.setPosition(stair_position.x, stair_position.y-30);
		Powerup.type = indexDrop;
		dropBag.push_back(Powerup);
		addtimer.restart();

	}
	if (deletetimer.getElapsedTime().asSeconds() >= 20)
	{
		if (!dropBag.empty())
		{
			dropBag.erase(dropBag.begin());
			deletetimer.restart();
		}
	}
}
//-------------------------------------------<<Main menu>>---------------------------------------------//
struct menu_Bg_and_Face
{
	Sprite face;
	Texture fa;
	float current_face = 0;
	float rotation = 0;
	bool porm = true;
	float updown = 0;
	bool morp = true;
	Texture texture;
	RectangleShape bg;

	void back_ground()
	{
		texture.loadFromFile("Assets/Textures/main menu.png");
		bg.setTexture(&texture);
		bg.setSize(Vector2f(window.getSize()));
	}
	void FaceMotion()
	{

		fa.loadFromFile("Assets/Textures/heads.png");

		face.setTexture(fa);

		face.setScale(2.25, 2.25);
		face.setOrigin(120, 200);
		current_face += 0.008f;
		if (current_face >= 2.999999)
			current_face = 0;
		face.setTextureRect(IntRect(209 * int(current_face), 0, 209, 258));

		if (rotation >= 8)
		{
			porm = true;
		}
		else if (rotation <= -8)
			porm = false;

		if (porm)
			rotation -= 0.5;
		else
			rotation += 0.5;

		if (updown >= 10)
			morp = true;
		else if (updown <= -10)
			morp = false;

		if (morp)
			updown -= 0.5;
		else
			updown += 0.5;

		face.setPosition(1450 - rotation, 460 + updown);
		face.setRotation(rotation);

	}
}menu_UI;
struct Menu
{
	Text mainmenu[10];
	int selected = 0;
	Font font;
	int height = 1080;
	int choises;
	int pageNumber;
	int positionOfHand = 60;
	Texture handTex;
	RectangleShape hand;

	void Hand_intilization()
	{
		handTex.loadFromFile("Assets/Textures/hand.png");
		hand.setTexture(&handTex);
		hand.setSize(Vector2f(100, 70));
		hand.setPosition(1140, 580);
	}

	void MoveDown(int& selected, int choises)
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
	void MoveUp(int& selected, int choises)
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
};
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
	int last_button_pressed = 1;
	void inti(Texture& texture)
	{
		player1.setTexture(texture);
		player1.setPosition(500, 500);
		player1.setTextureRect(IntRect(0, 0, 128, 128));
		player1.setOrigin(player1.getTextureRect().width / 2, player1.getTextureRect().height / 2);
		//player2
		player2.setSize(Vector2f(100, 100));
		player2.setPosition(450, 500);

		velocity_x = 0;
		velocity_y = 0;
		x = 0;
		check_on_ground = 0;
	}
	void update()
	{
		player1.move(velocity_x * dt, velocity_y * dt);
		if (velocity_x > 0)
		{
			player1.setScale(1, 1);
			x += 0.01f;
			player1.setTextureRect(IntRect(128 * int(x), 0, 128, 128));
		}
		if (velocity_x < 0)
		{
			player1.setScale(-1, 1);
			x += 0.01f;
			player1.setTextureRect(IntRect(128 * int(x), 0, 128, 128));

		}
		/*if (velocity_y < 0)
		{
			check_on_ground = false;
		}*/

		if (x >= 7)
			x = 0;

	}
	void Players_Motion()
	{
		if (Keyboard::isKeyPressed(Keyboard::D) && END)
		{
			velocity_x = 200;
			last_button_pressed = 1;

		}
		if (Keyboard::isKeyPressed(Keyboard::A) && END)
		{
			velocity_x = -200;
			last_button_pressed = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::W) && END)
		{
			velocity_y = -700;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && END)
		{
			velocity_y = 400;

		}
		//player2 --------------------------------------------------
		if (GameMode == 2)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && END)
			{
				player2.move(0, -700 * dt);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && END)
			{
				player2.move(0, 700 * dt);
			}
		}
		//------------------------------------------------------------------

		if (players.last_button_pressed == 1)
		{
			player1.setTextureRect(IntRect(0, 0, 128, 128));
		}
		if (players.last_button_pressed == 2)
		{
			player1.setScale(-1, 1);
			player1.setTextureRect(IntRect(0, 0, 128, 128));
		}
	}
}players;
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
	int currstair = 0;
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
			if (currstair % Stairs_OF_EachFloor == 0)
			{
				//cout << currstair << endl;
				floorTexture[0].loadFromFile("Assets/Textures/floor.png");
				stairs[currstair].setTexture(&floorTexture[0]);
				FloorTextures();
				stairs[currstair].setSize(Vector2f(floor_width, 50));
				stairs[currstair].setOrigin(floor_width / 2, 0);
				stairs[currstair].setPosition(Vector2f(background.LeftWall_Pos_x + floor_width/2, 955 - heightBetweenStair));
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
				stairs[currstair].setOrigin(size_Of_Stair.x/2, 0);
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

	}
	void updateStairs()
	{
		RightLimit = (background.RightWalls_Pos_x - background.Walls_Width) - stairs[currstair].getSize().x - (1920 - (background.RightWalls_Pos_x - background.Walls_Width));
		bool player2_Notexist = 1;
		if (GameMode == 2)
		{
			if (stairs[currstair].getPosition().y > player2_View.getCenter().y + 540)
				player2_Notexist = 1;
			else
				player2_Notexist = 0;
		}

		if (currstair == stairsNum)
			currstair = 0;

		if (stairs[currstair].getPosition().y > player1_View.getCenter().y + 540 && player2_Notexist)
		{	
			
			if (currstair % Stairs_OF_EachFloor == 0)
			{
				FloorTextures();
				StairPosition = (Vector2f(background.LeftWall_Pos_x + floor_width / 2, 955 - heightBetweenStair));
			}
			else
			{
				StairsTextures();
				StairPosition = Vector2f(rand() % RightLimit + (background.LeftWall_Pos_x + background.Walls_Width + stairs[currstair].getSize().x / 2), 955 - heightBetweenStair);
			}

			stairs[currstair].setPosition(StairPosition);
			strnum();
			//powerups
			if (GameMode == 3)
			{
				generateDrop(StairPosition, 0);
			}
			currstair++;
			heightBetweenStair += 205;
			Number_Of_Stair++;
		}
	}
}Stairs;
RectangleShape Strs10[100000];
Text strTxt[10000];
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
	gameclock.cl.setScale(2, 2);

	gameclock.clo2.loadFromFile("Assets/Textures/clock 1.png");
	gameclock.cl2.setTexture(gameclock.clo2);
	gameclock.cl2.setScale(1.7, 1.7);
	gameclock.cl2.setOrigin(9.5, 30);
	gameclock.cl2.setRotation(int(0));



}
void update_clock()
{
	gameclock.l += .08;
	gameclock.cl2.setRotation(int(gameclock.l) * 2);
}
struct MAP
{
	float Walls_velocity, Backgrond_Velocity, Stairs_velocity, view_velocity;
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
			for (int i = 0; i < strCnt; i++)
			{
				Strs10[i].move(0, Stairs_velocity * dt);
				strTxt[i].move(0, Stairs_velocity * dt);
			}
			for (int i = 0; i < dropBag.size(); i++)
				dropBag[i].dropShape.move(0, Stairs_velocity * dt);

			for (int i = 0; i < bgNums; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity * dt);
				background.wallsRight[i].move(0, Walls_velocity * dt);
				background.wallsLeft[i].move(0, Walls_velocity * dt);
			}
			for (int i = 0; i <= stairsNum; i++)
			{
				Stairs.stairs[i].move(0, Stairs_velocity * dt);
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
		strNumTxt.setFillColor(Color::White);
		strNumTxt.setCharacterSize(20);
		strNumTxt.setString(to_string(Number_Of_Stair));
		strNumTxt.setPosition(numberedStr.getPosition().x + 17, numberedStr.getPosition().y + 15);
		Strs10[strCnt] = numberedStr;
		strTxt[strCnt] = strNumTxt;
		strCnt++;
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

void reset()
{
	Stairs.StairPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.currstair = Number_Of_Stair = 0;
	Stairs.heightBetweenStair = 0;
	gameclock.l = 0;

	background.Curr_Background = background.Curr_walls = background.update_Background = background.update_wall_index = background.Difference_Between_bg = 0;
	END = background.player2_Out_of_Background = background.player2_Out_of_Walls = 1;
	dropBag.clear();
	RectangleShape clear10;
	clear10.setSize(Vector2f(0, 0));
	fill(Strs10, Strs10 + strCnt, clear10);
	fill(begin(Stairs.stairs), end(Stairs.stairs), clear10);
	for (int i = 0; i < 10000; i++) {
		strTxt[i].setString("");
	}
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
	for (int i = 0; i <= stairsNum; i++)
	{
		window.draw(Stairs.stairs[i]);
	}
	if (GameMode == 3)
	{
		for (int i = 0; i < dropBag.size(); i++)
			window.draw(dropBag[i].dropShape);
	}
	for (int i = 0; i < bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
	
	for (int i = 0; i < strCnt; i++)
	{
		Strs10[i].setTexture(&Block_texture);
		strTxt[i].setFont(Gfont);
		window.draw(Strs10[i]);
		window.draw(strTxt[i]);
	}
	
}
void Gameplay()
{

	

	// powerups
	setDrops();

	//player
	Texture tex;
	tex.loadFromFile("Assets/Textures/Run.png");
	players.inti(tex);

	//Map
	MAP Map;
	CameraView view;

	//map insilization
	Map.intilization();

	//view insilization
	view.view_insilization();

	while (window.isOpen())
	{
		for (int i = 0; i < dropBag.size(); i++)
		{
			if (players.player1.getGlobalBounds().intersects(dropBag[i].dropShape.getGlobalBounds()))
			{
				dropBag[i].dropShape.setScale(0, 0);
			}
		}
		/*if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			cout << pos.x << " " << pos.y << endl;
		}*/
		dt = clockk.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape) && !pressed)
			{
				pageNumber = 500;
				pressed = true;
				pageNumber = 500;
				window.setView(window.getDefaultView());
				reset();
				return;
			}
			if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}
		}
		//clock
		

		Map.update();
		view.SetView();

		//map Motion
		Map.Map_Motion();
		Map.Backgrond_Velocity = 30.f;
		Map.Walls_velocity = 150.f;
		Map.Stairs_velocity = 70.0f;
		Map.view_velocity = 100;

		//motion of players
		players.velocity_x = 0;
		players.velocity_y = 0;

		//freeze game
		if (players.player1.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && players.player2.getPosition().y > player2_View.getCenter().y + 540))
		{
			Map.Backgrond_Velocity = Map.Walls_velocity = Map.Stairs_velocity = Map.view_velocity = Power.PowerUP_veolcity = 0;
			END = 0;
		}

		players.Players_Motion();
		players.update();

		window.clear();
		window.setView(player1_View);
		DRAW();
		if (GameMode == 2){
			window.draw(players.player2);
		}
		window.draw(players.player1);
		
		window.setView(window.getDefaultView());
		//set position of clock then draw it
		/////////
		if (GameMode == 2){
			gameclock.cl.setScale(1, 1);
			gameclock.cl2.setScale(1, 1);
			gameclock.cl.setPosition(0, 118);
			gameclock.cl2.setPosition(40, 180);
		}
		else {
			gameclock.cl.setPosition(230, 118);
			gameclock.cl2.setPosition(315, 235);
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
			gameclock.cl.setScale(1, 1);
			gameclock.cl2.setScale(1, 1);
			gameclock.cl.setPosition(950, 118);
			gameclock.cl2.setPosition(990, 180);
			window.draw(gameclock.cl);
			window.draw(gameclock.cl2);

		}
		window.display();
	}
}
//-------------------------------------------------<<Menues>>---------------------------------------------------//
bool resusme = 1;
int shift = 60 * resusme;
void menu1(Menu& men1)
{	
	men1.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");

	if     (resusme) men1.mainmenu[0 + resusme].setFillColor(Color::Black);
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
	men1.mainmenu[2 + resusme].setPosition(Vector2f(1250, men1.height / 2 + 160  + shift));

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
}
void Play_menu()
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

				if (event.key.code == Keyboard::Enter)
				{
					if (menu2.selected == 0)   GameMode = 1;
					if (menu2.selected == 1)   GameMode = 2;
					if (menu2.selected == 2)   GameMode = 3;
					Gameplay();
				}
			}
		}
		menu_UI.FaceMotion();
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
void options_menu1()
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
		menu_UI.FaceMotion();
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
void options_menu()
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
					if (menu4.selected == 0)  options_menu1();
					if (menu4.selected == 2) {
						pageNumber = 1000;
						return;
					}
				}
			}
		}
		menu_UI.FaceMotion();
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
void instructions()
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
int main()
{

	//MainMenu;
	Menu men;
	//hand
	men.Hand_intilization();

	//background
	menu_UI.back_ground();

	menu1(men);

	while (window.isOpen())
	{
		if (pageNumber == 1000)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.key.code == Keyboard::Escape && !pressed && men.selected != 5 + resusme)
				{
					men.mainmenu[men.selected].setFillColor(Color::Black);
					men.selected = 5 + resusme;
					men.mainmenu[5 + resusme].setFillColor(Color{ 255,204,0 });
					men.hand.setPosition(1140, 890+shift);
					pressed = true;
				}

				if (event.key.code == Keyboard::Escape && !pressed && men.selected == 5 + resusme)
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
						men.MoveDown(men.selected, men.choises);
					if (event.key.code == Keyboard::Up)
						men.MoveUp(men.selected, men.choises);
					if (event.key.code == Keyboard::Enter)
					{

						if (men.selected == 5 + resusme)
							pageNumber = -1;
						if (men.selected == 0 + resusme)
							Play_menu();
						if (men.selected == 4 + resusme)
							options_menu();
						if (men.selected == 1 + resusme)
							instructions();
					}
				}

			}
		}
		menu_UI.FaceMotion();
		if (pageNumber == -1)
		{
			window.close();
			break;
		}


		window.clear();
		window.draw(menu_UI.bg);
		window.draw(menu_UI.face);
		for (int i = 0; i < men.choises; i++)
		{
			window.draw(men.mainmenu[i]);
		}
		window.draw(men.hand);
		window.display();
	}
}
