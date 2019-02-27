#include "SnakeGame.h"
#include <iostream>
#include <map>

#define GAME_TICK_MILLISECONDS 300
#define BOARD_FIELD_PIXEL_SIZE 30
#define BOARD_TEXT_MARGIN_SIZE 200
#define BOARD_FIELDS_SIZE 20

#define WINDOW_SIZE_PIXEL_X (BOARD_FIELD_PIXEL_SIZE * BOARD_FIELDS_SIZE + BOARD_TEXT_MARGIN_SIZE)
#define WINDOW_SIZE_PIXEL_Y (BOARD_FIELD_PIXEL_SIZE * BOARD_FIELDS_SIZE)

#define TEXT_POSITION_PIXEL_X (BOARD_FIELD_PIXEL_SIZE * BOARD_FIELDS_SIZE  + 10)

SnakeGame::SnakeGame(bool _controlViaEvents)
{
	controlViaEvents = _controlViaEvents;
	gameBoard = std::unique_ptr<Board>(new Board(BOARD_FIELDS_SIZE, BOARD_FIELDS_SIZE));

	window.create(sf::VideoMode(WINDOW_SIZE_PIXEL_X, WINDOW_SIZE_PIXEL_Y), "Snake");
	window.setVerticalSyncEnabled(true);

	if (!font.loadFromFile("font/Roboto-Regular.ttf"))
		throw("FONT NOT FOUND");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setPosition(TEXT_POSITION_PIXEL_X,0);
	text.setCharacterSize(24);

	srand(time(NULL));
	clock.restart();
}

bool SnakeGame::mainLoop(void)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (controlViaEvents == true)
				break;
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					if (dir != right)
						dir = left;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					if (dir != left)
						dir = right;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (dir != up)
						dir = down;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (dir != down)
						dir = up;
				}
			}
		}
		if (endOfGame) {
			gameBoard = std::unique_ptr<Board>(new Board(BOARD_FIELDS_SIZE, BOARD_FIELDS_SIZE));
		}

		elapsedTime = clock.getElapsedTime();
		if (elapsedTime > sf::milliseconds(GAME_TICK_MILLISECONDS)) {
			clock.restart();
			endOfGame = gameBoard->tick(dir);
			window.clear();
			composeView();
			window.display();
		}
	}
	return true;
}

void SnakeGame::composeView(void)
{
	for (int x = 0; x < BOARD_FIELDS_SIZE; x++)
		for (int y = 0; y < BOARD_FIELDS_SIZE; y++) {
			sf::RectangleShape field;
			field.setSize(sf::Vector2f(BOARD_FIELD_PIXEL_SIZE, BOARD_FIELD_PIXEL_SIZE));
			field.setOutlineColor(sf::Color::Blue);
			field.setOutlineThickness(-1);
			field.setPosition(x * BOARD_FIELD_PIXEL_SIZE, y * BOARD_FIELD_PIXEL_SIZE);

			std::map<board_field_content, sf::Color> filedColorMap = { {field_blank, sf::Color::Black}, {field_snake, sf::Color::White}, {field_food, sf::Color::Red} };
			field.setFillColor(filedColorMap[gameBoard->getFieldContent(x, y, false)]);
			window.draw(field);
		}

	auto score = std::unique_ptr<std::string>(new std::string("SCORE: "));
	score->append(std::to_string(gameBoard->getScore()));
	text.setString(*score);
	window.draw(text);
}

void SnakeGame::controlRequest(direction _dir)
{
	dir = _dir;
}