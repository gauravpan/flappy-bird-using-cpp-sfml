#include <SFML/Graphics.hpp>
#include <iostream>

#define HEIGHT 512
#define WIDTH 288
#define GAP 90

using namespace sf;

//generates 0 to -260
float randY()
{
	return -((((float)rand() / (RAND_MAX))) * 260);
}

int main()
{
	// Create the main window
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Flappy Bird");
	window.setFramerateLimit(60);
	class pipe
	{
	public:
		float x = WIDTH;
		float y = randY();
	};

	int i;

	bool isGameOver = false, startGame = false;
	signed int score = 0;

	pipe pipes[2];
	pipes[0].x = WIDTH;
	pipes[1].x = WIDTH + 230;

	// Load a sprites to display

	Texture backgroundImage;
	if (!backgroundImage.loadFromFile("images/bg.png"))
		return EXIT_FAILURE;
	Sprite background(backgroundImage);
	background.setPosition(Vector2f(0, 0));

	Texture floorImage;
	if (!floorImage.loadFromFile("images/fg.png"))
		return EXIT_FAILURE;
	Sprite floor(floorImage);
	floor.setPosition(Vector2f(0, HEIGHT - 100));

	Texture pipeUp;
	if (!pipeUp.loadFromFile("images/pipeup.png"))
		return EXIT_FAILURE;
	Sprite pipeNorth(pipeUp);

	Texture pipeDown;
	if (!pipeDown.loadFromFile("images/pipedown.png"))
		return EXIT_FAILURE;
	Sprite pipeSouth(pipeDown);

	Texture birdPic;
	if (!birdPic.loadFromFile("images/bird.png"))
		return EXIT_FAILURE;
	Sprite bird(birdPic);
	bird.setPosition(Vector2f(WIDTH / 5, HEIGHT / 2));

	//font
	Font font;
	if (!font.loadFromFile("font/font.otf"))
		return EXIT_FAILURE;

	Text playGameText;
	playGameText.setFont(font);
	playGameText.setString("Press Enter or Space to Play Game...");
	playGameText.setCharacterSize(13);
	playGameText.setPosition(30, (HEIGHT / 3));

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition(WIDTH - 60, 3);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(25);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(80, HEIGHT / 3);

	Text playAgainText;
	playAgainText.setFont(font);
	playAgainText.setString("Press Enter or Space  to  Play again...");
	playAgainText.setCharacterSize(13);
	playAgainText.setPosition(30, (HEIGHT / 3) + 35);

	while (window.isOpen())
	{
		while (!startGame)
		{
			Event eventTOStart;
			while (window.pollEvent(eventTOStart))
			{

				switch (eventTOStart.key.code)
				{
				case Keyboard::Enter:
					startGame = true;
					break;
				case Keyboard::Space:
					startGame = true;
					break;
				}
				// Close window: exit
				if (eventTOStart.type == Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(playGameText);
			window.display();
		}

		while (!isGameOver)
		{
			// Clear screen
			window.clear();
			window.draw(background);
			// Process events
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.key.code)
				{
				case Keyboard::Space:
					bird.move(0, -23);
					score = score + 10;
					break;
				}

				// Close window: exit
				if (event.type == Event::Closed)
					window.close();
			}

			bird.move(0, (float)2.3);
			// update pipe positions
			for (i = 0; i < 2; i++)
			{
				pipes[i].x = pipes[i].x - (float)1.7;
				if (pipes[i].x < -90)
				{
					pipes[i].x = WIDTH + 50;
					pipes[i].y = randY();
				}
			}
			scoreText.setString(std::to_string(score));
			//draw pipes

			for (i = 0; i < 2; i++)
			{

				pipeNorth.setPosition(pipes[i].x, pipes[i].y);
				window.draw(pipeNorth);
				// sprite.getGlobalBounds().intersects(sprite_two.getGlobalBounds())
				if (bird.getGlobalBounds().intersects(pipeNorth.getGlobalBounds()) || bird.getGlobalBounds().intersects(pipeSouth.getGlobalBounds()))
				{
					isGameOver = true;
				}
				pipeSouth.setPosition(pipes[i].x, (242 + pipes[i].y) + GAP);
				window.draw(pipeSouth);
			}
			//collision detection
			// sprite.getGlobalBounds().intersects(sprite_two.getGlobalBounds())

			if (bird.getGlobalBounds().intersects(pipeNorth.getGlobalBounds()) ||
				bird.getGlobalBounds().intersects(pipeSouth.getGlobalBounds()) ||
				bird.getGlobalBounds().intersects(floor.getGlobalBounds()))
			{
				isGameOver = true;
			}

			window.draw(floor);
			window.draw(bird);
			window.draw(scoreText);
			// Update the window
			window.display();
		}

		Event eventToRestart;
		while (window.pollEvent(eventToRestart))
		{

			switch (eventToRestart.key.code)
			{
			case Keyboard::Enter:

				pipes[0].x = WIDTH;
				pipes[1].x = WIDTH + 230;
				isGameOver = false;
				break;

			case Keyboard::Space:
				for (i = 0; i < 2; i++)
				{
					pipes[i].y = randY();
				}

				pipes[0].x = WIDTH;
				pipes[1].x = WIDTH + 230;
				isGameOver = false;
				bird.setPosition(Vector2f(WIDTH / 5, HEIGHT / 2));
				score = 0;
				break;
			}
			// Close window: exit
			if (eventToRestart.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(background);
		window.draw(gameOverText);
		window.draw(playAgainText);
		window.display();
	}
	// std::cout<<"  "<<std::endl;

	return EXIT_SUCCESS;
}
