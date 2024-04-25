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
		RectangleShape numberedStr;
		Text strNumTxt;
		numberedStr.setPosition(stairs[currstair].getPosition().x, stairs[currstair].getPosition().y + 30);
		numberedStr.setSize(Vector2f(50, 50));
		numberedStr.setOrigin(numberedStr.getSize().x / 2, 0);

		strNumTxt.setFillColor(Color::White);
		strNumTxt.setCharacterSize(20);
		strNumTxt.setString(to_string(Number_Of_Stair));
		//strNumTxt.setOrigin(strNumTxt.getScale().x/2, strNumTxt.getScale().y);
		strNumTxt.setPosition(numberedStr.getPosition().x, numberedStr.getPosition().y + 15);
		Strs10[currstair] = numberedStr;
		strTxt[currstair] = strNumTxt;
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
void STAIRS::updateStairs(int GameMode, View &player1_View, View &player2_View) {
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
