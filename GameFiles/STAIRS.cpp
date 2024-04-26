#include <iostream>
#include <SFML/Graphics.hpp>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
using namespace std;
using namespace sf;

extern Walls_And_Background background;
void generateDrop(Vector2f stair_position, bool check);

void STAIRS::strnum() {
	if (Number_Of_Stair % 10 == 0) {
		Strs10[currstair].setPosition(stairs[currstair].getPosition().x, stairs[currstair].getPosition().y + 30);
		Strs10[currstair].setSize(Vector2f(50, 50));
		Strs10[currstair].setOrigin(Strs10[currstair].getSize().x / 2, 0);

		strTxt[currstair].setFillColor(Color::White);
		strTxt[currstair].setCharacterSize(20);
		strTxt[currstair].setString(to_string(Number_Of_Stair));
		strTxt[currstair].setPosition(Strs10[currstair].getPosition().x, Strs10[currstair].getPosition().y + 15);
	}
}
void STAIRS::StairsTextures()
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
void STAIRS::FloorTextures() {
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
void STAIRS::intiliztion1(int GameMode) {
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
	stairs[0].setPosition(Vector2f(background.LeftWall_Pos_x + floor_width / 2, 955));
	Block_texture.loadFromFile("Assets/Textures/strnum.png");
	Gfont.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	//stairs & floors
	srand(static_cast<unsigned>(time(NULL)));
	for (currstair = 0; currstair < stairsNum; currstair++)
	{
		Strs10[currstair].setTexture(&Block_texture);
		strTxt[currstair].setFont(Gfont);
		if (currstair % Stairs_OF_EachFloor == 0) //50
		{
			//cout << currstair << endl;
			floorTexture[0].loadFromFile("Assets/Textures/floor.png");
			stairs[currstair].setTexture(&floorTexture[0]);
			FloorTextures();
			stairs[currstair].setSize(Vector2f(floor_width, 50));
			stairs[currstair].setOrigin(floor_width / 2, 0);
			if(currstair)
			stairs[currstair].setPosition(Vector2f(background.LeftWall_Pos_x + floor_width / 2, stairs[currstair-1].getPosition().y - heightBetweenStair));
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
			StairPosition = Vector2f((rand() % RightLimit) + (background.LeftWall_Pos_x + background.Walls_Width + stairs[currstair].getSize().x / 2), stairs[currstair - 1].getPosition().y - heightBetweenStair);
			stairs[currstair].setPosition(StairPosition);
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
void STAIRS::updateStairs(int GameMode, View &player1_View, View &player2_View) {
	RightLimit = ((background.RightWalls_Pos_x - distanceOfMove) - background.Walls_Width) - stairs[updatestair].getSize().x - (1920 - ((background.RightWalls_Pos_x - distanceOfMove) - background.Walls_Width));
	bool player2_Notexist = 1;
	if (GameMode == 2)
	{
		if (stairs[updatestair].getPosition().y > player2_View.getCenter().y + 540)
			player2_Notexist = 1;
		else
			player2_Notexist = 0;
	}

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
