// Copyright Tobias Falelr 2016

#include "State.h"
#include "IState.h"

namespace Sokoban {

State::State() :
		_player(0, 0), _boxes() {
}
State::State(const IState *state) :
		_player(state->getPlayerPosition()), _boxes {
				state->getBoxes()->cbegin(), state->getBoxes()->cend() } {
}

State* State::copyState(const IState *state) {
	return new State(state);
}

const std::unordered_map<Coordinate, BoxState>* State::getBoxes() const {
	return &_boxes;
}

std::unordered_map<Coordinate, BoxState>* State::getBoxes() {
	return &_boxes;
}

Coordinate State::getPlayerPosition() const {
	return _player;
}

void State::setPlayerPosition(Coordinate position) {
	_player = position;
}

State* State::clone() const {
	return new State(this);
}

}  // namespace Sokoban
