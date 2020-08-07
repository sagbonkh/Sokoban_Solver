// Copyright Tobias Faller 2016

#ifndef PROJEKT_COORDINATE_H_
#define PROJEKT_COORDINATE_H_

#include <stdint.h>
#include <initializer_list>
#include <tuple>

#include <functional>

#include "Direction.h"

namespace Sokoban {
typedef uint32_t map_unit_t;
using std::tuple;
using std::tie;
using std::initializer_list;

/*
 * Defines a index out of bounds error.
 */
constexpr const map_unit_t INDEX_OUT_OF_BOUNDS = 0xE1;


/*
 * Defines a coordinate with x and y position of type map_unit_t.
 */
struct Coordinate {
	map_unit_t x = 0;
	map_unit_t y = 0;

	/*
	 * Creates a new location with position 0x0.
	 */
	Coordinate() = default;

	/*
	 * Creates a new location with provided coordinates.
	 */
	explicit Coordinate(map_unit_t x, map_unit_t y);
	Coordinate(const initializer_list<map_unit_t> &values);
	Coordinate(const tuple<map_unit_t, map_unit_t> &values);
	Coordinate(const Coordinate&) = default;

	/*
	 * Destroys this coordinate object.
	 */
	~Coordinate() = default;

	/*
	 * Sets the location of this coordinate object.
	 */
	void set(map_unit_t x, map_unit_t y);

	/*
	 * Returns the x coordinate of this object.
	 */
	map_unit_t getX() const;

	/*
	 * Returns the y coordinate of this object.
	 */
	map_unit_t getY() const;

	Coordinate getAdjacent(Direction dir) const;

	/*
	 * Compares two locations and returns true if bot x and y coordinates are
	 * equal.
	 */
	bool operator==(const Coordinate &other) const;

	/*
	 * Returns true if the y location of this coordinate is lower.
	 * If the y coordinates are equal the algorithm is checking if the x
	 * coordinate is lower than the one of the other object.
	 */
	bool operator<(const Coordinate &other) const;
};

}  // namespace Sokoban

namespace std {

/*
 * Provides a hash function for the Coordinate struct.
 */
template<> struct hash<Sokoban::Coordinate> {
	size_t operator()(Sokoban::Coordinate const &c) const noexcept {
		return hash<uint64_t>()(static_cast<uint64_t>(c.x) // @suppress("Ambiguous problem")
		^ (static_cast<uint64_t>(c.y) << 32));
	}
};

}  // namespace std

#endif  // PROJEKT_COORDINATE_H_
