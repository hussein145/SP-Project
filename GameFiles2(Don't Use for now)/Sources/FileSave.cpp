#include <utility>
#include "menu_Bg_and_Face.h"
#include "Sounds.h"
#include "Players.h"
#include "FileSave.h"

extern Event event;
extern Sounds sound;
extern Players player1;

extern menu_Bg_and_Face menu_UI;
bool press = 0;
void FileSave::highscore_gameover(int score, int floor, int combo)
{

	highscoreENDtx.loadFromFile("Assets/Textures/High_Score.png");
	highscoreENDsp.setTexture(highscoreENDtx);
	highscoreENDsp.setPosition(500, 350);
	highscoreENDsp.setScale(2.5, 2.5);

	gameovertx.loadFromFile("Assets/Textures/gameover.png");
	gameoversp.setTexture(gameovertx);
	gameoversp.setPosition(400, 180);
	gameoversp.setScale(2, 2),

		font.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	scoreText1.setFont(font);
	scoreText2.setFont(font);
	scoreText3.setFont(font);


	scoreText1.setString("SCORE:   " + to_string(score));
	scoreText2.setString("FLOOR:   " + to_string(floor));
	scoreText3.setString("BEST COMBO:   " + to_string(combo));
	//scoreText3.setString()
	scoreText1.setPosition(600, 600);
	scoreText2.setPosition(600, 700);
	scoreText3.setPosition(600, 800);

	scoreText1.setCharacterSize(70);
	scoreText2.setCharacterSize(70);
	scoreText3.setCharacterSize(70);

	scoreText2.setFillColor(Color::White);
	scoreText3.setFillColor(Color::White);
	scoreText1.setFillColor(Color::White);

}
void  FileSave::highscore(RenderWindow& window)
{
	Texture profiltex;
	profiltex.loadFromFile("Assets/Textures/Capture.png");
	RectangleShape profilesp;
	profilesp.setTexture(&profiltex);
	profilesp.setPosition(100, 0);
	profilesp.setSize(Vector2f(1700, 1000));
	Font hisfont;
	hisfont.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	Text text[6], text2[6], text3[6], text4[6];
	for (int i = 0; i < 5; i++)
	{
		text[i].setFont(hisfont);
		text[i].setCharacterSize(30);
		text[i].setFillColor(Color::Black);
		text2[i].setFont(hisfont);
		text2[i].setCharacterSize(30);
		text2[i].setFillColor(Color::Black);
		text3[i].setFont(hisfont);
		text3[i].setCharacterSize(30);
		text3[i].setFillColor(Color::Black);
		text4[i].setFont(hisfont);
		text4[i].setCharacterSize(30);
		text4[i].setFillColor(Color::Black);

	}
	filetopair();
	for (size_t i = 0; i < 5; i++)
	{
		string scoreStr[5];
		scoreStr[i] = to_string(list[i].first);
		text[i].setString(scoreStr[i]);
		text[i].setPosition(500, 200 + ((i + 1) * 35));
		text2[i].setString(list[i].second.Name);
		text2[i].setPosition(250, 200 + ((i + 1) * 35));
		string floorStr[5];
		floorStr[i] = to_string(list[i].first / 10);
		text3[i].setString(floorStr[i]);
		text3[i].setPosition(500, 550 + ((i + 1) * 35));
		text4[i].setString(list[i].second.Name);
		text4[i].setPosition(250, 550 + ((i + 1) * 35));

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
		for (int i = 0; i < 5; i++)
		{
			window.draw(text[i]);
			window.draw(text2[i]);
			window.draw(text3[i]);
			window.draw(text4[i]);
		}
		window.display();
	}



}
void FileSave::TypeYourName()
{
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
			if (!boolenter)
			{

				enternameSP.setPosition(-1000, -1000);
				playerNameText.setPosition(-1000, -1000);
				infile = 1;
				boolenter = 1;
			}
		}
	}
	playerNameText.setString(playername);
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
	filetopair();


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
			}
		}
		else {
			// File is not empty; read data
			for (int i = 0; i < 5; i++) {
				file >> list[i].second.Name >> list[i].first >> list[i].second.floor >> list[i].second.max_compo;
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
			file << list[i].second.Name << "    " << list[i].first << "    " << list[i].second.floor << "    " << list[i].second.max_compo << "\n";
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
void FileSave::intopair(int score)
{
	if (score > list[4].first)
	{
		list[4].second.Name = playername;
		list[4].second.floor = player1.floor;
		list[4].second.max_compo = player1.Max_Compo;
		list[4].first = score;
	}
	sort(std::begin(list), std::end(list), comparePairs);
}
