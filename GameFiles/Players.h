#pragma once
struct Players
{
	int Score = 0;
	Sprite character;
	Texture texture;
	float velocity_x;
	float velocity_y;
	float x;
	bool check_on_ground = 1;
	int curr_colission = 0;
	const float gravity = 4.0f;
	const float jumpVelocity = 900.0f;
	bool pree;
	bool pree2;
	int reflectionR;
	int reflectionL;
	const float Ground = 900;
	const float Right_wall = 1500;
	const float Left_wall = 450;
	int droptype = -1;
	float incspeed = 1, addspeed = 0, superjump = 1, addsuperjump = 0;
	Sound so4;
	void inti(Texture& texture);
	void update();
	void Players_Motion(SoundBuffer& buff, Keyboard::Key left, Keyboard::Key right, Keyboard::Key jump);
};

