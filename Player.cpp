#include "Player.h"
#include "stdafx.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::playerDead()
{
	this->animState = PLAYER_ANIMATION_STATES::DEAD;
}

void Player::playerDance()
{
	this->animState = PLAYER_ANIMATION_STATES::WON;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Graphics/harami.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load image!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setPosition(sf::Vector2f(0.f, 700.f));
	this->currentFrame = sf::IntRect(0, 64, 32, 32);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.4f, 2.4f);
}

void Player::initAnimations() 
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 30.f;
	this->velocityMin = 1.f;
	this->acceleration = 25.f;
	this->drag = 0.93f;
	this->gravity = 2.f;
	this->velocityMaxY = 60.f;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}


Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//acceleration
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.x += dir_y * this->acceleration; gravity

	//limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//deceleration
	this->velocity *= this->drag;

	//limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	if (this->animState != PLAYER_ANIMATION_STATES::DEAD && this->animState != PLAYER_ANIMATION_STATES::WON)
	{
		this->animState = PLAYER_ANIMATION_STATES::IDLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
		{
			this->move(-1.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
		{
			this->move(1.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
		{
			this->sprite.move(0.f, -50.f);
			this->animState = PLAYER_ANIMATION_STATES::JUMPING;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
		{
			this->sprite.move(0.f, 1.f);
			this->animState = PLAYER_ANIMATION_STATES::JUMPING;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) //Fire
		{
			this->animState = PLAYER_ANIMATION_STATES::FIRING;
		}
	}

}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 64.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 32.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT || this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 192.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 96.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 64.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::FIRING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.001f)
		{
			this->currentFrame.top = 192.f;
			this->currentFrame.left = 128.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 192.f)
				this->currentFrame.left = 128.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::DEAD)
	{
		this->currentFrame.top = 224.f;
		this->currentFrame.left = 0.f;
		this->sprite.setTextureRect(this->currentFrame);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::WON)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f)
		{
			this->currentFrame.top = 121.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}



