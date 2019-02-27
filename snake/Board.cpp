#include "Board.h"
#include <stdlib.h>

#define SCORE_PER_GROW 100
#define SCORE_REDUCTION_PER_TICK 1

Board::Board(int h, int w)
{
	score = 0;
	height = h;
	width = w;
	foodX = rand() % width;
	foodY = rand() % height;
	snake = std::shared_ptr<SnakeNode>(new SnakeNode(nullptr, w / 2, h / 2));
}

bool Board::tick(direction dir)
{
	score -= SCORE_REDUCTION_PER_TICK;
	if ((snake->x == foodX) && (snake->y == foodY)) {
		score += SCORE_PER_GROW;
		snake->moveAndGrow(dir);
		do{
			foodX = rand() % width;
			foodY = rand() % height;
		} while (getFieldContent(foodX, foodY, false) == field_snake); 
		return false;
	}
	snake->move(dir);
	if (getFieldContent(snake->x, snake->y, true) == field_snake)
		return true;
	if (snake->x <0 || snake->x >= width)
		return true;
	if (snake->y <0 || snake->y >= height)
		return true;
	return false;
}

board_field_content Board::getFieldContent(int x, int y, bool ignoreSnakeHead)
{
	bool result = false;

	if (ignoreSnakeHead == false) {
		result = snake->getSnakeNodeOnCooridinates(snake, x, y);
	}
	else {
		if (snake->next == nullptr)
			return field_blank;
		result = snake->next->getSnakeNodeOnCooridinates(snake->next, x, y);
	}

	if (result == true) {
		return field_snake;
	}
	if ((foodX == x) && (foodY == y)) {
		return field_food;
	}
	return field_blank;
}