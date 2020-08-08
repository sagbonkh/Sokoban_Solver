// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_GAME_H_
#define PROJEKT_GAME_GAME_H_

#include <gtest/gtest.h>
#include <curses.h>

#include <string>

#include "../Display.h"
#include "GameLogic.h"

#include "GameLevel.h"

namespace Sokoban {

class Game;

namespace SokobanGame {

constexpr const uint32_t GAME_WIDTH = 30;
constexpr const uint32_t GAME_HEIGHT = 15;

enum State : uint32_t {
	Invalid, Play
};

}  // namespace SokobanGame

/*
 * Provides a class for a visual sokoban instance.
 * The game is started via the play function and provides a level selector
 * able to handle folders and display a preview of the level.
 */
class Game {
private:
	SokobanGame::State _state;
	std::string _levelFile;

	WINDOW *_window;
	Display *_display;

	vector<shared_ptr<const GameLevel>> _gameLevels;
	vector<shared_ptr<const GameLevel>>::const_iterator _currentLevel;
	GameLogic _gameLogic;

	bool _quit;

	/*
	 * Initializes the display and ncurses.
	 */
	uint32_t initDisplay();

	/*
	 * Destroys the display and uninitializes ncurses.
	 */
	void destroyDisplay();

	/*
	 * Changes level of a game.
	 */
	void nextLevel();
	void resetLevel();

	/*
	 * Handles user input
	 */
	bool handleKey();

	void redraw();
	bool handleFinished();
	void quit();

public:
	static const map<int, SokobanGameLogic::Command> KeyCommands;
	/*
	 * Creates a new Game instance with a working-directory.
	 */
	explicit Game(const std::string &directory);

	/*
	 * Destroys this instance of Sokoban.
	 */
	~Game();

	/*
	 * Starts this game.
	 */
	void play();

	/*
	 * Sets the number of steps which can be undone.
	 */
	void setUndoCount(uint32_t count);

	/*
	 * Returns the number of steps which can be undone.
	 */
	uint32_t getUndoCount() const;

	/*
	 * Sets the scale of the level display.
	 */
	void setScale(const Size &scale);

	/*
	 * Returns the scale of the level display.
	 */
	Size getScale() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_GAME_H_
