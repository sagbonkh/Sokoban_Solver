// Copyright Tobias Faller 2016

#include "Parser/ExpandedParser.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Sokoban;

int main(int argv, char** argc) {
//    try {
        std::ifstream levelFile("./contrib/Levels/100Boxes.sok.old", ios_base::in);
        if (!levelFile.is_open()) {
            cerr << "Could not open file" << endl;
            return 1;
        }
        ExpandedParser* parser = new ExpandedParser();
        const Map* map = parser->readStream(&levelFile);
        levelFile.close();
        const StaticMap* sMap = map->getMap();
        const State* state = map->getInitialState();
//    } catch (const Sokoban::SokobanParser::Error& exception) {
//        std::cerr << "Sokoban::SokobanParser::Error: " << exception << std::endl;
//    }
    return 0;
}
