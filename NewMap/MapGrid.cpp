/*
 * MapGrid.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */
#include <memory>

#include "MapGrid.h"
#include "Cell.h"

namespace Sokoban {
using std::shared_ptr;
MapGrid::MapGrid(const shared_ptr<MapState> &mapState) :
		_mapState(mapState), _width(mapState->getWidth()), _height(
				mapState->getHeight()), _initialMap(mapState->getInitialMap()) {
}


const shared_ptr<Cell>& MapGrid::get(const Coordinate &c) {
	if (_cells.contains(c)) // @suppress("Method cannot be resolved")
		return _cells[c];
	CellContents cellType = (*_initialMap)[c.y][c.x];
	return _cells[c] = Cell::fromCellType(_mapState, c, cellType);
}

const shared_ptr<Cell>& MapGrid::operator[](const Coordinate &c) {
	return get(c);
}


map_unit_t MapGrid::getHeight() const {
	return _height;
}

map_unit_t MapGrid::getWidth() const {
	return _width;
}

const shared_ptr<const Cell> MapGrid::get(const Coordinate &c) const {
	if (_cells.contains(c)) // @suppress("Method cannot be resolved")
		return _cells.at(c);
	CellContents cellType = (*_initialMap)[c.y][c.x];
	return _cells[c] = Cell::fromCellType(_mapState, c, cellType);
}

const shared_ptr<const Cell> MapGrid::operator [](const Coordinate &c) const {
	return get(c);
}

void MapGrid::reset() {
	_cells.clear();
}

} /* namespace Sokoban */
