/*
 * TargetCell.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */

#pragma once

#include <memory>

#include "../Coordinate.h"
#include "../Map/MapState.h"
#include "Cell.h"

namespace Sokoban {
using std::enable_shared_from_this;

class TargetCell: public Cell, public enable_shared_from_this<TargetCell> {
public:
	TargetCell() = delete;
	TargetCell(const TargetCell&) = delete;
	TargetCell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY);
	TargetCell(shared_ptr<MapState> mapState, const Coordinate &coordinate);
	virtual ~TargetCell() = default;

	virtual bool isTarget() const;
	operator StaticType() const;
	std::shared_ptr<TargetCell> getptr();
};

} /* namespace Sokoban */
