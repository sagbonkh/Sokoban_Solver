/*
 * Player.cpp
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#include "Player.h"

namespace Sokoban {

Player::Player(const shared_ptr<MapState> mapState,
		const shared_ptr<Cell> cell) :
		CellOccupant(mapState, cell) {
}

CellOccupantType Player::getType() const {
	return CellOccupantType::Player;
}

} /* namespace Sokoban */
