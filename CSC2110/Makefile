AutomatedMakefile = am
CC = g++ -std=c++11

CSC2110_PATH = $(GAME_PATH)/CSC2110
RANDOM_PATH = $(GAME_PATH)/random

SRC_DIR=./src
BUILD_DIR=./build
HEADER_DIR=./include

INC_DIRS = -I$(CSC2110_PATH)/include -I$(RANDOM_PATH)
LIB_DIRS = -L$(RANDOM_PATH)
LIBS = -lrandom

COMPILE = $(CC) $(INC_DIRS) -Wno-deprecated-declarations -c
LINK = $(CC) -o

CSC2110_FILES = build/Integer.o build/Double.o build/Keyboard.o build/Matrix.o build/Permutation.o build/Poly.o build/ReadFile.o build/WriteFile.o build/String.o build/HighPerformanceCounter.o

all: CSC2110_LIB

CSC2110_LIB: 					$(CSC2110_FILES)

$(BUILD_DIR)/String.o:				$(SRC_DIR)/String.cpp $(HEADER_DIR)/String_.h
						$(COMPILE) $< -o $@

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
								$(COMPILE) $< -o $@

