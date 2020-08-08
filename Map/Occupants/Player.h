/*
 * Player.h
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#pragma once

#include <map>

#include "Map/CellOccupant.h"

using std::shared_ptr;
using std::enable_shared_from_this;
using std::map;
namespace Sokoban {

class Player: public CellOccupant {
public:
	static const map<Direction, Direction> OppositeDirections;

	Player() = delete;
	Player(MapState &mapState, const shared_ptr<Cell> cell =
			nullptr);
	virtual ~Player() = default;
	explicit Player(const Player &other) = default;

	Cell::move_result_t moveIn(Direction dir);
	void reverseMoveIn(Direction initialDir, bool boxMoved);

	CellOccupant::Type getType() const override;

};

} /* namespace Sokoban */
