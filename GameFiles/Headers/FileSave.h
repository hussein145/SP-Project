#pragma once
struct FileSave
{
	pair <int, string> list[6];
	Texture enternameTX;
	Sprite enternameSP;
	Font playernamefont;
	Text playerNameText;
	string playername;
	bool infile = 0;
	bool boolenter = 0;

	void filetopair();
	void EnterName();
	void TypeYourName();
	void pairtofile();
	void intopair(int score);
	void  highscore(RenderWindow& window);
};

