/*
 * BoundaryCell.h
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#pragma once

#include "../Cell.h"

namespace Sokoban {

class WallCell: public Cell {
public:
	WallCell() = delete;
	WallCell(const Cell&) = delete;
	WallCell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY);
	WallCell(shared_ptr<MapState> mapState, const Coordinate &coordinate);
	virtual ~WallCell() = default;

	virtual bool canBeOccupied() const override;
	virtual bool isWall() const override;
	virtual char getDisplayChar() const override;
};

} /* namespace Sokoban */
