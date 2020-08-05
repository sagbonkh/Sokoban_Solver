// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_MAP_H_
#define PROJEKT_MAP_MAP_H_

#include <gtest/gtest_prod.h>

#include "IMap.h"
#include "State.h"
#include "StaticMap.h"

namespace Sokoban {

/*
 * Stores the initial state and the fixed blocks of the map.
 */
class Map: public IMap {
protected:
	const IState *_initState;
	const IStaticMap *_map;

public:
	/*
	 * Constructs a new map with the given movable and static components.
	 */
	Map(const IState *state, const IStaticMap *map, uint32_t width,
			uint32_t height);

	/*
	 * Destroys the map with its components.
	 */
	virtual ~Map();

	/*
	 * Returns the initial state of the map.
	 */
	const IState* getInitialState() const override;

	/*
	 * Returns the static components of this map.
	 */
	const IStaticMap* getMap() const override;

};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_MAP_H_
