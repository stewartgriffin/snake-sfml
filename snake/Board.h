#pragma once
#include "SnakeNode.h"

typedef enum {field_blank, field_snake, field_food} board_field_content;

class Board {
private:
	std::shared_ptr<SnakeNode> snake;
	int height, width;
	int foodX;
	int foodY;
	int score;
public:
	Board(int height, int width);
	int getScore() {
		return score;
	}
	bool tick(direction dir);
	board_field_content getFieldContent(int x, int y, bool ignoreSnakeHead);
};