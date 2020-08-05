// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_STATICMAP_H_
#define PROJEKT_MAP_STATICMAP_H_

#include <stdint.h>
#include <gtest/gtest_prod.h>

#include <set>

#include "IStaticMap.h"

#include "../Coordinate.h"

namespace Sokoban {
using std::set;

/*
 * Defines the static contents of the current map.
 * E.g: walls and targets.
 */
class StaticMap: public IStaticMap {
  FRIEND_TEST(StaticMap, GetSet);
  FRIEND_TEST(StaticMap, Types);
  FRIEND_TEST(StaticMap, Size);

  friend class MapBuilder;

 private:
	uint32_t _width;
	uint32_t _height;

	std::set<Coordinate> _targets;
  uint8_t* _map;

  /*
   * Protected constructor for the SokobanBuilder.
   */
  StaticMap(uint32_t width, uint32_t height);

  /*
   * Protected constructor for cloning.
   */
	explicit StaticMap(const StaticMap *map);

 public:
  /*
   * Destroys the static map and its internal memory block.
   */
	virtual ~StaticMap();

  /*
   * Returns the field at the provided position of this map or Nothing if the
   * field is empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	StaticType get(const Coordinate &position) const override;

  /*
   * Returns the field at the provided position of this map or Nothing if the
   * field is empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	StaticType get(uint32_t x, uint32_t y) const override;

  /*
   * Checks if the field at the provided position is a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isBlock(const Coordinate &position) const override;

  /*
   * Checks if the field at the provided position is a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isBlock(uint32_t x, uint32_t y) const override;

  /*
   * Checks if the field at the provided position is a target for a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isTarget(const Coordinate &position) const override;

  /*
   * Checks if the field at the provided position is a target for a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isTarget(uint32_t x, uint32_t y) const override;

  /*
   * Checks if the field at the provided position is a empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isEmpty(const Coordinate &position) const override;

  /*
   * Checks if the field at the provided position is a empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	bool isEmpty(uint32_t x, uint32_t y) const override;

  /*
   * Sets the field at the provided position to a specified type.
   * This method overwrites the old value.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	void set(const Coordinate &position, StaticType type) override;

  /*
   * Sets the field at the provided position to a specified type.
   * This method overwrites the old value.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
	void set(uint32_t x, uint32_t y, StaticType type) override;


  /*
   * Clones this StaticMap.
   */
	StaticMap* clone() const override;
	const std::set<Coordinate>& getTargets() const override;
	uint32_t getHeight() const override;
	uint32_t getWidth() const override;
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_STATICMAP_H_
