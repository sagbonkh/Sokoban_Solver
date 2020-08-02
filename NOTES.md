# Maps
## Static Map:
Stores immovable aspects of a map (targets and walls)
- size (width/height of map)
- one dimentional array containing the object (if any) at each coordinate
  - array uses two bits per coordinate (which holds the value of the enum StaticType for each cell)
- set of coordinates specifiying the targets boxes must be moved to
- Functions to check if a set of coordinates refers to a wall, target, or neither.

## State:
Opposite of Static Map. Stores:
- Coordinates of Player
- Coordinates of all Boxes

## Map:
Stores:
- Static Map
- Initial State