.PHONY: clean

CFLAGS=-Wall -Wextra -pedantic

all: dirs build/bin/main

dirs:
	mkdir -p build build/bin build/obj

build/bin/main: build/obj/main.o
	g++ -o build/bin/main build/obj/main.o
	ln -s build/bin/main main

build/obj/main.o: main.cpp
	g++ $(CFLAGS) -c -o build/obj/main.o main.cpp

clean:
	rm -rf build/