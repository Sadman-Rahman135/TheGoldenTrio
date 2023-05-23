#include "Bird.h"
#include "Globals.h"
#include "stdafx.h"

Bird::Bird() :
	gravity(11),
	flap_speed(250),
	anim_counter(0),
	texture_switch(1),
	should_fly(false)
{
	textures[0].loadFromFile("Graphics/harry_1.png");
	textures[1].loadFromFile("Graphics/harry_2.png");

	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(2, 2);
	bird_sprite.rotate(-20.f);
	resetBirdPosition();
}

void Bird::update(sf::Time& dt)
{
	if (bird_sprite.getGlobalBounds().top < (700 - bird_sprite.getGlobalBounds().height) && should_fly)
	{
		if (anim_counter == 5)
		{
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch) texture_switch = 0;
			else texture_switch = 1;
			anim_counter = 0;
		}

		anim_counter++;

		velocity_y += gravity * dt.asSeconds();
		bird_sprite.move(0, velocity_y);

		/*if (bird_sprite.getGlobalBounds().top < 0)
		{
			bird_sprite.setPosition(100, 0);
		}*/

	}
}

void Bird::flapBird(sf::Time& dt)
{
	velocity_y = -flap_speed * dt.asSeconds();
}

float Bird::getRightBound()
{
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;
}

void Bird::resetBirdPosition()
{
	bird_sprite.setPosition(100, 200);
	velocity_y = 0;
}

void Bird::setShouldFly(bool should_fly)
{
	this->should_fly = should_fly;
}