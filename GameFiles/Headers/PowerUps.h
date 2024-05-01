#pragma once
struct PowerUps
{
	PowerUps* dropBag;
	Sprite dropShape;		   // random powerup
	//RectangleShape blockShape; // random block
	int type;				   // drop type
	int PowerUP_veolcity;
	Texture DropsTex[4];
	Sprite Drops[4]; // 0 walls inwards(heart)
	float velocity_x = 20;
	bool skip = 0;

	void setDrops();
	void generateDrop(Vector2f stair_position, bool check);
	void dropcollision();
	void checkdrop(Clock& timerOfMove, bool& start, bool& StartReturning);
	void resetPowerups();
};



