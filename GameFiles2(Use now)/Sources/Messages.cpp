#include "Players.h"
#include "Messages.h"
#include "Sounds.h"

extern Players player1;
extern Sounds sound;
void Messages::messages(int shift)
{
	messages_tex[0].loadFromFile("Assets//Textures//Good.png");
	messages_tex[1].loadFromFile("Assets//Textures//Sweet!.png");

	message[0].setTexture(messages_tex[0]);
	message[1].setTexture(messages_tex[1]);

	message[0].setPosition(700 + shift, 700);
	message[1].setPosition(700 + shift, 700);


	message[0].setScale(3.5, 3.5);
	message[1].setScale(3, 3);

	Bounus = show = cnt = bounus_points = 0;
	timer = 10;
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
		cnt = 0;
		if (Bounus == 2) {
			sound.Good_sound();
			appear = 1;
			timer = 0;
			Bounus = 0;
			cnt = 0;
		}
		else if (Bounus >= 3) {
			sound.Sweet_sound();
			appear = 2;
			timer = 0;
			Bounus = 0;
			cnt = 0;
		}
	}
	else if (compo_cnt == 0)
		Bounus = 0;


}
