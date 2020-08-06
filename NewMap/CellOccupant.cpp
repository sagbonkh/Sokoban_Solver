/*
 * CellOccupant.cpp
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#include "../CellOccupant.h"

#include <memory>
#include <utility>

#include "../Map/MapState.h"
#include "../NewMap/Cell.h"

namespace Sokoban {
using std::shared_ptr;
using std::swap;

CellOccupant::CellOccupant(const shared_ptr<MapState> mapState,
		const shared_ptr<Cell> cell) :
		_mapState(mapState), _cell(cell) {
}

shared_ptr<Cell> CellOccupant::getCell() const {
	return _cell;
}

shared_ptr<MapState> CellOccupant::getMapState() const {
	return _mapState;
}

bool CellOccupant::isTarget() const {
	return _cell->isTarget();
}

bool CellOccupant::isNothing() const {
	return getType() == CellOccupantType::Nothing;
}

bool CellOccupant::isPlayer() const {
	return getType() == CellOccupantType::Player;
}

bool CellOccupant::isBox() const {
	return getType() == CellOccupantType::Box;
}

CellOccupant::operator bool() const {
	return !isNothing();
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

CellOccupantType CellOccupant::getType() const {
	return CellOccupantType::Nothing;
}

} /* namespace Sokoban */
