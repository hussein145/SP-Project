#include "include.h"
#pragma once
struct Messages
{
	//messages
	Texture messages_tex[2];
	Sprite message[2];
	int appear = 0;
	int Bounus = 0;
	bool show = 0;
	int cnt = 0;

	void messages();
	void update_messages();

};

