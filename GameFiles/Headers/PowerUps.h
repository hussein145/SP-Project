#pragma once
struct PowerUps
{
	Sprite dropShape;		   // random powerup
	//RectangleShape blockShape; // random block
	int type;				   // drop type
	int PowerUP_veolcity;
	Texture DropsTex[5];
	Sprite Drops[5]; // 0 walls inwards(heart)
	float velocity_x = 20;
	bool skip = 0;
	float stopsmall = 0, stopbig = 0;
	int rando;

	void setDrops();
	void generateDrop(Vector2f stair_position, bool check);
	void dropcollision();
	void checkdrop(Clock& timerOfMove, bool& start, bool& StartReturning);
	void resetPowerups();
};



