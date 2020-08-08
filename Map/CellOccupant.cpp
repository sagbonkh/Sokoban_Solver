/*
 * CellOccupant.cpp
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#include <memory>
#include <utility>

#include "Map/CellOccupant.h"
#include "Map/Cell.h"
#include "Map/MapState.h"

namespace Sokoban {
using std::shared_ptr;
using std::swap;

CellOccupant::CellOccupant(MapState &mapState,
		const shared_ptr<Cell> cell) :
		_mapState(mapState), _cell(cell) {
}

shared_ptr<Cell> CellOccupant::getCell() const {
	return _cell;
}

MapState& CellOccupant::getMapState() {
	return _mapState;
}

bool CellOccupant::isTarget() const {
	return _cell->isTarget();
}

bool CellOccupant::isNothing() const {
	return getType() == Type::None;
}

bool CellOccupant::isPlayer() const {
	return getType() == Type::Player;
}

bool CellOccupant::isBox() const {
	return getType() == Type::Box;
}

CellOccupant::operator bool() const {
	return !isNothing();
}

bool CellOccupant::isOnTarget() const {
	return _cell->isTarget();
}

shared_ptr<CellOccupant> CellOccupant::getptr() {
	return shared_from_this();
}

Coordinate CellOccupant::getCoordinate() const {
	return *dynamic_cast<const Coordinate*>(getCell().get());
}

void CellOccupant::updateCell(const shared_ptr<Cell> &cell) {
	if (cell->getOccupant() != getptr()) {
		throw "Cell occupant mismatch";
	}
	_cell = cell;
}

CellOccupant::Type CellOccupant::getType() const {
	return Type::None;
}

} /* namespace Sokoban */
