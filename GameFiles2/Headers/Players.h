#pragma once
#include "include.h"
struct Players
{
	Font font;

	Text score_txt;
	int score;

	int floor = 0;
	int compo_cnt = 0;
	int cnt = 0;
	int Max_Compo = 0;
	Text compo;

	Sprite character;
	Texture texture;
	bool oveer = 0;
	float j = 0.f;
	float velocity_x = 0;
	float velocity_y = 0;
	float jump_height;
	float Motion_Velocity;
	bool validL = 0, validR = 0;
	float x;
	float t = 0.f;
	bool check_on_ground = 1;
	int curr_colission = 0;
	const float gravity = 17.f;
	const float jumpVelocity = 8.f;

	int droptype = -1;
	float incspeed = 1, addspeed = 0, superjump = 1, addsuperjump = 0;

	Sound so4;

	void inti(Texture& texture);
	void update();
	void Players_Motion(SoundBuffer& buff, Keyboard::Key left, Keyboard::Key right, Keyboard::Key jump);
	bool ss = false;
};
