/*
 * BoundaryCell.cpp
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#include "WallCell.h"

namespace Sokoban {

WallCell::WallCell(shared_ptr<MapState> mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}
WallCell::WallCell(shared_ptr<MapState> mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}

bool WallCell::canBeOccupied() const {
	return false;
}

bool WallCell::isWall() const {
	return true;
}

StaticType WallCell::getStaticType() const {
	return StaticType::Block;
}

} /* namespace Sokoban */
