General:
- Use of a memory-efficient A\* algorithm, such as IDA\*. 
- make your implementation as efficient as possible.
- Cite all the help you used to make this algorithm.
- Save solutions in LURD format (Capital letters are used to indicate a move that pushes a box.)

Solver:
- recognize unsolvable puzzles
- Efficiently solve small/easy puzzles
- find good heuristics, using pattern databases, and/or do something beyond basic IDA\* search

Posibilities:
- identify positions for boxes that will result in the box being permanently unsavagable. prevent examining any paths that put a box in this position (list of positions can be done once, at beginning of solve)
- identify which positions each boxe can be moved from (i.e. they can be pushed in a direction that isn't a wall) and the direction to push
	- if any box can't move at all, reject this solution
	- narrow these possible moves to find positions we can push from without disturbing other boxes

To Code:
- function to identify all positions that result in the simulation failing (positions boxes can't be in ever)
- function to list all directions each box can be pushed in / positions each box can be pushed from 
- function to identify all positions we can reach without disturbing other boxes
- function to find shortest path to reach a position without moving other boxes
- variables to track these things and check them when they might have changed


Also:
- You list solutions to puzzles from some known collection of Sokoban puzzles -- it is important to demonstrate that your solver is correct and can solve well-known puzzles.
- clearly specify the biggest and most complex problem your solver can solve in at most 5 minutes.
- clearly specify the smallest problem that your solver cannot solve in 5 minutes or less. (make a non-trivial effort to find this smallest problem; For example, you could write a program that generates Sokoban puzzles and then solves them)
- Written report
