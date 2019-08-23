CC=g++
CFLAGS=-std=c++11
EXE=sort

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:src/%.cpp=obj/%.o)

OBJ_DIR=obj/ 
BIN_DIR=bin

all: dirs $(EXE)

dirs: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

obj/%.o: src/%.cpp 
	$(CC) $(CFLAGS) -c $^ -o $@

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

.PHONY: all dirs clean