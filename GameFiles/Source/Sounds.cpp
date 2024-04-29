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
}
void Sounds::music(int n) {

	if (n == 0) {
		bgmusic.openFromFile("Assets//Sounds//ori music.ogg");
	}
	else if (n == 1) {
		bgmusic.openFromFile("Assets//Sounds//backgmusic.ogg");
	}
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
