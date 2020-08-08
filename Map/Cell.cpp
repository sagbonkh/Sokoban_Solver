/*
 * Cell.cpp
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#include "../Map/Cell.h"

#include "../Map/Cells/TargetCell.h"
#include "../Map/Cells/WallCell.h"
#include "../Map/Occupants/Box.h"
#include "../Map/Occupants/Player.h"

namespace Sokoban {

Cell::Cell(MapState &mapState, uint32_t posX, uint32_t posY) noexcept :
		Coordinate(posX, posY), _mapState(mapState) {
}
Cell::Cell(MapState &mapState, const Coordinate &coordinate) noexcept :
		Coordinate(coordinate), _mapState(mapState) {
}

shared_ptr<CellOccupant> Cell::getOccupant() const {
	return _occupant;
}

MapState& Cell::getMapState() const {
	return _mapState;
}

bool Cell::isOccupied() const {
	return static_cast<bool>(_occupant) && static_cast<bool>(*_occupant);
}

bool Cell::isTarget() const {
	return false;
}

bool Cell::hasPlayer() const {
	return static_cast<bool>(_occupant) && _occupant->isPlayer();
}

void Cell::setOccupant(const shared_ptr<CellOccupant> &occupant) {
	if (!canBeOccupied() || !isUnoccupied())
		throw "Target cell already occupied.";
	_occupant = occupant;
	_occupant->updateCell(getptr());
}

void Cell::moveOccupantTo(const shared_ptr<Cell> &other) {
	if (!other->canBeOccupied() || !other->isUnoccupied()) {
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
	return _mapState.get(adjCoords);
}

bool Cell::canPushOccupantIn(Direction dir) {
	// if we are empty, we have no occupant to push. return true
	if (isUnoccupied())
		return true;
	// get adjacent cell (in direction specified)
	shared_ptr<Cell> adjCell = getAdjacent(dir);
	// now it's down to if adjacent cell can be occupied and it's not already occupied
	return adjCell->canBeOccupied() && adjCell->isUnoccupied();

}

// to be called from the cell a player wishes to move to (which may contain a box)
// tries to move any box on this cell, to the next cell in the same direction
Cell::move_result_t Cell::pushOccupantIn(Direction dir) {
	// if we have no occupant, return successful, but note nothing moved
	if (isUnoccupied())
		return make_tuple<bool, bool, bool>(true, false, false);
	// if we can't push our occupant, return unsuccessful
	if (!canPushOccupantIn(dir))
		return make_tuple<bool, bool, bool>(false, false, false);

	if (getOccupant()->getType() != CellOccupantType::Box) {
		throw "Invalid move. This function is only meant for boxes.";
	}

	// get adjacent cell (in direction specified)
	shared_ptr<Cell> adjCell = getAdjacent(dir);
	moveOccupantTo(adjCell);
	return make_tuple<bool, bool, bool>(true, true, false);
}

bool Cell::canEnterFrom(Direction dir, shared_ptr<CellOccupant> occupant) {
	// if this cell can't be occupied, we can't enter it from any direction, so return false
	// if we can't push the occupant of the  cell in the requested direction return false
	return canBeOccupied() && canPushOccupantIn(dir);
}

// when player tries to enter this cell, this is called with the the player's CellOccpant
// and the direction from which the player is entering
Cell::move_result_t Cell::enterFrom(Direction dir,
		shared_ptr<CellOccupant> occupant) {
	if (occupant->getType() != CellOccupantType::Player)
		throw "Invalid move. This function is only meant for the player.";

	// if this cell can't be entered (either because it can't be occupied or because the occupant can't be displaced
	// indicate failure
	if (!canEnterFrom(dir, occupant))
		return make_tuple<bool, bool, bool>(false, false, false);

	shared_ptr<Cell> adjCell = getAdjacent(dir);
	const move_result_t push_result = adjCell->pushOccupantIn(dir);
	// if not successful somehow, abort
	if (!get<0>(push_result))
		return make_tuple<bool, bool, bool>(false, false, false);

	shared_ptr<Cell> prevCell = occupant->getCell();
	prevCell->moveOccupantTo(getptr());
	return make_tuple<bool, bool, bool>(true, bool(get<1>(push_result)), true);
}

// if the cell has no occupant
bool Cell::isUnoccupied() const {
	return !isOccupied();
}

// if the cell is occupy-able (i.e. isn't a boundary)
bool Cell::canBeOccupied() const {
	return true;
}

shared_ptr<Cell> Cell::fromCellType(MapState &mapState,
		const Coordinate &c, const CellContents &type) {
	shared_ptr<Cell> cell = nullptr;
	shared_ptr<CellOccupant> cellOccupant = nullptr;

	if ((type & CellContents::Goal) == CellContents::Goal) {
		cell = make_shared<TargetCell>(mapState, c);
	} else if ((type & CellContents::Wall) == CellContents::Wall) {
		cell = make_shared<WallCell>(mapState, c);
	} else {
		cell = make_shared<Cell>(mapState, c);
	}
	if ((type & CellContents::Player) == CellContents::Player) {
		cellOccupant = make_shared<Player>(mapState, cell);
	} else if ((type & CellContents::Box) == CellContents::Box) {
		cellOccupant = make_shared<Box>(mapState, cell);
	}
	if (cellOccupant)
		cell->setOccupant(cellOccupant);
	return cell;
}

std::shared_ptr<Cell> Cell::getptr() {
	return shared_from_this();
}

bool Cell::isWall() const {
	return false;
}

char Cell::getDisplayChar() const {
	if (isOccupied() && getOccupant()->getType() == CellOccupantType::Player) {
		return '@';  // Player
	} else if (isOccupied() && getOccupant()->getType() == CellOccupantType::Box) {
		return '$';
	} else {
		return ' '; // Nothing (' ')
	}
}

Cell::operator char() const {
	return getDisplayChar();
}

} /* namespace Sokoban */
