/*
 * BoundaryCell.cpp
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#include "Map/Cells/WallCell.h"

namespace Sokoban {

WallCell::WallCell(MapState &mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}
WallCell::WallCell(MapState &mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}

bool WallCell::canBeOccupied() const {
	return false;
}

bool WallCell::isWall() const {
	return true;
}

char WallCell::getDisplayChar() const {
	return '#'; // Block
}

} /* namespace Sokoban */
