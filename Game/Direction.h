// Copyright Tobias Faller

#pragma once

#include <map>
using std::map;

namespace Sokoban {

/*
 * Defines all four movement directions.
 */
enum Direction {
	Left = 0, Right = 1, Up = 2, Down = 3
};

const map<Direction, Direction> OppositeDirections
{
		{ Direction::Up, Direction::Down },
		{ Direction::Down, Direction::Up },
		{ Direction::Left, Direction::Right },
		{ Direction::Right, Direction::Left } };



}  // namespace Sokoban
