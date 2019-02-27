#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Board.h"

class SnakeGame
{
private:
	bool controlViaEvents;
	sf::Font font;
	sf::Text text;
	sf::Clock clock;
	sf::Time elapsedTime;
	direction dir = left;
	std::unique_ptr<Board> gameBoard;
	bool endOfGame = true;
	sf::RenderWindow window;

	void composeView(void);

public:
	SnakeGame(bool externalControl);
	bool mainLoop(void);
	void controlRequest(direction _dir);
};

