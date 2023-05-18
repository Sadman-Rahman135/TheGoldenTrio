/*
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shooting Ball Example");

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(0.f, 590.f);

    sf::Clock clock;
    float elapsedTime = 0.f;
    bool ballMoving = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                ballMoving = true;
                clock.restart();
            }
        }

        if (ballMoving)
        {
            elapsedTime = clock.getElapsedTime().asSeconds();
            if (elapsedTime < 3.f) // Stop the ball after 3 seconds
            {
                float speed = 0.009f; // Pixels per second
                float dx = speed * cos(45.f * 3.14159f / 180.f); // Calculate x velocity
                float dy = -speed * sin(45.f * 3.14159f / 180.f); // Calculate y velocity
                ball.move(dx * elapsedTime, dy * elapsedTime); // Move the ball
            }
            else
            {
                ballMoving = false;
            }
        }

        window.clear(sf::Color::White);
        window.draw(ball);
        window.display();
    }

    return 0;
}
*/
