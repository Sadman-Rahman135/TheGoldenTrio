#pragma once
#include "stdafx.h"

class Spell
{
public:

	Spell(sf::Vector2f size, sf::Texture* text)
	{
		spell.setSize(size);
		spell.setTexture(text);
	}

	void fire(int speed)
	{
		spell.move(speed, 0);
	}


	int getRight()
	{
		return spell.getPosition().x + spell.getSize().x;
	}

	int getLeft()
	{
		return spell.getPosition().x;
	}

	int getTop()
	{
		return spell.getPosition().y;
	}

	int getBottom()
	{
		return spell.getPosition().y + spell.getSize().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(spell);
	}

	void setPos(sf::Vector2f newPos)
	{
		spell.setPosition(newPos);
	}

	/* getPos()
	{
		return spell.getPosition();
	}*/

private:

	sf::RectangleShape spell;

};



