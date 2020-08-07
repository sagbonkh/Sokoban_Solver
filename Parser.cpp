// Copyright Tobias Faller 2016

#include "Parser.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>

using Sokoban::SokobanParser::Tokens;
using Sokoban::SokobanParser::Error;
namespace Sokoban {

using std::make_shared;

mutex Parser::parser_in_use_mtx;

Parser::parse_result_t Parser::readFile(const std::string path) {
	if (path.empty())
		return parse_result_t("", nullptr);

	FILE *file = fopen(path.c_str(), "r");
	if (!file)
		return parse_result_t("", nullptr);

	Parser::parse_result_t result = readStream(file);
	fclose(file);

	return result;
}

shared_ptr<Parser> Parser::_singleton = nullptr;

Parser& Parser::get() {
	if (!_singleton) {
		_singleton = shared_ptr<Parser>(new Parser());
	}
	return *_singleton;
}

Parser::parse_result_t Parser::readStream(FILE *stream) {
	lock_guard<mutex> guard(parser_in_use_mtx);
	return get()._readStream(stream);
}

Parser::parse_result_t Parser::readStream(std::istream *stream) {
	lock_guard<mutex> guard(parser_in_use_mtx);
	return get()._readStream(stream);
}

Parser::parse_result_t Parser::readData(const std::string data) {
	lock_guard<mutex> guard(parser_in_use_mtx);
	return get()._readData(data);
}



uint32_t Parser::tokenizeData(const std::string &data, uint32_t *line) {
	ssize_t nextTerminator;
	uint32_t index = 0;

	while (true) {
		nextTerminator = getNextTerminator(data, index);
		if ((nextTerminator < 0) || (nextTerminator < index)) {
			break;
		}

		if (nextTerminator - index <= 1) {
			index = nextTerminator + 1;
			continue;
		}

		readLine(data.substr(index, nextTerminator - index), *line);
		(*line)++;

		index = nextTerminator + 1;
	}

	return index;
}

void Parser::addToken(char c, uint32_t x, uint32_t y) {
	switch (c) {
	case Tokens::Floor:
		break;
	case Tokens::Wall:
		_mapBuilder.addBlock(x, y);
		break;
	case Tokens::Box:
		_mapBuilder.addBox(x, y);
		break;
	case Tokens::BoxOnGoal:
		_mapBuilder.addBox(x, y);
		_mapBuilder.addTarget(x, y);
		break;
	case Tokens::Player:
		_mapBuilder.setPlayer(x, y);
		break;
	case Tokens::PlayerOnGoal:
		_mapBuilder.setPlayer(x, y);
		_mapBuilder.addTarget(x, y);
		break;
	case Tokens::Goal:
		_mapBuilder.addTarget(x, y);
		break;
	default:
		throw Error::InvalidChar;
	}
}

Parser::parse_result_t Parser::_readData(std::string data) {
	_mapBuilder.reset();

	uint32_t line = 0;
	uint32_t index = tokenizeData(data, &line);
	if ((index + 1) < data.length())
		readLine(data.substr(index), line);

	return _mapBuilder.build().second;
}

Parser::parse_result_t Parser::_readStream(FILE *stream) {
	_mapBuilder.reset();

	char *buffer = nullptr;
	size_t bufferLength = 0;

	std::string data;

	int32_t lineLength;
	uint32_t index = 0;
	uint32_t line = 0;
	while ((lineLength = getline(&buffer, &bufferLength, stream)) > 0) {
		data.append(buffer, buffer + lineLength);

		index = tokenizeData(data, &line);
		data = data.substr(index, data.size() - index);
	}

	if ((index + 1) < data.size())
		readLine(data.substr(index), line);

	if (buffer)
		free(buffer);  // Allocated using malloc

	return _mapBuilder.build().second;
}

Parser::parse_result_t Parser::_readStream(std::istream *stream) {
	_mapBuilder.reset();

	std::string buffer;
	std::string data;

	uint32_t lineLength;
	uint32_t index = 0;
	uint32_t line = 0;
	for (;;) {
		std::getline(*stream, data);

		if (data.size() <= 0) {
			break;
		}
		buffer.append(data);

		index = tokenizeData(buffer, &line);
		buffer = buffer.substr(index, buffer.size() - index);
	}

	if ((index + 1) < buffer.length())
		readLine(buffer.substr(index), line);

	auto [error, result] = _mapBuilder.build();
	if (error != SokobanBuilder::Error::Success)
		throw "Map Builder failed";
	return result;
}

ssize_t Parser::getNextTerminator(const std::string &data, uint32_t offset) {

	uint32_t size = data.size();
	if (offset >= size)
		return -1;

	bool lineEnd = false;
	for (uint32_t index = offset; index < size; index++) {
		switch (data[index]) {
		case '\r':
			lineEnd = true;
			break;
		case '\n':
			return index - (lineEnd ? 1 : 0);
		default:
			break;
		}
	}

	return -1;
}

uint32_t Parser::readLine(std::string line, uint32_t lineNumber) {
	uint32_t size = line.length();

	for (uint32_t index = 0; index < size; index++) {
		char c = line[index];
		switch (c) {
		case '\r':
		case '\n':
			break;
		case ';':
			_mapBuilder.setTitle(line.substr(index + 1));
			break;

		default:
			addToken(c, index, lineNumber);
			break;
		}
	}

	return 0;
}

}  // namespace Sokoban
