// Copyright Tobia Faller 2016


#include "../Map/MapBuilder.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iterator>

#include "../Coordinate.h"
#include "../Map/MapGrid.h"


using Sokoban::SokobanBuilder::Error;
using std::string;
using std::make_pair;
using std::set;
using std::inserter;
using std::set_intersection;

namespace Sokoban {


MapBuilder::MapBuilder() :
		_walls(), _boxes(), _targets(), _player(), _width(1), _height(1) {
}

MapBuilder& MapBuilder::addBlock(Coordinate position) {
	_walls.insert(position);

	_width = std::max(_width, position.x + 1);
	_height = std::max(_height, position.y + 1);
	return *this;
}
MapBuilder& MapBuilder::addTarget(Coordinate position) {
	_targets.insert(position);

	_width = std::max(_width, position.x + 1);
	_height = std::max(_height, position.y + 1);
	return *this;
}
MapBuilder& MapBuilder::addBox(Coordinate position) {
	_boxes.insert(position);

	_width = std::max(_width, position.x + 1);
	_height = std::max(_height, position.y + 1);
	return *this;
}
MapBuilder& MapBuilder::setPlayer(Coordinate position) {
	_player = position;

	_width = std::max(_width, position.x + 1);
	_height = std::max(_height, position.y + 1);
	return *this;
}
MapBuilder& MapBuilder::addBlocks(uint32_t fromX, uint32_t fromY, uint32_t toX,
		uint32_t toY) {

	uint32_t xMin = std::min(fromX, toX);
	uint32_t xMax = std::max(fromX, toX);
	uint32_t yMin = std::min(fromY, toY);
	uint32_t yMax = std::max(fromY, toY);

	for (uint32_t i = yMin; i <= yMax; ++i) {
		for (uint32_t j = xMin; j <= xMax; ++j) {
			_walls.insert(Coordinate(j, i));
		}
	}

	_width = std::max(_width, xMax + 1);
	_height = std::max(_height, yMax + 1);

	return *this;
}

MapBuilder& MapBuilder::addBlock(uint32_t x, uint32_t y) {
	return this->addBlock(Coordinate(x, y));
}
MapBuilder& MapBuilder::addTarget(uint32_t x, uint32_t y) {
	return this->addTarget(Coordinate(x, y));
}
MapBuilder& MapBuilder::addBox(uint32_t x, uint32_t y) {
	return this->addBox(Coordinate(x, y));
}
MapBuilder& MapBuilder::setPlayer(uint32_t x, uint32_t y) {
	return this->setPlayer(Coordinate(x, y));
}
MapBuilder& MapBuilder::addBlocks(Coordinate from, Coordinate to) {
	return this->addBlocks(from.x, from.y, to.x, to.y);
}

MapBuilder& MapBuilder::setTitle(const std::string &newTitle) {
	_title = newTitle;
	return *this;
}

MapBuilder& MapBuilder::reset() {
	_walls.clear();
	_targets.clear();
	_boxes.clear();
	_player.set(0, 0);
	_title.clear();
	_width = 1;
	_height = 1;

	return *this;
}

std::pair<SokobanBuilder::Error, MapBuilder::Result> MapBuilder::build() const {
	const Result empty_result = make_pair<string,
			shared_ptr<const MapGrid::initial_map_t>>("", nullptr);
	if (_targets.size() > _boxes.size())
		return pair<Error, Result>(
				Error::MoreTargetsThanBoxes,
				empty_result);

	set<Coordinate> overlaps;
	set_intersection(_walls.begin(), _walls.end(), _boxes.begin(), _boxes.end(),
			inserter(overlaps, overlaps.begin()));
	set_intersection(_walls.begin(), _walls.end(), _targets.begin(),
			_targets.end(), inserter(overlaps, overlaps.begin()));
	if (_walls.contains(_player))
		overlaps.insert(_player);
	if (!overlaps.empty())
		return pair<Error, Result>(Error::SpotTaken, empty_result);

	const vector<CellContents> rowTemplate(_width, CellContents::Floor);
	shared_ptr<MapGrid::initial_map_t> initialMapPtr = make_shared<
			MapGrid::initial_map_t>(_height, rowTemplate);
	MapGrid::initial_map_t &initialMap = *initialMapPtr;

	for (Coordinate p : _walls)
		initialMap[p.y][p.x] = CellContents::Wall;

	for (Coordinate p : _targets) {
		if (initialMap[p.y][p.x] != CellContents::Floor)
			return std::pair<Error, Result>(Error::SpotTaken, empty_result);

		initialMap[p.y][p.x] |= CellContents::Goal;
	}

	for (Coordinate p : _boxes) {
		if ((initialMap[p.y][p.x] & CellContents::Wall) == CellContents::Wall)
			return pair<Error, Result>(Error::SpotTaken, empty_result);

		initialMap[p.y][p.x] |= CellContents::Box;
	}

	// make sure player isn't added to a wall
	if ((initialMap[_player.y][_player.x] & CellContents::Wall)
			== CellContents::Wall)
		return pair<Error, Result>(Error::SpotTaken, empty_result);

	initialMap[_player.y][_player.x] |= CellContents::Player;

	Result result = pair<string, shared_ptr<MapGrid::initial_map_t>>(_title,
			initialMapPtr);
	return pair<Error, Result>(Error::Success, result);
}

}  // namespace Sokoban
