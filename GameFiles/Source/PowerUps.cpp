#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Players.h"
#include "PowerUps.h"
#include "GameClock.h"
using namespace std;
using namespace sf;

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
	DropsTex[0].loadFromFile("Assets//Textures//heart.png");
	DropsTex[1].loadFromFile("Assets//Textures//speed.png");
	DropsTex[2].loadFromFile("Assets//Textures//superjump.png");
	DropsTex[3].loadFromFile("Assets//Textures//danger.png");
	DropsTex[4].loadFromFile("Assets//Textures//rand.png");
	for (size_t i = 0; i < 5; i++)
	{
		Drops[i].setTexture(DropsTex[i]);
		Drops[i].setOrigin(Drops[i].getScale().x / 2, Drops[i].getScale().y / 2);
	}
	Drops[0].setScale(0.15, 0.15);
	Drops[1].setScale(0.15, 0.15);
	Drops[2].setScale(0.15, 0.15);
	Drops[3].setScale(0.15, 0.15);
	Drops[4].setScale(0.15, 0.15);
}
void PowerUps::generateDrop(Vector2f stair_position, bool check)
{
	float timee;
	if (check)
		timee = addtimer.getElapsedTime().asMilliseconds();
	else
		timee = addtimer.getElapsedTime().asSeconds();

	int x = rand() % 5 + 2;
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
			}
		}
}
void PowerUps::checkdrop(Clock& timerOfMove, bool& start, bool& StartReturning) {
	if (player1.droptype == 0)
	{
		Stairs.distanceOfMove = 100;
		skip = 1;
		start = 1;
		if (timerOfMove.getElapsedTime().asSeconds() <= 5)
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
			
			gameclock.cl.move(velocity_x * dt, 0);
			gameclock.cl2.move(velocity_x * dt, 0);
		}
		else if (timerOfMove.getElapsedTime().asSeconds() > 5 && timerOfMove.getElapsedTime().asSeconds() < 8)
		{
			velocity_x = 0;
		}
		else if (timerOfMove.getElapsedTime().asSeconds() >= 8)
		{
			StartReturning = 1;
			velocity_x = -20;
			timerOfMove.restart();
		}
		if (timerOfMove.getElapsedTime().asSeconds() >= 5 && StartReturning)
		{
			StartReturning = 0;
			player1.droptype = -1;
			start = 0;
			velocity_x = 20;
			skip = 0;
			Stairs.distanceOfMove = 0;
		}
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
	else if (player1.droptype == 4)
	{
		rando = abs(rand() % 2);
		if (rando)
		{
			stopsmall = 7;
			for (int currstair = 0; currstair < Stairs.stairsNum; currstair++)
			{
				if (currstair % 100 != 0 || currstair % 5 != 0) {
					Stairs.stairs[currstair].setSize(Stairs.stairs[currstair].getSize() - Vector2f(50, 0));
				}
			}
		}
		else
		{
			stopbig = 7;
			for (int currstair = 0; currstair < Stairs.stairsNum; currstair++)
			{
				if (currstair % 100 != 0 || currstair % 5 != 0) {
					Stairs.stairs[currstair].setSize(Stairs.stairs[currstair].getSize() + Vector2f(50, 0));
				}
			}
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
		player1.droptype = -1;
	}
	if (player1.addsuperjump <= 0) {
		player1.addsuperjump = 0;
		player1.superjump = 1;
	}
	else {
		player1.addsuperjump -= 0.005;
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
		player1.droptype = -1;
	}
	if (stopbig < 0) {
		stopbig = 0;
		for (int currstair = 0; currstair < Stairs.stairsNum; currstair++)
		{
			if (currstair % 100 != 0 || currstair % 5 != 0)
				Stairs.stairs[currstair].setSize(Stairs.stairs[currstair].getSize() - Vector2f(50, 0));
		}
	}
	else {
		if (stopbig != 0)
			stopbig -= 0.01;
		player1.droptype = -1;
	}
}
