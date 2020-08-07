// Copyright Tobias Faller 2016

#pragma once

#include <stdint.h>

#include <set>

#include "../Coordinate.h"

namespace Sokoban {

class MapBuilder;

/*
 * Defines the two types of static elements.
 */
enum StaticType {
	Nothing = 0, Block = 1, Target = 2
};


/*
 * Defines the static contents of the current map.
 * E.g: walls and targets.
 */
class IStaticMap {

	friend class MapBuilder;

protected:
	/*
	 * Protected constructor for the SokobanBuilder.
	 */
	IStaticMap() = default;

public:
	/*
	 * Destroys the static map and its internal memory block.
	 */
	virtual ~IStaticMap() = default;

	/*
	 * Returns the field at the provided position of this map or Nothing if the
	 * field is empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual StaticType get(const Coordinate &position) const = 0;

	/*
	 * Returns the field at the provided position of this map or Nothing if the
	 * field is empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual StaticType get(map_unit_t x, map_unit_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isBlock(const Coordinate &position) const = 0;

	/*
	 * Checks if the field at the provided position is a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isBlock(map_unit_t x, map_unit_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a target for a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isTarget(const Coordinate &position) const = 0;

	/*
	 * Checks if the field at the provided position is a target for a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isTarget(map_unit_t x, map_unit_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isEmpty(const Coordinate &position) const = 0;

	/*
	 * Checks if the field at the provided position is a empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isEmpty(map_unit_t x, map_unit_t y) const = 0;

	/*
	 * Sets the field at the provided position to a specified type.
	 * This method overwrites the old value.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual void set(const Coordinate &position, StaticType type) = 0;

	/*
	 * Sets the field at the provided position to a specified type.
	 * This method overwrites the old value.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual void set(map_unit_t x, map_unit_t y, StaticType type) = 0;

	/*
	 * Returns the width of the map.
	 */
	virtual map_unit_t getWidth() const = 0;

	/*
	 * Returns the height of the map.
	 */
	virtual map_unit_t getHeight() const = 0;

	/*
	 * Clones this StaticMap.
	 */
	virtual IStaticMap* clone() const = 0;

	/*
	 * Returns all positions of the targets.
	 */
	virtual const std::set<Coordinate>& getTargets() const = 0;
};

}  // namespace Sokoban
