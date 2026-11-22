.PHONY: clean test

CFLAGS=-Wall -Wextra -Werror -pedantic -std=c++11

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

test: all
	@set -e; \
	./main --help >/dev/null; \
	./main 10 5 10 >/dev/null; \
	./main 10 5 0 >/dev/null; \
	! ./main 0 5 10 >/dev/null 2>&1; \
	! ./main 10 0 10 >/dev/null 2>&1; \
	! ./main 10 5 -1 >/dev/null 2>&1; \
	! ./main 10 5 nope >/dev/null 2>&1; \
	echo "All tests passed."