#include "Players.h"
#include "GameClock.h"
#include "Sounds.h"


extern Players player1, player2;
extern float dt;
extern int GameMode;
extern View player1_View;
extern float resize, resize2;
extern Sounds sound;

void GameClock::Set_Textures() {

	herry.loadFromFile("Assets\\Textures\\Hurry_Up.png");
	clock_tex.loadFromFile("Assets/Textures/clock2.png");
	Hour_hand_tex.loadFromFile("Assets/Textures/clock 1.png");
	star_tex.loadFromFile("Assets/Textures/Star.png");
	herry2.setTexture(herry);
	clock.setTexture(clock_tex);
	Hour_hand.setTexture(Hour_hand_tex);
	star.setTexture(star_tex);
	clock.setPosition(230, 118);
	herry2.setScale(0, 0);
}
void GameClock::setclock(int position, float sizeOfClock, Vector2f HourHand_pos, Vector2f Power_pos, Vector2f compo_pos, int star_pos, Players &player)
{
	Hour_hand.setOrigin(9.5, 30);
	Hour_hand.setRotation(int(0));

	power.setFillColor({ 180,3,3 });

	clock.setScale(sizeOfClock, sizeOfClock);
	Hour_hand.setScale(sizeOfClock, sizeOfClock);
	if(GameMode != 3)
		clock.setPosition(position, 118);
	Hour_hand.setPosition(clock.getPosition().x + HourHand_pos.x, clock.getPosition().y + HourHand_pos.y);
	power.setPosition(clock.getPosition().x + Power_pos.x, clock.getPosition().y + Power_pos.y);
	star.setPosition(clock.getPosition().x, clock.getPosition().y + star_pos);
	player.compo.setPosition(star.getPosition().x + compo_pos.x, star.getPosition().y + compo_pos.y);
}
void GameClock::update_clock(float& view_velocity, bool move, int position_hurryUp)
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
		herry2.setPosition(position_hurryUp, 1080);
		herry2.setScale(2.5, 2.5);
		view_velocity += 5;
		sound.clock_ring_sound();
		sound.hurry_up_sound();
	}
}
