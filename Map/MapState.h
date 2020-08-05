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
#include <unordered_map>

#include "../Coordinate.h"
#include "Map.h"
#include "IState.h"
#include "State.h"

namespace Sokoban {

using std::set;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
class Cell;
class CellOccupant;

// Map has (Initial) State and StaticMap
// StaticMap has walls and targets
// State has Boxes and Player
class MapState: private Map, protected IState {
	Coordinate player;
	const uint32_t &_height, &_width;
	// TODO: integrate targets into Cell class
	const set<Coordinate> _targets;
	vector<vector<shared_ptr<Cell>>> cells;

	void setPlayerPosition(Coordinate playerPosition) override;

public:
	MapState() = delete;
	MapState(const Map &map);
	MapState(const Map &map, const State &state);
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
	Coordinate getPlayerPosition() const override;
	const unordered_map<Coordinate, BoxState> getBoxes() const override;
	const set<Coordinate>& getTargets() const;

	int getNumBoxes() const;
	int getNumCompletedBoxes() const;
	int getNumBoxesLeft() const;
	bool isWon() const;

	IState* clone() const override;
	

};

} /* namespace Sokoban */

