/*
 * TargetCell.cpp
 *
 *  Created on: Aug. 5, 2020
 *      Author: sidney
 */
#include "Map/Cells/TargetCell.h"

#include <memory>


namespace Sokoban {

TargetCell::TargetCell(MapState &mapState, uint32_t posX,
		uint32_t posY) :
		Cell(mapState, posX, posY) {
}

TargetCell::TargetCell(MapState &mapState,
		const Coordinate &coordinate) :
		Cell(mapState, coordinate) {
}

bool TargetCell::isTarget() const {
	return true;
}

char TargetCell::getDisplayChar() const {
	if (isOccupied() && getOccupant()->getType() == CellOccupantType::Player) {
		return '+'; // Player on target
	} else if (isOccupied() && getOccupant()->getType() == CellOccupantType::Box) {
		return '*'; // Box on target
	} else {
		return '.'; // Target
	}




}

} /* namespace Sokoban */
