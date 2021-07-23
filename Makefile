all: sfml sfml-build

sfml: main.cpp Snake.cpp Piece.cpp Game.cpp Food.cpp Helper.cpp
	g++ -c main.cpp Snake.cpp Piece.cpp Game.cpp Helper.cpp Food.cpp

sfml-build: main.o Snake.o Piece.o Game.o Food.o Helper.o
		g++ main.o Snake.o Piece.o Game.o Food.o Helper.o -o out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o sfml
