#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Snake.hpp"

class Game
{
	public:
		Game();
		void run();

	private:
		void processEvents();
		void update(sf::Time dt);
		void render();
		void handlePlayerInput(sf::Keyboard::Key key);

		sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	private:
		sf::RenderWindow m_window;
		Snake m_snake;
};

#endif
