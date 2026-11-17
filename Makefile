.PHONY: clean

CFLAGS=-Wall -Wextra -Werror -pedantic

SRC=src
BIN=build/bin
OBJ=build/obj

all: dirs $(BIN)/main

dirs:
	mkdir -p $(BIN) $(OBJ)

$(BIN)/main: $(OBJ)/main.o
	rm -f main
	g++ -o $(BIN)/main $(OBJ)/main.o
	ln -s $(BIN)/main main

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ $(CFLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
	rm -rf build/ main