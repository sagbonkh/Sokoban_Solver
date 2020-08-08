#CXX = g++ -std=gnu++11 -O3 -Wall -Wpedantic -Wextra
CXX = g++  

# General
CFLAGS += -std=c++2a
CFLAGS += -I$(shell pwd)
CFLAGS += -fdiagnostics-color=always
# Debugging
CFLAGS += -ggdb
CFLAGS += -gdwarf
CFLAGS += -g3 
CFLAGS += -O0 
CFLAGS += -fno-eliminate-unused-debug-symbols
CFLAGS += -fvar-tracking
CFLAGS += -fvar-tracking-assignments
CFLAGS += -ginline-points
CFLAGS += -gstatement-frontiers

# Warnings
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wctor-dtor-privacy
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wformat=2
CFLAGS += -Winit-self
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wnoexcept
CFLAGS += -Wold-style-cast
CFLAGS += -Woverloaded-virtual
CFLAGS += -Wredundant-decls
CFLAGS += -Wshadow
CFLAGS += -Wsign-promo
CFLAGS += -Wstrict-null-sentinel
CFLAGS += -Wstrict-overflow=5
CFLAGS += -Wundef
CFLAGS += -Wno-unused
CFLAGS += -Wno-variadic-macros
CFLAGS += -Wno-parentheses
CFLAGS += -fdiagnostics-show-option

DEBUG_LIB_DIR = /usr/lib/x86_64-linux-gnu/debug
LIBS = -Wl,--rpath=$(DEBUG_LIB_DIR) -Wl,--no-strip-discarded -L$(DEBUG_LIB_DIR) -lcurses -lstdc++

MAIN_BINARIES = Build/SokobanMain
#TEST_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Test.cpp) $(wildcard *Test.cpp)))

HEADER = $(wildcard **/*.h)
OBJECTS = $(addprefix Build/, $(addsuffix .o, $(basename $(wildcard **/*.cpp) $(wildcard *.cpp))))

CPPLINT_PATH = ../cpplint.py

.PRECIOUS: Build/%.o

all: compile 

compile: $(MAIN_BINARIES)

clean:
	rm -rf Build/*


Build/SokobanMain: $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

#Build/%Main: FORCE
#	make -j4 $($*_OBJECTS)
#	$(CXX) $(CFLAGS) -o $@ $($*_OBJECTS) $(LIBS)
	
FORCE: 

Build/%.o: %.cpp $(HEADER)
	@mkdir -p $(shell dirname $@) || true
	$(CXX) $(CFLAGS) -c -o $@ $< 

