/*
 * IStaticMap.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */

#include "IStaticMap.h"

#include <string.h>

#include <set>

namespace Sokoban {

using std::set;

IStaticMap::IStaticMap(uint32_t width, uint32_t height) :
		_width(width), _height(_height), _targets() {
}

uint32_t IStaticMap::getWidth() const {
	return _width;
}

uint32_t IStaticMap::getHeight() const {
	return _height;
}

const set<Coordinate>& IStaticMap::getTargets() const {
	return _targets;
}
}
