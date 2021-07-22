all: sfml sfml-build

sfml: main.cpp Snake.cpp Piece.cpp Game.cpp
	g++ -c main.cpp Snake.cpp Piece.cpp Game.cpp

sfml-build: main.o Snake.o Piece.o Game.o
		g++ main.o Snake.o Piece.o Game.o -o out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o sfml
