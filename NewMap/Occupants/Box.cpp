/*
 * Box.cpp
 *
 *  Created on: Aug. 6, 2020
 *      Author: sidney
 */

#include "Box.h"

namespace Sokoban {

Box::Box(const shared_ptr<MapState> mapState, const shared_ptr<Cell> cell) :
		CellOccupant(mapState, cell) {
}

CellOccupantType Box::getType() const {
	return CellOccupantType::Box;
}

} /* namespace Sokoban */
