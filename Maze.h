#pragma once
#include "stdafx.h"

enum player_states { idle = 0 , left , right , up , down , dead , won};

class Maze
{
public:
	Maze(sf::RenderWindow&);
	sf::RenderWindow& wind;
	void mazeStartLoop();

private:

	//Rectangles
	sf::RectangleShape rect[81];
	sf::Texture recttext1, recttext2, trophytext;
	sf::Font font;
	sf::Text win_text, level_text, proceed_text, last_text;
	sf::SoundBuffer buffer1, buffer2;
	sf::Sound sound1, sound2;
	bool game_won;

	//Player
	sf::Sprite player;
	sf::Texture playertext;

	//Animation
	short animState;
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//MOdifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetVelocityX();

	//functions for  player movement
	void initSprite();
	void initAnimations();
	void initVariables();
	void initPhysics();
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;
	void resetAnimationTimer();
	void updateMovement();
	void updateAnimations();
	void updatePhysics();
	void move(const float dir_x, const float dir_y);
	void update();
	void rect_sizeset();
	void rect_posset();
	void updateCollision();
	void go_to_last_window();
	void render();
};