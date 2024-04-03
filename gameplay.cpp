#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
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
int stairsNum, floorsnum, bgNums;
void Intilize_Numbers()
{
	if (GameMode == 2)
	{
		stairsNum = 200, floorsnum = 50;
		bgNums = 200;
	}
	else
	{
		stairsNum = 8; floorsnum = 1;
		bgNums = 3;
	}
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
void generateDrop(Vector2f stair_position, int Stair_width)
{
	if (addtimer.getElapsedTime().asSeconds() >= rand() % 5 + 1)
	{
		int indexDrop = rand() % 4;
		PowerUps Powerup;
		Powerup.dropShape = Drops[indexDrop];
		Powerup.dropShape.setPosition(stair_position.x + (Stair_width / 2), stair_position.y);
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
	int positionOfHand = 70;
	Texture handTex;
	RectangleShape hand;

	void Hand_intilization()
	{
		handTex.loadFromFile("Assets/Textures/hand.png");
		hand.setTexture(&handTex);
		hand.setSize(Vector2f(100, 70));
		hand.setPosition(1140, 600);
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
				hand.setPosition(1140, 600);
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

	void intiliztion()
	{
		Intilize_Numbers();
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
			wallsLeft[Curr_Background].setTexture(&wallTexture);
			wallsLeft[Curr_Background].setSize(Vector2f(Walls_Width, 1080));
			wallsLeft[Curr_Background].setPosition(LeftWall_Pos_x, -Difference_Between_bg);

			wallsRight[Curr_Background].setTexture(&wallTexture);
			wallsRight[Curr_Background].setSize(Vector2f(Walls_Width, 1080));
			wallsRight[Curr_Background].setScale(-1, 1);
			wallsRight[Curr_Background].setPosition(RightWalls_Pos_x, -Difference_Between_bg);

			bg[Curr_Background].setTexture(&backGround);
			bg[Curr_Background].setSize(Vector2f(bg_width, 1080));
			bg[Curr_Background].setPosition(LeftWall_Pos_x, -Difference_Between_bg);
			Difference_Between_bg += 1080;
		}
	}
	void updateBackground_And_Walls()
	{
		bool player2_Out_of_Background = 1;
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
		bool player2_Out_of_Walls = 1;
		if (GameMode == 2) // 2player
		{
			if (wallsLeft[update_wall_index].getPosition().y > player2_View.getCenter().y + 540)
				player2_Out_of_Walls = 1;
			else
				player2_Out_of_Walls = 0;
		}
		if (wallsLeft[update_wall_index].getPosition().y > player1_View.getCenter().y + 540 && player2_Out_of_Walls)
		{
			wallsLeft[update_wall_index].setPosition(Vector2f(LeftWall_Pos_x, wallsLeft[Curr_walls].getPosition().y - 1080));
			wallsRight[update_wall_index].setPosition(Vector2f(RightWalls_Pos_x, wallsLeft[Curr_walls].getPosition().y - 1080));
			Curr_walls = update_wall_index;
			update_wall_index++;
		}
		//Difference_Between_bg += 1080;
		update_Background %= (bgNums - 1);
		update_wall_index %= (bgNums - 1);

	}
}background;
struct STAIRS {
	RectangleShape stairs[N];
	RectangleShape floor[N];
	Texture stairTexture, floorTexture;

	//positions
	Vector2f StairPosition;
	Vector2f floorPosition;
	//sizes
	Vector2f size_Of_Stair;
	int floor_width;

	//limit of stairs positions
	int RightLimit;

	//counters
	int heightBetweenStair;
	int currstair = 0, currFloor = 0;
	int Stair_Update_index = 0, Floor_Update_index = 0;
	int Stairs_OF_EachFloor = 50;

	//stairs intiliztion
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
		stairTexture.loadFromFile("Assets/Textures/Stair.png");
		floorTexture.loadFromFile("Assets/Textures/floor.png");
		//stairs & floors
		heightBetweenStair = 0;
		srand(static_cast<unsigned>(time(NULL)));
		for (currstair = 0; currstair < stairsNum; currstair++)
		{
			if (currstair % Stairs_OF_EachFloor == 0)
			{
				floor[currFloor].setTexture(&floorTexture);
				floor[currFloor].setSize(Vector2f(floor_width, 150));
				floor[currFloor].setPosition(Vector2f(background.LeftWall_Pos_x, 955 - heightBetweenStair));
				currFloor++;
				heightBetweenStair += 205;
			}

			stairs[currstair].setTexture(&stairTexture);
			//SET SIZE
			size_Of_Stair = Vector2f((rand() % 300 + 250), 150);
			stairs[currstair].setSize(size_Of_Stair);
			RightLimit = (background.RightWalls_Pos_x - background.Walls_Width) - stairs[currstair].getSize().x - (1920 - (background.RightWalls_Pos_x - background.Walls_Width));

			//SET POSITION
			StairPosition = Vector2f((rand() % RightLimit) + (background.LeftWall_Pos_x + background.Walls_Width), 955 - heightBetweenStair);
			stairs[currstair].setPosition(StairPosition);

			heightBetweenStair += 205;

			/*if (GameMode == 3)
			{
				generateDrop(stairs[i].getPosition(), stairs[i].getSize().x);
			}*/
		}

	}
	void updateStairs()
	{
		RightLimit = (background.RightWalls_Pos_x - background.Walls_Width) - stairs[Stair_Update_index].getSize().x - (1920 - (background.RightWalls_Pos_x - background.Walls_Width));
		bool player2_Notexist = 1;
		if (GameMode == 2)
		{
			if (stairs[Stair_Update_index].getPosition().y > player2_View.getCenter().y + 540)
				player2_Notexist = 1;
			else
				player2_Notexist = 0;
		}
		if (stairs[Stair_Update_index].getPosition().y > player1_View.getCenter().y + 540 && player2_Notexist)
		{
			if (currstair % Stairs_OF_EachFloor == 0)
			{
				floor[Floor_Update_index].setPosition(Vector2f(background.LeftWall_Pos_x, 955 - heightBetweenStair));
				Floor_Update_index++;
				heightBetweenStair += 205;
			}
			StairPosition = Vector2f(rand() % RightLimit + (background.LeftWall_Pos_x + background.Walls_Width), 955 - heightBetweenStair);
			stairs[Stair_Update_index].setPosition(StairPosition);

			//powerups
			if (GameMode == 3)
			{
				generateDrop(StairPosition, stairs[Stair_Update_index].getSize().x);
			}
			currstair++;
			Stair_Update_index++;
			heightBetweenStair += 205;
		}

		if (!(currstair % Stairs_OF_EachFloor))
			Floor_Update_index = 0;

		Stair_Update_index %= (stairsNum - 1);
	}
}Stairs;
struct MAP
{
	float Walls_velocity, Backgrond_Velocity, Stairs_velocity, view_velocity;
	bool move = 0;
	void intilization()
	{
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
			for (int i = 0; i < dropBag.size(); i++)
				dropBag[i].dropShape.move(0, Power.PowerUP_veolcity * dt);

			for (int i = 0; i < bgNums; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity * dt);
				background.wallsRight[i].move(0, Walls_velocity * dt);
				background.wallsLeft[i].move(0, Walls_velocity * dt);
			}
			for (int i = 0; i < stairsNum; i++)
			{
				Stairs.stairs[i].move(0, Stairs_velocity * dt);
			}
			for (int i = 0; i < floorsnum; i++)
			{
				Stairs.floor[i].move(0, Stairs_velocity * dt);
			}
			player2_View.move(0, -view_velocity * dt);
			player1_View.move(0, -view_velocity * dt);
		}
	}
};

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
	Stairs.StairPosition = Stairs.floorPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.Floor_Update_index = Stairs.Stair_Update_index = Stairs.currFloor = Stairs.currstair = Stairs.heightBetweenStair = Stairs.RightLimit = 0;

	background.Curr_Background = background.update_Background = background.Difference_Between_bg = 0;
	END = 1;
	dropBag.clear();
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
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
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			cout << pos.x << " " << pos.y << endl;
		}
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
		Map.update();
		view.SetView();

		//map Motion
		Map.Map_Motion();
		Map.Backgrond_Velocity = 30.f;
		Map.Walls_velocity = 150.f;
		Map.Stairs_velocity = Power.PowerUP_veolcity = 70.0f;
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
		for (int i = 0; i < bgNums; i++)
		{
			window.draw(background.bg[i]);
		}
		for (int i = 0; i < floorsnum; i++)
		{
			window.draw(Stairs.floor[i]);
		}
		for (int i = 0; i < bgNums; i++)
		{
			window.draw(background.wallsLeft[i]);
			window.draw(background.wallsRight[i]);
		}
		for (int i = 0; i < stairsNum; i++)
		{
			window.draw(Stairs.stairs[i]);
		}
		if (GameMode == 2)
			window.draw(players.player2);
		window.draw(players.player1);
		if (GameMode == 3)
		{
			for (int i = 0; i < dropBag.size(); i++)
				window.draw(dropBag[i].dropShape);
		}
		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);

			for (int i = 0; i < bgNums; i++)
			{
				window.draw(background.bg[i]);
			}
			for (int i = 0; i < floorsnum; i++)
			{
				window.draw(Stairs.floor[i]);
			}
			for (int i = 0; i < bgNums; i++)
			{
				window.draw(background.wallsLeft[i]);
				window.draw(background.wallsRight[i]);
			}
			window.draw(players.player1);
			window.draw(players.player2);
			for (int i = 0; i < stairsNum; i++)
			{
				window.draw(Stairs.stairs[i]);
			}
		}
		//--------------------------------------------------------------
		window.display();
	}
}
//-------------------------------------------------<<Menues>>---------------------------------------------------//
void menu1(Menu& men1)
{
	men1.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	men1.choises = 6;
	men1.mainmenu[0].setFont(men1.font);
	men1.mainmenu[0].setFillColor(Color{ 255,204,0 });
	men1.mainmenu[0].setString("Play Game");
	men1.mainmenu[0].setCharacterSize(50);
	men1.mainmenu[0].setPosition(Vector2f(1250, men1.height / 2 + 60));

	men1.mainmenu[1].setFont(men1.font);
	men1.mainmenu[1].setFillColor(Color::Black);
	men1.mainmenu[1].setString("Instructions");
	men1.mainmenu[1].setCharacterSize(50);
	men1.mainmenu[1].setPosition(Vector2f(1250, men1.height / 2 + 130));

	men1.mainmenu[2].setFont(men1.font);
	men1.mainmenu[2].setFillColor(Color::Black);
	men1.mainmenu[2].setString("Profile");
	men1.mainmenu[2].setCharacterSize(50);
	men1.mainmenu[2].setPosition(Vector2f(1250, men1.height / 2 + 200));

	men1.mainmenu[3].setFont(men1.font);
	men1.mainmenu[3].setFillColor(Color::Black);
	men1.mainmenu[3].setString("High Score");
	men1.mainmenu[3].setCharacterSize(50);
	men1.mainmenu[3].setPosition(Vector2f(1250, men1.height / 2 + 270));

	men1.mainmenu[4].setFont(men1.font);
	men1.mainmenu[4].setFillColor(Color::Black);
	men1.mainmenu[4].setString("Options");
	men1.mainmenu[4].setCharacterSize(50);
	men1.mainmenu[4].setPosition(Vector2f(1250, men1.height / 2 + 340));

	men1.mainmenu[5].setFont(men1.font);
	men1.mainmenu[5].setFillColor(Color::Black);
	men1.mainmenu[5].setString("Exit");
	men1.mainmenu[5].setCharacterSize(50);
	men1.mainmenu[5].setPosition(Vector2f(1250, men1.height / 2 + 410));
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
	menu2.mainmenu[0].setPosition(Vector2f(1250, menu2.height / 2 + 60));

	menu2.mainmenu[1].setFont(menu2.font);
	menu2.mainmenu[1].setString("Multi");
	menu2.mainmenu[1].setCharacterSize(50);
	menu2.mainmenu[1].setFillColor(Color::Black);
	menu2.mainmenu[1].setPosition(Vector2f(1250, menu2.height / 2 + 130));

	menu2.mainmenu[2].setFont(menu2.font);
	menu2.mainmenu[2].setString("PowerUps");
	menu2.mainmenu[2].setCharacterSize(50);
	menu2.mainmenu[2].setFillColor(Color::Black);
	menu2.mainmenu[2].setPosition(Vector2f(1250, menu2.height / 2 + 200));

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
	menu4.mainmenu[0].setPosition(Vector2f(1250, menu4.height / 2 + 60));

	menu4.mainmenu[1].setFont(menu4.font);
	menu4.mainmenu[1].setFillColor(Color::Black);
	menu4.mainmenu[1].setString("Sound options");
	menu4.mainmenu[1].setCharacterSize(50);
	menu4.mainmenu[1].setPosition(Vector2f(1250, menu4.height / 2 + 130));

	menu4.mainmenu[2].setFont(menu4.font);
	menu4.mainmenu[2].setFillColor(Color::Black);
	menu4.mainmenu[2].setString("Back");
	menu4.mainmenu[2].setCharacterSize(50);
	menu4.mainmenu[2].setPosition(Vector2f(1250, menu4.height / 2 + 200));
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
					menu4.hand.setPosition(1140, 740);
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
	men.choises = 6;

	while (window.isOpen())
	{
		if (pageNumber == 1000)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.key.code == Keyboard::Escape && !pressed && men.selected != 5)
				{
					men.mainmenu[men.selected].setFillColor(Color::Black);
					men.selected = 5;
					men.mainmenu[5].setFillColor(Color{ 255,204,0 });
					men.hand.setPosition(1140, 950);
					pressed = true;
				}

				if (event.key.code == Keyboard::Escape && !pressed && men.selected == 5)
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

						if (men.selected == 5)
							pageNumber = -1;
						if (men.selected == 0)
							Play_menu();
						if (men.selected == 4)
							options_menu();
						if (men.selected == 1)
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
