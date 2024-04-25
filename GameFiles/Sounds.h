#pragma once
struct Sounds
{
	int k = 0;
	Music bgmusic;
	SoundBuffer buf1, buf2;
	Sound so, so2, so3;
	void LoadMusic();
	void music(int n);
	void change_option_Sound();
	void select_option_Sound();
};

