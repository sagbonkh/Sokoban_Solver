/*
 * MapGrid.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */

#pragma once
#include <map>
#include <memory>
#include <vector>

#include "../Coordinate.h"
#include "Cell.h"

namespace Sokoban {
using std::vector;
using std::map;
using std::shared_ptr;

enum class CellContents : uint8_t {
	Floor = 0,
	Goal = 1 << 0,
	Wall = 1 << 1,
	Player = 1 << 2,
	Box = 1 << 3,
	PlayerOnGoal = Player | Goal,
	BoxOnGoal = Box | Goal
};


class MapGrid {
public:
	typedef vector<vector<CellContents>> initial_map_t;
	typedef map<Coordinate, shared_ptr<Cell>> sparse_map_t;
private:
	map_unit_t _width, _height;
	shared_ptr<const initial_map_t> _initialCells;
	sparse_map_t _cells;
public:
	MapGrid() = delete;
	MapGrid(const shared_ptr<const initial_map_t> &initialMap);
	MapGrid(const MapGrid &other);
	virtual ~MapGrid() = default;

	shared_ptr<Cell> get(const Coordinate &c);
	map_unit_t getHeight() const;
	map_unit_t getWidth() const;
	void reset();
};

} /* namespace Sokoban */
