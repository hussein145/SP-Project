#include "include.h"
#pragma once
struct Messages
{
	//messages
	Texture messages_tex[2];
	Sprite message[2];
	float timer1 = 10, timer2 = 10;
	int Bounus = 0;
	bool show = 0;
	int cnt = 0;
	bool cont1 = 0, cont2 = 0;

	void messages();
	void update_messages();

};

