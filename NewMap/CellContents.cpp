/*
 * CellContents2.cpp
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#include "CellContents.h"

namespace Sokoban {
const CellContents CellContents::Floor(0);
const CellContents CellContents::Goal(1 << 0);
const CellContents CellContents::Wall(1 << 1);
const CellContents CellContents::Player(1 << 2);
const CellContents CellContents::Box(1 << 3);
const CellContents CellContents::PlayerOnGoal(
		CellContents::Player | CellContents::Goal);
const CellContents CellContents::BoxOnGoal(
		CellContents::Box | CellContents::Goal);

CellContents::CellContents() :
		_value(0) {
}

CellContents::CellContents(const uint8_t &num) :
		_value(num) {
}

CellContents& CellContents::operator =(const CellContents &b) {
	_value = b._value;
	return *this;
}

CellContents& CellContents::operator &=(const CellContents &b) {
	_value &= b._value;
	return *this;
}

CellContents& CellContents::operator |=(const CellContents &b) {
	_value |= b._value;
	return *this;
}

CellContents& CellContents::operator ^=(const CellContents &b) {
	_value ^= b._value;
	return *this;
}

CellContents CellContents::operator &(const CellContents &other) const {
	CellContents theCopy(*this);
	theCopy._value &= other._value;
	return theCopy;
}

CellContents CellContents::operator |(const CellContents &other) const {
	CellContents theCopy(*this);
	theCopy._value |= other._value;
	return theCopy;
}

CellContents CellContents::operator ^(const CellContents &other) const {
	CellContents theCopy(*this);
	theCopy._value ^= other._value;
	return theCopy;
}

bool CellContents::operator ==(const CellContents &other) const {
	return _value == other._value;
}

bool CellContents::operator !=(const CellContents &other) const {
	return _value != other._value;
}

bool CellContents::operator <(const CellContents &other) const {
	return _value < other._value;
}

bool CellContents::operator >(const CellContents &other) const {
	return _value > other._value;
}

bool CellContents::operator <=(const CellContents &other) const {
	return _value <= other._value;
}

CellContents::operator bool() const {
	return _value > 0;
}

CellContents::operator uint8_t() const {
	return _value;
}

} /* namespace Sokoban */
