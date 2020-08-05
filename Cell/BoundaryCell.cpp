/*
 * BoundaryCell.cpp
 *
 *  Created on: Aug. 3, 2020
 *      Author: sidney
 */

#include "BoundaryCell.h"

namespace Sokoban {

BoundaryCell::BoundaryCell(shared_ptr<MapState> mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}
BoundaryCell::BoundaryCell(shared_ptr<MapState> mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}

bool BoundaryCell::canBeOccupied() const {
	return false;
}

bool BoundaryCell::isBoundary() const {
	return true;
}

StaticType BoundaryCell::getStaticType() const {
	return StaticType::Block;
}

} /* namespace Sokoban */
