#include "Game.h"
#include "Menu.h"
#include "Spell.h"
#include "Enemy.h"


int main()
{
	//srand(time(0));

	//logo design
	sf::Texture logo;

	if (!logo.loadFromFile("Graphics/Triwizardry.png")) {
		exit(1);
	}

	sf::Sprite sp;
	sp.setTexture(logo);
	sp.scale(1, 1); 

	int logoWidth = sp.getGlobalBounds().width;
	int logoHeight = sp.getGlobalBounds().height;

	sf::RenderWindow window(sf::VideoMode(logoWidth, logoHeight), "SFML", sf::Style::None); 
	sf::Clock timer;
	sf::Time time = timer.restart();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			
		}

		time += timer.restart();
		if (time >= sf::seconds(3.f)) {
			window.close();
		}

		window.clear();
		window.draw(sp);
		window.display();
	}

	//mainmenu design
	Menu mainmenu;

	sf::RenderWindow MENU(sf::VideoMode(1600, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
	mainmenu.setMenu(MENU.getSize().x, MENU.getSize().y);

	/*sf::Music music;
	music.openFromFile("Audio/background.wav");
	music.setVolume(20.0f);
	music.play();*/

	//set background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1600, 800));
	sf::Texture Maintexture;
	Maintexture.loadFromFile("Graphics/mainmenu.png");
	background.setTexture(&Maintexture);

	

	
	//photo to about
	sf::RectangleShape Abackground;
	Abackground.setSize(sf::Vector2f(1600, 800));
	sf::Texture about_texture;
	about_texture.loadFromFile("Graphics/blabla.png");
	Abackground.setTexture(&about_texture);


	//game starts
	while (MENU.isOpen())
	{
		sf::Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) MENU.close();
			
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					mainmenu.moveUp();
					break;
				}
				if (event.key.code == sf::Keyboard::Down)
				
				{
					mainmenu.moveDown();
					break;
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					sf::RenderWindow Options(sf::VideoMode(1600, 800), "Options");
					sf::RenderWindow About(sf::VideoMode(1600, 800), "About");

					int  x = mainmenu.menuPressed();
					if (x == 0)
					{
						Game game;
						while (game.getWindow().isOpen())
						{
							game.update();
							game.render();

							Options.close();
							About.close();

						}


						std::cout << "Hello from Triwizardry!" << "\n";
					}

					if (x == 1)
					{
						while (Options.isOpen())
						{
							sf::Event aevent;
							while (Options.pollEvent(aevent))
							{
								if (aevent.type == sf::Event::Closed) Options.close();
								if (aevent.type == sf::Event::KeyPressed)
								{
									if (aevent.key.code == sf::Keyboard::Escape) Options.close();
								}
							}
							Options.clear();
							//Options.draw(Obackground);
							About.close();

							Options.display();
						}
						

					}
					if (x == 2)
					{
						while (About.isOpen())
						{
							sf::Event aevent;
							while (About.pollEvent(aevent))
							{
								if (aevent.type == sf::Event::Closed) About.close();
								if (aevent.type == sf::Event::KeyPressed)
								{
									if (aevent.key.code == sf::Keyboard::Escape) About.close();
								}
							}
							Options.close();
							About.clear();
							About.draw(Abackground);

							About.display();
						}

					}
					if (x == 3) MENU.close();
					break;
				}
				
			}
		}

		MENU.clear();
		MENU.draw(background);
		mainmenu.draw(MENU);
		MENU.display();

	}
	system("PAUSE");

	// End of  application
	return 0;
}

//functions for mainmenu
void Menu::setMenu(int width, int height)
{
	if (!font.loadFromFile("Fonts/NITEMARE.ttf"))
		std::cout << "No font is here!!" << "\n";

	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Play");
	menu[0].setCharacterSize(60);
	menu[0].setPosition(1000, 280);

	//Options
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Cyan);
	menu[1].setString("Options");
	menu[1].setCharacterSize(50);
	menu[1].setPosition(1000, 360);

	//About
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Cyan);
	menu[2].setString("About");
	menu[2].setCharacterSize(50);
	menu[2].setPosition(1000, 440);

	//Exit
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Cyan);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(50);
	menu[3].setPosition(1000, 520);

	menuSelected = -1;

}

Menu::~Menu()
{

}

//Draw MainMenu
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_MENU; i++)
	{
		window.draw(menu[i]);
	}
}

//Moveup
void Menu::moveUp()
{
	if (menuSelected - 1 >= 0)
	{
		menu[menuSelected].setFillColor(sf::Color::Cyan);

		menuSelected--;
		if (menuSelected == -1) menuSelected = 2;
		menu[menuSelected].setFillColor(sf::Color::Yellow);
	}
}

//moveDown
void Menu::moveDown()
{
	if (menuSelected + 1 <= MAX_MENU)
	{

		menu[menuSelected].setFillColor(sf::Color::Cyan);

		menuSelected++;
		if (menuSelected == 4) menuSelected = 0;
		menu[menuSelected].setFillColor(sf::Color::Yellow);
	}
}

//level 2 check

/*
#include "Globals.h"
#include "Game1.h"
#include "stdafx.h"

int main()
{
	sf::RenderWindow win(sf::VideoMode(1600, 800), "Triwizardry");
	Game1 game(win);
	game.startGameLoop();
	return 0;
}*/

/*photo to game
	sf::RectangleShape Pbackground;
	Pbackground.setSize(sf::Vector2f(1200, 800));
	sf::Texture back_texture;
	back_texture.loadFromFile("d44t");
	Pbackground.setTexture(&back_texture);

	//photo to options
	sf::RectangleShape Obackground;
	Obackground.setSize(sf::Vector2f(1200, 800));
	sf::Texture options_texture;
	options_texture.loadFromFile("d44t");
	Obackground.setTexture(&options_texture);*/

//level 3 check

/*
#include "Maze.h"
#include "stdafx.h"

int main()
{
	sf::RenderWindow wind(sf::VideoMode(1600, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
	Maze maze(wind);
	maze.mazeStartLoop();
}*/