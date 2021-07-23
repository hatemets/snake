#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Food.hpp"

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

		sf::Time TimePerFrame = sf::seconds(1.f / 400.f);

	private:
		sf::RenderWindow m_window;
		sf::Text m_scoreBoard;
		std::unique_ptr<sf::Font> m_font;
		Snake m_snake;
		Food m_food;
		bool m_gameOver;
		int m_score;
};

#endif
