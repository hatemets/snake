#include "Snake.hpp"

Direction keyToDirection(sf::Keyboard::Key key)
{
	Direction direction;

	switch (key)
	{
		case sf::Keyboard::Key::W:
			direction.m_up = true;
			break;
		case sf::Keyboard::Key::A:
			direction.m_left = true;
			break;
		case sf::Keyboard::Key::S:
			direction.m_down = true;
			break;
		case sf::Keyboard::Key::D:
			direction.m_right = true;
			break;
	}

	return direction;
}

int main()
{
	sf::RenderWindow window{sf::VideoMode(1920, 1080), "Snake game"};

	Snake snake;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					snake.setDirection(keyToDirection(event.key.code));
					break;
			}
		}

		window.clear();
		snake.move();
		window.draw(snake);
		window.display();
	}

	return 0;
}
