#pragma once
#include"include.h"
#include <utility> // Include for std::pair
#include <string> // Include for std::string
struct Data {
	string Name;
	int floor;
	int max_compo;
	int min;
	int sec;
};
struct user_data {
	string user_name;
	int  st_lvl2_score = 0, st_lvl3_score = 0, st_lvl4_score = 0, highest_stair, Index;
	float  view_speed2, view_speed3, view_speed4;
};
struct FileSave
{
	pair <int, Data> list[6];
	Texture enternameTX;
	Sprite enternameSP;
	Font playernamefont;
	Text playerNameText;
	string playername;
	string SaveName;
	Text profile;
	Text welcome;
	bool erase = 1;
	Texture highscoreENDtx;
	Sprite highscoreENDsp;
	Texture gameovertx;
	Texture win, lose;
	Sprite winner, losser;
	Sprite gameoversp;
	Text scoreText1, scoreText2, scoreText3, scoreText4;
	Font font;

	int shift = 0;
	bool infile = 0;
	bool boolenter = 0;
	bool press = 0;
	int index;
	int sec, min;
	void filetopair();
	void EnterName();
	void TypeYourName();
	void pairtofile();
	void intopair(int score, int min, int sec);
	void  highscore(RenderWindow& window);
	void highscore_gameover(int Score, int floor, int combo, int shift, int min, int sec);
	void out_file();
	void in_file();
	void into_arr(string username, int stair, int score_lvl2, int score_lvl3, int score_lvl4,
		float vx_lvl2, float vx_lvl3, float vx_lvl4);
	void search(string username);
};
