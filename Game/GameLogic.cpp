// Copyright Tobias Faller 2016


#include <utility>
#include <set>
#include <ctime>

#include "Game/GameLogic.h"
#include "Map/Coordinate.h"
#include "Map/Cell.h"
#include "Map/Occupants/Player.h"

#include "Map/MapState.h"
#include "Stack/Stack.h"
#include "Stack/StackFrame.h"

using Sokoban::SokobanGameLogic::Command;
namespace Sokoban {

const map<Command, Direction> GameLogic::CommandDirections
	{
		{ Command::Up, Direction::Up },
		{ Command::Down, Direction::Down },
		{ Command::Left, Direction::Left },
		{ Command::Right, Direction::Right } };

GameLogic::GameLogic() : _startTime(), _endTime(), _finished(false), _steps(0), _undoUsage(0), _undoCount(0) {
	_map = nullptr;
}

void GameLogic::reset(const shared_ptr<const GameLevel> &level) {
	_map = make_shared<MapState>(level->getMap());
	_steps = 0;
	_finished = false;
	clock_gettime(CLOCK_MONOTONIC, &_startTime);
}

bool GameLogic::update(SokobanGameLogic::Command command) {
	if (_finished) return false;

	if (command == SokobanGameLogic::Command::Undo) {
		return undo();
	}
	if (!CommandDirections.contains(command)) return false;
	shared_ptr<Player> player = _map->getPlayer();

	// this means the command was to move the player in a direction
	StackFrame frame;

	Direction dir = CommandDirections.at(command);
	Cell::move_result_t move_result = player->moveIn(dir);
	bool box_moved = get<2>(move_result);
	++_steps;
	if (box_moved) checkFinished();
	frame.setMoveBox(box_moved);
	frame.setDirection(dir);
	_stack.push(frame);
	if (_undoUsage > 0) _undoUsage--;
	return true;

}

bool GameLogic::undo() {

	if ((_undoUsage >= _undoCount) || _stack.isEmpty()) return false;
	StackFrame frame;

	_undoUsage++;
	_stack.pop(&frame);

	int32_t modX = 0;
	int32_t modY = 0;

	shared_ptr<Player> player = _map->getPlayer();
	player->reverseMoveIn(frame.getDirection(), frame.isMoveBox());
	return true;
}

bool GameLogic::isFinished() const {
	return _finished;
}

bool GameLogic::checkFinished() {
	if (!_map->won()) return false;

	clock_gettime(CLOCK_MONOTONIC, &_endTime);
	_finished = true;
	return true;
}

double GameLogic::getTime() const {
	double deltaTime;

	if (_finished) {
		deltaTime = (_endTime.tv_sec - _startTime.tv_sec);
		deltaTime += (_endTime.tv_nsec - _startTime.tv_nsec) / 1000000000.0;
	} else {
		struct timespec currentTime;
		clock_gettime(CLOCK_MONOTONIC, &currentTime);

		deltaTime = (currentTime.tv_sec - _startTime.tv_sec);
		deltaTime += (currentTime.tv_nsec - _startTime.tv_nsec) / 1000000000.0;
	}

	return deltaTime;
}

uint32_t GameLogic::getSteps() const {
	return _steps;
}

void GameLogic::setUndoCount(uint32_t count) {
	_undoCount = count;
}

uint32_t GameLogic::getUndoCount() const {
	return _undoCount;
}

shared_ptr<const MapState> GameLogic::getState() const {
	return _map;
}

shared_ptr<const MapGrid> GameLogic::getGrid() const {
	return _map->getGrid();
}

}  // namespace Sokoban
