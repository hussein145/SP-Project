#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Players.h"
using namespace std;
using namespace sf;
extern Clock clockk;
extern float dt;
extern Walls_And_Background background;

void Players::inti(Texture& texture) {
	character.setTexture(texture);
	character.setPosition(500, 850);
	character.setTextureRect(IntRect(0, 0, 50, 60));
	character.setOrigin(25, 30);
	character.setScale(2.4, 2.4);
	score_Tex.loadFromFile("Assets//Fonts//BrownieStencil-8O8MJ.ttf");
	score.setFont(score_Tex);
	score.setCharacterSize(50);
	score.setPosition(240, 1000);

	velocity_x = 0;
	velocity_y = 0;
	x = 0;
	check_on_ground = 0;
	pree = false;
	pree2 = false;
	reflectionR = 0;
	reflectionL = 0;
}

void Players::update() {
	character.move(velocity_x, velocity_y);
	if (velocity_x == 0 && velocity_y == 0) {
		x += 0.02f;
		character.setTextureRect(IntRect(50 * int(x), 0, 50, 60));
	}
	if (velocity_x > 0)
	{
		character.setScale(2.4, 2.4);
		x += 0.02f;
		character.setTextureRect(IntRect(50 * (int)(x), 60, 50, 60));
	}
	if (velocity_x < 0)
	{
		character.setScale(-2.4, 2.4);
		x += 0.02f;
		character.setTextureRect(IntRect(50 * (int)(x), 60, 50, 60));
	}
	if (velocity_y < 0)
	{
		character.setTextureRect(IntRect(0, 60 * 2, 50, 60));
	}
	else if (velocity_y < 0 && Keyboard::isKeyPressed(Keyboard::Right))
	{
		character.setTextureRect(IntRect(50, 60 * 2, 50, 60));
	}
	if (x > 3.9)
		x = 0;
}

void Players::Players_Motion(SoundBuffer& buff, Keyboard::Key left, Keyboard::Key right, Keyboard::Key jump) {
	if (reflectionL <= 0 && reflectionR <= 0) {
		if (Keyboard::isKeyPressed(right)) {
			if (pree2 && !pree) {
				//clockk2.restart();
				//dt2 = 0;
			}
			velocity_x = 710 * dt * incspeed;
			pree = true;
			pree2 = false;
		}
		if (Keyboard::isKeyPressed(left)) {
			if (pree && !pree2) {
				//clockk2.restart();
				//dt2 = 0;
			}
			velocity_x = -710 * dt * incspeed;
			pree2 = true;
			pree = false;
		}
		if (velocity_x == 0 && velocity_y == 0) {
			//clockk2.restart();
			//dt2 = 0;
			pree = false;
			pree2 = false;
			reflectionR = 0;
			reflectionL = 0;
		}
	}
	else {
		if (reflectionL > 0) {
			velocity_x = reflectionL;
			reflectionL--;
		}
		if (reflectionR > 0) {
			velocity_x = -reflectionR;
			reflectionR--;
		}
		pree = false;
		pree2 = false;
	}

	if (velocity_y > 0 || !check_on_ground) {
		character.setTextureRect(IntRect(50 * 3, 60 * 2, 50, 60));
	}
	if (check_on_ground) {
		velocity_y = 0;
	}
	else {
		velocity_y += gravity;
	}
	if (Keyboard::isKeyPressed(jump) && check_on_ground) {

		velocity_y = -jumpVelocity - addsuperjump;
		//cout << velocity_y << " " << dt << endl;
		check_on_ground = false;
		so4.setBuffer(buff);
		so4.play();
		//cout << dt << endl;
	}
	if (character.getPosition().x > background.wallsRight[0].getPosition().x - background.Walls_Width)
	{
		character.setPosition(background.wallsRight[0].getPosition().x - background.Walls_Width - 5, character.getPosition().y);
		reflectionR = abs(velocity_x) - 2;
	}
	if (character.getPosition().x < background.wallsLeft[0].getPosition().x + background.Walls_Width)
	{
		character.setPosition(background.wallsLeft[0].getPosition().x + background.Walls_Width + 5, character.getPosition().y);
		reflectionL = abs(velocity_x) - 2;
	}
}