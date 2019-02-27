#include <map>
#include <tuple>
#include "SnakeNode.h"

SnakeNode::SnakeNode(std::shared_ptr<SnakeNode> _next, int _x, int _y)
{
	x = _x;
	y = _y;
	next = _next;
}

void SnakeNode::move(direction dir)
{
	std::map<direction, std::tuple<int, int>> directionMap = { {up, {0, 1}}, {down, {0, -1}}, {left, {-1, 0}}, {right, {1, 0}} };
	this->updateCoordinates(x + std::get<0>(directionMap[dir]), y + std::get<1>(directionMap[dir]));
}

void SnakeNode::moveAndGrow(direction dir)
{
	auto lastNode = std::shared_ptr<SnakeNode> (new SnakeNode(*getLastNode(shared_from_this())));
	move(dir);
	auto newLastNode = getLastNode(shared_from_this());
	newLastNode->next = lastNode;
}

void SnakeNode::updateCoordinates(int new_x, int new_y)
{
	if (next != nullptr) {
		next->updateCoordinates(this->x, y);
	}
	x = new_x;
	y = new_y;
}

std::shared_ptr<SnakeNode> SnakeNode::getLastNode(std::shared_ptr<SnakeNode> node)
{
	if (node->next != nullptr) {
		return getLastNode(node->next);	
	}
	return node;
}

bool SnakeNode::getSnakeNodeOnCooridinates(std::shared_ptr<SnakeNode> node, int x, int y)
{
	if ((node->x == x) && (node->y == y)) {
		return true;
	}
	else if (node->next != nullptr) {
		return getSnakeNodeOnCooridinates(node->next, x, y);
	}
	return false;
}