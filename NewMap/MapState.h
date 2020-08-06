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
#include "../Map/IState.h"
#include "../Map/IStaticMap.h"
#include "../Map/Map.h"
#include "../Map/State.h"

namespace Sokoban {

using std::map;
using std::set;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
class Cell;
class CellOccupant;

// Map has (Initial) State and StaticMap
// StaticMap has walls and targets
// State has Boxes and Player
class MapState: protected IMap, protected IState, public IStaticMap {
	Coordinate player;
	const uint32_t &_height, &_width;
	map<Coordinate, shared_ptr<Cell>> cells, initialCells;

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
//	shared_ptr<Cell> get(const Coordinate &position);
//	shared_ptr<Cell> get(uint32_t x, uint32_t y);
	shared_ptr<CellOccupant> getOccupant(const Coordinate &position);
	shared_ptr<CellOccupant> getOccupant(uint32_t x, uint32_t y);

	bool isTarget(const Coordinate &position) const override;
	bool isTarget(uint32_t x, uint32_t y) const override;

	/*
	 * Returns the width of the map.
	 */
	uint32_t getWidth() const override;

	/*
	 * Returns the height of the map.
	 */
	uint32_t getHeight() const override;

	/*
	 * Returns positions of items in the map
	 */
	Coordinate getPlayerPosition() const override;
//	const unordered_map<Coordinate, BoxState> getBoxes() const;
	const std::set<Coordinate>& getTargets() const;

	int getNumBoxes() const;
	int getNumCompletedBoxes() const;
	int getNumBoxesLeft() const;
	bool isWon() const;

	const IState* getInitialState() const override;
	const IStaticMap* getMap() const override;
	void set(uint32_t x, uint32_t y, Sokoban::StaticType type) override;
	bool isBlock(const Sokoban::Coordinate &position) const override;
	bool isEmpty(uint32_t x, uint32_t y) const override;
	bool isEmpty(const Sokoban::Coordinate &position) const override;
	void set(const Sokoban::Coordinate &position, Sokoban::StaticType type)
			override;
	bool isBlock(uint32_t x, uint32_t y) const override;
};

} /* namespace Sokoban */

