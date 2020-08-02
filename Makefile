#CXX = g++ -std=gnu++11 -O3 -Wall -Wpedantic -Wextra
CXX = g++  
CFLAGS = -ggdb3 -O0 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
LIBS = -lcurses -lstdc++ 

MAIN_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Main.cpp) $(wildcard *Main.cpp)))
TEST_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Test.cpp) $(wildcard *Test.cpp)))

HEADER = $(wildcard **/*.h)
OBJECTS = $(addprefix Build/, $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard **/*.cpp) $(wildcard *.cpp)))))

CPPLINT_PATH = ../cpplint.py

.PRECIOUS: Build/%.o

all: compile 

compile: $(MAIN_BINARIES)

clean:
	rm -rf Build/*
	
Build/%Main: Build/%Main.o $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

Build/%.o: %.cpp $(HEADER)
	@mkdir -p $(shell dirname $@) || true
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
