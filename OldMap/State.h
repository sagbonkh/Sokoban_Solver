// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_STATE_H_
#define PROJEKT_MAP_STATE_H_

#include <stdint.h>

#include <unordered_map>

#include "../BoxState.h"
#include "../Coordinate.h"
#include "../OldMap/IState.h"

namespace Sokoban {

/**
 * Data-object to store the position of the player and the movable boxes.
 * For easier computation the dead lock state of the boxes are stored in
 * the BoxState structure.
 */
class State: public IState {
protected:
	Coordinate _player;
	std::unordered_map<Coordinate, BoxState> _boxes;

	/*
	 * Protected constructor for copying.
	 */
	explicit State(const IState *state);

public:
	/*
	 * Creates a new state.
	 */
	State();
	static State* copyState(const IState *state);

	/*
	 * Destroys this state and its data.
	 */
	virtual ~State() = default;

	/*
	 * Returns the coordinates of the player.
	 */
	Coordinate getPlayerPosition() const override;

	/*
	 * Sets the coordinates of the player.
	 */
	void setPlayerPosition(Coordinate playerPosition) override;

	/*
	 * Returns the list of boxes and their states.
	 */
	std::unordered_map<Coordinate, BoxState>* getBoxes() override;
	const std::unordered_map<Coordinate, BoxState>* getBoxes() const override;

	/*
	 * Creates a copy of this State.
	 */
	State* clone() const override;
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_STATE_H_
