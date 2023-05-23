#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Spell.h"
#include "stdafx.h"
#include "Fire.h"
#include "Health.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	sf::SoundBuffer buffer[10];
	sf::Sound sound[10];
	sf::SoundBuffer buffer2;
	sf::Sound sound2;
	sf::SoundBuffer buffer3;
	sf::Sound sound3;
	sf::SoundBuffer buffer4;
	sf::Sound sound4;
	sf::SoundBuffer buffer5;
	sf::Sound sound5;

	sf::Font font;
	sf::Text level[10];

	std::string string;

	Player* player;
	Enemy* enemy;

	int hitPlayer = 0;
	int hitEnemy = 0;
	bool isFiring;
	bool goDragon;
	std::vector<Spell> spellVec;
	std::vector<Fire> fireVec;
	
	void initWindow();
	void initPlayer();
	void initEnemy();

public:
	

	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void updateEnemy();
	void updateCollision();
	void update();
	void renderPlayer();
	void renderEnemy();
	void render();
	void smallAnimations();
	void healthBar();
	void fontUpdate();
	void goLevel2();

	const sf::RenderWindow& getWindow() const;
};
