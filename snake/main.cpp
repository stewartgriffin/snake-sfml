#include "SnakeGame.h"

int WinMain()
{
	SnakeGame game(false);
	while (game.mainLoop());
	return 0;
}