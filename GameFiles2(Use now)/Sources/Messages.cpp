#include "Players.h"
#include "Messages.h"

extern Players player1;
void Messages::messages()
{
	messages_tex[0].loadFromFile("Assets//Textures//Good.png");
	messages_tex[1].loadFromFile("Assets//Textures//Sweet!.png");

	message[0].setTexture(messages_tex[0]);
	message[1].setTexture(messages_tex[1]);

	message[0].setPosition(700, 700);
	message[1].setPosition(700, 700);


	message[0].setScale(3.5, 3.5);
	message[1].setScale(3, 3);

	Bounus = 0;
	timer1 = timer2 =  10;
	show = 0;
}
void Messages::update_messages()
{
	if (player1.compo_cnt > 1 && cnt != player1.compo_cnt) { //2
		Bounus++; //1 2
		cnt = player1.compo_cnt;

	}
	if (player1.compo_cnt == 0 && Bounus > 0)
	{
		if (Bounus == 2)
			timer1 = 0;
		else if (Bounus >= 3)
			timer2 = 0;
	}


}