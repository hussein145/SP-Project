#include"include.h"
#include"Menu.h"
#include "menu_Bg_and_Face.h"
#include "Walls_And_Background.h"
#include "STAIRS.h"
#include "Sounds.h"
#include "Players.h"
#include "PowerUps.h"
#include "GameClock.h"
#include "FileSave.h"
#include "Messages.h"

Menu menu;
Walls_And_Background background;
STAIRS Stairs;
Sounds sound;
Players player1; Players player2;
FileSave File;
user_data user[5];
PowerUps Power;
GameClock gameclock;
Messages Good1;
Messages Good2;


RenderWindow window(VideoMode(1920, 1080), "icyTower", Style::Close | Style::Fullscreen);
int GameMode;
Clock clockk, clockk2;
float dt, dt2;
View player1_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
View player2_View(Vector2f(0.f, 0.f), Vector2f(1920, 1080));
bool check1 = 1;

// game time
Font clockFont;
Text clockText;
Time elapsedTime;
bool stopTime = false;
void clockCountIni() {
	clockFont.loadFromFile("Assets/Fonts/BrownieStencil-8O8MJ.ttf");
	clockText.setFont(clockFont);
	clockText.setString("");
	clockText.setCharacterSize(50);
	clockText.setPosition(245, 930);
	clockText.setFillColor(Color::White);
}
void clockCount(Clock clockcnt, Time paused_time) {
	if (check1 == 0) {
		elapsedTime = paused_time;
	}
	else {
		elapsedTime = clockcnt.getElapsedTime() + paused_time;
	}
	int sec = (int)elapsedTime.asSeconds() % 60, min = ((int)elapsedTime.asSeconds() % 3600) / 60;
	if (sec == 60)
		sec = 0;
	if (min == 60)
		min = 0;
	string timeString = "Time:  " + to_string(min) + ":" + to_string(sec);
	clockText.setString(timeString);
}

// stage stars
Sprite star1, star2;
Texture starT1, starT2;
bool go = 0, go2 = 1;
bool whowin;
void starsIntiliztion() {
	starT1.loadFromFile("Assets\\Textures\\newstage.png");
	starT2.loadFromFile("Assets\\Textures\\newstage2.png");
	star1.setTexture(starT1);
	star1.setPosition(350, player1.character.getPosition().y - 700);
	star1.setScale(0.65, 0.8);
	star2.setTexture(starT2);
	star2.setPosition(350, player1.character.getPosition().y - 700);
	star2.setScale(0.4, 0.6);
	go = 0;
	go2 = 1;
}
void starsMove(Players player, View player_view) {
	if ((player.floor % 50 >= 0 && player.floor % 50 <= 8 && player.floor > 40)) {
		star1.move(0, 4);
		star2.move(0, 4);
		go = 1;
	}
	if (go && go2) {

		star1.setPosition(350, player.character.getPosition().y - 700);
		star2.setPosition(350, player1.character.getPosition().y - 700);
		go2 = 0;
	}

	if (star1.getPosition().y > player_view.getCenter().y + 540 && !(player.floor % 50 >= 0 && player.floor % 50 <= 8)) {
		go = 0;
		go2 = 1;
	}
}

void Intilize_Numbers()
{
	if (GameMode == 2) {
		Stairs.stairsNum = 200;
		background.bgNums = 40;
	}
	else {
		Stairs.stairsNum = 50;
		background.bgNums = 20;
	}
}
bool END = 1;
int strCnt = 0;
extern bool pressed;
struct MAP
{
	float Walls_velocity_y, Backgrond_Velocity_y, Stairs_velocity_y, view_velocity;
	//float Walls_velocity_x, Stairs_velocity_x;
	bool move = 0;
	bool enough = 1;
	void intilization()
	{
		Stairs.intiliztion1(GameMode);
		background.intiliztion(GameMode, player1_View, player2_View);
		gameclock.setclock();
	}
	void update()
	{
		Stairs.updateStairs(GameMode, player1_View, player2_View);
		background.updateBackground_And_Walls(GameMode, player1_View, player2_View);
	}
	void Map_Motion()
	{
		if ((player1.character.getPosition().y < 100 || player2.character.getPosition().y < 100) && enough)
		{
			move = 1;
			enough = 0;
		}

		gameclock.update_clock(view_velocity, move);
		if (move)
		{
			for (int i = 0; i < background.bgNums; i++)
			{
				background.bg[i].move(0, Backgrond_Velocity_y * dt);
				background.wallsRight[i].move(0, Walls_velocity_y * dt);
				background.wallsLeft[i].move(0, Walls_velocity_y * dt);
			}
			for (int i = 0; i < Stairs.stairsNum; i++)
			{
				Stairs.stairs[i].move(0, Stairs_velocity_y * dt);
			}
			player2_View.move(0, -view_velocity * dt);
			player1_View.move(0, -view_velocity * dt * Power.mapspeed);
		}
	}
};
void Set_ObjectsOnStairs()
{
	for (int i = 0; i < Stairs.stairsNum; i++)
	{
		Stairs.Strs10[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
		Stairs.strTxt[i].setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y + 30);
		Power.dropBag[i].dropShape.setPosition(Stairs.stairs[i].getPosition().x, Stairs.stairs[i].getPosition().y - 50);
	}
}
struct CameraView
{
	void view_insilization()
	{
		player1_View.setCenter(Vector2f(960, 540));
		if (GameMode == 2)
		{
			player2_View.setCenter(Vector2f(960, 540));
			player1_View.setViewport(FloatRect(0.f, 0.f, 0.49f, 1.f));
			player2_View.setViewport(FloatRect(0.5f, 0.f, 0.5f, 1.f));
		}
		else
		{
			player1_View.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
			player2_View.setViewport(FloatRect(0.f, 0.f, 0.f, 0.f));
		}
	}
	void SetView()
	{
		if (player1.character.getPosition().y < player1_View.getCenter().y - 340)
		{
			player1_View.setCenter(Vector2f(960, player1.character.getPosition().y + 340));
		}
		if (GameMode == 2 && player2.character.getPosition().y < player2_View.getCenter().y - 340)
		{
			player2_View.setCenter(Vector2f(960, player2.character.getPosition().y + 340));
		}
	}
};
//--------------------------------------------------------------------------------------------------
void reset()
{
	Stairs.StairPosition = Stairs.size_Of_Stair = Vector2f(0, 0);
	Stairs.currstair = Stairs.updatestair = Stairs.Number_Of_Stair = 0;
	gameclock.l = 0;
	gameclock.f = 0;

	background.Curr_Background = background.Curr_walls = background.update_Background = background.update_wall_index = background.Difference_Between_bg = 0;
	END = background.player2_Out_of_Background = background.player2_Out_of_Walls = 1;
	delete[] Power.dropBag;
	Power.dropBag = nullptr;

	delete[] Stairs.stairs;
	Stairs.stairs = nullptr;

	delete[] Stairs.Strs10;
	Stairs.Strs10 = nullptr;

	delete[] Stairs.strTxt;
	Stairs.strTxt = nullptr;

	delete[] background.bg;
	background.bg = nullptr;

	delete[] background.wallsLeft, background.wallsRight;
	background.wallsLeft = background.wallsRight = nullptr;

	player1.droptype = -1;
	Power.skip = 0;
}
//---------------------------------------------<<GamePlay Main function>>--------------------------------------------//
void CountScore(Players& player, int i)
{
	if (player.curr_colission > i) {
		if ((player.curr_colission - i) <= 9) { // Fall from stair
			player.floor -= player.curr_colission - i;
			player.cnt = 1;
		}
		else { // Jump and loop repeat itself
			player.cnt = (Stairs.stairsNum - player.curr_colission) + i;
			player.floor += (Stairs.stairsNum - player.curr_colission) + i;
		}
	}
	else { // i > curr_colission (Normal Condition)
		player.cnt = (i - player.curr_colission);
		player.floor += (i - player.curr_colission);
	}
	player.curr_colission = i;
}
void collisions(Players& player)
{
	player.check_on_ground = false;
	if (player.velocity_y >= 0) {
		for (int i = 0; i < Stairs.stairsNum; i++)
		{
			if (player.character.getGlobalBounds().intersects(Stairs.stairs[i].getGlobalBounds()))
			{
				if (player.character.getPosition().y + 25 <= Stairs.stairs[i].getPosition().y)
				{
					player.character.setPosition(player.character.getPosition().x, Stairs.stairs[i].getPosition().y - 60);
					player.check_on_ground = true;
					CountScore(player, i);
					break;
				}
			}
		}
	}
}
void DRAW()
{
	for (int i = 0; i < background.bgNums; i++)
	{
		window.draw(background.bg[i]);
	}
	window.draw(gameclock.herry2);
	for (int i = 0; i < Stairs.stairsNum; i++)
	{
		window.draw(Stairs.stairs[i]);
		window.draw(Stairs.Strs10[i]);
		window.draw(Stairs.strTxt[i]);
		if (GameMode == 3)
		{
			window.draw(Power.dropBag[i].dropShape);
		}
	}
	if (go) {
		window.draw(star1);
		window.draw(star2);
	}
	for (int i = 0; i < background.bgNums; i++)
	{
		window.draw(background.wallsLeft[i]);
		window.draw(background.wallsRight[i]);
	}
}
int arr[4];
void DRAW_View1()
{
	if (GameMode == 2) {
		window.draw(player2.character);
	}
	window.draw(player1.character);
	window.setView(window.getDefaultView());


	gameclock.View1_SetClock();
	window.draw(gameclock.clock);
	window.draw(gameclock.Hour_hand);
	window.draw(gameclock.power);
	window.draw(gameclock.star);

	if (GameMode == 2)
	{
		player1.score_txt.setPosition(30, 990);
	}
	window.draw(player1.score_txt);
	window.draw(player1.compo);
	if (!END)
	{
		File.highscore_gameover(arr[0], arr[1], player1.Max_Compo, -File.shift, File.min, File.sec);
		if (player1.oveer && GameMode != 2)
		{
			window.draw(File.highscoreENDsp);
			window.draw(File.scoreText1);
			window.draw(File.scoreText2);
			window.draw(File.scoreText3);
		}
		else
		{
			if (GameMode == 2 && whowin) {
				File.winner.setPosition(100, 400);
				window.draw(File.winner);
			}
			else if (GameMode == 2 && !whowin) {
				File.losser.setPosition(100, 250);
				window.draw(File.losser);
			}
			else {
				window.draw(File.gameoversp);
			}
			window.draw(File.scoreText1);
			window.draw(File.scoreText2);
			window.draw(File.scoreText3);
			window.draw(File.scoreText4);
		}
	}
	if (Good1.appear == 1 && Good1.timer <= 2) {
		window.draw(Good1.message[0]);
		Good1.timer += 0.008;

	}
	else if (Good1.appear == 2 && Good1.timer <= 2) {
		window.draw(Good1.message[1]);
		Good1.timer += 0.008;
	}

	// game time
	window.draw(clockText);
}
void DRAW_View2()
{
	window.draw(player1.character);
	window.draw(player2.character);

	window.setView(window.getDefaultView());

	gameclock.View2_SetClock();
	window.draw(gameclock.clock);
	window.draw(gameclock.Hour_hand);
	window.draw(gameclock.power2);
	window.draw(gameclock.star2);

	player2.score_txt.setPosition(980, 990);
	window.draw(player2.score_txt);
	window.draw(player2.compo);
	if (!END)
	{
		if (GameMode == 2 && whowin) {
			File.losser.setPosition(1100, 250);
			window.draw(File.losser);
		}
		else if (GameMode == 2 && !whowin) {
			File.winner.setPosition(1100, 400);
			window.draw(File.winner);
		}
		File.highscore_gameover(arr[2], arr[3], player2.Max_Compo, File.shift, File.min, File.sec);
		if (player1.oveer)
		{
			//window.draw(File.highscoreENDsp);
			window.draw(File.scoreText1);
			window.draw(File.scoreText2);
			window.draw(File.scoreText3);
		}
		else
		{
			//window.draw(File.gameoversp);
			window.draw(File.scoreText1);
			window.draw(File.scoreText2);
			window.draw(File.scoreText3);
		}
	}
	if (Good2.appear == 1 && Good2.timer <= 2) {
		window.draw(Good2.message[0]);
		Good2.timer += 0.008;

	}
	else if (Good2.appear == 2 && Good2.timer <= 2) {
		window.draw(Good2.message[1]);
		Good2.timer += 0.008;
	}
}

float resize = 0, resize2 = 0;

void Gameplay()
{
	Intilize_Numbers();
	Stairs.stairs = new RectangleShape[Stairs.stairsNum];
	Stairs.Strs10 = new RectangleShape[Stairs.stairsNum];
	Stairs.strTxt = new Text[Stairs.stairsNum];

	background.bg = new RectangleShape[background.bgNums];
	background.wallsLeft = new RectangleShape[background.bgNums];
	background.wallsRight = new RectangleShape[background.bgNums];

	Power.dropBag = new PowerUps[Stairs.stairsNum];

	SoundBuffer buff;
	buff.loadFromFile("Assets//Sounds//jump.ogg");

	sound.music(1);
	Texture GameTexture;

	MAP Map;
	CameraView view;

	// powerups
	Power.setDrops();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool message = 0;
	bool respawn = 0;
	/////////////////////
	if (GameMode == 2) {
		Good1.messages(-500);
		Good2.messages(500);
	}
	else  Good1.messages(0);
	//////////////////////////
	if (menu.level == 2) {
		respawn = 1;
		Map.view_velocity = user[File.index].view_speed2;
		Good1.bounus_points = user[File.index].st_lvl2_score;
		Stairs.Number_Of_Stair = 50;

	}
	else if (menu.level == 3) {
		respawn = 1;
		Map.view_velocity = user[File.index].view_speed3;
		Good1.bounus_points = user[File.index].st_lvl3_score;
		Stairs.Number_Of_Stair = 100;
	}
	else if (menu.level == 4) {
		respawn = 1;
		Map.view_velocity = user[File.index].view_speed4;
		Good1.bounus_points = user[File.index].st_lvl4_score;
		Stairs.Number_Of_Stair = 100;
	}
	// ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//map insilization
	Map.intilization();

	// new stage starts intiliztion
	starsIntiliztion();

	// game timer
	clockCountIni();
	Clock clockcnt;
	Time paused_time;

	//player
	extern int PLayer1;
	extern int PLayer2;
	Texture tex[5];

	tex[0].loadFromFile("Assets/Textures/icytower1.png");
	tex[1].loadFromFile("Assets/Textures/icytower2.png");
	tex[2].loadFromFile("Assets/Textures/icy_demon1.png");
	tex[3].loadFromFile("Assets/Textures/SpiderMan.png");
	tex[4].loadFromFile("Assets/Textures/Hurry_Potter.png");

	if (PLayer1 == 0)
		player1.inti(tex[0]);
	else if (PLayer1 == 1)
		player1.inti(tex[1]);
	else if (PLayer1 == 2)
		player1.inti(tex[2]);
	else if (PLayer1 == 3)
		player1.inti(tex[3]);
	else if (PLayer1 == 4)
		player1.inti(tex[4]);

	if (PLayer2 == 0)
		player2.inti(tex[2]);
	else if (PLayer2 == 1)
		player2.inti(tex[0]);
	else if (PLayer2 == 2)
		player2.inti(tex[2]);
	else if (PLayer2 == 3)
		player1.inti(tex[3]);
	else if (PLayer2 == 4)
		player1.inti(tex[4]);
	view.view_insilization();

	bool StartMoving = 0;
	bool StartReturning = 0;
	int disapp = 0, disapp2;
	Map.Backgrond_Velocity_y = 20.0f;
	Map.Walls_velocity_y = 120.0f;
	Map.Stairs_velocity_y = 50.0f;
	if (respawn == 0) {
		Map.view_velocity = 80.0f;
	}
	int score_lvl2 = 0, score_lvl3 = 0, score_lvl4 = 0;
	float vx_lvl2 = 0, vx_lvl3 = 0, vx_lvl4 = 0;
	bool alive = true;


	while (window.isOpen())
	{
		/*if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			cout << pos.x << " " << pos.y << endl;
		}*/
		Event Play;
		while (window.pollEvent(Play))
		{
			if (Play.type == Event::Closed)
				window.close();
			if (END ? (Play.key.code == Keyboard::Escape && !pressed) : (Play.type == Event::KeyPressed && !pressed))  //&& !menu.pressed
			{
				pressed = true;
				GameTexture.create(1920, 1080);
				GameTexture.update(window);
				Power.pausedTime = Power.TimeOfMove.getElapsedTime();
				paused_time += clockcnt.getElapsedTime();
				menu.Pause(window, GameTexture);
				clockcnt.restart();
				clockk.restart();

				Power.TimeOfMove.restart();
				if (menu.exit)
				{
					menu.exit = 0;
					sound.music(0);
					reset();
					return;
				}

				if (menu.exit)
				{
					menu.exit = 0;
					sound.music(0);
					reset();
					return;
				}
			}
			if (!Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pressed = false;
			}
		}

		// game time
		clockCount(clockcnt, paused_time);

		// new stage stars move
		starsMove(player1, player1_View);
		starsMove(player2, player2_View);

		if (player1.compo_cnt > 0 && player1.compo_cnt != disapp)
			resize = GameMode == 2 ? 103 : 203;
		else if (player1.compo_cnt == 0)
		{
			resize = 0; disapp = 0;
		}

		if (resize > 0)
		{
			gameclock.power.setOrigin(0, gameclock.power.getSize().y);
			gameclock.power.setSize({ GameMode == 2 ? 18.f : 35.f, resize });
			resize -= GameMode == 2 ? .25 : .5;
		}
		else
			gameclock.power.setSize({ 0,0 });

		disapp = player1.compo_cnt;

		//-------------------------------------------------------------------------------

		if (player2.compo_cnt > 0 && player2.compo_cnt != disapp2)
			resize2 = 103;
		else if (player2.compo_cnt == 0)
		{
			resize2 = 0; disapp2 = 0;
		}

		if (resize2 > 0)
		{
			gameclock.power2.setOrigin(0, gameclock.power2.getSize().y);
			gameclock.power2.setSize({ 18.f, resize2 });
			resize2 -= .25;
		}
		else
			gameclock.power2.setSize({ 0,0 });

		disapp2 = player2.compo_cnt;

		dt = clockk.restart().asSeconds();
		collisions(player1);
		collisions(player2);
		//= ====================================calculate score and compo================================== = //
		player1.score = (player1.floor * 10) + Good1.bounus_points;// + user[0].st_lvl2_score
		player2.score = player2.floor * 10 + Good2.bounus_points;

		player1.score_txt.setString("Score: " + to_string(player1.score));
		player2.score_txt.setString("Score: " + to_string(player2.score));
		if (player1.cnt != 1)
		{
			player1.compo_cnt += player1.cnt;
			player1.cnt = 0;
			player1.Max_Compo = max(player1.compo_cnt, player1.Max_Compo);
		}
		else {
			player1.compo_cnt = 0;
		}
		player1.compo.setString(to_string(player1.compo_cnt));

		if (player2.cnt > 1 || player2.cnt == 0)
		{
			player2.compo_cnt += player2.cnt;
			player2.Max_Compo = max(player2.compo_cnt, player2.Max_Compo);
			player2.compo.setString(to_string(player2.compo_cnt));
		}
		else {
			player2.compo_cnt = 0;
		}
		//= ====================================calculate score and compo================================== = //
		Good1.update_messages(player1.compo_cnt);
		Good2.update_messages(player2.compo_cnt);

		//////////////////////////////////////////////
		Set_ObjectsOnStairs();

		if (GameMode == 3)
		{
			Power.dropcollision();
			//clock
			if (!StartMoving)
			{
				Power.TimeOfMove.restart();
				Power.elapsedTime = Power.TimeOfMove.getElapsedTime();
				Power.pausedTime = Power.TimeOfMove.getElapsedTime();
			}
			Power.elapsedTime = Power.TimeOfMove.getElapsedTime() + Power.pausedTime;

			Power.checkdrop(StartMoving, StartReturning);

			Power.resetPowerups();

		}
		Map.update();
		view.SetView();
		if (player1.floor == 50) {
			score_lvl2 = player1.score;
			vx_lvl2 = Map.view_velocity;

		}
		if (player1.floor == 100) {
			score_lvl3 = player1.score;
			vx_lvl3 = Map.view_velocity;
		}

		if (player1.floor == 150) {
			score_lvl4 = player1.score;
			vx_lvl4 = Map.view_velocity;
		}

		//cout << player2_View.getCenter().x << endl;
		//map Motion
		Map.Map_Motion();
		//=====================================================<<freeze game>>============================================================//
		if ((player1.character.getPosition().y > player1_View.getCenter().y + 550
			|| (GameMode == 2 && player2.character.getPosition().y > player2_View.getCenter().y + 540)) && check1)
		{
			if (GameMode == 2 && player1.character.getPosition().y > player1_View.getCenter().y + 550)
			{
				whowin = false;
			}
			else if (GameMode == 2 && player2.character.getPosition().y > player2_View.getCenter().y + 540) {
				whowin = true;
			}
			check1 = 0;
			if (GameMode == 1) {
				if (player1.score > File.list[0].first) {
					player1.oveer = 1;
				}
				else {
					player1.oveer = 0;
				}
				File.intopair(player1.score);
				File.pairtofile();
				File.into_arr(File.playername, player1.floor, score_lvl2, score_lvl3, score_lvl4, vx_lvl2, vx_lvl3, vx_lvl4);
				File.in_file();
			}

			if (GameMode == 2)
			{
				File.shift = 500;
			}
			else {
				File.shift = 0;
			}
			arr[0] = player1.score;
			arr[1] = player1.floor;
			arr[2] = player2.score;
			arr[3] = player2.floor;

			Map.move = 0;
			END = 0;

			if (alive)
			{
				if (sound.so4.getStatus() == Sound::Stopped)
				{
					sound.falling_sound();
					alive = false;
				}
			}
			paused_time += clockcnt.getElapsedTime();
		}

		//cout << dt << endl;
		player1.Players_Motion(buff, Keyboard::A, Keyboard::D, Keyboard::Space);
		player2.Players_Motion(buff, Keyboard::Left, Keyboard::Right, Keyboard::Numpad0);
		player1.update();
		player2.update();
		if (player1.compo_cnt == 0 || resize == 0)
		{
			gameclock.star.setScale(0, 0);
			player1.compo.setCharacterSize(0);
		}
		if (player2.compo_cnt == 0 || resize2 == 0)
		{
			gameclock.star2.setScale(0, 0);
			player2.compo.setCharacterSize(0);
		}
		//= ================================================== = DRAW================================ = //
		window.clear();
		window.setView(player1_View);
		DRAW();
		DRAW_View1();
		//------------------------------------------------------
		if (GameMode == 2)
		{
			window.setView(player2_View);
			DRAW();
			DRAW_View2();
		}
		window.display();
	}
}
//-------------------------------------------------<<Menues>>---------------------------------------------------//
int main()
{
	window.setFramerateLimit(120);
	//MainMenu
	menu.menu1(window, GameMode);
	//menu.Menues(window);
}
