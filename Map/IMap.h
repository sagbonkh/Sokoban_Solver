// Copyright Tobias Faller 2016

#pragma once

#include "IMap.h"
#include "IState.h"
#include "IStaticMap.h"

namespace Sokoban {

/*
 * Stores the initial state and the fixed blocks of the map.
 */
class IMap {
 protected:

  const uint32_t _width;
  const uint32_t _height;

 public:
  /*
   * Constructs a new map with the given movable and static components.
   */
	IMap(uint32_t width, uint32_t height);

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
	virtual uint32_t getWidth() const;

  /*
   * Returns the height of the map.
   */
	virtual uint32_t getHeight() const;
};

inline IMap::IMap(uint32_t width, uint32_t height) :
		_width(width), _height(height) {
}

inline uint32_t IMap::getWidth() const {
	return _width;
}

inline uint32_t IMap::getHeight() const {
	return _height;
}

}  // namespace Sokoban
