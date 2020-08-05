// Copyright Tobias Faller 2016

#include "Map.h"

namespace Sokoban {

Map::Map(const IState *state, const IStaticMap *map, uint32_t width,
		uint32_t height) :
		IMap(width, height), _initState(state), _map(map) {
}

Map::~Map() {
	delete _initState;
	delete _map;
}

const IState* Map::getInitialState() const {
	return _initState;
}
const IStaticMap* Map::getMap() const {
	return _map;
}

}  // namespace Sokoban
