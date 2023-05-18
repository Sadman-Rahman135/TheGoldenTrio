/*
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
int main()
{
	RenderWindow window(VideoMode(700, 500), "FML Works", Style::Titlebar | Style::Resize);
	RectangleShape player(Vector2f(100.0f, 100.0f));
	player.setFillColor(Color::Red);
	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				cout << "Width " << evnt.size.width << "Height" << evnt.size.height << endl;
				break;
			case Event::TextEntered:
				if (evnt.text.unicode < 128)
				{
					printf("%c", evnt.text.unicode);
				}
				//cout << evnt.text.unicode << "";


			}


		}
		float speed = 1.0f;
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			player.move(-speed, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			player.move(0.0f, -speed);
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			player.move(0.0f, speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			player.move(speed, 0.0f);
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mouseposition = Mouse::getPosition(window);
			cout << "Mouse_X" << mouseposition.x << "Mouse_Y" << mouseposition.y << endl;
		}
		window.clear(Color::Cyan);
		window.draw(player);
		window.display();
		
	}
}

*/