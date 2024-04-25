#pragma once
//#define N 500
struct STAIRS
{
	int stairsNum = 100;
	int Number_Of_Stair = 0;
	RectangleShape stairs[500];
	RectangleShape Strs10[500];
	Text strTxt[500];
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
	int heightBetweenStair = 0;
	int currstair = 0, updatestair = 0;
	int Stairs_OF_EachFloor = 50;

	//stairs intiliztion
	void StairsTextures();
	void FloorTextures();
	void intiliztion1(int GameMode);
	void updateStairs(int GameMode, View &player1_View, View &player2_View);
	void strnum();
};
