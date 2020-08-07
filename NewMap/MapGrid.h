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
#include <type_traits>

#include "../Coordinate.h"
#include "CellContents.h"

namespace Sokoban {
using std::vector;
using std::map;
using std::shared_ptr;


class MapState;
class Cell;

class MapGrid {
public:
	typedef vector<vector<CellContents>> initial_map_t;
	typedef map<Coordinate, shared_ptr<Cell>> sparse_map_t;
private:
	shared_ptr<MapState> _mapState;
	map_unit_t _width, _height;
	shared_ptr<const initial_map_t> _initialMap;
	mutable sparse_map_t _cells;
public:
	MapGrid() = delete;
	MapGrid(const shared_ptr<MapState> &mapState);
	MapGrid(const MapGrid &other) = delete;
	virtual ~MapGrid() = default;

	const shared_ptr<Cell>& get(const Coordinate &c);
	const shared_ptr<const Cell> get(const Coordinate &c) const;
	const shared_ptr<Cell>& operator[](const Coordinate &c);
	const shared_ptr<const Cell> operator[](const Coordinate &c) const;
	map_unit_t getHeight() const;
	map_unit_t getWidth() const;
//	shared_ptr<MapGrid> clone() const;
	void reset();
};

} /* namespace Sokoban */
