// Copyright Tobias Faller 2016

#include <cassert>

#include "Coordinate.h"
#include "Direction.h"
#include "OldMap/StaticMap.h"

namespace Sokoban {

Coordinate::Coordinate(map_unit_t posX, map_unit_t posY) :
		x(posX), y(posY) {
}
void Coordinate::set(map_unit_t posX, map_unit_t posY) {
	this->x = posX;
	this->y = posY;
}

map_unit_t Coordinate::getX() const {
	return x;
}
map_unit_t Coordinate::getY() const {
	return y;
}

bool Coordinate::operator==(const Coordinate &other) const {
	return (x == other.x) && (y == other.y);
}

bool Coordinate::operator<(const Coordinate &other) const {
	return (y < other.y) || (x < other.x);
}

Coordinate Coordinate::getAdjacent(Direction dir) const {
	map_unit_t newX = x;
	map_unit_t newY = y;
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

Coordinate::Coordinate(const initializer_list<map_unit_t> &values) {
	assert(values.size() == 2);
	auto it = values.begin();
	x = *(it++);
	y = *(it++);
}

Coordinate::Coordinate(const tuple<map_unit_t, map_unit_t> &values) {
	tie(x, y) = values;
}

}  // namespace Sokoban
