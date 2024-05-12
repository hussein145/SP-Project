#pragma once
#include"include.h"

struct GameClock
{
	Texture clock_tex;
	Sprite clock;
	Texture Hour_hand_tex;
	Sprite Hour_hand;

	float velocity_cl = 0;
	float velocity_clo2 = 0;

	float l = 0;
	Texture herry;
	Sprite herry2;
	RectangleShape power;

	Sprite star;
	Texture star_tex;

	bool f = 0;
	void Set_Textures();
	void setclock(int position, float sizeOfClock, Vector2f HourHand_pos, Vector2f Power_pos, Vector2f compo_pos, int star_pos, Players &player);
	void update_clock(float& view_velocity, bool move,int position_hurryUp);
	//void View1_SetClock();
	//void View2_SetClock();
};
