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


# New Maps
- GameLevel(s) are created when loading in level file, which lazily loads in the map data
- GameLevel class has a function to get a MapGrid::initial_map_t, using MapBuilder to generate it
- When MapState is created, it is given the MapGrid::initial_map_t and creates a MapGrid object with itself and the grid