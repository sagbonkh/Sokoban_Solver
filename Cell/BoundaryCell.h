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
	virtual bool isOccupied() const override;
	virtual bool isTarget() const override;
	virtual void moveOccupantTo(const std::shared_ptr<Sokoban::Cell> &other)
			override;
	virtual bool hasPlayer() const override;
	virtual bool hasBox() const override;
	virtual void setOccupant(
			const std::shared_ptr<Sokoban::CellOccupant> &occupant) override;
	virtual bool isEmpty() const override;
	virtual bool canBeOccupied() const override;
	virtual void enterFrom(Sokoban::Direction dir,
			std::shared_ptr<Sokoban::CellOccupant> occupant) override;
	virtual bool canEnterFrom(Sokoban::Direction dir,
			std::shared_ptr<Sokoban::CellOccupant> occupant) override;

protected:
	virtual void pushOccupantIn(Sokoban::Direction dir) override;
	virtual bool canPushOccupantIn(Sokoban::Direction dir) override;
};

} /* namespace Sokoban */
