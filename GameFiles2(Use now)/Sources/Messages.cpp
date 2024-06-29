#include "Players.h"
#include "Messages.h"
#include "Sounds.h"

extern Players player1;
extern Sounds sound;
void Messages::messages(int shift)
{
	messages_tex[0].loadFromFile("Assets//Textures//Good.png");
	messages_tex[1].loadFromFile("Assets//Textures//Sweet!.png");

	message[0].setTexture(&messages_tex[0]);
	message[1].setTexture(&messages_tex[1]);

	message[0].setPosition(900 + shift, 600);
	message[1].setPosition(900 + shift, 600);

	Bounus = show = cnt = bounus_points = 0;
	timer = 10;
	message[0].setRotation(int(0));
}
void Messages::update_messages(int compo_cnt)
{
	if (compo_cnt > 1 && cnt != compo_cnt) { //2
		Bounus++; //1 2
		cnt = compo_cnt;

	}
	if (compo_cnt == 0 && Bounus > 1)
	{
		bounus_points += cnt * cnt;
		zoom = 50;
		if (Bounus == 2) {
			sound.Good_sound();
			appear = 1;
		}
		else if (Bounus >= 3) {
			sound.Sweet_sound();
			appear = 2;
		}
		timer = stop = Bounus = rotate = cnt = x = 0;
	}
	else if (compo_cnt == 0)
		Bounus = 0;
}

void Messages::Animation(int num) {
	message[num].setRotation(int(rotate));
	message[num].setSize(Vector2f(zoom, zoom/4));
	message[num].setOrigin(message[num].getSize().x / 2, message[num].getSize().y / 2);

	zoom += cnt_zoom;
	if (!x) {
		rotate += 5.f;
		cnt_zoom = 6;
	}

	else if (x && stop >= 1){
		rotate -= 5.f;
		cnt_zoom = -6;
	}

	if ((int(rotate) >= 360 || x) && stop < 1) {
		stop += 0.01;
		rotate = 0;
		cnt_zoom = 0;
		x = 1;
	}
}