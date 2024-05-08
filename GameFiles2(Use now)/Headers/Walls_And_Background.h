#pragma once
#include "include.h"
struct Walls_And_Background
{
	int x;
	int bgNums;
	sf::Texture backGround[2], wallTexture;

	sf::RectangleShape* bg;
	sf::RectangleShape* wallsLeft;
	sf::RectangleShape *wallsRight;

	int Curr_Background = 0, Curr_walls = 0;
	int update_Background = 0, update_wall_index = 0, Difference_Between_bg = 0;

	int LeftWall_Pos_x, RightWalls_Pos_x, bg_width, floor_width;
	int Walls_Width = 160;

	bool player2_Out_of_Walls = 1;
	bool player2_Out_of_Background = 1;

	void intiliztion(int GameMode, View& player1_View, View &player2_View);
	void updateBackground_And_Walls(int GameMode, View& player1_View, View &player2_View);
		
};

