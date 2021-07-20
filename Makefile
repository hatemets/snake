all: sfml sfml-build

sfml: main.cpp Snake.cpp
	g++ -c main.cpp Snake.cpp

sfml-build: main.o Snake.o
		g++ main.o Snake.o -o out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o sfml
