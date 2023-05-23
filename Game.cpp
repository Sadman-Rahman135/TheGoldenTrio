#include "Game.h"
#include "Enemy.h"
#include "Spell.h"
#include "Fire.h"
#include "Health.h"
#include "Game1.h"


void Game::initWindow()
{
	this->window.create(sf::VideoMode(1600, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemy()
{
	this->enemy = new Enemy();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initEnemy();
}

Game::~Game()
{
	delete this->player;
	delete this->enemy;
}

void Game::update()
{
	this->isFiring = false;

	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::S ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::Space))
			this->player->resetAnimationTimer();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (this->hitPlayer <10) )
		{
			this->isFiring = true;
		}

	}

		this->updatePlayer();
		this->updateEnemy();

		this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderEnemy()
{
	this->enemy->render(this->window);
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateEnemy()
{
	this->enemy->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > (this->window.getSize().y - 230))
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->player->getGlobalBounds().height - 230);
	}

	//Collision left side of the screen
	if (this->player->getGlobalBounds().left < 0)
	{
		this->player->resetVelocityX();
		this->player->setPosition(0, this->player->getGlobalBounds().top);
	}

	//Collision right side of  the screen
	if (this->player->getGlobalBounds().left > (this->window.getSize().x) / 2)
	{
		this->player->resetVelocityX();
		this->player->setPosition((this->window.getSize().x) / 2, this->player->getGlobalBounds().top);
	}

	//Collision top of  the screen
	if (this->player->getGlobalBounds().top < 0)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left , 0);
	}
}

void::Game::smallAnimations()
{

	sf::Texture firesText;
	firesText.loadFromFile("Graphics/dragon_fireball.png");

	sf::Texture spellText;
	spellText.loadFromFile("Graphics/The_Blue.png");

	if (this->isFiring == true)
	{
		Spell newSpell(sf::Vector2f(80, 30), &spellText);
		newSpell.setPos(sf::Vector2f((this->player->getGlobalBounds().left + this->player->getGlobalBounds().width), (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2)));
		this->spellVec.push_back(newSpell);

		this->buffer[1].loadFromFile("Audio/spell_cast.wav");
		this->sound[1].setBuffer(buffer[1]);
		this->sound[1].setVolume(30.0f);
		this->sound[1].play();

		this->isFiring = false;
	}

	for (int i = 0; i < this->spellVec.size(); i++)
	{
		this->spellVec[i].draw(this->window);
		this->spellVec[i].fire(40);
	}

	for (int i = 0; i < this->spellVec.size(); i++)
	{
		if (this->spellVec[i].getRight() > 1300.f &&
			this->spellVec[i].getTop() < (this->enemy->getGlobalBounds().top + this->enemy->getGlobalBounds().height) &&
			this->spellVec[i].getBottom() > this->enemy->getGlobalBounds().top)
		{
			//std::cout << "Collision Detected!" << "\n";
			//std::cout << i << "normal\n";
			//this->count = i;
			this->spellVec[i].setPos(sf::Vector2f(-500, -500));
			this->hitEnemy++;

			if (i % 2 == 0 || i % 3 == 0)
			{
				this->buffer[2].loadFromFile("Audio/roar.wav");
				this->sound[2].setBuffer(buffer[2]);
				this->sound[2].setVolume(40.0f);
				this->sound[2].play();

				//std::cout << i << " not normal\n";
				Fire newFire(sf::Vector2f(130, 130), &firesText);
				newFire.setPos(sf::Vector2f((this->enemy->getGlobalBounds().left), (this->enemy->getGlobalBounds().top + this->enemy->getGlobalBounds().height / 2)));
				this->fireVec.push_back(newFire);
			}

			//std::cout << "Enemy hit" << hitEnemy << "\n";
		}

		else if (this->spellVec[i].getRight() > 1600)
			this->spellVec[i].setPos(sf::Vector2f(-500, -500));

	}


	for (int i = 0; i < this->fireVec.size(); i++)
	{
		this->fireVec[i].draw(this->window);
		this->fireVec[i].fire(-40);
	}

	for (int i = 0; i < this->fireVec.size(); i++)
	{
		if (this->fireVec[i].getLeft() < (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2) &&
			this->fireVec[i].getRight() > (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2) &&
			this->fireVec[i].getTop() < (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height) &&
			this->fireVec[i].getBottom() > this->player->getGlobalBounds().top)
		{
			//std::cout << "Collision Detected!" << "\n"
			this->fireVec[i].setPos(sf::Vector2f(-400, -400));
			this->hitPlayer++;

			this->buffer[3].loadFromFile("Audio/player_hit.wav");
			this->sound[3].setBuffer(buffer[3]);
			this->sound[3].setVolume(40.0f);
			this->sound[3].play();

			//std::cout << "Player hit" << hitPlayer << "\n";
		}

		else if (this->fireVec[i].getLeft() < 0)
			this->fireVec[i].setPos(sf::Vector2f(-400, -400));

	}

	this->healthBar();
	this->fontUpdate();

}

void Game::healthBar()
{
	sf::Texture phealthText;
	phealthText.loadFromFile("Graphics/blue.png");

	sf::Texture ehealthText;
	ehealthText.loadFromFile("Graphics/red.png");

	PlayerHealth phealth(sf::Vector2f(500 - (this->hitPlayer * 50), 30), &phealthText);
	EnemyHealth ehealth(sf::Vector2f(500 - (this->hitEnemy * 10), 30), &ehealthText);

	phealth.setPos(sf::Vector2f(100, 30));
	ehealth.setPos(sf::Vector2f(100, 80));

	if (this->hitPlayer < 10)
	{
		phealth.draw(this->window);
	}
	else if (this->hitPlayer == 10)
	{
		this->sound[3].pause();
		this->buffer[4].loadFromFile("Audio/game_over.wav");
		this->sound[4].setBuffer(buffer[4]);
		this->sound[4].setVolume(60.0f);
		this->sound[4].play();
		this->hitPlayer++;
	}
	else
	{
		this->player->playerDead();
		this->player->update();
		this->fontUpdate();
	}

	if (this->hitEnemy < 50)
		ehealth.draw(this->window);

	else if (this->hitEnemy == 50)
	{
		this->sound[2].pause();
		this->buffer[5].loadFromFile("Audio/gta.wav");
		this->sound[5].setBuffer(buffer[5]);
		this->sound[5].setVolume(60.0f);
		this->sound[5].play();
		this->hitEnemy++;
	}
	else
	{
		this->enemy->enemyDead();
		this->enemy->update();
		this->player->playerDance();
		this->fontUpdate();
		this->goLevel2();
	}
}

void::Game::fontUpdate()
{
	this->font.loadFromFile("Fonts/NITEMARE.ttf");

	this->level[0].setFont(font);
	this->level[0].setFillColor(sf::Color::Black);
	this->level[0].setString("Level:1");
	this->level[0].setCharacterSize(40);
	this->level[0].setPosition(1500, 20);

	this->level[1].setFont(font);
	this->level[1].setFillColor(sf::Color::Blue);
	this->level[1].setString("You");
	this->level[1].setCharacterSize(40);
	this->level[1].setPosition(10, 20);

	this->level[2].setFont(font);
	this->level[2].setFillColor(sf::Color::Red);
	this->level[2].setString("Enemy");
	this->level[2].setCharacterSize(40);
	this->level[2].setPosition(10, 70);

	window.draw(this->level[0]);
	window.draw(this->level[1]);
	window.draw(this->level[2]);

	if (this->hitPlayer >= 10)
	{
		this->level[3].setFont(font);
		this->level[3].setFillColor(sf::Color::Black);
		this->level[3].setString("Game Over");
		this->level[3].setCharacterSize(120);
		this->level[3].setPosition(600, 250);
		window.draw(this->level[3]);
	}

	if (this->hitEnemy >= 50)
	{
		this->level[4].setFont(font);
		this->level[4].setFillColor(sf::Color::Black);
		this->level[4].setString("Golden Egg Retrieved!");
		this->level[4].setCharacterSize(120);
		this->level[4].setPosition(400, 180);
		window.draw(this->level[4]);

		this->level[5].setFont(font);
		this->level[5].setFillColor(sf::Color::Blue);
		this->level[5].setString("Press F To Proceed");
		this->level[5].setCharacterSize(60);
		this->level[5].setPosition(580, 400);
		window.draw(this->level[5]);

		this->level[6].setFont(font);
		this->level[6].setFillColor(sf::Color::Black);
		this->level[6].setString("But Ron is in trouble! Save him!");
		this->level[6].setCharacterSize(40);
		this->level[6].setPosition(565, 350);
		window.draw(this->level[6]);
	}

}

void Game::render()
{		
	this->window.clear(sf::Color::White);
	sf::Texture bg;
	bg.loadFromFile("Graphics/background.png");
	sf::Sprite bgd(bg);
	window.draw(bgd);

	this->smallAnimations();

	//Render game
	this->renderPlayer();
	this->renderEnemy();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	//TODO: insert return statement here
	return this->window;
}

void Game::goLevel2()
{
	while (this->window.pollEvent(this->ev))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			this->window.close();
			sf::RenderWindow win(sf::VideoMode(1600, 800), "Triwizardry");
			Game1 game(win);
			game.startGameLoop();
		}
	}
}