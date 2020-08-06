// Copyright Tobias Faller 2016

#include "Game.h"

#include <unistd.h>
#include <curses.h>

#include <string>
#include <functional>
#include <utility>

#include "GameLogic.h"

#include "../Display/ColoredDisplay.h"

#include "../Map/Map.h"
#include "../Map/State.h"
#include "../Map/StaticMap.h"

namespace Sokoban {

Game::Game(const std::string &directory) {
	_state = SokobanGame::State::Play;
	_quit = false;
	_directory = directory;


	if (initDisplay() != 0) {
		_state = SokobanGame::State::Invalid;
		return;
	}

	_display = new ColoredDisplay(_window);
	if (!_display->isValid()) {
		_state = SokobanGame::State::Invalid;
		return;
	}

	_display->setEnabled(false);
	_display->setRectangle(
			Rectangle(0, 3, SokobanGame::GAME_WIDTH, SokobanGame::GAME_HEIGHT));

	_gameLogic.setUndoCount(5);
}

Game::~Game() {
	if (_display)
		delete _display;

	if (_gameLevel)
		delete _gameLevel;

	destroyDisplay();
}

void Game::play() {
	if (_state == SokobanGame::State::Invalid)
		return;

	while (!_quit) {
		if (!handleKey()) {
			return;
		}

		usleep(10);
	}
}

void Game::changeLevel(const GameLevel &level, const IMap *map) {

	_gameLevel = level;
	_gameLogic.reset(level.getMap());

	wclear(_window);
	_display->setMap(map);
	_display->updateState(_gameLogic.getState());
	_display->setEnabled(true);
	wrefresh(_window);
}

uint32_t Game::initDisplay() {
	_window = initscr();
	if (!_window) {
		printf("Could not init curse!");
		return 1;
	}

	raw();
	nonl();
	cbreak();  // No waiting for char

	noecho();  // Don't print char
	curs_set(false);  // Don't show the cursor

	keypad(stdscr, true);  // Special keycodes.
	nodelay(stdscr, true);  // Don't buffer the input

	return 0;
}

void Game::destroyDisplay() {
	endwin();
}

bool Game::handleKey() {
	int key = getch();

	switch (key) {
	case KEY_CLOSE:  // Quit / Close
	case 'm':  // Menu
	case 'q':  // Quit to menu
		_display->setEnabled(false);
		return false;
	case KEY_UP:
		if (_gameLogic.update(SokobanGameLogic::Command::Up))
			_display->updateState(_gameLogic.getState());
		break;
	case KEY_DOWN:
		if (_gameLogic.update(SokobanGameLogic::Command::Down))
			_display->updateState(_gameLogic.getState());
		break;
	case KEY_LEFT:
		if (_gameLogic.update(SokobanGameLogic::Command::Left))
			_display->updateState(_gameLogic.getState());
		break;
	case KEY_RIGHT:
		if (_gameLogic.update(SokobanGameLogic::Command::Right))
			_display->updateState(_gameLogic.getState());
		break;
	case 'U':  // undo
	case 'u':
		if (_gameLogic.update(SokobanGameLogic::Command::Undo))
			_display->updateState(_gameLogic.getState());
		break;
	case 'R':  // reset
	case 'r':
		_gameLogic.reset(_display->getMap());
		break;
	default:
		break;
	}

	werase(_window);
	_display->update();

	wmove(_window, 0, 0);
	wprintw(_window, "Time: %.2f sec", _gameLogic.getTime());

	wmove(_window, 1, 0);
	wprintw(_window, "Finished: %s", (_gameLogic.isFinished() ? "yes" : "no"));
	wrefresh(_window);

	return true;
}

void Game::setUndoCount(uint32_t count) {
	_gameLogic.setUndoCount(count);
}

uint32_t Game::getUndoCount() const {
	return _gameLogic.getUndoCount();
}

void Game::setScale(const Size &scale) {
	_display->setScale(scale);
}

Size Game::getScale() const {
	return _display->getScale();
}

}  // namespace Sokoban
