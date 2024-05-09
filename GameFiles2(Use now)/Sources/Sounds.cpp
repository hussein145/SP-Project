#include "Sounds.h"
extern int PLayer1;
extern int PLayer2;

void Sounds::LoadMusic(int n)
{
	if (n == 1)
		buf1.loadFromFile("Assets//Sounds//menu_change.ogg");
	if (n == 2)
		buf1.loadFromFile("Assets//Sounds//menu_choose.ogg");
	if (n == 3)
		buf1.loadFromFile("Assets//Sounds//falling_sound.ogg");

	buf3.loadFromFile("Assets//Sounds//ring.ogg");
	if (n == 5)
		buf1.loadFromFile("Assets//Sounds//jump.ogg");

	buf2.loadFromFile("Assets//Sounds//hurryup.ogg");
	if (n == 7)
		buf1.loadFromFile("Assets//Sounds//gonna_fall.ogg");
	if (n == 8)
		buf1.loadFromFile("Assets//Sounds//jump_p3.wav");
	if (n == 9)
		buf1.loadFromFile("Assets//Sounds//jump_p4.wav");
	if (n == 10)
		buf1.loadFromFile("Assets//Sounds//edge_p3.wav");
	if (n == 11)
		buf1.loadFromFile("Assets//Sounds//rotate_p3.wav");
	if (n == 12)
		buf1.loadFromFile("Assets//Sounds//rotate_p4.wav");
	if (n == 13)
		buf1.loadFromFile("Assets//Sounds//hello_p3.wav");
	if (n == 14)
		buf1.loadFromFile("Assets//Sounds//hello_p4.wav");
	if (n == 15)
		buf1.loadFromFile("Assets//Sounds//falling_p3.wav");
	if (n == 16)
		buf1.loadFromFile("Assets//Sounds//falling_p4.wav");
	if (n == 17)
		buf1.loadFromFile("Assets//Sounds//start 1.ogg");
	if (n == 18)
		buf1.loadFromFile("Assets//Sounds//flip chr 0.ogg");
	if (n == 19)
		buf1.loadFromFile("Assets//Sounds//flip chr1.ogg");
	if (n == 20)
		buf1.loadFromFile("Assets//Sounds//jump chr 1.ogg");
	if (n == 21)
		buf1.loadFromFile("Assets//Sounds//falling chr1.ogg");
	if (n == 22)
		buf1.loadFromFile("Assets//Sounds//start chr0.ogg");
	if (n == 23)
		buf1.loadFromFile("Assets//Sounds//gameover.ogg");
	if (n == 24)
		buf1.loadFromFile("Assets//Sounds//good.ogg");
	if (n == 25)
		buf1.loadFromFile("Assets//Sounds//cheer.ogg");
	if (n == 26)
		buf1.loadFromFile("Assets//Sounds//sweet.ogg");
	if (n == 27)
		buf1.loadFromFile("Assets//Sounds//edge_p4.wav");
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

	LoadMusic(1);
	so.setBuffer(buf1);
	so.play();
}
void Sounds::rotation_sound() {
	if (PLayer1 == 0 || PLayer1 == 2)
		LoadMusic(18);
	else if (PLayer1 == 1) {
		LoadMusic(19);
	}
	else if (PLayer1 == 3)
		LoadMusic(11);
	else if (PLayer1 == 4)
		LoadMusic(12);

	so9.setBuffer(buf1);
	so9.play();
}
void Sounds::select_option_Sound() {
	LoadMusic(2);
	so2.setBuffer(buf1);
	so2.play();
}
void Sounds::falling_sound() {
	if (PLayer1 == 0 || PLayer1 == 2)
		LoadMusic(3);
	else if (PLayer1 == 1) {
		LoadMusic(21);
	}
	else if (PLayer1 == 3)
		LoadMusic(15);
	else if (PLayer1 == 4)
		LoadMusic(16);

	so4.setBuffer(buf1);
	so4.play();
}
void Sounds::clock_ring_sound() {
	LoadMusic(4);
	so5.setBuffer(buf1);
	so5.play();
}
void Sounds::hurry_up_sound() {
	LoadMusic(5);
	so6.setBuffer(buf2);
	so6.play();
}

void Sounds::gameover() {
	LoadMusic(23);
	so.setBuffer(buf1);
	so.play();
}
void Sounds::gonna_fall() {
	if (PLayer1 == 0 || PLayer1 == 2 || PLayer1 == 1)
		LoadMusic(7);
	else if (PLayer1 == 3)
		LoadMusic(10);
	else if (PLayer1 == 4)
		LoadMusic(27);
	so7.setBuffer(buf1);
	so7.play();
}
void Sounds::jump() {
	if (PLayer1 == 0 || PLayer1 == 2)
		LoadMusic(5);
	else if (PLayer1 == 1)
		LoadMusic(20);
	else if (PLayer1 == 3)
		LoadMusic(8);
	else if (PLayer1 == 4)
		LoadMusic(9);
	so8.setBuffer(buf1);
	so8.play();
}
void Sounds::cheer() {
	LoadMusic(25);
	so13.setBuffer(buf1);
	so13.play();
}
