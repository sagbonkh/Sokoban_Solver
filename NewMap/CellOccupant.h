/*
 * CellOccupant.h
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#pragma once
#include <memory>

#include "../Direction.h"
#include "Cell.h"
#include "MapState.h"

namespace Sokoban {

enum class CellOccupantType {
	Nothing = 0, Player = 3, Box = 4,
};

//Cell Occupant types = empty, boundary, box or person
using std::shared_ptr;
using std::enable_shared_from_this;

class CellOccupant: public enable_shared_from_this<CellOccupant> {
protected:
	friend Cell;
	shared_ptr<MapState> _mapState;
	shared_ptr<Cell> _cell;

	void updateCell(const shared_ptr<Cell> &cell);
public:
	CellOccupant() = delete;
	CellOccupant(const shared_ptr<MapState> mapState,
			const shared_ptr<Cell> cell = nullptr);
	virtual ~CellOccupant() = default;
	explicit CellOccupant(const CellOccupant &other) = default;

	bool isTarget() const;

	virtual CellOccupantType getType() const = 0;
	bool isNothing() const;
	bool isPlayer() const;
	bool isBox() const;
	operator bool() const;

	Coordinate getCoordinate() const;
	shared_ptr<Cell> getCell() const;
	shared_ptr<MapState> getMapState() const;
	virtual shared_ptr<CellOccupant> getptr();
};

} /* namespace Sokoban */
