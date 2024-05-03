#pragma once
struct GameClock
{
	Texture clock_tex;
	Sprite clock;
	Texture Hour_hand_tex;
	Sprite Hour_hand;
	bool enter = 1;

	float velocity_cl = 0;
	float velocity_clo2 = 0;

	float l = 0;
	Texture herry;
	Sprite herry2;
	RectangleShape power;
	RectangleShape power2;

	Sprite star;
	Sprite star2;
	Texture star_tex;

	bool f = 0;
	void setclock();
	//void setclock2();
	float save_view_velocity;
	void update_clock(float& view_velocity, bool move);
	void View1_SetClock();
	void View2_SetClock();
};
