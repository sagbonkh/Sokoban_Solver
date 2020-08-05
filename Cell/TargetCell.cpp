/*
 * TargetCell.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */
#include <memory>

#include "TargetCell.h"

namespace Sokoban {

TargetCell::TargetCell(shared_ptr<MapState> mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}

TargetCell::TargetCell(shared_ptr<MapState> mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}

bool TargetCell::isTarget() const {
	return true;
}

TargetCell::operator StaticType() const {
	return StaticType::Target;
}

std::shared_ptr<TargetCell> TargetCell::getptr() {
	return std::enable_shared_from_this<TargetCell>::shared_from_this();
}

} /* namespace Sokoban */
