#include "Walls_And_Background.h"
#include "STAIRS.h"

void Walls_And_Background::intiliztion(int GameMode, View& player1_View, View& player2_View)
{
	backGround[0].loadFromFile("Assets/Textures/BackGround game1.png");
	backGround[1].loadFromFile("Assets/Textures/BackGround game2.png");

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

		if(Curr_Background % (rand()%4+3) == 0 && Curr_Background!=0)
			bg[Curr_Background].setTexture(&backGround[1]);
		else
			bg[Curr_Background].setTexture(&backGround[0]);
		bg[Curr_Background].setSize(Vector2f(bg_width, 1080));
		bg[Curr_Background].setPosition(LeftWall_Pos_x, -Difference_Between_bg);
		Difference_Between_bg += 1080;
	}
	Curr_Background--;
}
void  Walls_And_Background::updateBackground_And_Walls(int GameMode, View& player1_View, View& player2_View)
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
		bg[update_Background].setPosition(Vector2f(bg[Curr_Background].getPosition().x, bg[Curr_Background].getPosition().y - 1080));
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
		wallsLeft[update_wall_index].setPosition(Vector2f(wallsLeft[Curr_walls].getPosition().x, wallsLeft[Curr_walls].getPosition().y - 1080));
		wallsRight[update_wall_index].setPosition(Vector2f(wallsRight[Curr_walls].getPosition().x, wallsRight[Curr_walls].getPosition().y - 1080));
		Curr_walls = update_wall_index;
		update_wall_index++;
	}
	update_Background %= (bgNums - 1);
	update_wall_index %= (bgNums - 1);
}