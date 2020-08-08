/*
 * TargetCell.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */

#pragma once

#include <memory>

#include "../../Coordinate.h"
#include "../Cell.h"
#include "../MapState.h"

namespace Sokoban {
using std::enable_shared_from_this;

class TargetCell: public Cell {
public:
	TargetCell() = delete;
	TargetCell(const TargetCell&) = delete;
	TargetCell(MapState &mapState, uint32_t posX, uint32_t posY);
	TargetCell(MapState &mapState, const Coordinate &coordinate);
	virtual ~TargetCell() = default;

	virtual bool isTarget() const override;
	char getDisplayChar() const override;
};

} /* namespace Sokoban */
