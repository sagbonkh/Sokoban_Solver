/*
 * CellContents2.h
 *
 *  Created on: Aug. 6, 20
 *      Author: sidney
 */

#pragma once

#include <cstdint>
#include <string>
#include <map>

using std::string;
using std::map;

namespace Sokoban {

class CellContents {
private:
	uint8_t _value;
public:
	static const CellContents Floor, Goal, Wall, Player, Box, PlayerOnGoal,
			BoxOnGoal;
	static const map<char, CellContents> Tokens;
	static const map<CellContents, char> ReverseTokens;

	CellContents();
	CellContents(const uint8_t &num);
	CellContents(const CellContents &c) = default;
	~CellContents() = default;

	CellContents& operator=(const CellContents &b);
	CellContents& operator&=(const CellContents &b);
	CellContents& operator|=(const CellContents &b);
	CellContents& operator^=(const CellContents &b);
	CellContents operator&(const CellContents &other) const;
	CellContents operator|(const CellContents &other) const;
	CellContents operator^(const CellContents &other) const;
	bool operator==(const CellContents &other) const;
	bool operator!=(const CellContents &other) const;
	bool operator<(const CellContents &other) const;
	bool operator>(const CellContents &other) const;
	bool operator<=(const CellContents &other) const;

	operator bool() const;
	operator uint8_t() const;
	operator char() const;
	operator string() const;
	static CellContents fromToken(char c);
};

} /* namespace Sokoban */
