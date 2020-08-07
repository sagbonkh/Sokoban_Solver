/*
 * Cell.h
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#pragma once

#include <memory>
#include <tuple>

#include "../Coordinate.h"
#include "MapState.h"
#include "../Direction.h"
#include "CellOccupant.h"
#include "CellContents.h"

using std::shared_ptr;
using std::make_shared;
using std::enable_shared_from_this;
using std::tuple;
using std::make_tuple;
using std::get;

namespace Sokoban {

class CellOccupant;

class Cell: public Coordinate, public enable_shared_from_this<Cell> {
public:
	// return type specifying result of a move
	// from a given operation: make_tuple<bool, bool, bool>(success, box_did_move, player_did_move);
	typedef tuple<bool, bool, bool> move_result_t;
protected:
	shared_ptr<MapState> _mapState = nullptr;
	shared_ptr<CellOccupant> _occupant = nullptr;
	// based on https://stackoverflow.com/a/2986902/1959179
	using Coordinate::set;

public:
	static shared_ptr<Cell> fromCellType(const shared_ptr<MapState> &mapState,
			const Coordinate &c, const CellContents &type);
	Cell() = delete;
	Cell(const Cell&) = delete;
	Cell(shared_ptr<MapState> mapState, uint32_t posX, uint32_t posY) noexcept;
	Cell(shared_ptr<MapState> mapState, const Coordinate &coordinate) noexcept;
	virtual ~Cell() = default;

	shared_ptr<Cell> getAdjacent(Direction dir) const;
	shared_ptr<CellOccupant> getOccupant() const;
	virtual void setOccupant(const shared_ptr<CellOccupant> &occupant);
	virtual void moveOccupantTo(const shared_ptr<Cell> &other);

	virtual move_result_t pushOccupantIn(Direction dir);
	virtual bool canPushOccupantIn(Direction dir);

	virtual move_result_t enterFrom(Direction dir,
			shared_ptr<CellOccupant> occupant);
	virtual bool canEnterFrom(Direction dir, shared_ptr<CellOccupant> occupant);

	shared_ptr<MapState> getMapState() const;
	virtual bool canBeOccupied() const;
	bool isOccupied() const;
	virtual bool isUnoccupied() const;
	virtual bool isTarget() const;
	virtual bool isWall() const;
	virtual bool hasPlayer() const;
	virtual bool hasBox() const;
	virtual char getDisplayChar() const;
	operator char() const;

	std::shared_ptr<Cell> getptr();

};
} /* namespace Sokoban */
