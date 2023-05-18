
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(1700, 900), "Image SFML", Style::Resize | Style::Default);
    string img_path = "C:/Users/Lenovo/Desktop/image file/Harry.png";
    string image_path = "C:/Users/Lenovo/Desktop/image file/harry_potter_EXP!.png";
    Texture text_1;
    Texture texture;
    if (!texture.loadFromFile(img_path) || !text_1.loadFromFile(image_path))
    {
        return 1;
    }
    Vector2u size = texture.getSize();
    cout << "Height" << size.x << "Width " << size.y;
    Sprite sprite(texture);
    Sprite background(text_1);
    background.setScale(2.0f, 1.0f);
    sprite.setScale(0.25f, 0.25f);// using for reducing the scale setiing
    sprite.setPosition(Vector2f(10, 10));
    // Vector2f spritePosition = sprite.getPosition();
    float speed = 0.7f;
    const float maxY = 5.0f;
    const Vector2f gravity(0.0f, 1.0f);
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {

            switch (evnt.type)
            {
            case Event::Closed:
                window.close();
            case Event::TextEntered:
                if (evnt.text.unicode < 128)
                {
                    printf("%c ", evnt.text.unicode);
                }

            }
            
            

            if (evnt.type == Event::MouseButtonPressed)
            {
                Vector2i mouse_pos = Mouse::getPosition(window);
                sprite.setOrigin((float)size.x / 2, (float)size.y / 2);
                switch (evnt.key.code)
                {

                case Mouse::Left:
                    cout << mouse_pos.x << " " << mouse_pos.y << endl;
                    //set posotion always works as float
                    sprite.setPosition((float)mouse_pos.x, (float)mouse_pos.y);

                    break;
                case Mouse::Right:
                    printf("%d \n", mouse_pos.y);
                    break;
                }
            }
        }
        // Vector2f spritepos = sprite.getPosition();
        
        
        

            // this movement is rather more smooth than the previous one so to use this is better.
            if (Keyboard::isKeyPressed(Keyboard::Key::A))
            {
                sprite.move(-speed, 0.0f);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::W))
            {
                sprite.move(0.0f, -speed);
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::S))
            {
                sprite.move(0.0f, speed);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::D))
            {
                sprite.move(speed, 0.0f);
            }

            // Draw graphics here...
            window.clear(Color::Cyan);
            window.draw(background);
            window.draw(sprite);
            
            window.display();
        
    }
}

