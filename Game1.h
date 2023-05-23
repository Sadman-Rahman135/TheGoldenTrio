#pragma once
#include "stdafx.h"
#include "Bird.h"
#include<vector>
#include "Pipe.h"
#include<random>

class Game1
{
public:

	Game1(sf::RenderWindow&);
	sf::RenderWindow& win;
	void startGameLoop();

private:

	sf::Texture bg_texture1, bg_texture2, bg_texture3, ground_texture;
	sf::Sprite bg_sprite1, bg_sprite2, bg_sprite3, ground_sprite1, ground_sprite2;
	sf::Texture coral1Text, coral2Text;
	sf::Sprite coral;
	sf::SoundBuffer buffer[5];
	sf::Sound sound[5];
	sf::Event event;

	Bird bird;
	bool is_enter_pressed, run_game, start_monitoring;
	bool have_won;
	const int move_speed = 270;
	int pipe_counter, pipe_spawn_time, score;

	void draw();
	void moveGround(sf::Time&);
	void doProcessing(sf::Time& dt);
	void checkCollisions();
	//void restartGame();
	void checkScore();
	void go_to_level3();

	std::string toString(int);
	std::vector<Pipe> pipes;
	std::random_device rd;
	std::uniform_int_distribution<int> dist{ 100,700 };
	sf::Font font;
	sf::Text gameover_text, score_text, win_text, enter_text, proceed_text, level_text, more_text;

};