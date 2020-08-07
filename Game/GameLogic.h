// Copyright Tobias Faller 2016

#pragma once
#include <stdint.h>
#include <map>

#include "GameLevel.h"
#include "../NewMap/MapState.h"
#include "../Stack/Stack.h"
#include "../Stack/StackFrame.h"

using std::map;
using std::shared_ptr;
using std::make_shared;

namespace Sokoban {

namespace SokobanGameLogic {

/*
 * Provides the number of commands useable in-game.
 */
enum Command {
	Up,
	Down,
	Left,
	Right,
	Undo //Reset?
};

}

/*
 * Provides the basic sokoban logics.
 * E.g: Pushing boxes and detecting if the level was successfully finished.
 */
class GameLogic {
private:
	static const map<SokobanGameLogic::Command, Direction> CommandDirections;
	struct timespec _startTime;
	struct timespec _endTime;
	bool _finished;
	uint32_t _steps;

	uint32_t _undoUsage;
	uint32_t _undoCount;
	Stack _stack;

	shared_ptr<MapState> _map;

	/*
	 * Checks if all targets have a box on top.
	 */
	bool checkFinished();

public:
	/*
	 * Creates a new GameLogic object without a map loaded.
	 */
	GameLogic();

	/*
	 * Destroys this GameLogic object and possibly the saved state.
	 */
	~GameLogic() = default;

	/*
	 * Resets the internal state to the provided one
	 */
	void reset(const shared_ptr<const GameLevel> &level);
	// resets level to beginning
	void reset();

	/*
	 * Updates the current state.
	 * Returns true if the state changed.
	 */
	bool update(SokobanGameLogic::Command command);
	bool undo();

	/*
	 * Returns the current state.
	 */
	shared_ptr<const MapState> getState() const;

	/*
	 * Returns if this level is currently solved.
	 */
	bool isFinished() const;

	/*
	 * Returns the current time taken to solve the level.
	 * If the level is finished the stopped time is returned.
	 */
	double getTime() const;

	/*
	 * Returns the number of steps needed to solve the level.
	 */
	uint32_t getSteps() const;

	/*
	 * Sets the number of undo operations.
	 */
	void setUndoCount(uint32_t count);

	/*
	 * Returns the number of undo operations.
	 */
	uint32_t getUndoCount() const;
};

}  // namespace Sokoban

