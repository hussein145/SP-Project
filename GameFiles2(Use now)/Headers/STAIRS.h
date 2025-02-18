#pragma once
#include "include.h"
struct STAIRS
{
	sf::Texture Block_texture;
	sf::Font Gfont;

	int x;
	int stairsNum;
	int Number_Of_Stair = 0;
	sf::RectangleShape* stairs;
	sf::RectangleShape* Strs10;
	Text* strTxt;

	Texture stairTexture[3], floorTexture[3];

	//positions
	int distanceOfMove = 0;
	Vector2f StairPosition;
	//sizes
	Vector2f size_Of_Stair;
	int floor_width;

	//limit of stairs positions
	int RightLimit;

	//counters
	int heightBetweenStair = 195;
	int currstair = 0, updatestair = 0;
	int Stairs_OF_EachFloor = 50;

	//stairs intiliztion
	void Textures();
	void StairsTextures();
	void FloorTextures();
	void intiliztion1(int GameMode);
	void updateStairs(int GameMode, View &player1_View, View &player2_View);
	void strnum();
};

