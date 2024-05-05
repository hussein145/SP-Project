#pragma once
struct FileSave
{
	pair <int, string> list[6];
	Texture enternameTX;
	Sprite enternameSP;
	Font playernamefont;
	Text playerNameText;
	string playername;
	Texture highscoreENDtx;
	Sprite highscoreENDsp;
	Text scoreText1, scoreText2, scoreText3;
	Font font;
	bool infile = 0;
	bool boolenter = 0;

	void filetopair();
	void EnterName();
	void TypeYourName();
	void pairtofile();
	void intopair(int score);
	void  highscore(RenderWindow& window);
	void highscoreEND(int score, int floor, int combo);
};

