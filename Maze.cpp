#include "stdafx.h"
#include "Maze.h"

Maze::Maze(sf::RenderWindow& window) : wind(window)
{

}

void Maze::mazeStartLoop()
{
	//Initializing Player
	game_won = false;
	initVariables();
	initSprite();
	initAnimations();
	initPhysics();
	recttext1.loadFromFile("Graphics/grass.png");
	recttext2.loadFromFile("Graphics/grass1.png");
	trophytext.loadFromFile("Graphics/triwizardry.png");
	font.loadFromFile("Fonts/NITEMARE.ttf");
	buffer1.loadFromFile("Audio/gta.wav");
	sound1.setBuffer(buffer1);

	while (wind.isOpen())
	{ 
		wind.setFramerateLimit(60);

		rect_sizeset();

		rect_posset();	

		//Setting Rectangle Textures
		for (int i = 0; i <= 72; i++)
		{
			if (i % 2)
				rect[i].setTexture(&recttext1);
			else
				rect[i].setTexture(&recttext2);
		}

		rect[73].setTexture(&trophytext);

		//Polling events
		sf::Event event;
		while (wind.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) wind.close();

			if (event.type == sf::Event::KeyReleased && game_won == false
				(event.key.code == sf::Keyboard::A ||
		        event.key.code == sf::Keyboard::D  ||
				event.key.code == sf::Keyboard::S  ||
				event.key.code == sf::Keyboard::W  ))
				 resetAnimationTimer();

			if (game_won && (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F))
				go_to_last_window();
		}

		update();
		updateCollision();
		render();
		wind.display();
	}
}

void Maze::initSprite()
{
	playertext.loadFromFile("Graphics/harry_potter.png");
	player.setTexture(playertext);
	player.setPosition(sf::Vector2f(1560.f, 160.f));
	currentFrame = sf::IntRect(0, 0, 32, 32);
	player.setTextureRect(currentFrame);
	player.setScale(0.8f, 0.8f);
}

void Maze::initAnimations()
{
	animationTimer.restart();
	animationSwitch = true;
}

void Maze::initPhysics()
{
	velocityMax = 14.f;
	velocityMin = 1.f;
	acceleration = 1.f;
	drag = 0.4f;
	gravity = 0.f;
	velocityMaxY = 14.f;
}

void Maze::initVariables()
{
	animState = player_states::idle;
}

const bool& Maze::getAnimSwitch()
{
	bool anim_switch = animationSwitch;

	if (animationSwitch)
		animationSwitch = false;

	return anim_switch;
}

void Maze::resetAnimationTimer()
{
	animationTimer.restart();
	animationSwitch = true;
}

const sf::FloatRect Maze::getGlobalBounds() const
{
	return player.getGlobalBounds();
}

void Maze::setPosition(const float x, const float y)
{
	player.setPosition(x, y);
}

void Maze::updateMovement()
{
	if (animState != player_states::dead && this->animState != player_states::won)
	{
		animState = player_states::idle;

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
		{

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
		{
			move(-25.f, 0.f);
			animState = player_states::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
		{
			move(25.f, 0.f);
			animState = player_states::right;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
		{
			move(0.f, -25.f);
			animState = player_states::up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
		{
			move(0.f, 25.f);
			animState = player_states::down;
		}
	}
}

void Maze::updateAnimations()
{
	if (animState == player_states::idle)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 0.f;
			currentFrame.left += 32.f;
			if (currentFrame.left >= 32.f)
				currentFrame.left = 0;

			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
	}

	else if (animState == player_states::right)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 64.f;
			currentFrame.left += 32.f;
			if (currentFrame.left >= 128.f)
				currentFrame.left = 0;

			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
	}

	else if (animState == player_states::left)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 32.f;
			currentFrame.left += 32.f;
			if (currentFrame.left >= 128.f)
				currentFrame.left = 0;

			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
	}

	else if (animState == player_states::up)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 96.f;
			currentFrame.left += 32.f;
			if (currentFrame.left >= 128.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
	}

	else if (animState == player_states::down)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 0.f;
			currentFrame.left += 32.f;
			if (currentFrame.left >= 128.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
	}

	/*else if (animState == player_states::dead)
	{
		currentFrame.top = 224.f;
		currentFrame.left = 0.f;
		player.setTextureRect(currentFrame);
	}*/

	else if (animState == player_states::won)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimSwitch())
		{
			currentFrame.top = 0.f;
			currentFrame.left = 192.f;
			animationTimer.restart();
			player.setTextureRect(currentFrame);
		}
		
	}
}

void Maze::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Maze::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Maze::move(const float dir_x, const float dir_y)
{
	//acceleration
	velocity.x += dir_x * acceleration;
	//this->velocity.x += dir_y * this->acceleration; gravity

	//limit velocity
	if (std::abs(velocity.x) > velocityMax)
	{
		velocity.x = velocityMax * ((velocity.x < 0.f) ? -1.f : 1.f);
	}

	//acceleration
	velocity.y += dir_y * acceleration;
	//this->velocity.x += dir_y * this->acceleration; gravity

	//limit velocity
	if (std::abs(velocity.y) > velocityMaxY)
	{
		velocity.y = velocityMaxY * ((velocity.y < 0.f) ? -1.f : 1.f);
	}
}

void Maze::updatePhysics()
{
	//Gravity
	velocity.y += 1.0 * gravity;
	if (std::abs(velocity.y) > velocityMaxY)
	{
		velocity.y = velocityMaxY * ((velocity.y < 0.f) ? -1.f : 1.f);
	}

	//deceleration
	velocity *= drag;

	//limit deceleration
	if (std::abs(velocity.x) < velocityMin)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < velocityMin)
		velocity.y = 0.f;

	player.move(velocity);
}

void Maze::update()
{
	updateMovement();
	updateAnimations();
	updatePhysics();
}

void Maze::updateCollision()
{
	/*//Collision bottom of screen
	if (player.getGlobalBounds().top + player.getGlobalBounds().height > (wind.getSize().y - 230))
	{
		resetVelocityY();
		setPosition(player.getGlobalBounds().left, wind.getSize().y - player.getGlobalBounds().height - 230);
	}

	//Collision left side of the screen
	if (player.getGlobalBounds().left < 0)
	{
		resetVelocityX();
		setPosition(0, player.getGlobalBounds().top);
	}*/

	//Collision with rectangle
	for (int i = 0; i <= 72; i++)
	{
		//left collision
		if (animState == player_states::left && player.getGlobalBounds().intersects(rect[i].getGlobalBounds()))
		{
			resetVelocityX();
			setPosition((rect[i].getGlobalBounds().left + rect[i].getGlobalBounds().width), player.getGlobalBounds().top);
		}

		//right collision
		else if (animState == player_states::right && player.getGlobalBounds().intersects(rect[i].getGlobalBounds()))
		{
			resetVelocityX();
			setPosition((rect[i].getGlobalBounds().left - player.getGlobalBounds().width), player.getGlobalBounds().top);
		}

		//top collision
		else if (animState == player_states::up && player.getGlobalBounds().intersects(rect[i].getGlobalBounds()))
		{
			resetVelocityY();
			setPosition(player.getGlobalBounds().left, (rect[i].getGlobalBounds().top + rect[i].getGlobalBounds().height));
		}

		//bottom collision
		else if (animState == player_states::down && player.getGlobalBounds().intersects(rect[i].getGlobalBounds()))
		{
			resetVelocityY();
			setPosition(player.getGlobalBounds().left, (rect[i].getGlobalBounds().top - player.getGlobalBounds().height));
		}
	}

	if (animState == player_states::right && player.getGlobalBounds().intersects(rect[73].getGlobalBounds()))
	{
		resetVelocityX();
		setPosition((rect[73].getGlobalBounds().left - player.getGlobalBounds().width), player.getGlobalBounds().top);
		game_won = true;
		animState = player_states::won;
		sound1.play();
	}
}

void Maze::render()
{
	wind.clear(sf::Color::White);
	sf::Texture bg;
	bg.loadFromFile("Graphics/maze.png");
	sf::Sprite bgd(bg);
	wind.draw(bgd);
	wind.draw(player);
	
	level_text.setFont(font);
	level_text.setFillColor(sf::Color::Black);
	level_text.setString("Level:3");
	level_text.setCharacterSize(40);
	level_text.setPosition(1500, 20);

	for (int i = 0; i <= 80; i++) wind.draw(rect[i]);

	if (game_won)
	{
		win_text.setFont(font);
		win_text.setFillColor(sf::Color::Black);
		win_text.setString("You Won!");
		win_text.setCharacterSize(120);
		win_text.setPosition(600, 250);
		wind.draw(win_text);

		proceed_text.setFont(font);
		proceed_text.setFillColor(sf::Color::Black);
		proceed_text.setString("Press F to proceed");
		proceed_text.setCharacterSize(70);
		proceed_text.setPosition(550, 370);
		wind.draw(proceed_text);
	}
}

void Maze::go_to_last_window()
{
	wind.close();
	sf::RenderWindow windo(sf::VideoMode(1600, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
	while (windo.isOpen())
	{
		sf::Texture bg;
		bg.loadFromFile("Graphics/lastslide.png");
		sf::Sprite bgd(bg);
		windo.draw(bgd);

		last_text.setFont(font);
		last_text.setFillColor(sf::Color::White);
		last_text.setString("You won the Triwizard Cup!\nThe eternal glory!\nThe champion of the champions\nThe prize brings you a lot of fame, and money!\n1000 Galleons!\nBut...........at what cost ?\n .... ");
		last_text.setCharacterSize(70);
		last_text.setPosition(760, 50);
		windo.draw(last_text);


		windo.display();
	}
}


void Maze::rect_sizeset()
{
	rect[0].setSize(sf::Vector2f(40, 160));
	rect[1].setSize(sf::Vector2f(40, 600));
	rect[2].setSize(sf::Vector2f(1560, 40));
	rect[3].setSize(sf::Vector2f(1560, 40));
	rect[4].setSize(sf::Vector2f(40, 720));
	rect[5].setSize(sf::Vector2f(200, 40));
	rect[6].setSize(sf::Vector2f(120, 40));
	rect[7].setSize(sf::Vector2f(40, 40));
	rect[8].setSize(sf::Vector2f(200, 40));
	rect[9].setSize(sf::Vector2f(40, 400));
	rect[10].setSize(sf::Vector2f(200, 40));
	rect[11].setSize(sf::Vector2f(40, 200));
	rect[12].setSize(sf::Vector2f(40, 160));
	rect[13].setSize(sf::Vector2f(40, 40));
	rect[14].setSize(sf::Vector2f(160, 40));
	rect[15].setSize(sf::Vector2f(40, 160));
	rect[16].setSize(sf::Vector2f(80, 40));
	rect[17].setSize(sf::Vector2f(40, 320));
	rect[18].setSize(sf::Vector2f(200, 40));
	rect[19].setSize(sf::Vector2f(40, 40));
	rect[20].setSize(sf::Vector2f(40, 40));
	rect[21].setSize(sf::Vector2f(160, 40));
	rect[22].setSize(sf::Vector2f(160, 40));
	rect[23].setSize(sf::Vector2f(200, 40));
	rect[24].setSize(sf::Vector2f(40, 40));
	rect[25].setSize(sf::Vector2f(40, 120));
	rect[26].setSize(sf::Vector2f(40, 120));
	rect[27].setSize(sf::Vector2f(40, 80));
	rect[28].setSize(sf::Vector2f(80, 40));
	rect[29].setSize(sf::Vector2f(40, 120));
	rect[30].setSize(sf::Vector2f(80, 40));
	rect[31].setSize(sf::Vector2f(40, 240));
	rect[32].setSize(sf::Vector2f(160, 40));
	rect[33].setSize(sf::Vector2f(40, 80));
	rect[34].setSize(sf::Vector2f(160, 40));
	rect[35].setSize(sf::Vector2f(320, 40));
	rect[36].setSize(sf::Vector2f(40, 200));
	rect[37].setSize(sf::Vector2f(200, 40));
	rect[38].setSize(sf::Vector2f(40, 40));
	rect[39].setSize(sf::Vector2f(40, 40));
	rect[40].setSize(sf::Vector2f(200, 40));
	rect[41].setSize(sf::Vector2f(40, 80));
	rect[42].setSize(sf::Vector2f(40, 240));
	rect[43].setSize(sf::Vector2f(240, 40));
	rect[44].setSize(sf::Vector2f(40, 240));
	rect[45].setSize(sf::Vector2f(320, 40));
	rect[46].setSize(sf::Vector2f(40, 40));
	rect[47].setSize(sf::Vector2f(200, 40));
	rect[48].setSize(sf::Vector2f(80, 40));
	rect[49].setSize(sf::Vector2f(40, 200));
	rect[50].setSize(sf::Vector2f(200, 40));
	rect[51].setSize(sf::Vector2f(40, 120));
	rect[52].setSize(sf::Vector2f(200, 40));
	rect[53].setSize(sf::Vector2f(40, 40));
	rect[54].setSize(sf::Vector2f(40, 120));
	rect[55].setSize(sf::Vector2f(80, 40));
	rect[56].setSize(sf::Vector2f(40, 360));
	rect[57].setSize(sf::Vector2f(160, 40));
	rect[58].setSize(sf::Vector2f(40, 280));
	rect[59].setSize(sf::Vector2f(40, 40));
	rect[60].setSize(sf::Vector2f(80, 40));
	rect[61].setSize(sf::Vector2f(40, 160));
	rect[62].setSize(sf::Vector2f(240, 40));
	rect[63].setSize(sf::Vector2f(40, 120));
	rect[64].setSize(sf::Vector2f(40, 80));
	rect[65].setSize(sf::Vector2f(480, 40));
	rect[66].setSize(sf::Vector2f(40, 360));
	rect[67].setSize(sf::Vector2f(120, 40));
	rect[68].setSize(sf::Vector2f(240, 40));
	rect[69].setSize(sf::Vector2f(320, 40));
	rect[70].setSize(sf::Vector2f(160, 40));
	rect[71].setSize(sf::Vector2f(40, 40));
	rect[72].setSize(sf::Vector2f(160, 40));

	rect[73].setSize(sf::Vector2f(40, 40));
}

void Maze::rect_posset()
{
	rect[0].setPosition(1560, 0);
	rect[1].setPosition(1560, 200);
	rect[2].setPosition(0, 0);
	rect[3].setPosition(0, 760);
	rect[4].setPosition(0, 40);
	rect[5].setPosition(40, 80);
	rect[6].setPosition(80, 160);
	rect[7].setPosition(160, 200);
	rect[8].setPosition(80, 240);
	rect[9].setPosition(80, 280);
	rect[10].setPosition(80, 680);
	rect[11].setPosition(240, 480);
	rect[12].setPosition(160, 480);
	rect[13].setPosition(200, 480);
	rect[14].setPosition(160, 240);
	rect[15].setPosition(280, 160);
	rect[16].setPosition(320, 200);
	rect[17].setPosition(360, 240);
	rect[18].setPosition(160, 400);
	rect[19].setPosition(400, 360);
	rect[20].setPosition(400, 440);
	rect[21].setPosition(160, 320);
	rect[22].setPosition(280, 80);
	rect[23].setPosition(400, 120);
	rect[24].setPosition(360, 40);
	rect[25].setPosition(320, 520);
	rect[26].setPosition(360, 600);
	rect[27].setPosition(320, 680);
	rect[28].setPosition(400, 600);
	rect[29].setPosition(480, 560);
	rect[30].setPosition(400, 280);
	rect[31].setPosition(480, 200);
	rect[32].setPosition(520, 400);
	rect[33].setPosition(640, 320);
	rect[34].setPosition(560, 280);
	rect[35].setPosition(480, 480);
	rect[36].setPosition(760, 280);
	rect[37].setPosition(520, 200);
	rect[38].setPosition(680, 160);
	rect[39].setPosition(640, 80);
	rect[40].setPosition(640, 120);
	rect[41].setPosition(800, 160);
	rect[42].setPosition(880, 40);
	rect[43].setPosition(840, 280);
	rect[44].setPosition(840, 320);
	rect[45].setPosition(560, 560);
	rect[46].setPosition(560, 600);
	rect[47].setPosition(560, 640);
	rect[48].setPosition(720, 680);
	rect[49].setPosition(960, 40);
	rect[50].setPosition(1000, 200);
	rect[51].setPosition(1040, 320);
	rect[52].setPosition(1080, 400);
	rect[53].setPosition(1240, 440);
	rect[54].setPosition(1440, 40);
	rect[55].setPosition(1480, 200);
	rect[56].setPosition(1440, 200);
	rect[57].setPosition(1320, 480);
	rect[58].setPosition(1360, 80);
	rect[59].setPosition(1400, 640);
	rect[60].setPosition(1280, 80);
	rect[61].setPosition(1240, 80);
	rect[62].setPosition(1120, 280);
	rect[63].setPosition(1480, 640);
	rect[64].setPosition(1200, 520);
	rect[65].setPosition(1040, 560);
	rect[66].setPosition(960, 400);
	rect[67].setPosition(840, 640);
	rect[68].setPosition(920, 480);
	rect[69].setPosition(1000, 680);
	rect[70].setPosition(1280, 640);
	rect[71].setPosition(1400, 320);
	rect[72].setPosition(1040, 80);

	rect[73].setPosition(240, 280);
}

