// Copyright Tobias Faller 2016


#include <stdlib.h>

#include "Parser.h"


using std::make_shared;
using std::cerr;
using std::endl;
using std::string;
using std::istream;
using std::ifstream;
using std::istringstream;
using std::isspace;
using std::find_if_not;
using std::max;
using std::back_inserter;
using std::vector;
using std::bind;
using std::mem_fn;
using std::function;
using std::move;
using std::size_t;
using std::for_each;


using namespace std::placeholders;
namespace Sokoban {

Parser::Parser() : _done(false), _error(true) {
}

Parser Parser::loadFile(const std::string path) {
	if (path.empty()) return Parser();
	ifstream in(path);
	if (!in.is_open()) return Parser();
	Parser p(in);
	in.close();
	return p;
}

Parser::Parser(istream &stream) {
	readStream(stream);
}

Parser::Parser(const std::string &data) {
	istringstream in(data);
	readStream(in);
}

void Parser::readStream(istream &stream) {
	if (_done) throw "Stream was already read.";
	_map = make_shared<MapGrid::initial_map_t>();
	std::string line;
	uint32_t lineNo = 0;

	while (!_done && !_error) {
		if (stream.eof()) break;
		getline(stream, line);
		readLine(line, ++lineNo);
	}

	if (_error) {
		_map = nullptr;
		return;
	}

	_height = _map->size();
	static auto resize_fn_unbound = mem_fn<void(size_t, const CellContents&)>(
			&vector<CellContents>::resize);
	static auto resize_fn = bind(resize_fn_unbound, _1, _width, CellContents::Floor);
	for_each(_map->begin(), _map->end(), resize_fn);

	// TODO: error check
	_done = true;
}

void Parser::strip(string &str, const function<bool(const char &c)> &fn) {
	// Find first non-space character from beginning of string
	auto begin_it = find_if_not(str.begin(), str.end(), fn);
	str.erase(str.begin(), begin_it);

	// Find first non-space character from end of string
	auto end_it = find_if_not(str.rbegin(), str.rend(), fn);
	// TODO: confirm this works with reverse iterators
	str.erase(end_it.base(), str.end());
}

void Parser::stripSpaces(string &str) {
	static function<bool(const char &c)> is_space_char = [](const char &c) -> bool {
		if (c == '\0') return true;
		return isspace(static_cast<unsigned char>(c));
	};
	strip(str, is_space_char);
}

void Parser::stripNulls(string &str) {
	static function<bool(const char &c)> is_null_char = [](const char &c) -> bool {
		return c == '\0';
	};
	strip(str, is_null_char);
}


void Parser::readLine(string &line, const uint32_t &lineNumber) {
	stripNulls(line);
	if (line.empty()) {
		_done = true;
		return;
	} else if (line.starts_with(';')) {
		line.erase(0, 1);
		stripSpaces(line);
		_name = line;
		return;
	}

	_width = max(_width, static_cast<map_unit_t>(line.size()));
	vector<CellContents> newLine(_width, CellContents::Floor);
	function<CellContents(char)> charToCellContents = bind(&CellContents::fromToken, _1);

	try {
		transform(line.begin(), line.end(), newLine.begin(), charToCellContents);
	} catch (const std::exception &e) {
		cerr << "Warning: " << e.what() << endl;
		_error = true;
		return;
	}
	_map->push_back(move(newLine));
}

const string& Parser::getName()
{
	return _name;
}

shared_ptr<const MapGrid::initial_map_t> Parser::getMap()
{
	return (!_error) ? _map : nullptr;
}

bool Parser::success() const
{
	return !_error;
}

map_unit_t Parser::getHeight() const
{
	return (!_error) ? _height : -1;
}

map_unit_t Parser::getWidth() const
{
	return (!_error) ? _width : -1;
}

}  // namespace Sokoban
