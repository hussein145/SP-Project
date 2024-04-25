#include "menu_Bg_and_Face.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

void menu_Bg_and_Face::back_ground(RenderWindow& window)
{
	texture.loadFromFile("Assets/Textures/main menu.png");
	bg.setTexture(&texture);
	bg.setSize(Vector2f(window.getSize()));
}
void menu_Bg_and_Face::FaceMotion(RenderWindow& window)
{

	fa.loadFromFile("Assets/Textures/heads.png");

	face.setTexture(fa);

	face.setScale(2.25, 2.25);
	face.setOrigin(120, 200);
	current_face += 0.008f;
	if (current_face >= 2.999999)
		current_face = 0;
	face.setTextureRect(IntRect(209 * int(current_face), 0, 209, 258));

	if (rotation >= 8)
	{
		porm = true;
	}
	else if (rotation <= -8)
		porm = false;

	if (porm)
		rotation -= 0.5;
	else
		rotation += 0.5;

	if (updown >= 10)
		morp = true;
	else if (updown <= -10)
		morp = false;

	if (morp)
		updown -= 0.5;
	else
		updown += 0.5;

	face.setPosition(1450 - rotation, 460 + updown);
	face.setRotation(rotation);

}
