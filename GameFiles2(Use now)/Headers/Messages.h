#include "include.h"
#pragma once
struct Messages
{
	//messages
	Texture messages_tex[2];
	Sprite message[2];
	float timer = 10;
	int Bounus = 0;
	int bounus_points;
	bool show = 0;
	int cnt = 0;
	bool cont1 = 0, cont2 = 0;
	int appear = 0;

	void messages();
	void update_messages();

};

