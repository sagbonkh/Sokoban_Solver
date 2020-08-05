// Copyright Tobias Faller 2016
#pragma once

#include <stdint.h>

#include <unordered_map>

#include "../BoxState.h"
#include "../Coordinate.h"

namespace Sokoban {

/**
 * Data-object to store the position of the player and the movable boxes.
 * For easier computation the dead lock state of the boxes are stored in
 * the BoxState structure.
 */
class IState {
public:
	/*
	 * Creates a new state.
	 */
	IState() = default;

	/*
	 * Destroys this state and its data.
	 */
	virtual ~IState() = default;

	/*
	 * Returns the coordinates of the player.
	 */
	virtual Coordinate getPlayerPosition() const = 0;

	/*
	 * Sets the coordinates of the player.
	 */
	virtual void setPlayerPosition(Coordinate playerPosition) = 0;

	/*
	 * Returns the list of boxes and their states.
	 */
	virtual std::unordered_map<Coordinate, BoxState>* getBoxes() = 0;
	virtual const std::unordered_map<Coordinate, BoxState>* getBoxes() const = 0;

	/*
	 * Creates a copy of this State.
	 */
	virtual IState* clone() const = 0;
};

}  // namespace Sokoban
