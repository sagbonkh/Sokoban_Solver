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
#include "../Map/MapGrid.h"

using std::map;
using std::set;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
namespace Sokoban {

class Cell;
class CellOccupant;
class Player;


class MapState {
	shared_ptr<MapGrid> _mapGrid;
	const uint32_t &_height, &_width;


public:
	MapState() = delete;
	MapState(const shared_ptr<const MapGrid::initial_map_t> &map);
	MapState(const MapState &other) = default;
	virtual ~MapState() = default;

	/*
	 * Returns the cell at the provided position of this map
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is thrown.
	 */
	const shared_ptr<Cell>& get(const Coordinate &position);
	const shared_ptr<Cell>& get(uint32_t x, uint32_t y);
	const shared_ptr<Cell>& operator[](const Coordinate &c);

	shared_ptr<CellOccupant> getOccupant(const Coordinate &position);
	shared_ptr<CellOccupant> getOccupant(uint32_t x, uint32_t y);


	uint32_t getWidth() const;
	uint32_t getHeight() const;

	const shared_ptr<Player>& getPlayer() const;
	const set<shared_ptr<Box>>& getBoxes() const;
	const set<shared_ptr<TargetCell>>& getTargets() const;

	int numBoxes() const;
	int numBoxesOnTargets() const;
	bool won() const;

	const shared_ptr<const MapGrid::initial_map_t> getInitialMap() const;
	const shared_ptr<const MapGrid> getGrid() const;

	bool isValid(const Coordinate &position) const;
	bool isValid(uint32_t x, uint32_t y) const;
};

} /* namespace Sokoban */

