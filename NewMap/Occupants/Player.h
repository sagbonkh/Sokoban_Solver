/*
 * Player.h
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#pragma once

#include "../CellOccupant.h"
namespace Sokoban {
using std::shared_ptr;
using std::enable_shared_from_this;

class Player: public CellOccupant {
public:
	Player() = delete;
	Player(const shared_ptr<MapState> mapState, const shared_ptr<Cell> cell =
			nullptr);
	virtual ~Player() = default;
	explicit Player(const Player &other) = default;

	CellOccupantType getType() const override;
};

} /* namespace Sokoban */
