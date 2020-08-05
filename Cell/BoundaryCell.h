/*
 * BoundaryCell.h
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#pragma once

#include "Cell.h"

namespace Sokoban {

class BoundaryCell: public Cell {
public:
	BoundaryCell() = delete;
	BoundaryCell(const Cell&) = delete;
	BoundaryCell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY);
	BoundaryCell(shared_ptr<MapState> mapState, const Coordinate &coordinate);
	virtual ~BoundaryCell() = default;

	virtual bool canBeOccupied() const override;
	virtual bool isBoundary() const override;
	virtual StaticType getStaticType() const override;

};

} /* namespace Sokoban */
