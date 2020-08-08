// Copyright Tobias Faller 2016

#include "GameLevel.h"

#include <numeric>
#include <fstream>
#include <string>
#include "../Parser.h"
#include "../Map/MapGrid.h"

namespace Sokoban {
using std::ifstream;
using std::istream;
using std::to_string;
using std::string;
using std::endl;
using std::cout;
using std::cerr;
using std::plus;
using std::accumulate;
using namespace std::string_literals;

GameLevel::GameLevel(const std::string &path, pos_type pos) :
		_path(path), _pos(pos) {
}

GameLevel::GameLevel(const std::string &path, ifstream &in) :
		_path(path), _pos(in.tellg()) {
	// loop until next level
	string line = " ";
	while (!line.empty() && !in.eof()) {
		getline(in, line);
	}
}

GameLevel::GameLevel(istream &in) {
	load(in);
}

vector<shared_ptr<const GameLevel>> GameLevel::loadAllFromFile(const string &filename) {
	vector<shared_ptr<const GameLevel>> result;
	ifstream in(filename);
	if (!in.is_open()) throw "File not found";
	shared_ptr<const GameLevel> nextLevel = nullptr;
	do {
		nextLevel = nullptr;
		if (in.eof()) break;
		try {
			nextLevel = make_shared<GameLevel>(filename, in);
			if (!*nextLevel) continue;
			result.push_back(nextLevel);
//			cout << static_cast<string>(*nextLevel) << endl;
		} catch (std::exception &e) {
			cerr << "Level could not be parsed." << endl;
		}
	} while (nextLevel);
	in.close();
	return result;
}

void GameLevel::load(istream &in) const {
	if (_loaded)
		return;

	Parser parser(in);
	if (!parser.success()) throw "Parsing failed";

	_name = parser.getName();
	_map = parser.getMap();
	if (_map->empty()) {
		_map = nullptr;
	}
	_loaded = true;

}

void GameLevel::load() const {
	if (_loaded)
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
}

const std::string& GameLevel::getName() const {
	if (!_loaded)
		load();
	return _name;

}

const shared_ptr<const MapGrid::initial_map_t>& GameLevel::getMap() const {
	if (!_loaded)
		load();
	return _map;
}

std::shared_ptr<const GameLevel> GameLevel::getptr() const {
	return shared_from_this();
}

bool GameLevel::isEmpty() const
{
	if (!_loaded)
		load();
	return !_map || _map->empty();
}

GameLevel::operator bool() const
{
	return !isEmpty();
}

GameLevel::operator string() const {
	if (isEmpty()) return "<EMPTY GAME LEVEL>";

	string result;
	const MapGrid::initial_map_t &map = *getMap();
	result += "; " + getName() + "\n";
	for (const auto &row : map) {
		result += accumulate(row.begin(), row.end(), string(), plus<string> {}) + "\n";
	}
	return result;
}



}  // namespace Sokoban
