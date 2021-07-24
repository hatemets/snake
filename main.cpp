#include "Game.hpp"
#include <iostream>

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (const char* errMsg)
	{
		std::cerr << "Error: " << errMsg << '\n';
	}

	return 0;
}
