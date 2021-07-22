#include "Game.hpp"
#include <iostream>

Game::Game()
	: m_window(sf::VideoMode(640, 480), "snake")
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code);
				break;
			case sf::Event::Closed:
				m_window.close();
				break;
		}
	}
}

void Game::update(sf::Time dt)
{
	if (m_snake.isDead())
	{
		std::cout << "game over" << std::endl;
		return;
	}

	m_snake.move(dt);
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_snake);
	m_window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key)
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
		default:
			return;
	}

	m_snake.setDirection(direction);
}
