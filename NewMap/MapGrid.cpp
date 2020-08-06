/*
 * MapGrid.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */
#include <memory>

#include "MapGrid.h"

namespace Sokoban {
using std::shared_ptr;
MapGrid::MapGrid(const shared_ptr<const initial_map_t> &initialMap) :
		_width(initialMap->front().size()), _height(initialMap->size()), _initialCells(
				initialMap) {
}

MapGrid::MapGrid(const MapGrid &other) :
		MapGrid(other._initialCells) {
}

shared_ptr<Cell> MapGrid::get(const Coordinate &c) {
	if (_cells.contains(c))
		return _cells[c];
	return nullptr;
}

map_unit_t MapGrid::getHeight() const {
	return _height;
}

map_unit_t MapGrid::getWidth() const {
	return _width;
}


void MapGrid::reset() {
}

} /* namespace Sokoban */
