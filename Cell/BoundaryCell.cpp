/*
 * BoundaryCell.cpp
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#include "BoundaryCell.h"

namespace Sokoban {

BoundaryCell::BoundaryCell(shared_ptr<MapState> mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}
BoundaryCell::BoundaryCell(shared_ptr<MapState> mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}


bool BoundaryCell::isOccupied() const {
	return false;
}

bool BoundaryCell::isTarget() const {
	return false;
}

void BoundaryCell::moveOccupantTo(const std::shared_ptr<Sokoban::Cell> &other) {
	throw "Not implemented for Boundary Cells";
}

bool BoundaryCell::hasPlayer() const {
	return false;
}

bool BoundaryCell::hasBox() const {
	return false;
}

void BoundaryCell::setOccupant(
		const std::shared_ptr<Sokoban::CellOccupant> &occupant) {
	throw "Not implemented for Boundary Cells";
}

bool BoundaryCell::isEmpty() const {
	return true;
}

bool BoundaryCell::canBeOccupied() const {
	return false;
}

void BoundaryCell::enterFrom(Sokoban::Direction dir,
		std::shared_ptr<Sokoban::CellOccupant> occupant) {
	throw "Not implemented for Boundary Cells";
}

bool BoundaryCell::canEnterFrom(Sokoban::Direction dir,
		std::shared_ptr<Sokoban::CellOccupant> occupant) {
	return false;
}

void BoundaryCell::pushOccupantIn(Sokoban::Direction dir) {
	throw "Not implemented for Boundary Cells";
}

bool BoundaryCell::canPushOccupantIn(Sokoban::Direction dir) {
	return false;
}

} /* namespace Sokoban */
