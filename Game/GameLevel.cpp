// Copyright Tobias Faller 2016

#include "GameLevel.h"

#include <fstream>
#include <string>
#include "../Parser.h"
#include "../NewMap/MapGrid.h"

namespace Sokoban {
using std::ifstream;
using std::istream;
using std::to_string;
using std::string;
using namespace std::string_literals;

GameLevel::GameLevel(const std::string &path, pos_type pos) :
		_path(path), _pos(pos) {
}

GameLevel::GameLevel(const std::string &path, ifstream &in) :
		_path(path), _pos(in.tellg()) {
	// TODO: loop until next level
}

GameLevel::GameLevel(istream &in) {
	load(in);
}

void GameLevel::load(istream &in) const {
	if (_map)
		return;
	_map = Parser::readStream(&in);
}

void GameLevel::load() const {
	if (_map)
		return;
	ifstream in(_path);
	try {
		if (!in.is_open())
			throw "File not found";
		in.seekg(_pos);
		load(in);
		in.close();
	} catch (const std::exception &e) {
		throw "Level could not be read from path "s + _path + " at position "s
				+ to_string(_pos);
	}
	//TODO: call parser
}

const std::string& GameLevel::getName() const {
	if (!_map)
		load();
	return _map->getName();

}

const shared_ptr<const MapGrid::initial_map_t>& GameLevel::getMap() const {
	if (!_map)
		load();
	return _map;
}
}  // namespace Sokoban
