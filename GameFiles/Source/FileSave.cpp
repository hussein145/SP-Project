#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Sounds.h"
#include "FileSave.h"

extern Event event;
bool press = 0;
void FileSave::TypeYourName()
{
	if (event.type == Event::KeyPressed) {
		press = 1;
	}
	if (event.type == Event::KeyReleased && press) {
		press = 0;
		if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z)
		{
			playername.push_back('A' + event.key.code);

		}
		else if (event.key.code == Keyboard::BackSpace)
		{
			playername.pop_back();
		}
		else if (event.key.code == Keyboard::Space)
		{
			playername.push_back(' ');
		}

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
	fstream file("high score.txt", ios::in);
	if (file.is_open())
	{
		// Check if file is empty
		if (file.peek() == std::ifstream::traits_type::eof()) {
			// File is empty; initialize with default values
			for (int i = 0; i < 5; i++) {
				list[i].second = "NONE";
				list[i].first = 0;
			}
		}
		else {
			// File is not empty; read data
			for (int i = 0; i < 5; i++) {
				file >> list[i].first >> list[i].second;
			}
		}
		file.close();
	}
}

void FileSave::pairtofile()
{
	ofstream file("high score.txt", ios::out);
	if (file.is_open()) {
		for (int i = 0; i < 5; i++) {
			file << list[i].first << "    " << list[i].second << "\n";
		}
		file.close();
	}
	else {
		std::cerr << "Error opening file for writing." << std::endl;
	}
}
void FileSave::intopair(int score)
{
	if (score * 10 > list[4].first)
	{
		list[4].second = playername;
		list[4].first = score * 10;
	}
	sort(list, list + 5);
	reverse(list, list + 5);
}
