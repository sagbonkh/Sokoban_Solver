// Copyright Tobias Faller 2016

#include "Game.h"

#include <unistd.h>
#include <curses.h>

#include <string>
#include <functional>
#include <utility>

#include "GameLogic.h"

#include "../Display.h"


namespace Sokoban {
using SokobanGameLogic::Command;
const map<int, Command> Game::KeyCommands
	{
		{ KEY_UP, Command::Up },
		{ KEY_DOWN, Command::Down },
		{ KEY_LEFT, Command::Left },
		{ KEY_RIGHT, Command::Right },
		{ 'u', Command::Undo },
		{ 'U', Command::Undo },
		{ 'r', Command::Reset },
		{ 'R', Command::Reset },
		{ KEY_CLOSE, Command::Quit },
		{ 'q', Command::Quit } };

Game::Game(const std::string &levelFile) {
	_state = SokobanGame::State::Play;
	_quit = false;
	_levelFile = levelFile;
	_gameLevels = GameLevel::loadAllFromFile(_levelFile);
	_currentLevel = _gameLevels.begin();

	if (initDisplay() != 0) {
		_state = SokobanGame::State::Invalid;
		return;
	}

	_display = new Display(_window);
	if (!_display->isValid()) {
		_state = SokobanGame::State::Invalid;
		return;
	}

	_display->setEnabled(false);
	_display->setRectangle(Rectangle(0, 3, SokobanGame::GAME_WIDTH, SokobanGame::GAME_HEIGHT));

	_gameLogic.setUndoCount(5);
	_gameLogic.reset(*_currentLevel);
}

Game::~Game() {
	if (_display) delete _display;
	destroyDisplay();
}

void Game::play() {
	if (_state == SokobanGame::State::Invalid) return;

	while (!_quit) {
		if (!handleKey()) {
			return;
		}

		usleep(10);
	}
	return;
}

void Game::nextLevel() {
	++_currentLevel;
	if (_currentLevel == _gameLevels.end()) {
		quit();
		return;
	}
	resetLevel();
}

void Game::resetLevel() {
	_gameLogic.reset(*_currentLevel);

	wclear(_window);
	_display->setGrid(_gameLogic.getGrid());
	_display->updateState();
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
	if (!KeyCommands.contains(key)) {
		redraw();
		handleFinished();
		return false;
	}

	Command cmd = KeyCommands.at(key);
	if (cmd == Command::Quit) {
		_display->setEnabled(false);
		return false;
	}

	if (_gameLogic.update(cmd)) _display->updateState();
	if (handleFinished()) return false;

	redraw();
	return true;
}

bool Game::handleFinished() {
	if (!_gameLogic.isFinished()) return false;
	//TODO: reset game to next level and continue, but for now just quit
	quit();
	return true;
	_display->setEnabled(false);

	_gameLogic.reset();

	werase(_window);
	wrefresh(_window);
}
void Game::quit() {
	_display->setEnabled(false);
	_quit = true;
	werase(_window);
	wrefresh(_window);
}

void Game::redraw() {
	werase(_window);
	_display->update();

	wmove(_window, 0, 0);
	wprintw(_window, "Time: %.2f sec", _gameLogic.getTime());

	wmove(_window, 1, 0);
	wprintw(_window, "Finished: %s", (_gameLogic.isFinished() ? "yes" : "no"));
	wrefresh(_window);
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
