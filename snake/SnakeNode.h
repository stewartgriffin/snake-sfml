#pragma once
#include <memory>

typedef enum {up, down, left, right} direction;

class SnakeNode : public std::enable_shared_from_this<SnakeNode>
{
public:
	std::shared_ptr<SnakeNode> next = nullptr;
	int x, y;
	SnakeNode() {
		x = 0;
		y = 0;
		next = nullptr;
	}
	SnakeNode(std::shared_ptr<SnakeNode> _next, int _x, int _y);
	SnakeNode(const SnakeNode & otherNode) {
		x = otherNode.x;
		y = otherNode.y;
		if (otherNode.next != nullptr) {
			*next = *otherNode.next;
		}
		else {
			next = nullptr;
		}
	}
	void move(direction dir);
	void moveAndGrow(direction dir);
	bool getSnakeNodeOnCooridinates(std::shared_ptr<SnakeNode> _next, int x, int y);
private:
	void updateCoordinates(int _x, int _y);
	std::shared_ptr<SnakeNode> getLastNode(std::shared_ptr<SnakeNode> _next);
};