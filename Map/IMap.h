// Copyright Tobias Faller 2016

#pragma once

#include "../Map/IState.h"
#include "../Map/IStaticMap.h"

namespace Sokoban {

/*
 * Stores the initial state and the fixed blocks of the map.
 */
class IMap {
protected:

	const map_unit_t _width;
	const map_unit_t _height;

public:
	/*
	 * Constructs a new map with the given movable and static components.
	 */
	IMap(map_unit_t width, map_unit_t height);

	/*
	 * Destroys the map with its components.
	 */
	virtual ~IMap() = default;

	/*
	 * Returns the initial state of the map.
	 */
	virtual const IState* getInitialState() const = 0;

	/*
	 * Returns the static components of this map.
	 */
	virtual const IStaticMap* getMap() const = 0;

	/*
	 * Returns the width of the map.
	 */
	virtual map_unit_t getWidth() const;

	/*
	 * Returns the height of the map.
	 */
	virtual map_unit_t getHeight() const;
};

inline IMap::IMap(map_unit_t width, map_unit_t height) :
		_width(width), _height(height) {
}

inline map_unit_t IMap::getWidth() const {
	return _width;
}

inline map_unit_t IMap::getHeight() const {
	return _height;
}

}  // namespace Sokoban
