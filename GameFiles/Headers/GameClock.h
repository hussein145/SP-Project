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
	Texture herry;
	Sprite herry2;
	bool f = 0;
	void setclock();
	void update_clock();
};

