#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Players.h"
#include "PowerUps.h"
#include "GameClock.h"
using namespace std;
using namespace sf;

extern float dt;
extern int GameMode;
extern View player1_View;

void GameClock::setclock()
{
	herry.loadFromFile("Assets\\Textures\\Hurry_Up.png");
	herry2.setTexture(herry);
	herry2.setScale(0, 0);

	clo.loadFromFile("Assets/Textures/clock2.png");
	cl.setTexture(clo);

	clo2.loadFromFile("Assets/Textures/clock 1.png");
	cl2.setTexture(clo2);

	cl2.setOrigin(9.5, 30);
	cl2.setRotation(int(0));
	if (GameMode == 2) {
		cl.setScale(1, 1);
		cl2.setScale(1, 1);
		cl.setPosition(0, 118);
		cl2.setPosition(40, 180);
	}
	else {
		cl.setScale(2, 2);
		cl2.setScale(1.7, 1.7);
		cl.setPosition(230, 118);
		cl2.setPosition(315, 235);
	}
}
void GameClock::update_clock(float &view_velocity)
{
	l += 0.07f + acceleration;
	cl2.setRotation(int(l));

	herry2.move(0, -550 * dt);
	int end = int(l);
	if (end % 360 != 0) {

		f = true;

	}
	if (end % 360 == 0 && f == true) {
		herry2.setPosition(650, player1_View.getCenter().y + 550);
		herry2.setScale(2.5, 2.5);
		view_velocity += 5;
		acceleration += 0.02;
	}
}
