// Copyright Tobias Faller 2016

#pragma once


#include <curses.h>

#include "../Level/MapGrid.h"
#include "Map/Coordinate.h"
#include "Display/Rectangle.h"
#include "Display/Size.h"

namespace Sokoban {

/*
 * Provides a interface for a (n)curses driven display.
 * The display provides a basic sheme also used by the sokoban level format.
 */
class Display {
protected:
	bool _valid;

	WINDOW *_window;
	shared_ptr<const MapGrid> _grid;

	bool _enabled;
	Rectangle _rectangle;
	Size _scale;


public:
	/*
	 * Creates a new Display at position (0/0) with
	 * no map.
	 */
	explicit Display(WINDOW *window);

	/*
	 * Destroys the Display leaving the window usable.
	 */
	virtual ~Display() = default;

	/*
	 * Sets the underlying map for this Display.
	 */
	void setGrid(const shared_ptr<const MapGrid> &grid);

	/*
	 * Updates the displayed state of this Display.
	 */
	void updateState();

	/*
	 * Returns the drawn map.
	 */
	const shared_ptr<const MapGrid> getGrid() const;

	/*
	 * Enables / disables this Display instance.
	 */
	void setEnabled(bool enabled);

	/*
	 * Sets the position of this Display instance.
	 */
	void setPosition(const Coordinate &position);

	/*
	 * Gets the current position of this Display.
	 */
	Coordinate getPosition() const;

	/*
	 * Sets the size of this Display.
	 */
	void setSize(const Size &size);

	/*
	 * Returns the size of this Display.
	 */
	Size getSize() const;

	/*
	 * Sets the rectangle of this Dispaly.
	 */
	void setRectangle(const Rectangle &rectangle);

	/*
	 * Gets the rectangle of this Display.
	 */
	Rectangle getRectangle() const;

	/*
	 * Returns if this Display is enabled.
	 */
	bool isEnabled();

	/*
	 * Draws the level onto the Display.
	 */
	virtual void update();

	/*
	 * Retrieves if this display was correctly initialized.
	 */
	bool isValid() const;

	Size getScale() const;
	void setScale(const Size &scale);

protected:

	/*
	 * Returns the color for a displayed character.
	 */
	static uint16_t getColorForChar(char c);

	/*
	 * Modifies a character before displaying it.
	 */
	static char modifyChar(char c);
};

}  // namespace Sokoban

