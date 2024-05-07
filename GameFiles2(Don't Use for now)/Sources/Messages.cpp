#include "Players.h"
#include "Messages.h"

extern Players player1;
void Messages::messages()
{
	messages_tex[0].loadFromFile("Assets//Textures//Good.png");
	messages_tex[1].loadFromFile("Assets//Textures//Sweet!.png");

	message[0].setTexture(messages_tex[0]);
	message[1].setTexture(messages_tex[1]);

	message[0].setPosition(540, 900);
	message[1].setPosition(540, 900);


	message[0].setScale(3, 3);
	message[1].setScale(3, 3);

	Bounus = 0;
	appear = 0;
	show = 0;
}
void Messages::update_messages()
{
	if (player1.compo_cnt > 1 && cnt != player1.compo_cnt) { //2
		Bounus++;
		cnt = player1.compo_cnt;

	}
	else if(player1.compo_cnt == 0 && Bounus == 0) {
		
		appear = 0;
	}
	if (player1.compo_cnt == 0 && Bounus > 0)
	{
		show = 1;
		//if(Bounus )
		
		//meesage good

	}


}
