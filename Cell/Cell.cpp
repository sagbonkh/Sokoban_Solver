/*
 * Cell.cpp
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#include "Cell.h"

namespace Sokoban {


Cell::Cell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY) :
		Coordinate(posX, posY), _mapState(mapState) {
}
Cell::Cell(shared_ptr<MapState> mapState, const Coordinate &coordinate) :
		Coordinate(coordinate), _mapState(mapState) {
}

shared_ptr<CellOccupant> Cell::getOccupant() const {
	return _occupant;
}

shared_ptr<MapState> Cell::getMapState() const {
	return _mapState;
}

bool Cell::isOccupied() const {
	return static_cast<bool>(_occupant) && static_cast<bool>(*_occupant);
}

bool Cell::isTarget() const {
	return _mapState->isTarget(*dynamic_cast<const Coordinate*>(this));
}

bool Cell::hasPlayer() const {
	return static_cast<bool>(_occupant) && _occupant->isPlayer();
}

void Cell::setOccupant(const shared_ptr<CellOccupant> &occupant) {
	if (!canBeOccupied() || !isEmpty())
		throw "Target cell already occupied.";
	_occupant = occupant;
	_occupant->updateCell(getptr());
}

void Cell::moveOccupantTo(const shared_ptr<Cell> &other) {
	if (!other->canBeOccupied() || !other->isEmpty()) {
		throw "Target cell already occupied.";
	}
	swap(_occupant, other->_occupant);
	_occupant->updateCell(getptr());
	other->_occupant->updateCell(other);
}

bool Cell::hasBox() const {
	return static_cast<bool>(_occupant) && _occupant->isBox();
}

shared_ptr<Cell> Cell::getAdjacent(Direction dir) const {
	Coordinate adjCoords = Coordinate::getAdjacent(dir);
	return _mapState->get(adjCoords);
}

bool Cell::canPushOccupantIn(Direction dir) {
	// if we are empty, we have no occupant to push. return true
	if (isEmpty())
		return true;
	// get adjacent cell (in direction specified)
	shared_ptr<Cell> adjCell = getAdjacent(dir);
	// now it's down to if adjacent cell can be occupied and it's not already occupied
	return adjCell->canBeOccupied() && adjCell->isEmpty();

}

// to be called from the cell next to the player (in the direction they are moving)
// tries to move any box on this cell, to the next cell in the same direction
void Cell::pushOccupantIn(Direction dir) {
	// if we can't push our occpant, throw an error
	if (!canPushOccupantIn(dir))
		throw "Cannot push cell's occupant in the given direction";
	// get adjacent cell (in direction specified)
	shared_ptr<Cell> adjCell = getAdjacent(dir);
	moveOccupantTo(adjCell);
}

bool Cell::canEnterFrom(Direction dir, shared_ptr<CellOccupant> occupant) {
	// if this cell can't be occupied, we can't enter it from any direction, so return false
	// if we can't push the occupant of the  cell in the requested direction return false
	return canBeOccupied() && canPushOccupantIn(dir);
}

// when player tries to enter this cell, this is called with the the player's CellOccpant
// and the direction from which the player is entering
void Cell::enterFrom(Direction dir, shared_ptr<CellOccupant> occupant) {
	if (!canEnterFrom(dir, occupant))
		throw "Cannot enter this cell from the given direction";
	// we were able to push our occupant, so we will accept our new one
	shared_ptr<Cell> prevCell = occupant->getCell();
	prevCell->moveOccupantTo(getptr());
}

// if the cell has no occupant
bool Cell::isEmpty() const {
	return !isOccupied();
}

// if the cell is occupy-able (i.e. isn't a boundary)
bool Cell::canBeOccupied() const {
	return true;
}

std::shared_ptr<Cell> Cell::getptr() {
	return shared_from_this();
}

} /* namespace Sokoban */
