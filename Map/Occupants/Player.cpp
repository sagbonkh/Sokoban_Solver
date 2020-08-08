/*
 * Player.cpp
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#include "Map/Occupants/Player.h"

namespace Sokoban {

Player::Player(MapState &mapState,
		const shared_ptr<Cell> cell) :
		CellOccupant(mapState, cell) {
}

CellOccupant::Type Player::getType() const {
	return Type::Player;
}

Cell::move_result_t Player::moveIn(Direction dir) {
	shared_ptr<Cell> nextCell = getCell()->getAdjacent(dir);
	return nextCell->enterFrom(dir, getptr());
}

void Player::reverseMoveIn(Direction initialDir, bool boxMoved) {
	shared_ptr<Cell> initialCell = getCell();
	Direction oppositeDir = OppositeDirections.at(initialDir);
	shared_ptr<Cell> newCell = getCell()->getAdjacent(oppositeDir);
	Cell::move_result_t moveResult = newCell->enterFrom(oppositeDir, getptr());
	if (!get<2>(moveResult)) throw "Reverse move of player failed!";
	if (!boxMoved) return;

	shared_ptr<Cell> currentBoxCell = initialCell->getAdjacent(initialDir);
	moveResult = currentBoxCell->pushOccupantIn(oppositeDir);
	if (!get<1>(moveResult)) throw "Reverse move of box failed!";
}


} /* namespace Sokoban */
