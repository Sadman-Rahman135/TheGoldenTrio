#pragma once
#include "stdafx.h"

class PlayerHealth
{
public:
	PlayerHealth(sf::Vector2f size, sf::Texture* text)
	{
		playerHealth.setSize(size);
		playerHealth.setTexture(text);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(playerHealth);
	}

	void setPos(sf::Vector2f newPos)
	{
		playerHealth.setPosition(newPos);
	}

private:

	sf::RectangleShape playerHealth;
};

class EnemyHealth
{
public:
	EnemyHealth(sf::Vector2f size, sf::Texture* text)
	{
		enemyHealth.setSize(size);
		enemyHealth.setTexture(text);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(enemyHealth);
	}

	void setPos(sf::Vector2f newPos)
	{
		enemyHealth.setPosition(newPos);
	}

private:
	sf::RectangleShape enemyHealth;
};
