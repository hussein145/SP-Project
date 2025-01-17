#include <utility>
#include "menu_Bg_and_Face.h"
#include "Sounds.h"
#include "Players.h"
#include "FileSave.h"
#include "Menu.h"

extern Event event;
extern Sounds sound;
extern Players player1;
extern Menu menu;

extern menu_Bg_and_Face menu_UI;
extern int GameMode;
extern user_data user[5];
void FileSave::highscore_gameover(int score, int floor, int combo, int shift, int min, int sec)
{
	highscoreENDtx.loadFromFile("Assets/Textures/High_Score.png");
	highscoreENDsp.setTexture(highscoreENDtx);
	highscoreENDsp.setPosition(500 + shift, 350);
	highscoreENDsp.setScale(2.5, 2.5);

	gameovertx.loadFromFile("Assets/Textures/gameover.png");
	gameoversp.setTexture(gameovertx);
	gameoversp.setPosition(470 + shift, 180);
	gameoversp.setScale(1.5, 1.5),

		win.loadFromFile("Assets/Textures/winner.png");
	winner.setTexture(win);
	winner.setScale(1.5, 1.5);


	lose.loadFromFile("Assets/Textures/losser.png");
	losser.setTexture(lose);
	losser.setScale(1.5, 1.5);

	font.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	scoreText1.setFont(font);
	scoreText2.setFont(font);
	scoreText3.setFont(font);
	scoreText4.setFont(font);


	scoreText1.setString("SCORE:   " + to_string(score));
	scoreText2.setString("FLOOR:   " + to_string(floor));
	scoreText3.setString("BEST COMBO:   " + to_string(combo));
	scoreText4.setString("TIME:   " + to_string(min) + " : " + to_string(sec));

	//scoreText3.setString()
	scoreText1.setPosition(600 + shift, 600);
	scoreText2.setPosition(600 + shift, 700);
	scoreText3.setPosition(600 + shift, 800);
	scoreText4.setPosition(600 + shift, 900);

	scoreText1.setCharacterSize(70);
	scoreText2.setCharacterSize(70);
	scoreText3.setCharacterSize(70);
	scoreText4.setCharacterSize(70);

	scoreText1.setFillColor(Color::White);
	scoreText2.setFillColor(Color::White);
	scoreText3.setFillColor(Color::White);
	scoreText4.setFillColor(Color::White);
}
void  FileSave::highscore(RenderWindow& window)
{
	Texture profiltex;
	profiltex.loadFromFile("Assets/Textures/Capture.png");
	Sprite profilesp;
	profilesp.setTexture(profiltex);
	profilesp.setPosition(500, 0);
	profilesp.setScale(2.5, 2.5);
	Font hisfont, font2;
	hisfont.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	font2.loadFromFile("Assets/Fonts/Freedom-10eM.ttf");
	Text SCOREtext[6], NAMEFORSCOREtext[6], FLOORtext[6], NAMEFORFLOORtext[6], NAMEFORCOMBOtext[6], COMBOtext[6], mins[6], secs[6], timeText[6], bestscore, bestfloor, bestcombo, Time;

	bestscore.setFont(font2);
	bestfloor.setFont(font2);
	bestcombo.setFont(font2);
	Time.setFont(font2);

	bestscore.setPosition(600, 150);
	bestfloor.setPosition(600, 450);
	bestcombo.setPosition(600, 750);
	Time.setPosition(1070, 170);

	bestscore.setCharacterSize(50);
	bestfloor.setCharacterSize(50);
	bestcombo.setCharacterSize(50);
	Time.setCharacterSize(40);

	bestscore.setFillColor(Color::Black);
	bestfloor.setFillColor(Color::Black);
	bestcombo.setFillColor(Color::Black);
	Time.setFillColor(Color::Black);

	bestscore.setString("BEST SCORES ");
	bestfloor.setString("HIGHEST FLOORS ");
	bestcombo.setString("BEST COMBO  ");
	Time.setString("TIME ");

	for (int i = 0; i < 5; i++)
	{
		SCOREtext[i].setFont(hisfont);
		SCOREtext[i].setCharacterSize(30);
		SCOREtext[i].setFillColor(Color::Black);

		NAMEFORSCOREtext[i].setFont(hisfont);
		NAMEFORSCOREtext[i].setCharacterSize(30);
		NAMEFORSCOREtext[i].setFillColor(Color::Black);

		FLOORtext[i].setFont(hisfont);
		FLOORtext[i].setCharacterSize(30);
		FLOORtext[i].setFillColor(Color::Black);

		NAMEFORFLOORtext[i].setFont(hisfont);
		NAMEFORFLOORtext[i].setCharacterSize(30);
		NAMEFORFLOORtext[i].setFillColor(Color::Black);

		COMBOtext[i].setFont(hisfont);
		COMBOtext[i].setCharacterSize(30);
		COMBOtext[i].setFillColor(Color::Black);

		NAMEFORCOMBOtext[i].setFont(hisfont);
		NAMEFORCOMBOtext[i].setCharacterSize(30);
		NAMEFORCOMBOtext[i].setFillColor(Color::Black);

		mins[i].setFont(hisfont);
		mins[i].setCharacterSize(30);
		mins[i].setFillColor(Color::Black);

		secs[i].setFont(hisfont);
		secs[i].setCharacterSize(30);
		secs[i].setFillColor(Color::Black);

		timeText[i].setFont(hisfont);
		timeText[i].setCharacterSize(30);
		timeText[i].setFillColor(Color::Black);
	}
	filetopair();
	for (size_t i = 0; i < 5; i++)
	{
		string scoreStr[5];
		scoreStr[i] = to_string(list[i].first);
		SCOREtext[i].setString(scoreStr[i]);
		SCOREtext[i].setPosition(900, 200 + ((i + 1) * 45));

		NAMEFORSCOREtext[i].setString(list[i].second.Name);
		NAMEFORSCOREtext[i].setPosition(600, 200 + ((i + 1) * 45));

		string floorStr[5];
		floorStr[i] = to_string(list[i].second.floor);
		FLOORtext[i].setString(floorStr[i]);
		FLOORtext[i].setPosition(900, 500 + ((i + 1) * 45));

		NAMEFORFLOORtext[i].setString(list[i].second.Name);
		NAMEFORFLOORtext[i].setPosition(600, 500 + ((i + 1) * 45));

		string COMBOStr[5];
		COMBOStr[i] = to_string(list[i].second.max_compo);
		COMBOtext[i].setString(COMBOStr[i]);
		COMBOtext[i].setPosition(900, 800 + ((i + 1) * 45));

		NAMEFORCOMBOtext[i].setString(list[i].second.Name);
		NAMEFORCOMBOtext[i].setPosition(600, 800 + ((i + 1) * 45));

		string minStr[5];
		minStr[i] = to_string(list[i].second.min);
		mins[i].setString(minStr[i]);
		mins[i].setPosition(1100, 200 + ((i + 1) * 45));

		string secStr[5];
		secStr[i] = to_string(list[i].second.sec);
		secs[i].setString(secStr[i]);
		secs[i].setPosition(1140, 200 + ((i + 1) * 45));

		timeText[i].setString(":");
		timeText[i].setPosition(1125, 200 + ((i + 1) * 45));
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			sound.select_option_Sound();
			//menu.pageNumber = 1000;
			return;
		}

		window.clear();
		window.draw(menu_UI.bg);
		window.draw(profilesp);
		window.draw(bestscore);
		window.draw(bestfloor);
		window.draw(bestcombo);
		window.draw(Time);
		for (int i = 0; i < 5; i++)
		{
			window.draw(SCOREtext[i]);
			window.draw(NAMEFORSCOREtext[i]);
			window.draw(FLOORtext[i]);
			window.draw(NAMEFORFLOORtext[i]);
			window.draw(COMBOtext[i]);
			window.draw(NAMEFORCOMBOtext[i]);
			window.draw(mins[i]);
			window.draw(secs[i]);
			window.draw(timeText[i]);
		}
		window.display();
	}
}
void FileSave::TypeYourName()
{
	if (erase)
		playername = "";
	erase = 0;
	if (event.type == Event::KeyPressed) {
		press = 1;
		if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z)
		{
			playername.push_back('A' + event.key.code);

		}
		else if (event.key.code == Keyboard::BackSpace)
		{
			if (playername.size())
				playername.pop_back();
		}
		else if (event.key.code == Keyboard::Space)
		{
			playername.push_back(' ');
		}
	}
	if (event.type == Event::KeyReleased && press) {
		press = 0;
		if (event.key.code == Keyboard::Enter)
		{
			welcome.setString("Welcome " + playername);
			search(playername);
			if (index != -1) {
				profile.setString("Profile Is Already Exist");
			}
			else {
				profile.setString("Profile Has Been Created");
			}

			if (!boolenter)
			{
				if (playername.size())
				{
					enternameSP.setPosition(-1000, -1000);
					playerNameText.setPosition(-1000, -1000);
					infile = 1;
					boolenter = 1;
				}
			}
		}
		else if (event.key.code == Keyboard::Escape)
		{
			playername = SaveName;
			enternameSP.setPosition(-1000, -1000);
			playerNameText.setPosition(-1000, -1000);
			infile = 1;
			boolenter = 1;
		}
	}
	playerNameText.setString(playername);
}

void FileSave::out_file() {
	fstream file("user_data.txt", ios::in);
	if (file.is_open())
	{
		// Check if file is empty
		if (file.peek() == std::ifstream::traits_type::eof()) {
			// File is empty; initialize with default values
			for (int i = 0; i < 5; i++) {
				user[i].user_name = "NONE";
				user[i].highest_stair = 0;
				user[i].st_lvl2_score = 0;
				user[i].st_lvl3_score = 0;
				user[i].st_lvl4_score = 0;
				user[i].view_speed2 = 0;
				user[i].view_speed3 = 0;
				user[i].view_speed4 = 0;
			}
		}
		else {
			// File is not empty; read data
			for (int i = 0; i < 5; i++) {
				file >> user[i].user_name >> user[i].highest_stair >> user[i].st_lvl2_score >> user[i].st_lvl3_score >>
					user[i].st_lvl4_score >> user[i].view_speed2 >> user[i].view_speed3 >> user[i].view_speed4;
			}
		}
		file.close();
	}
}
void FileSave::EnterName() {
	enternameTX.loadFromFile("Assets/Textures/entername.png");
	enternameSP.setTexture(enternameTX);
	enternameSP.setPosition(500, 450);
	enternameSP.setScale(2, 2);
	playernamefont.loadFromFile("Assets/Fonts/HalloweenSlimePersonalUse-4B80D.otf");

	playerNameText.setFont(playernamefont);
	playerNameText.setCharacterSize(24);
	playerNameText.setFillColor(sf::Color::Black);
	playerNameText.setPosition(570, 690);

	profile.setFont(playernamefont);
	profile.setCharacterSize(70);
	profile.setFillColor(sf::Color::White);
	profile.setPosition(570, 20);

	welcome.setFont(playernamefont);
	welcome.setCharacterSize(50);
	welcome.setFillColor(sf::Color::White);
	welcome.setPosition(10, 20);

	filetopair();
	out_file();
	boolenter = 0;
	infile = 0;
	press = 0;

}
void FileSave::filetopair() {
	fstream file("Text.txt", ios::in);
	if (file.is_open())
	{
		// Check if file is empty
		if (file.peek() == std::ifstream::traits_type::eof()) {
			// File is empty; initialize with default values
			for (int i = 0; i < 5; i++) {
				list[i].first = 0;
				list[i].second.Name = "NONE";
				list[i].second.floor = 0;
				list[i].second.max_compo = 0;
				list[i].second.min = 0;
				list[i].second.sec = 0;
			}
		}
		else {
			// File is not empty; read data
			for (int i = 0; i < 5; i++) {
				file >> list[i].second.Name >> list[i].first >> list[i].second.floor >> list[i].second.max_compo >> list[i].second.min >> list[i].second.sec;
			}
			//list[i].first
		}
		file.close();
	}
}

void FileSave::pairtofile()
{
	ofstream file("Text.txt", ios::out);
	if (file.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			file << list[i].second.Name << "      " << list[i].first << "      " << list[i].second.floor << "      " << list[i].second.max_compo << "      " << list[i].second.min << "      " << list[i].second.sec << "\n" << "\n";
		}
		file.close();
	}
	else
	{
		cout << "Error opening file for writing." << endl;
	}
}
bool comparePairs(const std::pair<int, Data>& a, const std::pair<int, Data>& b) {
	return a.first > b.first; // Change > to < for ascending order
}
void FileSave::into_arr(string username, int stair, int score_lvl2, int score_lvl3, int score_lvl4,
	float vx_lvl2, float vx_lvl3, float vx_lvl4) {

	bool exist = 0;
	int curr_index;
	for (int i = 0; i < 5; i++) {
		if (user[i].user_name == username) {
			exist = 1;
			curr_index = i;
			if (user[i].highest_stair < stair) {
				user[index].highest_stair = stair;
			}
			user[i].st_lvl2_score = score_lvl2;
			user[i].st_lvl3_score = score_lvl3;
			user[i].st_lvl4_score = score_lvl4;
			user[i].view_speed2 = vx_lvl2;
			user[i].view_speed3 = vx_lvl3;
			user[i].view_speed4 = vx_lvl4;
			break;
		}
		else if (user[i].st_lvl2_score == 0) {
			curr_index = i;
			user[i].user_name = username;
			user[i].highest_stair = stair;
			user[i].st_lvl2_score = score_lvl2;
			user[i].st_lvl3_score = score_lvl3;
			user[i].st_lvl4_score = score_lvl4;
			user[i].view_speed2 = vx_lvl2;
			user[i].view_speed3 = vx_lvl3;
			user[i].view_speed4 = vx_lvl4;
			break;
		}
	}


}

void FileSave::intopair(int score, int minute, int second)
{
	if (score > list[4].first)
	{
		list[4].second.Name = playername;
		list[4].second.floor = player1.floor;
		list[4].second.max_compo = player1.Max_Compo;
		list[4].first = score;
		list[4].second.min = minute;
		list[4].second.sec = second;
	}
	sort(std::begin(list), std::end(list), comparePairs);
}
void FileSave::in_file()
{
	ofstream file("user_data.txt", ios::out);
	if (file.is_open())
	{
		for (int i = 0; i < 5; i++) {
			file << user[i].user_name << " " << user[i].highest_stair << " " << user[i].st_lvl2_score << " " << user[i].st_lvl3_score << " " <<
				user[i].st_lvl4_score << " " << user[i].view_speed2 << " " << user[i].view_speed3 << " " << user[i].view_speed4 << endl;
		}
		file.close();
	}
	else
	{
		cout << "Error opening file for writing." << endl;
	}
}
void FileSave::search(string username) {
	for (int i = 0; i < 5; i++) {
		//cout << user[i].user_name << endl;
		if (user[i].user_name == username) {
			//cout << i;
			index = i;
			break;
		}
		else index = -1;
	}

}
