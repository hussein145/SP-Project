#pragma once
struct Data {
	string Name;
	int floor ;
	int max_compo ;
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
	std::string playername;
	Texture highscoreENDtx;
	Sprite highscoreENDsp;
	Texture gameovertx;
	Sprite gameoversp;
	Text scoreText1, scoreText2, scoreText3;
	Font font;

	bool infile = 0;
	bool boolenter = 0;
	int index;
	void filetopair();
	void EnterName();
	void TypeYourName();
	void pairtofile();
	void intopair(int score);
	void  highscore(RenderWindow& window);
	void highscore_gameover(int Score, int floor, int combo);
	void out_file();
	void in_file();
	void into_arr(string username, int stair, int score_lvl2, int score_lvl3, int score_lvl4,
		float vx_lvl2, float vx_lvl3, float vx_lvl4);
	void search(string username);
};

