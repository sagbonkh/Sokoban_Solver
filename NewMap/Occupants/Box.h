/*
 * Box.h
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#pragma once

#include "../CellOccupant.h"
namespace Sokoban {
using std::shared_ptr;
using std::enable_shared_from_this;

class Box: public CellOccupant {
public:
	Box() = delete;
	Box(const shared_ptr<MapState> mapState, const shared_ptr<Cell> cell =
			nullptr);
	virtual ~Box() = default;
	explicit Box(const Box &other) = default;

	CellOccupantType getType() const override;
};

} /* namespace Sokoban */
