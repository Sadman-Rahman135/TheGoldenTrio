#pragma once
#include "stdafx.h"

class Pipe
{
public:
	Pipe(int);
	sf::Sprite sprite_up;
	static void loadTextures();
	void update(sf::Time&);
	float getRightBound();

private:
	static sf::Texture texture_up;
	static int pipe_distance, move_speed;
}; 
