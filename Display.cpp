// Copyright Tobias Faller 2016

#include "Display.h"

#include <curses.h>

#include <algorithm>

#include "Map/Cell.h"
#include "Map/MapGrid.h"
#include "Map/MapState.h"

namespace Sokoban {

Display::Display(WINDOW *window) : _valid(false), _window(window), _grid(nullptr), _enabled(false),
		_rectangle(0, 0, 30, 20), _scale(3, 2) {
	if (start_color() == ERR) {
		_valid = false;
		return;
	}

	init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Nothing (' ')
	init_pair(2, COLOR_WHITE, COLOR_BLACK);  // Block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Player
	init_pair(4, COLOR_GREEN, COLOR_BLUE);  // Player on target
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Box
	init_pair(6, COLOR_YELLOW, COLOR_BLUE);  // Box on target
	init_pair(7, COLOR_BLACK, COLOR_BLUE);  // Target
	_valid = true;
}

void Display::setEnabled(bool enabled) {
	_enabled = enabled;

	if (enabled) update();
}

bool Display::isEnabled() {
	return _enabled;
}

void Display::setPosition(const Coordinate &position) {
	_rectangle.setPosition(position);
}

Coordinate Display::getPosition() const {
	return _rectangle.getPosition();
}

void Display::setSize(const Size &size) {
	_rectangle.setSize(size);
}

Size Display::getSize() const {
	return _rectangle.getSize();
}

void Display::setRectangle(const Rectangle &rectangle) {
	_rectangle = rectangle;
}

Rectangle Display::getRectangle() const {
	return _rectangle;
}

void Display::setGrid(const shared_ptr<const MapGrid> &grid) {
	_grid = grid;
	update();
}

void Display::updateState() {
	update();
}

void Display::update() {
	if (!_enabled || !_grid) return;

	uint32_t width = std::min(_grid->getWidth(), _rectangle.width);
	uint32_t height = std::min(_grid->getHeight(), _rectangle.height);

	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t subY = 0; subY < _scale.height; subY++) {
			bool moved = false;

			for (uint32_t x = 0; x < width; x++) {
				char c = _grid->get(
					{ x, y })->getDisplayChar();

				wattron(_window, COLOR_PAIR(getColorForChar(c)));

				if (c != ' ' || moved) {
					if (!moved && (moved = true)) {
						wmove(_window, _rectangle.y + (y * _scale.height) + subY, _rectangle.x + (x * _scale.width));
					}

					c = modifyChar(c);
					for (uint32_t subX = 0; subX < _scale.width; subX++) {
						waddch(_window, c);
					}
				}
			}
		}
	}
}

Size Display::getScale() const {
	return _scale;
}

void Display::setScale(const Size &scale) {
	_scale = scale;
}

char Display::modifyChar(char c) {
	switch (c) {
		case '#':  // Block
			return '#';
		case '+':  // Player
			return '@';
		case '@':  // Player on target
			return '@';
		case '$':  // Box
			return 'O';
		case '*':  // Box on target
			return 'O';
		case '.':  // Target
			return ' ';
		default:  // Nothing (' ')
			return ' ';
	}
}

uint16_t Display::getColorForChar(char c) {
	switch (c) {
		case '#':  // Block
			return 2;
		case '@':  // Player
			return 3;
		case '+':  // Player on target
			return 4;
		case '$':  // Box
			return 5;
		case '*':  // Box on target
			return 6;
		case '.':  // Target
			return 7;
		default:  // Nothing (' ')
			return 1;
	}
}
bool Display::isValid() const {
	return _valid;
}
}  // namespace Sokoban
