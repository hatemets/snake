all: sfml sfml-build clean

sfml: main.cpp Snake.cpp Piece.cpp Game.cpp Helper.cpp Food.cpp
	g++ -c main.cpp Snake.cpp Piece.cpp Game.cpp Helper.cpp Food.cpp

sfml-build: main.o Snake.o Piece.o Game.o Helper.o Food.o
		g++ main.o Snake.o Piece.o Game.o Helper.o Food.o -o out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o sfml
