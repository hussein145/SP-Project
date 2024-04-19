#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct menu_Bg_and_Face
{
	Sprite face;
	Texture fa;
	float current_face = 0;
	float rotation = 0;
	bool porm = true;
	float updown = 0;
	bool morp = true;
	Texture texture;
	RectangleShape bg;

	void back_ground(RenderWindow& window);
	void FaceMotion(RenderWindow& window);
	
};

