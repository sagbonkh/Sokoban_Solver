/*
 * MapState.cpp
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#include <algorithm>
#include <functional>

#include "Map/MapState.h"
#include "Map/CellOccupant.h"
#include "Map/Occupants/Box.h"

using std::bind;
using std::mem_fn;
using std::count_if;
using std::all_of;
using namespace std::placeholders;

namespace Sokoban {

MapState::MapState(const shared_ptr<const MapGrid::initial_map_t> &map) : _mapGrid(make_shared<MapGrid>(*this, map)),
		_height(_mapGrid->getHeight()), _width(_mapGrid->getWidth()) {
}

const shared_ptr<Cell>& MapState::get(const Coordinate &position) {
	return (*_mapGrid)[position];
}

const shared_ptr<Cell>& MapState::get(uint32_t x, uint32_t y) {
	return (*_mapGrid)[ { x, y }];
}

const shared_ptr<Cell>& MapState::operator [](const Coordinate &c) {
	return get(c);
}

shared_ptr<CellOccupant> MapState::getOccupant(const Coordinate &position) {
	shared_ptr<Cell> cell = get(position);
	if (!cell) return nullptr;
	return cell->getOccupant();
}

shared_ptr<CellOccupant> MapState::getOccupant(uint32_t x, uint32_t y) {
	return getOccupant( { x, y });
}

uint32_t MapState::getWidth() const {
	return _width;
}

uint32_t MapState::getHeight() const {
	return _height;
}

const shared_ptr<Player>& MapState::getPlayer() const {
	return _mapGrid->getPlayer();
}

int MapState::numBoxes() const {
	return getBoxes().size();
}

int MapState::numBoxesOnTargets() const {
	const set<shared_ptr<Box>> boxes = getBoxes();
	return count_if(boxes.begin(), boxes.end(), bind(mem_fn(&Box::isOnTarget), _1));
}

bool MapState::won() const {
	const set<shared_ptr<Box>> boxes = getBoxes();
	return all_of(boxes.begin(), boxes.end(), bind(mem_fn(&Box::isOnTarget), _1));
}

const shared_ptr<const MapGrid::initial_map_t> MapState::getInitialMap() const {
	return _mapGrid->getInitialMap();
}

const shared_ptr<const MapGrid> MapState::getGrid() const {
	return _mapGrid;
}

bool MapState::isValid(const Coordinate &c) const {
	// TODO: deal with negative coordinates flipping over to really high positive numbers
	if (c.x >= getWidth()) return false;
	if (c.y >= getHeight()) return false;
	return true;
}

bool MapState::isValid(uint32_t x, uint32_t y) const {
	return isValid( { x, y });
}

const set<shared_ptr<Box> >& MapState::getBoxes() const {
	return _mapGrid->getBoxes();
}

const set<shared_ptr<TargetCell> >& MapState::getTargets() const {
	return _mapGrid->getTargets();
}

}
