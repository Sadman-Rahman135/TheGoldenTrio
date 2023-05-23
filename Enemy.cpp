#include "stdafx.h"
#include "Enemy.h"


void Enemy::initVariables()
{
	this->animState = season::spring;
}

void Enemy::enemyDead()
{
	this->animState = season::summer;
}

void Enemy::initTexture()
{
	if (!this->textureSheet.loadFromFile("Graphics/Black_flyDragon.png"))
	{
		std::cout << "ERROR::ENEMY::Could not load image!" << "\n";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setPosition(sf::Vector2f(1130.f, -5.f));
	this->currentFrame = sf::IntRect(0, 0, 149.5f, 139.f);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
}

void Enemy::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Enemy::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::resetVelocityY()
{
	this->velocity.y = 0.f;
}

Enemy::Enemy()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	/*this->initPhysics();*/
}

Enemy::~Enemy()
{

}

const bool& Enemy::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void Enemy::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Enemy::updateMovement()
{
	this->animState = season::spring;
}

void Enemy::updateAnimations()
{
	if (this->animState == season::spring)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.07f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;				
			this->currentFrame.left -= 149.5f;

			if (this->currentFrame.left <= 0.f)
				this->currentFrame.left = 747.5f;

			this->sprite.move(0.f, 10.f);
			if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= 800)
			{
				this->sprite.setPosition(1130.f, -200.f);
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	
	else
	{
		this->currentFrame.left = 747.5f;
		this->sprite.setTextureRect(this->currentFrame);
		this->sprite.move(0, 4.f);
	}
}

void Enemy::update()
{
	if(this->animState != season::summer)  this->updateMovement();
	this->updateAnimations();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
