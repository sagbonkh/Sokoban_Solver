/*
 * MapState.h
 *
 *  Created on: Aug. 2, 2020
 *      Author: sidney
 */

#pragma once
#include <set>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

#include "../Coordinate.h"
#include "MapGrid.h"

using std::map;
using std::set;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
namespace Sokoban {

class Cell;
class CellOccupant;
class Player;




// Map has (Initial) State and StaticMap
// StaticMap has walls and targets
// State has Boxes and Player
class MapState {
	Coordinate player;
	const uint32_t &_height, &_width;
	shared_ptr<MapGrid> _mapGrid;

public:
	MapState() = delete;
	MapState(const shared_ptr<const MapGrid::initial_map_t> &map);
	MapState(const MapState &other) = default;
	virtual ~MapState() = default;

	/*
	 * Returns the cell at the provided position of this map
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is thrown.
	 */
	shared_ptr<Cell> get(const Coordinate &position);
	shared_ptr<Cell> get(uint32_t x, uint32_t y);
	shared_ptr<CellOccupant> getOccupant(const Coordinate &position);
	shared_ptr<CellOccupant> getOccupant(uint32_t x, uint32_t y);

	bool isTarget(const Coordinate &position) const;
	bool isTarget(uint32_t x, uint32_t y) const;

	/*
	 * Returns the width of the map.
	 */
	uint32_t getWidth() const;

	/*
	 * Returns the height of the map.
	 */
	uint32_t getHeight() const;

	/*
	 * Returns positions of items in the map
	 */
	const shared_ptr<Player>& getPlayer();

//	const unordered_map<Coordinate, BoxState> getBoxes() const;
//	const std::set<Coordinate>& getTargets() const;

	int getNumBoxes() const;
	int getNumCompletedBoxes() const;
	int getNumBoxesLeft() const;
	bool isWon() const;

	const shared_ptr<const MapGrid::initial_map_t> getInitialMap() const;

	bool isBlock(const Sokoban::Coordinate &position) const;
	bool isEmpty(uint32_t x, uint32_t y) const;
	bool isEmpty(const Sokoban::Coordinate &position) const;
	bool isBlock(uint32_t x, uint32_t y) const;
};

} /* namespace Sokoban */

