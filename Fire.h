#pragma once
#include "stdafx.h"


class Fire
{
public:

	Fire(sf::Vector2f size, sf::Texture* text)
	{
		fires.setSize(size);
		fires.setTexture(text);
	}

	void fire(int speed)
	{
		fires.move(speed, 0);
	}


	int getRight()
	{
		return fires.getPosition().x + fires.getSize().x;
	}

	int getLeft()
	{
		return fires.getPosition().x;
	}

	int getTop()
	{
		return fires.getPosition().y;
	}

	int getBottom()
	{
		return fires.getPosition().y + fires.getSize().y;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(fires);
	}

	void setPos(sf::Vector2f newPos)
	{
		fires.setPosition(newPos);
	}

	/* getPos()
	{
		return spell.getPosition();
	}*/

private:

	sf::RectangleShape fires;

};