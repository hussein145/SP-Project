#pragma once
#include "include.h"
struct Sounds
{
	int k = 0;
	Music bgmusic;
	sf::SoundBuffer buf1, buf2, buf3, buf4, buf5, buf6;
	Sound so, so2, so3, so4, so5, so6, so7;
	void LoadMusic();
	void music(int n);
	void change_option_Sound();
	void select_option_Sound();
	void falling_sound();
	void clock_ring_sound();
	void hurry_up_sound();
	void gonna_fall();

};

