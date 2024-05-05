#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
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
extern STAIRS Stairs;
extern int GameMode;

void Players::inti(Texture& texture) {

	floor = compo_cnt = cnt = Max_Compo = curr_colission = 0;
	j = velocity_x = velocity_y = 0;
	int droptype = -1;
	incspeed = superjump = 1,
		addspeed = addsuperjump = 0;

	character.setTexture(texture);
	character.setPosition(500, Stairs.stairs[0].getPosition().y - 30);
	character.setTextureRect(IntRect(0, 0, 50, 60));
	character.setOrigin(25, 30);
	character.setScale(2.4, 2.4);

	font.loadFromFile("Assets//Fonts//BrownieStencil-8O8MJ.ttf");

	score_txt.setFont(font);
	score_txt.setCharacterSize(50);
	score_txt.setPosition(240, 1000);
	compo.setFont(font);
	compo.setPosition(300, 580);

	x = 0;
	check_on_ground = 0;

}

void Players::update() {
	if (GameMode == 2)
		compo.setCharacterSize(30);
	else
		compo.setCharacterSize(50);
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

	if (velocity_y < 0 && velocity_x>0)
	{
		character.setTextureRect(IntRect(50, 60 * 2, 50, 60));
	}
	if (velocity_y < 0 && velocity_x < 0)
	{
		character.setScale(-2.4, 2.4);
		character.setTextureRect(IntRect(50, 60 * 2, 50, 60));
	}
	if (velocity_y < 0 && velocity_x == 0)
	{
		character.setTextureRect(IntRect(0, 60 * 2, 50, 60));
	}
	if (Stairs.stairs[curr_colission].getPosition().x + (Stairs.stairs[curr_colission].getSize().x) / 2 <= character.getPosition().x && check_on_ground) {
		character.setTextureRect(IntRect(50 * int(t), 60 * 3, 50, 60));
		t += 0.02f;
	}
	if (Stairs.stairs[curr_colission].getPosition().x - (Stairs.stairs[curr_colission].getSize().x) / 2 >= character.getPosition().x && check_on_ground) {
		character.setScale(-2.4, 2.4);
		character.setTextureRect(IntRect(50 * int(t), 60 * 3, 50, 60));
		t += 0.02f;
	}
	if (t >= 2)
		t = 0;
	if (x > 3.9)
		x = 0;
}

void Players::Players_Motion(SoundBuffer& buff, Keyboard::Key left, Keyboard::Key right, Keyboard::Key jump) {
	if (GameMode == 2)
		Motion_Velocity = 12;
	else
		Motion_Velocity = 6;
	/*============================================================*/
	if (Keyboard::isKeyPressed(right)) {
		velocity_x += Motion_Velocity * dt * incspeed * 1.05;
		validL = 0;
	}
	else if (Keyboard::isKeyPressed(left)) {
		velocity_x -= Motion_Velocity * dt * incspeed * 1.05;
		validR = 0;
	}
	/*============================================================*/
	if (velocity_x > 0.f && validL) {
		velocity_x -= Motion_Velocity * dt * incspeed + 0.2;
		if (velocity_x < 0.f)
			velocity_x = 0;
	}
	else if (velocity_x < 0.f && validR) {
		velocity_x += Motion_Velocity * dt * incspeed + 0.2;
		if (velocity_x > 0.f)
			velocity_x = 0;
	}
	validL = validR = 1;
	/*================================================================*/
	if (velocity_y > 0 || !check_on_ground) {
		character.setTextureRect(IntRect(50 * 3, 60 * 2, 50, 60));
	}
	if (Keyboard::isKeyPressed(jump) && check_on_ground) {
		velocity_y = -jumpVelocity - addsuperjump;
		if (GameMode == 2)
		{
			if (abs(velocity_x) > 7.5f)
				velocity_y *= abs(velocity_x) / 7.5f;
			//jump_height = velocity_y;
		}
		else
		{
			if (abs(velocity_x) > 4.f)
				velocity_y *= abs(velocity_x) / 4.f;
			//jump_height = velocity_y;
		}
		check_on_ground = false;
		so4.setBuffer(buff);
		so4.play();
	}
	if (check_on_ground) {
		velocity_y = 0;
	}
	else {
		velocity_y += (gravity)*dt;
	}
	/*========================================================================*/
	if (character.getPosition().x - 5 <= background.wallsLeft[0].getPosition().x + background.Walls_Width && j == 0) {
		character.setPosition(background.wallsLeft[0].getPosition().x + background.Walls_Width + 12, character.getPosition().y);
		velocity_x = -velocity_x / 1.5f;
		//j = 1;
	}
	else if (character.getPosition().x + 5 >= background.wallsRight[0].getPosition().x - background.Walls_Width && j == 0)
	{
		character.setPosition(background.wallsRight[0].getPosition().x - background.Walls_Width - 12, character.getPosition().y);
		velocity_x = -velocity_x / 1.5f;
		//j = 1;
	}
	/*if (j) {j += 0.02;}

	if (j >= 3) { j = 0; }*/
}
