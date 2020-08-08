/*
 * BoundaryCell.h
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#pragma once

#include "Map/Cell.h"

namespace Sokoban {

class WallCell: public Cell {
public:
	WallCell() = delete;
	WallCell(const Cell&) = delete;
	WallCell(MapState &mapState, uint32_t posX, uint32_t posY);
	WallCell(MapState &mapState, const Coordinate &coordinate);
	virtual ~WallCell() = default;

	virtual bool canBeOccupied() const override;
	virtual bool isWall() const override;
	virtual char getDisplayChar() const override;
};

} /* namespace Sokoban */
