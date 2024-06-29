#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Players.h"
#include "PowerUps.h"
#include "GameClock.h"

extern PowerUps Power;
extern Players player1;
extern STAIRS Stairs;
extern Walls_And_Background background;
extern GameClock gameclock;
extern float dt;

PowerUps* dropBag = new PowerUps[100];//stairsNum
//PowerUps Power;
Clock addtimer;
void PowerUps::setDrops()
{
	addtimer.restart();
	velocity_x = 20;
	DropsTex[0].loadFromFile("Assets//Textures//rand.png");
	DropsTex[1].loadFromFile("Assets//Textures//superjump.png");
	DropsTex[2].loadFromFile("Assets//Textures//speed.png");
	DropsTex[3].loadFromFile("Assets//Textures//danger.png");
	DropsTex[4].loadFromFile("Assets//Textures//heart.png");
	counter_font.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	for (size_t i = 0; i < 5; i++)
	{
		Drops[i].setTexture(DropsTex[i]);
		Drops[i].setOrigin(Drops[i].getScale().x / 2, Drops[i].getScale().y / 2);
	}
	Drops[0].setScale(0.1, 0.1);
	Drops[1].setScale(0.1, 0.1);
	Drops[2].setScale(0.1, 0.1);
	Drops[3].setScale(0.1, 0.1);
	Drops[4].setScale(0.1, 0.1);
	srand(static_cast<unsigned>(time(NULL)));
}
void PowerUps::generateDrop(Vector2f stair_position, bool check){
	float timee;
	int x = 0;
	if (check) {
		timee = addtimer.getElapsedTime().asMilliseconds();
		x = rand() % 6;
	}

	else {
		timee = addtimer.getElapsedTime().asSeconds();
		x = rand() % 4 + 7;
	}
	//cout << timee << endl;
	if (timee >= x)
	{
		int indexDrop = rand() % 5;
		//PowerUps Powerup;
		Power.dropShape = Drops[indexDrop];
		Power.dropShape.setPosition(stair_position.x, stair_position.y - 30);
		Power.type = indexDrop;
		dropBag[Stairs.currstair] = Power;
		addtimer.restart();
	}
}
void PowerUps::dropcollision()
{
	if (!skip)
		for (int i = 0; i < Stairs.stairsNum; i++)
		{
			if (player1.character.getGlobalBounds().intersects(dropBag[i].dropShape.getGlobalBounds()))
			{
				player1.droptype = dropBag[i].type;
				dropBag[i].dropShape.setScale(0, 0);
				if (player1.droptype == 0){
					if (rand() % 2)  velocity_x = 20;
					else  velocity_x = -20;
					directionOfVelocity = velocity_x;
					counter.setFont(counter_font);
					counter.setPosition(960, 50);
					square.setFillColor(Color::Black);
					square.setSize(Vector2f(80, 80));
					square.setPosition(940, 55);
					//counter.setCharacterSize(50);
					counter.setScale(2, 2);
					counter.setFillColor(Color::Red);
					countdowntime = seconds(13);
					countdownClock.restart();
				}
				rando = rand() % 2;
			}
		}
}
void PowerUps::checkdrop(bool& start, bool& StartReturning) {
	
	if (player1.droptype == 0){
		Stairs.distanceOfMove = 100;
		skip = 1;
		start = 1;
		if (elapsedTime.asSeconds() <= 5)
		{
			for (int i = 0; i < Stairs.stairsNum; i++)
			{
				if (Stairs.stairs[i].getPosition().x > 960)
					Stairs.stairs[i].move(-velocity_x * dt, 0);
				else if (Stairs.stairs[i].getPosition().x < 960)
					Stairs.stairs[i].move(velocity_x * dt, 0);
			}
			for (int i = 0; i < background.bgNums; i++)
			{
				background.wallsLeft[i].move(velocity_x * dt, 0);
				background.wallsRight[i].move(-velocity_x * dt, 0);
			}
			gameclock.clock.move(velocity_x * dt, 0);
		}
		else if (elapsedTime.asSeconds() > 5 && elapsedTime.asSeconds() < 8)
		{
			velocity_x = 0;
		}
		else if (elapsedTime.asSeconds() >= 8)
		{
			StartReturning = 1;
			velocity_x = -directionOfVelocity;
			TimeOfMove.restart();
			elapsedTime = TimeOfMove.getElapsedTime();
			pausedTime = TimeOfMove.getElapsedTime();
		}
		if (elapsedTime.asSeconds() >= 5 && StartReturning)
		{
			StartReturning = 0;
			player1.droptype = -1;
			start = 0;
			velocity_x = 20;
			skip = 0;
			Stairs.distanceOfMove = 0;
			counter.setScale(0,0);
			square.setSize(Vector2f(0, 0));
		}
		counter.setString(to_string(calculate));
		fetchTime = countdownClock.restart();
		countdowntime -= fetchTime;
		calculate = countdowntime.asSeconds();
	}
	else if (player1.droptype == 1)
	{
		player1.addsuperjump = 5;
		player1.superjump = 1.5;
	}
	else if (player1.droptype == 2)
	{
		player1.addspeed = 7;
		player1.incspeed = 1.5;
	}
	else if (player1.droptype == 3)
	{
		mapspeed += 100;
		addmapspeed = 7;
	}
	else if (player1.droptype == 4)
	{
		if (rando)
		{
			stopsmall = 7;
			for (int currstair = 0; currstair < Stairs.stairsNum; currstair++)
			{
				if (currstair % 100 != 0 || currstair % 5 != 0) {
					Stairs.stairs[currstair].setSize(Stairs.stairs[currstair].getSize() - Vector2f(50, 0));
				}
			}
			player1.droptype = -1;
		}
		else if (player1.check_on_ground)
		{
			int changable_stair = player1.curr_colission;
			for (int i = 0; i < 5; i++)
			{
				Stairs.stairs[changable_stair].setTexture(&Stairs.floorTexture[0]);
				Stairs.stairs[changable_stair].setOrigin(Stairs.floor_width / 2, 0);
				Stairs.stairs[changable_stair].setSize(Vector2f(Stairs.floor_width, 50));
				Stairs.stairs[changable_stair].setPosition(960, Stairs.stairs[changable_stair].getPosition().y);
				changable_stair++;
				changable_stair %= Stairs.stairsNum;
			}
			player1.droptype = -1;
		}
	}
}
void PowerUps::resetPowerups()
{
	if (player1.addspeed <= 0) {
		player1.addspeed = 0;
		player1.incspeed = 1;
	}
	else {
		player1.addspeed -= 0.01;
		if (player1.droptype == 2)
			player1.droptype = -1;
	}

	if (player1.addsuperjump <= 0) {
		player1.addsuperjump = 0;
		player1.superjump = 1;
	}
	else {
		player1.addsuperjump -= 0.005;
		if (player1.droptype == 1)
			player1.droptype = -1;
	}

	if (addmapspeed <= 0)
	{
		mapspeed = 0;
		addmapspeed = 0;
	}
	else
	{
		addmapspeed -= 0.01;
		if (player1.droptype == 3)
			player1.droptype = -1;
	}
	if (stopsmall < 0) {
		stopsmall = 0;
		for (int currstair = 0; currstair < Stairs.stairsNum; currstair++)
		{
			if (currstair % 100 != 0 || currstair % 5 != 0)
				Stairs.stairs[currstair].setSize(Stairs.stairs[currstair].getSize() + Vector2f(50, 0));
		}
	}
	else {
		if (stopsmall != 0)
			stopsmall -= 0.01;
	}

}
