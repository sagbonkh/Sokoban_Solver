// Copyright Tobias Faller 2016

#pragma once

#include <stdio.h>

#include <string>
#include <iostream>
#include <memory>
#include <mutex>

#include "Map/Map.h"
#include "NewMap/MapBuilder.h"

namespace Sokoban {
using std::mutex;
using std::lock_guard;
using std::shared_ptr;
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

	static shared_ptr<Parser> _singleton;
	static Parser& get();
	static mutex parser_in_use_mtx;
public:
	typedef pair<string, shared_ptr<const MapGrid::initial_map_t>> parse_result_t;
	/*
	 * Destroys this parser.
	 */
	~Parser() = default;

	static parse_result_t readStream(FILE *stream);
	static parse_result_t readStream(std::istream *stream);
	static parse_result_t readData(const std::string data);
	static parse_result_t readFile(const std::string path);

private:
	MapBuilder _mapBuilder;

	/*
	 * Reads a file stream and interprets it as sokoban level.
	 */
	parse_result_t _readStream(FILE *stream);

	/*
	 * Reads a stream and interprets it as sokoban level.
	 */
	parse_result_t _readStream(std::istream *stream);

	/*
	 * Reads some data and interprets it as sokoban level.
	 */
	parse_result_t _readData(const std::string data);


	/*
	 * Creates a new parser for a sokoban map.
	 */
	Parser() = default;

	/*
	 * Parses a line of data and appends it to the MapBuilder.
	 */
	uint32_t readLine(std::string line, uint32_t lineNumber);

	/*
	 * Returns the next vertical separator for this stream.
	 */
	ssize_t getNextTerminator(const std::string &data, uint32_t offset);
	/*
	 * Interprets the provided Token as object at position x, y and adds
	 * it to the builder.
	 */
	void addToken(char c, uint32_t x, uint32_t y);

	/*
	 * Small subroutine for splitting a string into lines.
	 * Returns the remaining chars in the buffer.
	 */
	uint32_t tokenizeData(const std::string &data, uint32_t *line);


};

}  // namespace Sokoban
