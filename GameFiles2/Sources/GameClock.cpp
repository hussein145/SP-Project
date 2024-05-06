#include "Players.h"
#include "GameClock.h"
#include "Sounds.h"


extern Players player1, player2;
extern float dt;
extern int GameMode;
extern View player1_View;
extern float resize, resize2;
extern Sounds sound;

void GameClock::View1_SetClock()
{
	if (GameMode == 2)
	{
		clock.setScale(1, 1);
		Hour_hand.setScale(1, 1);
		clock.setPosition(0, 118);
		Hour_hand.setPosition(clock.getPosition().x + 42, clock.getPosition().y + 60);
		power.setPosition(clock.getPosition().x + 32, clock.getPosition().y + 220);
		star.setPosition(clock.getPosition().x, clock.getPosition().y + 230);
		player1.compo.setPosition(star.getPosition().x + 40, star.getPosition().y + 5);
		if (player1.compo_cnt && resize)
		{
			star.setScale(1, 1);
		}
	}
	else
	{
		clock.setScale(2, 2);
		Hour_hand.setScale(1.7, 1.7);
		if (enter) {
			clock.setPosition(230, 118);
			enter = 0;
		}
		power.setPosition(clock.getPosition().x + 65, clock.getPosition().y + 440);
		star.setPosition(clock.getPosition().x, clock.getPosition().y + 450);
		Hour_hand.setPosition(clock.getPosition().x + 85, clock.getPosition().y + 120);
		player1.compo.setPosition(star.getPosition().x + 80, star.getPosition().y + 15);
		if (player1.compo_cnt && resize)
			star.setScale(2, 2);
	}
}

void GameClock::View2_SetClock()
{
	enter = 1;
	clock.setScale(1, 1);
	Hour_hand.setScale(1, 1);
	clock.setPosition(960, 118);
	Hour_hand.setPosition(clock.getPosition().x + 42, clock.getPosition().y + 60);
	star2.setPosition(clock.getPosition().x, clock.getPosition().y + 230);
	power2.setPosition(clock.getPosition().x + 32, clock.getPosition().y + 220);
	player2.compo.setPosition(star2.getPosition().x + 40, star2.getPosition().y + 5);
	if (player2.compo_cnt && resize2)
	{
		star2.setScale(1, 1);
	}
}

void GameClock::setclock()
{
	enter = 1;
	herry.loadFromFile("Assets\\Textures\\Hurry_Up.png");
	herry2.setTexture(herry);
	herry2.setScale(0, 0);

	clock_tex.loadFromFile("Assets/Textures/clock2.png");
	clock.setTexture(clock_tex);

	Hour_hand_tex.loadFromFile("Assets/Textures/clock 1.png");
	Hour_hand.setTexture(Hour_hand_tex);

	star_tex.loadFromFile("Assets/Textures/Star.png");
	star.setTexture(star_tex);
	star2.setTexture(star_tex);

	Hour_hand.setOrigin(9.5, 30);
	Hour_hand.setRotation(int(0));

	power.setFillColor({ 180,3,3 });
	power2.setFillColor({ 180,3,3 });
}
void GameClock::update_clock(float& view_velocity, bool move)
{
	if (move) {
		l += 0.07f;
		Hour_hand.setRotation(int(l));
		herry2.move(0, -550 * dt);
	}
	int end = int(l);
	if (end % 360 != 0) {

		f = true;
	}
	if (end % 360 == 0 && f == true) {
		herry2.setPosition(650, player1_View.getCenter().y + 550);
		herry2.setScale(2.5, 2.5);
		view_velocity += 5;
		sound.clock_ring_sound();
		sound.hurry_up_sound();
	}
}
