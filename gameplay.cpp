#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include <vector>
#include <math.h>
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Fullscreen);
Clock clockk;
float dt;
int GameMode;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
const int stairsNum = 400, floorsnum = 9, bgNums = 200;
int pageNumber = 1000;

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
		current_face += 0.008;
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
	/*Texture texture;
	RectangleShape bg;

	void back_ground()
	{
		texture.loadFromFile("Assets/Textures/main menu.png");
		bg.setTexture(&texture);
		bg.setSize(Vector2f(window.getSize()));
	}*/

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
			//player.move(velocity_x * time, 0);

			player1.setScale(1, 1);
			x += 0.01f;
			player1.setTextureRect(IntRect(128 * int(x), 0, 128, 128));
		}
		if (velocity_x < 0)
		{
			//player.move(velocity_x * time, 0);
			player1.setScale(-1, 1);
			x += 0.01f;
			player1.setTextureRect(IntRect(128 * int(x), 0, 128, 128));

		}
		if (velocity_y < 0)
		{
			check_on_ground = false;
		}

		if (x >= 7)
			x = 0;

	}
}players;
struct MAP
{
	RectangleShape bg[bgNums];
	RectangleShape wallsLeft[bgNums], wallsRight[bgNums];
	RectangleShape stairs[stairsNum];
	RectangleShape floor[floorsnum];

	//velocities
	float Walls_velocity, Backgrond_Velocity, Stairs_velocity, view_velocity;

	//positions
	Vector2f StairPosition;
	Vector2f floorPosition;
	int LeftWall_Pos_x, RightWalls_Pos_x, bg_width, floor_width;

	//sizes
	Vector2f size_Of_Stair;
	int Walls_Width = 160;

	//limits
	int RightLimit;
	float limit_of_finalStair_position;

	//counters
	int heightBetweenStair;
	int currstair = 0, currFloor = 0;
	int count_stairs = 0;
	int Background_Index = 0, Wall_Index = 0;
	int previous_Background = bgNums - 1, previous_wall = bgNums - 1;
	int Stairs_OF_EachFloor = 50;

	void intiliztion(Texture& backGround, Texture& stairTexture, Texture& floorTexture, Texture& wallTexture)
	{
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

		for (int i = 0; i < bgNums; i++)
		{
			wallsLeft[i].setTexture(&wallTexture);
			wallsLeft[i].setSize(Vector2f(Walls_Width, 1080));
			wallsLeft[i].setPosition(LeftWall_Pos_x, -i * 1080);

			wallsRight[i].setTexture(&wallTexture);
			wallsRight[i].setSize(Vector2f(Walls_Width, 1080));
			wallsRight[i].setScale(-1, 1);
			wallsRight[i].setPosition(RightWalls_Pos_x, -i * 1080);

			bg[i].setTexture(&backGround);
			bg[i].setSize(Vector2f(bg_width, 1080));
			bg[i].setPosition(LeftWall_Pos_x, -i * 1080);
		}

		//stairs & floors
		limit_of_finalStair_position = 1670;
		heightBetweenStair = 0;
		srand(static_cast<unsigned>(time(NULL)));
		for (int i = 0; i < stairsNum; i++)
		{
			if (count_stairs % Stairs_OF_EachFloor == 0)
			{
				floor[currFloor].setTexture(&floorTexture);
				floor[currFloor].setPosition(floorPosition);
				floor[currFloor].setSize(Vector2f(floor_width, 150));
				floor[currFloor].setPosition(Vector2f(LeftWall_Pos_x, 955 - heightBetweenStair));
				currFloor++;
				heightBetweenStair += 205;
			}
			count_stairs++;
			stairs[i].setTexture(&stairTexture);
			//SET SIZE
			size_Of_Stair = Vector2f((rand() % 300 + 250), 150);
			stairs[i].setSize(size_Of_Stair);
			RightLimit = (RightWalls_Pos_x - Walls_Width) - stairs[i].getSize().x - (1920 - (RightWalls_Pos_x - Walls_Width));

			//SET POSITION
			StairPosition = Vector2f((rand() % RightLimit) + (LeftWall_Pos_x + Walls_Width), 955 - heightBetweenStair);
			stairs[i].setPosition(StairPosition);

			heightBetweenStair += 205;
		}

	}

	void updateStairs(Texture floorr)
	{
		RightLimit = (RightWalls_Pos_x - Walls_Width) - stairs[currstair].getSize().x - (1920 - (RightWalls_Pos_x - Walls_Width));
		bool player2_Notexist = 1;
		if (GameMode == 2)
		{
			if (stairs[currstair].getPosition().y > player2_View.getCenter().y + 540)
				player2_Notexist = 1;
			else
				player2_Notexist = 0;
		}

		if (stairs[currstair].getPosition().y > player1_View.getCenter().y + 540 && player2_Notexist)
		{
			if (count_stairs % Stairs_OF_EachFloor == 0)
			{
				floor[currFloor].setPosition(Vector2f(LeftWall_Pos_x, 955 - heightBetweenStair));
				currFloor++;
				heightBetweenStair += 205;
			}
			StairPosition = Vector2f(rand() % RightLimit + (LeftWall_Pos_x + Walls_Width), 955 - heightBetweenStair);
			stairs[currstair].setPosition(StairPosition);
			currstair++;
			count_stairs++;
			heightBetweenStair += 205;
		}

		currstair %= (stairsNum - 1);
		currFloor %= (floorsnum - 1);
	}
	void updateBackground_And_Walls()
	{
		bool player2_Out_of_Background = 1;
		if (GameMode == 2) // 2player
		{
			if (bg[Background_Index].getPosition().y >= player2_View.getCenter().y + 880)
				player2_Out_of_Background = 1;
			else
				player2_Out_of_Background = 0;
		}
		if (bg[Background_Index].getPosition().y >= player1_View.getCenter().y + 880 && player2_Out_of_Background)
		{
			bg[Background_Index].setPosition(Vector2f(240, bg[previous_Background].getPosition().y - 1080));
			previous_Background = Background_Index;
			Background_Index++;
			if (Background_Index >= bgNums)
			{
				Background_Index = 0;
			}
		}
		bool player2_Out_of_Walls = 1;
		if (GameMode == 2) // 2player
		{
			if (wallsLeft[Wall_Index].getPosition().y >= player2_View.getCenter().y + 880)
				player2_Out_of_Walls = 1;
			else
				player2_Out_of_Walls = 0;
		}
		if (wallsLeft[Wall_Index].getPosition().y >= player1_View.getCenter().y + 880 && player2_Out_of_Walls)
		{
			wallsLeft[Wall_Index].setPosition(Vector2f(0, wallsLeft[previous_wall].getPosition().y - 1080));
			wallsRight[Wall_Index].setPosition(Vector2f(1920, wallsRight[previous_wall].getPosition().y - 1080));
			previous_wall = Wall_Index;
			Wall_Index++;
			if (Wall_Index >= bgNums)
			{
				Wall_Index = 0;
			}
		}

	}
	bool move = 0;
	void Map_Motion(float dt)
	{
		if (players.player1.getPosition().y < 100 || players.player2.getPosition().y < 100)
			move = 1;
		if (move)
		{
			for (int i = 0; i < bgNums; i++)
			{
				bg[i].move(0, Backgrond_Velocity * dt);
				wallsRight[i].move(0, Walls_velocity * dt);
				wallsLeft[i].move(0, Walls_velocity * dt);
			}
			for (int i = 0; i < stairsNum; i++)
			{
				stairs[i].move(0, Stairs_velocity * dt);
			}
			for (int i = 0; i < floorsnum; i++)
			{
				floor[i].move(0, Stairs_velocity * dt);
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

void Gameplay()
{
	//player
	Texture tex;
	tex.loadFromFile("Assets/Textures/Run.png");
	players.inti(tex);

	//Map
	MAP Map;
	CameraView view;

	//background
	Texture background, wall;
	background.loadFromFile("Assets/Textures/BackGround game1.png");
	wall.loadFromFile("Assets/Textures/wall1.png");

	//stairs
	Texture stairs, floor;
	stairs.loadFromFile("Assets/Textures/Stair.png");
	floor.loadFromFile("Assets/Textures/floor.png");

	//map insilization
	Map.intiliztion(background, stairs, floor, wall);

	//view insilization
	view.view_insilization();

	//int animation_cnt = 0;
	int Background_Index = 0, Wall_Index = 0;
	int previous_Background = bgNums - 1, previous_wall = bgNums - 1;

	/*Clock clock;
	float dt;*/
	bool END = 1;

	while (window.isOpen())
	{
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
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
			{
				pageNumber = 1000;
				window.setView(window.getDefaultView());
				return;
			}
		}
		//camera view
		view.SetView();

		//map update
		Map.updateStairs(floor);
		Map.updateBackground_And_Walls();

		//map Motion
		Map.Map_Motion(dt);
		Map.Backgrond_Velocity = 30.f;
		Map.Walls_velocity = 150.f;
		Map.Stairs_velocity = 70.f;
		Map.view_velocity = 100;

		//motion of players
		players.velocity_x = 0;
		players.velocity_y = 0;

		//freeze game
		if (players.player1.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && players.player2.getPosition().y > player2_View.getCenter().y + 540))
		{
			Map.Backgrond_Velocity = Map.Walls_velocity = Map.Stairs_velocity = Map.view_velocity = 0;
			END = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && END)
		{
			players.velocity_x = 50;
			players.last_button_pressed = 1;

		}
		if (Keyboard::isKeyPressed(Keyboard::A) && END)
		{
			players.velocity_x = -50;
			players.last_button_pressed = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::W) && END)
		{
			players.velocity_y = -700;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && END)
		{
			players.velocity_y = 400;

		}
		//player2 --------------------------------------------------
		if (GameMode == 2)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && END)
			{
				players.player2.move(0, -700 * dt);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && END)
			{
				players.player2.move(0, 700 * dt);
			}
		}
		//------------------------------------------------------------------

		if (players.last_button_pressed == 1)
		{
			players.player1.setTextureRect(IntRect(0, 0, 128, 128));
		}
		if (players.last_button_pressed == 2)
		{
			players.player1.setScale(-1, 1);
			players.player1.setTextureRect(IntRect(0, 0, 128, 128));
		}
		players.update();

		window.clear();
		window.setView(player1_View);
		for (int i = 0; i < bgNums; i++)
		{
			window.draw(Map.bg[i]);
		}
		for (int i = 0; i < floorsnum; i++)
		{
			window.draw(Map.floor[i]);
		}
		for (int i = 0; i < bgNums; i++)
		{
			window.draw(Map.wallsLeft[i]);
			window.draw(Map.wallsRight[i]);
		}
		for (int i = 0; i < stairsNum; i++)
		{
			window.draw(Map.stairs[i]);
		}
		if (GameMode == 2)
			window.draw(players.player2);
		window.draw(players.player1);
		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);

			for (int i = 0; i < bgNums; i++)
			{
				window.draw(Map.bg[i]);
			}
			for (int i = 0; i < floorsnum; i++)
			{
				window.draw(Map.floor[i]);
			}
			for (int i = 0; i < bgNums; i++)
			{
				window.draw(Map.wallsLeft[i]);
				window.draw(Map.wallsRight[i]);
			}
			window.draw(players.player1);
			window.draw(players.player2);
			for (int i = 0; i < stairsNum; i++)
			{
				window.draw(Map.stairs[i]);
			}
		}
		//--------------------------------------------------------------
		window.display();

	}
}

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

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pageNumber = 1000;
			break;
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
void options_menu()
{
	Menu menu3;
	menu3.Hand_intilization();
	menu3.font.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	menu3.choises = 3;

	menu3.mainmenu[0].setFont(menu3.font);
	menu3.mainmenu[0].setFillColor(Color{ 255,204,0 });
	menu3.mainmenu[0].setString("GFX Options");
	menu3.mainmenu[0].setCharacterSize(50);
	menu3.mainmenu[0].setPosition(Vector2f(1250, menu3.height / 2 + 60));

	menu3.mainmenu[1].setFont(menu3.font);
	menu3.mainmenu[1].setFillColor(Color::Black);
	menu3.mainmenu[1].setString("Sound options");
	menu3.mainmenu[1].setCharacterSize(50);
	menu3.mainmenu[1].setPosition(Vector2f(1250, menu3.height / 2 + 130));

	menu3.mainmenu[2].setFont(menu3.font);
	menu3.mainmenu[2].setFillColor(Color::Black);
	menu3.mainmenu[2].setString("Back");
	menu3.mainmenu[2].setCharacterSize(50);
	menu3.mainmenu[2].setPosition(Vector2f(1250, menu3.height / 2 + 200));
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
					menu3.MoveDown(menu3.selected, menu3.choises);
				if (event.key.code == Keyboard::Up)
					menu3.MoveUp(menu3.selected, menu3.choises);

				if (event.key.code == Keyboard::Enter)
				{
					//if (menu3.selected == 0)   options_menu(bg);
					if (menu3.selected == 2) {
						pageNumber = 1000;
						break;
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pageNumber = 1000;
			break;
		}
		menu_UI.FaceMotion();
		window.clear();
		window.draw(menu_UI.bg);
		for (int i = 0; i < menu3.choises; i++)
		{
			window.draw(menu3.mainmenu[i]);
		}
		window.draw(menu_UI.face);
		window.draw(menu3.hand);
		window.display();
	}
}
void options_menu1()
{
	Menu menu3;
	menu3.Hand_intilization();
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
				/*if (event.KeyPressed && event.key.code == Keyboard::Escape)
					window.close();*/
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
		if (pageNumber == 1000 || pageNumber == 500)
		{
			for (int i = 0; i < men.choises; i++)
			{
				window.draw(men.mainmenu[i]);
			}
		}

		window.draw(men.hand);
		window.display();
	}

}
