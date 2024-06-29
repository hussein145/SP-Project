#include "include.h"
#pragma once
struct Messages
{
	//messages
	Texture messages_tex[2];
	RectangleShape message[2];
	float timer = 10;
	float stop = 0;
	int Bounus = 0;
	int bounus_points;
	bool show = 0, x = 0;
	
	int cnt = 0;
	int appear = 0;
	float rotate = 0.f;
	float zoom = 0.f;
	float cnt_zoom = 1;

	void messages(int shift);
	void update_messages(int compo_cnt);
	void Animation(int num);

};
