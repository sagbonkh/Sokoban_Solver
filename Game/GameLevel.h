// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_MAPENTRY_H_
#define PROJEKT_GAME_MAPENTRY_H_

#include <istream>
#include <memory>
#include <string>

#include "../NewMap/MapGrid.h"

namespace Sokoban {
using std::istream;
using std::shared_ptr;
using std::ifstream;
using std::string;

/*
 * Defines a map selectable by the LevelSelector class.
 * It holds the name of the map name and its path.
 */
class GameLevel {
public:
	typedef std::istream::pos_type pos_type;
private:
	std::string _path;
	pos_type _pos;

	mutable string _name = "";
	mutable shared_ptr<const MapGrid::initial_map_t> _map = nullptr;

	void load(istream &in) const;
	void load() const;

public:
	/*
	 * Creates a new MapEntry with a name and a path or from an istream.
	 */
	GameLevel() = delete;
	GameLevel(const std::string &path, pos_type pos);
	GameLevel(istream &in);
	GameLevel(const std::string &path, ifstream &in);
	GameLevel(const GameLevel &mapEntry) = delete;
	~GameLevel() = default;

	const std::string& getName() const;
	const shared_ptr<const MapGrid::initial_map_t>& getMap() const;

};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_MAPENTRY_H_
