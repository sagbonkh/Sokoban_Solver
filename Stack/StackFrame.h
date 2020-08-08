// Copyright Tobias Faller

#pragma once

#include <stdint.h>

#include "Game/Direction.h"

namespace Sokoban {

/*
 * Provides a class for updating / storing stack segments.
 */
class StackFrame {
	friend class Stack;

private:
	uint8_t _data;

public:
	/*
	 * Creates a new StackFrame.
	 */
	StackFrame();

	/*
	 * Copies the provided StackFrame.
	 */
	explicit StackFrame(const StackFrame &frame);

	/*
	 * Destroys this StackFrame.
	 */
	~StackFrame();

	/*
	 * Gets the direction of this StackFrame.
	 */
	Direction getDirection() const;

	/*
	 * Sets the direction of this StackFrame.
	 */
	void setDirection(Direction);

	/*
	 * Returns if this StackFrame element moves a box.
	 */
	bool isMoveBox() const;

	/*
	 * Sets if this StackFrame element moves a box.
	 */
	void setMoveBox(bool moveBox);

	/*
	 * Returns if this element is special.
	 * Just because there was 1 bit of free data left.
	 */
	bool isSpecial() const;

	/*
	 * Sets if this element is special.
	 * Just because there was 1 bit of free data left.
	 */
	void setSpecial(bool special);
};

}  // namespace Sokoban

