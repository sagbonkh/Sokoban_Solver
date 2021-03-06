/*
 * Box.cpp
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#include "Map/Occupants/Box.h"

namespace Sokoban {

Box::Box(MapState &mapState, const shared_ptr<Cell> cell) :
		CellOccupant(mapState, cell) {
}

CellOccupant::Type Box::getType() const {
	return Type::Box;
}

} /* namespace Sokoban */
