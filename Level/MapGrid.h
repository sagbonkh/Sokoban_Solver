/*
 * MapGrid.h
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */

#pragma once
#include <set>
#include <map>
#include <memory>
#include <vector>
#include <type_traits>

#include "../Level/CellContents.h"
#include "Map/Coordinate.h"

namespace Sokoban {
using std::vector;
using std::map;
using std::shared_ptr;
using std::set;



class MapState;
class Cell;
class TargetCell;
class Box;
class Player;

class MapGrid {
public:
	typedef vector<vector<CellContents>> initial_map_t;
	typedef map<Coordinate, shared_ptr<Cell>> sparse_map_t;
private:
	MapState &_mapState;
	shared_ptr<const initial_map_t> _initialMap;
	map_unit_t _width, _height;
	shared_ptr<Player> _player;
	set<shared_ptr<Box>> _boxes;
	set<shared_ptr<TargetCell>> _targets;
	mutable sparse_map_t _cells;

public:
	MapGrid() = delete;
	MapGrid(MapState &mapState, const shared_ptr<const initial_map_t> &initialMap);
	MapGrid(const MapGrid &other) = delete;
	virtual ~MapGrid() = default;

	const shared_ptr<Cell>& get(const Coordinate &c);
	const shared_ptr<const Cell> get(const Coordinate &c) const;
	const shared_ptr<Cell>& operator[](const Coordinate &c);
	const shared_ptr<const Cell> operator[](const Coordinate &c) const;
	const map_unit_t& getHeight() const;
	const map_unit_t& getWidth() const;
	uint8_t getNumBoxes() const;

	const shared_ptr<Player>& getPlayer() const;
	const set<shared_ptr<Box>>& getBoxes() const;
	const set<shared_ptr<TargetCell>>& getTargets() const;

	const shared_ptr<const initial_map_t>& getInitialMap() const;
//	shared_ptr<MapGrid> clone() const;
	void reset();
};

} /* namespace Sokoban */
