// Copyright Tobias Faller 2016

#include "Coordinate.h"
#include "Direction.h"
#include "Map/StaticMap.h"

namespace Sokoban {

Coordinate::Coordinate(uint32_t posX, uint32_t posY) :
		x(posX), y(posY) {
}
Coordinate::Coordinate() :
		Coordinate(0, 0) {
}
Coordinate::~Coordinate() {
}

void Coordinate::set(uint32_t posX, uint32_t posY) {
	this->x = posX;
	this->y = posY;
}

uint32_t Coordinate::getX() const {
	return x;
}
uint32_t Coordinate::getY() const {
	return y;
}

bool Coordinate::operator==(const Coordinate &other) const {
	return (x == other.x) && (y == other.y);
}

bool Coordinate::operator<(const Coordinate &other) const {
	return (y < other.y) || (x < other.x);
}

Coordinate Coordinate::getAdjacent(Direction dir) const {
	uint32_t newX = x;
	uint32_t newY = y;
	if (dir == Up) {
		++newY;
	} else if (dir == Down) {
		--newY;
	} else if (dir == Left) {
		--newX;
	} else if (dir == Right) {
		++newX;
	} else {
		throw INDEX_OUT_OF_BOUNDS;
	}
	return Coordinate(newX, newY);
}

}  // namespace Sokoban
