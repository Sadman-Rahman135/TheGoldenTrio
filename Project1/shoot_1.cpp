/*
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(1000, 800), "Shooting status", Style::Resize);
	RectangleShape player(Vector2f (740.0f, 320.0f));
	Texture playerTexture;
	if (!playerTexture.loadFromFile("C:/Users/Lenovo/Desktop/image file/harry_potter_movement.png"))
	{
		return 1;
	}

	player.setPosition(10.0f, 10.0f);
	Vector2f velocity(0.0f, 0.0f);
    player.setTexture(&playerTexture);
	Vector2u text_size = playerTexture.getSize();
	cout << text_size.x << " " << text_size.y << endl;
	text_size.x /= 9;
	text_size.y /= 2;
	cout << text_size.x << " " << text_size.y << endl;

	player.setTextureRect(IntRect(text_size.x * 1, text_size.y * 1, text_size.x, text_size.y));
	player.setScale(0.25f, 0.25f);
	// spr.setScale(.75f, .75f);
	player.setPosition(10.0f, 10.0f);
	while (window.isOpen())
	{
		Event evnt;

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
				break;
			*/
			/*
			if (evnt.type == Event::MouseButtonPressed)
			{
				if (evnt.key.code == Mouse::Left)
				{
					velocity.x = -0.5f;
					velocity.y = -0.5f;
					
				}
				if (evnt.key.code == Mouse::Right)
				{
					velocity.x = 0.5f;
					velocity.y = 0.5f;
					
				}
			}*/
/*

		}
		// spr.setPosition(spr.getPosition() + velocity);
		window.clear(Color::Red);
		window.draw(player);
		window.display();
				
	}
}
*/