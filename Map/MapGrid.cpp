/*
 * MapGrid.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */
#include "../Map/MapGrid.h"

#include <memory>
#include <functional>
#include <algorithm>

#include "../Map/Cell.h"
#include "../Map/CellOccupant.h"
#include "../Map/Cells/TargetCell.h"
#include "../Map/Occupants/Box.h"
#include "../Map/Occupants/Player.h"

using std::transform;
using std::shared_ptr;
using std::bind;
using std::mem_fn;
using std::dynamic_pointer_cast;
using namespace std::placeholders;

namespace Sokoban {

MapGrid::MapGrid(MapState &mapState, const shared_ptr<const initial_map_t> &initialMap) : _mapState(mapState),
		_initialMap(initialMap), _width(initialMap->front().size()), _height(initialMap->size()) {
	Coordinate player;
	set<Coordinate> boxes, targets;
	for (map_unit_t y = 0; y < _height; ++y) {
		for (map_unit_t x = 0; x < _width; ++x) {
			CellContents content((*initialMap)[y][x]);
			if ((content & CellContents::Player) == CellContents::Player) {
				player = { x, y };
			} else if ((content & CellContents::Box) == CellContents::Box) {
				boxes.insert( { x, y });
			}
			if ((content & CellContents::Goal) == CellContents::Goal) {
				targets.insert( { x, y });
			}
		}
	}
	_player = dynamic_pointer_cast<Player, CellOccupant>(get(player)->getOccupant());
	for (const Coordinate &c : boxes)
		_boxes.insert(dynamic_pointer_cast<Box, CellOccupant>(get(c)->getOccupant()));
	for (const Coordinate &c : targets)
		_targets.insert(dynamic_pointer_cast<TargetCell, Cell>(get(c)));
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

const map_unit_t& MapGrid::getHeight() const {
	return _height;
}

const map_unit_t& MapGrid::getWidth() const {
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

uint8_t MapGrid::getNumBoxes() const {
	return getBoxes().size();
}

const shared_ptr<Player>& MapGrid::getPlayer() const {
	return _player;
}

const set<shared_ptr<Box> >& MapGrid::getBoxes() const {
	return _boxes;
}

const set<shared_ptr<TargetCell> >& MapGrid::getTargets() const {
	return _targets;
}

const shared_ptr<const MapGrid::initial_map_t>& MapGrid::getInitialMap() const {
	return _initialMap;
}

void MapGrid::reset() {
	_cells.clear();
}

} /* namespace Sokoban */
