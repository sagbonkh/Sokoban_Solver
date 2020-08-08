// Copyright Tobias Faller 2016

#pragma once

#include <stdio.h>

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <functional>
#include <algorithm>
#include <utility>
#include "Map/MapBuilder.h"

using std::shared_ptr;
using std::istream;
using std::function;

namespace Sokoban {

namespace SokobanParser {

enum Tokens : char {
	Wall = '#',
	Player = '@',
	PlayerOnGoal = '+',
	Box = '$',
	BoxOnGoal = '*',
	Goal = '.',
	Floor = ' '
};

enum Error : uint32_t {
	InvalidChar = 0xE1
};

}  // namespace SokobanParser

/*
 * Defines a basic interface for the sokoban level parser.
 */
class Parser {
private:
	bool _done = false;
	bool _error = false;
	string _name;
	map_unit_t _height = 0, _width = 0;
	shared_ptr<MapGrid::initial_map_t> _map;

	explicit Parser();

	void readLine(string &line, const uint32_t &lineNumber);
	void readStream(istream &stream);
	static void strip(string &str, const function<bool(const char &c)> &fn);
	static void stripSpaces(string &str);
	static void stripNulls(string &str);
public:

	Parser(istream &stream);
	Parser(const std::string &data);
	static Parser loadFile(const std::string path);
	~Parser() = default;

	const string& getName();
	shared_ptr<const MapGrid::initial_map_t> getMap();
	bool success() const;
	map_unit_t getHeight() const;
	map_unit_t getWidth() const;

};

}  // namespace Sokoban
