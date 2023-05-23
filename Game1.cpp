#include "Game1.h"
#include"Globals.h"
#include<sstream>
#include "stdafx.h"
#include "Maze.h"

Game1::Game1(sf::RenderWindow& window) : win(window),
is_enter_pressed(false),
run_game(true),
start_monitoring(false),
pipe_counter(71),
pipe_spawn_time(100),
score(0),
have_won(false)
{
	buffer[0].loadFromFile("Audio/bubble.wav");
	buffer[1].loadFromFile("Audio/game_over.wav");
	buffer[2].loadFromFile("Audio/gta.wav");
	sound[0].setBuffer(buffer[0]);
	sound[1].setBuffer(buffer[1]);
	sound[2].setBuffer(buffer[2]);

	win.setFramerateLimit(60);
	bg_texture1.loadFromFile("Graphics/underwater.png");
	bg_sprite1.setTexture(bg_texture1);
	bg_sprite1.setScale(2, 2.2);
	bg_sprite1.setPosition(0.f, 150.f);

	coral1Text.loadFromFile("Graphics/coral.png");
	coral2Text.loadFromFile("Graphics/monsters.png");
	coral.setPosition(-500.f, 180.f);

	bg_texture2.loadFromFile("Graphics/background_up.png");
	bg_sprite2.setTexture(bg_texture2);
	bg_sprite2.setScale(1600/bg_sprite2.getGlobalBounds().width , 0.55);

	bg_texture3.loadFromFile("Graphics/background_up.png");
	bg_sprite3.setTexture(bg_texture3);
	bg_sprite3.setScale(1600/bg_sprite3.getGlobalBounds().width, 0.55);

	bg_sprite2.setPosition(0, 0);
	bg_sprite3.setPosition(bg_sprite2.getGlobalBounds().width, 0);

	ground_texture.loadFromFile("Graphics/underground_final.png");
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);

	ground_sprite1.setScale(4, 1);
	ground_sprite2.setScale(4, 1);

	ground_sprite1.setPosition(0, 700);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 700);

	font.loadFromFile("Fonts/NITEMARE.ttf");
	gameover_text.setFont(font);
	gameover_text.setCharacterSize(80);
	gameover_text.setFillColor(sf::Color::White);
	gameover_text.setPosition(650, 350);
	gameover_text.setString("Game Over");

	win_text.setFont(font);
	win_text.setCharacterSize(100);
	win_text.setFillColor(sf::Color::White);
	win_text.setPosition(580, 250);
	win_text.setString("You Saved Ron!");

	score_text.setFont(font);
	score_text.setCharacterSize(30);
	score_text.setFillColor(sf::Color::Black);
	score_text.setPosition(15, 15);
	score_text.setString(" 100 percent to go !");

	enter_text.setFont(font);
	enter_text.setCharacterSize(60);
	enter_text.setFillColor(sf::Color::White);
	enter_text.setPosition(600, 350);
	enter_text.setString("Press Enter To Start");

	proceed_text.setFont(font);
	proceed_text.setCharacterSize(55);
	proceed_text.setFillColor(sf::Color::White);
	proceed_text.setPosition(620, 490);
	proceed_text.setString("Press F To Proceed");

	more_text.setFont(font);
	more_text.setFillColor(sf::Color::Cyan);
	more_text.setString("But here comes the final challenge\n   Can you solve the maze?");
	more_text.setCharacterSize(40);
	more_text.setPosition(600, 380);

	level_text.setFont(font);
	level_text.setFillColor(sf::Color::Black);
	level_text.setString("Level:2");
	level_text.setCharacterSize(40);
	level_text.setPosition(1500, 20);

	Pipe::loadTextures();

}

void Game1::doProcessing(sf::Time& dt)
{
	if (is_enter_pressed)
	{
		moveGround(dt);

		if (pipe_counter > pipe_spawn_time)
		{
			pipes.push_back(Pipe(dist(rd)));
			pipe_counter = 0;
		}
		pipe_counter++;

		for (int i = 0; i < pipes.size(); i++)
		{
			pipes[i].update(dt);
			if (pipes[i].getRightBound() < 0)
			{
				pipes.erase(pipes.begin() + i);
			}
		}

		checkCollisions();
		checkScore();
	}
	bird.update(dt);
}

void Game1::startGameLoop()
{
	sf::Clock clock;
	//Game Loop
	while (win.isOpen())
	{
		sf::Time dt = clock.restart();

		//Event Loop
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}
			if (event.type == sf::Event::KeyPressed && run_game)
			{
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed)
				{
					is_enter_pressed = true;
					bird.setShouldFly(true);
				}
				if (event.key.code == sf::Keyboard::Space && is_enter_pressed)
				{
					bird.flapBird(dt);
					sound[0].setVolume(300.f);
					sound[0].play();
				}
			}
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F && !run_game && have_won))
			{
				win.close();
				go_to_level3();
			}
			/*if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{

				if (restart_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					restartGame();
				}

			}*/
		}

		doProcessing(dt);


		draw();
		//display the win
		win.display();
	}
}

void Game1::checkCollisions()
{
	if (pipes.size() > 0)
	{
		if ((pipes[0].sprite_up.getGlobalBounds().left + 80 < (bird.bird_sprite.getGlobalBounds().left + bird.bird_sprite.getGlobalBounds().width ) &&
			 (pipes[0].sprite_up.getGlobalBounds().left + pipes[0].sprite_up.getGlobalBounds().width) > (bird.bird_sprite.getGlobalBounds().left + bird.bird_sprite.getGlobalBounds().width / 2) &&
			 pipes[0].sprite_up.getGlobalBounds().top < (bird.bird_sprite.getGlobalBounds().top + bird.bird_sprite.getGlobalBounds().height) &&
			 pipes[0].sprite_up.getGlobalBounds().top + pipes[0].sprite_up.getGlobalBounds().height > bird.bird_sprite.getGlobalBounds().top) ||

			(coral.getGlobalBounds().left + 80 < (bird.bird_sprite.getGlobalBounds().left + bird.bird_sprite.getGlobalBounds().width) &&
			(coral.getGlobalBounds().left + coral.getGlobalBounds().width) > (bird.bird_sprite.getGlobalBounds().left + bird.bird_sprite.getGlobalBounds().width / 2) &&
			coral.getGlobalBounds().top < (bird.bird_sprite.getGlobalBounds().top + bird.bird_sprite.getGlobalBounds().height) &&
			coral.getGlobalBounds().top + coral.getGlobalBounds().height > bird.bird_sprite.getGlobalBounds().top) ||

			 bird.bird_sprite.getGlobalBounds().top + bird.bird_sprite.getGlobalBounds().height >= 700 ||
			 bird.bird_sprite.getGlobalBounds().top <= 150)
			//pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds())
		{
			is_enter_pressed = false;
			run_game = false;
			if(!have_won) sound[1].play();
		}
	}
}

void Game1::checkScore()
{
	if (pipes.size() > 0)
	{
		if (!start_monitoring)
		{
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_up.getGlobalBounds().left &&
				bird.getRightBound() < pipes[0].getRightBound())
			{
				start_monitoring = true;
			}
		}
		else
		{
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].getRightBound())
			{
				score++;
				score_text.setString( toString(100 - 4*score) + " percent to go!!");
				start_monitoring = false;

				if (100 - 4 * score == 0 || score == 25)
				{
					run_game = false;
					have_won = true;
					sound[2].play();
				}

				if (score != 0 && score % 10 == 0)
				{
					coral.setPosition(1650, 450);
					coral.setScale(0.3, 0.5);
					coral.setTexture(coral2Text);
				}
				else if (score != 0 && score % 5 == 0)
				{
					coral.setPosition(1650, 450);
					coral.setScale(0.2, 0.5);
					coral.setTexture(coral1Text);
				}
			}
		}
	}
}
void Game1::draw()
{
	win.clear();

	coral.move(-7, 0);

	win.draw(bg_sprite1);
	win.draw(bg_sprite2);
	win.draw(bg_sprite3);
	win.draw(coral);

	for (Pipe& pipe : pipes)
	{
		//win.draw(pipe.sprite_down);
		win.draw(pipe.sprite_up);
	}
	win.draw(ground_sprite1);
	win.draw(ground_sprite2);
	win.draw(score_text);
	win.draw(level_text);
	if (!run_game && !have_won)
	{
		win.draw(gameover_text);
		
		/*sf::SoundBuffer buffer;
		sf::Sound sound;
		buffer.loadFromFile("Audio/roar.wav");
		sound.setBuffer(buffer);
		sound.setVolume(50.f);
		sound.play();*/
	}
	else if(!have_won)
	{
		if (!is_enter_pressed) win.draw(enter_text);
	}

	if (!have_won)
	{
		win.draw(bird.bird_sprite);
	}
	else
	{
		win.draw(win_text);
		win.draw(proceed_text);
		win.draw(more_text);
	}
}

void Game1::moveGround(sf::Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);

	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
	{
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 700);
	}
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
	{
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 700);
	}

	bg_sprite2.move(-move_speed * dt.asSeconds(), 0.f);
	bg_sprite3.move(-move_speed * dt.asSeconds(), 0.f);

	if (bg_sprite2.getGlobalBounds().left + bg_sprite2.getGlobalBounds().width < 0)
	{
		bg_sprite2.setPosition(bg_sprite3.getGlobalBounds().left + bg_sprite3.getGlobalBounds().width, 0);
	}
	if (bg_sprite3.getGlobalBounds().left + bg_sprite3.getGlobalBounds().width < 0)
	{
		bg_sprite3.setPosition(bg_sprite2.getGlobalBounds().left + bg_sprite2.getGlobalBounds().width, 0);
	}

}

/*void Game1::restartGame()
{
	bird.resetBirdPosition();
	bird.setShouldFly(false);
	run_game = true;
	is_enter_pressed = false;
	pipe_counter = 71;
	pipes.clear();
	score = 0;
	score_text.setString("Score: 0");
}*/

std::string Game1::toString(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

void Game1::go_to_level3()
{
		std::cout << "kaj kortese";
		sf::RenderWindow wind(sf::VideoMode(1600, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
		Maze maze(wind);
		maze.mazeStartLoop();
}