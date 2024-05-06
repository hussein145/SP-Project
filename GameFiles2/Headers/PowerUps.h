#pragma once
#include "include.h"
struct PowerUps
{
	PowerUps* dropBag;
	Sprite dropShape;		   // random powerup
	//RectangleShape blockShape; // random block
	int type;				   // drop type
	int PowerUP_veolcity;
	Texture DropsTex[5];
	Sprite Drops[5]; // 0 walls inwards(heart)
	float velocity_x = 20;
	bool skip = 0;
	float stopsmall = 0;
	float mapspeed = 1, addmapspeed = 0;
	int rando;

	Clock TimeOfMove;
	Time elapsedTime;
	Time pausedTime;

	void setDrops();
	void generateDrop(Vector2f stair_position, bool check);
	void dropcollision();
	void checkdrop(bool& start, bool& StartReturning);
	void resetPowerups();
};