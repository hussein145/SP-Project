#pragma once
struct GameClock
{
	Texture clo;
	Sprite cl;
	Texture clo2;
	Sprite cl2;
	float velocity_cl = 0;
	float velocity_clo2 = 0;

	float l = 0;
	float acceleration = 0;
	Texture herry;
	Sprite herry2;

	Sprite star;
	Texture star_tex;

	bool f = 0;
	void setclock();
	//void setclock2();
	void update_clock(float& view_velocity);
	float save_view_velocity;
};

