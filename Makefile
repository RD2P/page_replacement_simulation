.PHONY: clean

CFLAGS=-Wall -Wextra -Werror -pedantic

SRC=src
BIN=build/bin
OBJ=build/obj

all: dirs $(BIN)/main

dirs:
	mkdir -p $(BIN) $(OBJ)

$(BIN)/main: $(OBJ)/main.o $(OBJ)/page_replacement.o
	rm -f main
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/page_replacement.o
	ln -s $(BIN)/main main

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/page_replacement.h
	g++ $(CFLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/page_replacement.o: $(SRC)/page_replacement.cpp $(SRC)/page_replacement.h
	g++ $(CFLAGS) -c -o $(OBJ)/page_replacement.o $(SRC)/page_replacement.cpp

clean:
	rm -rf build/ main