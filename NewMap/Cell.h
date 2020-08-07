/*
 * Cell.h
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#pragma once

#include <memory>

#include "../Coordinate.h"
#include "MapState.h"
#include "../Direction.h"
#include "CellOccupant.h"
#include "CellContents.h"

namespace Sokoban {
using std::shared_ptr;
using std::make_shared;
using std::enable_shared_from_this;

class CellOccupant;

class Cell: public Coordinate, public enable_shared_from_this<Cell> {
protected:
	shared_ptr<MapState> _mapState = nullptr;
	shared_ptr<CellOccupant> _occupant = nullptr;
	// based on https://stackoverflow.com/a/2986902/1959179
	using Coordinate::set;
	virtual void pushOccupantIn(Direction dir);
	virtual bool canPushOccupantIn(Direction dir);

public:
	static shared_ptr<Cell> fromCellType(const shared_ptr<MapState> &mapState,
			const Coordinate &c, const CellContents &type);
	Cell() = delete;
	Cell(const Cell&) = delete;
	Cell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY);
	Cell(shared_ptr<MapState> mapState, const Coordinate &coordinate);
	virtual ~Cell() = default;

	shared_ptr<Cell> getAdjacent(Direction dir) const;
	shared_ptr<CellOccupant> getOccupant() const;
	virtual void setOccupant(const shared_ptr<CellOccupant> &occupant);
	virtual void moveOccupantTo(const shared_ptr<Cell> &other);
	virtual void enterFrom(Direction dir, shared_ptr<CellOccupant> occupant);
	virtual bool canEnterFrom(Direction dir, shared_ptr<CellOccupant> occupant);

	shared_ptr<MapState> getMapState() const;
	virtual bool canBeOccupied() const;
	bool isOccupied() const;
	virtual bool isUnoccupied() const;
	virtual bool isTarget() const;
	virtual bool isWall() const;
	virtual bool hasPlayer() const;
	virtual bool hasBox() const;
	virtual StaticType getStaticType() const;
	operator StaticType() const;

	std::shared_ptr<Cell> getptr();

};
} /* namespace Sokoban */
