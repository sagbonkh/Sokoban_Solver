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
 * Defines a index out of bounds error.
 */
constexpr const uint32_t INDEX_OUT_OF_BOUNDS = 0xE1;

/*
 * Defines the static contents of the current map.
 * E.g: walls and targets.
 */
class IStaticMap {

	friend class MapBuilder;

protected:
	uint32_t _width;
	uint32_t _height;

	std::set<Coordinate> _targets;

	/*
	 * Protected constructor for the SokobanBuilder.
	 */
	IStaticMap(uint32_t width, uint32_t height);

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
	virtual StaticType get(Coordinate position) const = 0;

	/*
	 * Returns the field at the provided position of this map or Nothing if the
	 * field is empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual StaticType get(uint32_t x, uint32_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isBlock(Coordinate position) const = 0;

	/*
	 * Checks if the field at the provided position is a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isBlock(uint32_t x, uint32_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a target for a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isTarget(Coordinate position) const = 0;

	/*
	 * Checks if the field at the provided position is a target for a block.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isTarget(uint32_t x, uint32_t y) const = 0;

	/*
	 * Checks if the field at the provided position is a empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isEmpty(Coordinate position) const = 0;

	/*
	 * Checks if the field at the provided position is a empty.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual bool isEmpty(uint32_t x, uint32_t y) const = 0;

	/*
	 * Sets the field at the provided position to a specified type.
	 * This method overwrites the old value.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual void set(Coordinate position, StaticType type) = 0;

	/*
	 * Sets the field at the provided position to a specified type.
	 * This method overwrites the old value.
	 * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
	 * thrown.
	 */
	virtual void set(uint32_t x, uint32_t y, StaticType type) = 0;

	/*
	 * Returns the width of the map.
	 */
	virtual uint32_t getWidth() const;

	/*
	 * Returns the height of the map.
	 */
	virtual uint32_t getHeight() const;

	/*
	 * Clones this StaticMap.
	 */
	virtual IStaticMap* clone() const = 0;

	/*
	 * Returns all positions of the targets.
	 */
	virtual const std::set<Coordinate>& getTargets() const;
};

}  // namespace Sokoban
