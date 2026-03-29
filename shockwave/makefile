all:build run

CXX = g++
SRC = src/*.cpp
LIBS = -lSDL2 -lGL -lGLU -lpugixml
INCLUDE = -Iinclude/
BUILD_O = shockwaveplayer

build:
	$(CXX) $(SRC) $(INCLUDE) $(LIBS) -o $(BUILD_O)

run:
	./$(BUILD_O)