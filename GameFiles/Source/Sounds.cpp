#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Sounds.h"
using namespace std;
using namespace sf;

void Sounds::LoadMusic()
{
	buf1.loadFromFile("Assets//Sounds//menu_change.ogg");
	buf2.loadFromFile("Assets//Sounds//menu_choose.ogg");
	buf3.loadFromFile("Assets//Sounds//falling_sound.ogg");
	buf4.loadFromFile("Assets//Sounds//ring.ogg");
	buf5.loadFromFile("Assets//Sounds//hurryup.ogg");
	buf6.loadFromFile("Assets//Sounds//gonna_fall.ogg");

}
void Sounds::music(int n) {

	if (n == 0) {
		bgmusic.openFromFile("Assets//Sounds//ori music.ogg");

	}
	else if (n == 1) {
		bgmusic.openFromFile("Assets//Sounds//backgmusic.ogg");

	}
	/*else if (n == 2) {
		bgmusic.openFromFile("Assets//Sounds//hurryup.ogg");
	}*/
	bgmusic.setLoop(true);
	bgmusic.play();

}
void Sounds::change_option_Sound() {
	so.setBuffer(buf1);
	so.play();
}
void Sounds::select_option_Sound() {
	so2.setBuffer(buf2);
	so2.play();
}
void Sounds::falling_sound() {
	so4.setBuffer(buf3);
	so4.play();
}
void Sounds::clock_ring_sound() {
	so5.setBuffer(buf4);
	so5.play();
}
void Sounds::hurry_up_sound() {
	so6.setBuffer(buf5);
	so6.play();
}
void Sounds::gonna_fall() {
	so7.setBuffer(buf6);
	so7.play();
}
