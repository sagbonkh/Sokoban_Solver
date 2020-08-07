#CXX = g++ -std=gnu++11 -O3 -Wall -Wpedantic -Wextra
CXX = g++  
CFLAGS = -ggdb3 -O0 -std=c++2a -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
LIBS = -lcurses -lstdc++ 

MAIN_BINARIES = Build/SokobanMain
#TEST_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Test.cpp) $(wildcard *Test.cpp)))

HEADER = $(wildcard **/*.h)
OBJECTS = $(addprefix Build/, $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard **/*.cpp) $(wildcard *.cpp)))))
Sokoban_OBJECTS += Build/SokobanMain.o
Sokoban_OBJECTS += Build/Coordinate.o
Sokoban_OBJECTS += Build/Display.o
#Sokoban_OBJECTS += Build/Game/Game.o
#Sokoban_OBJECTS += Build/Game/GameLogic.o
Sokoban_OBJECTS += Build/Game/GameLevel.o
Sokoban_OBJECTS += Build/Map/Map.o
Sokoban_OBJECTS += Build/Map/State.o
Sokoban_OBJECTS += Build/Map/StaticMap.o
Sokoban_OBJECTS += Build/NewMap/Cell.o
Sokoban_OBJECTS += Build/NewMap/Cells/TargetCell.o
Sokoban_OBJECTS += Build/NewMap/Cells/WallCell.o
Sokoban_OBJECTS += Build/NewMap/MapGrid.o
Sokoban_OBJECTS += Build/NewMap/MapBuilder.o
Sokoban_OBJECTS += Build/NewMap/CellContents.o
#Sokoban_OBJECTS += Build/NewMap/MapState.o
Sokoban_OBJECTS += Build/NewMap/CellOccupant.o
Sokoban_OBJECTS += Build/NewMap/Occupants/Player.o
Sokoban_OBJECTS += Build/NewMap/Occupants/Box.o
Sokoban_OBJECTS += Build/Parser.o
Sokoban_OBJECTS += Build/Rectangle.o
Sokoban_OBJECTS += Build/Size.o
Sokoban_OBJECTS += Build/Stack/MemoryBlock.o
Sokoban_OBJECTS += Build/Stack/Stack.o
Sokoban_OBJECTS += Build/Stack/StackFrame.o


CPPLINT_PATH = ../cpplint.py

.PRECIOUS: Build/%.o

all: compile 

compile: $(MAIN_BINARIES)

clean:
	rm -rf Build/*


Build/%Main: FORCE
	make -j4 $($*_OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $($*_OBJECTS) $(LIBS)
	
FORCE: 

Build/%.o: %.cpp $(HEADER)
	@mkdir -p $(shell dirname $@) || true
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)

