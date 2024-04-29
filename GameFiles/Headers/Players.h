#pragma once
struct Players
{
	Font score_Tex;
	Text score;
	int Score = 0;
	Sprite character;
	Texture texture;
	float j = 0.f;
	float velocity_x = 0;
	float velocity_y = 0;
	float Motion_Velocity = 6.f;
	bool validL = 0, validR = 0;
	float x;
	float t = 0.f;
	bool check_on_ground = 1;
	int curr_colission = 0;
	const float gravity = 0.2f;
	const float jumpVelocity = 9.f;
	const float Ground = 900;
	int droptype = -1;
	float incspeed = 1, addspeed = 0, superjump = 1, addsuperjump = 0;
	Sound so4;
	void inti(Texture& texture);
	void update();
	void Players_Motion(SoundBuffer& buff, Keyboard::Key left, Keyboard::Key right, Keyboard::Key jump);
};

