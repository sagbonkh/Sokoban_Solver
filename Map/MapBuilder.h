// Copyright Tobias Faller 2016
#pragma once

#include <stdint.h>

#include <set>
#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "../Coordinate.h"
#include "../Map/MapGrid.h"


using std::string;
using std::set;
using std::vector;
using std::pair;
using std::make_pair;
using std::make_shared;
using std::shared_ptr;
using Sokoban::MapGrid;

namespace Sokoban {

namespace SokobanBuilder {


/*
 * Defines all possible errors thrown by the MapBuilder class.
 */
enum Error : uint32_t {
	Success, MoreTargetsThanBoxes, SpotTaken
};

}  // namespace SokobanBuilder

/*
 * Defines a builder class for creating Sokoban levels.
 * This builder dynamically allocates memory and returns the
 * fixed-size map.
 */
class MapBuilder {
private:
	string _title;
	set<Coordinate> _walls, _boxes, _targets;
	Coordinate _player;

	map_unit_t _width;
	map_unit_t _height;

	template<typename T>
	static bool hasDuplicates(const vector<T> &vec);

public:
	//	typedef vector<vector<CellContents>> initial_map_t;
	typedef std::pair<string, shared_ptr<const MapGrid::initial_map_t>> Result;
	/*
	 * Creates a new Sokoban MapBuilder to create levels dynamically.
	 */
	MapBuilder();

	/*
	 * Destroys this builder and its internal state.
	 */
	~MapBuilder() = default;

	/*
	 * Creates a new map without destroying the internal state of this builder.
	 * Returns error code Success if the created map is valid.
	 * If there are more targets than boxes MoreTargetsThanBoxes will be returned.
	 * If there overlapping components (at the same spot) a SpotTaken error
	 * will be returned.
	 */
	std::pair<SokobanBuilder::Error, Result> build() const;

	/*
	 * Resets the state of this builder to an empty map.
	 */
	MapBuilder& reset();

	/*
	 * Adds a block at the provided coordinate.
	 */
	MapBuilder& addBlock(Coordinate position);

	/*
	 * Adds a block at the provided coordinate.
	 */
	MapBuilder& addBlock(uint32_t x, uint32_t y);

	/*
	 * Adds a box at the provided coordinate.
	 */
	MapBuilder& addBox(Coordinate position);

	/*
	 * Adds a box at the provided coordinate.
	 */
	MapBuilder& addBox(uint32_t x, uint32_t y);

	/*
	 * Sets the position of the player to the provided coordinate.
	 */
	MapBuilder& setPlayer(Coordinate position);

	/*
	 * Sets the position of the player to the provided coordinate.
	 */
	MapBuilder& setPlayer(uint32_t x, uint32_t y);

	/*
	 * Adds a target to put a box on at the provided coordinate.
	 */
	MapBuilder& addTarget(Coordinate position);

	/*
	 * Adds a target to put a box on at the provided coordinate.
	 */
	MapBuilder& addTarget(uint32_t x, uint32_t y);

	/*
	 * Adds a square of blocks to this builder starting from <from> and going
	 * to <to> (inclusive).
	 */
	MapBuilder& addBlocks(Coordinate from, Coordinate to);

	/*
	 * Adds a square of blocks to this builder starting from <from> and going
	 * to <to> (inclusive).
	 */
	MapBuilder& addBlocks(uint32_t fromX, uint32_t fromY, uint32_t toX,
			uint32_t toY);

	MapBuilder& setTitle(const std::string &newTitle);

};



}  // namespace Sokoban

