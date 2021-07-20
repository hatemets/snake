#include "Snake.hpp"
#include <iostream>
#include <utility>

bool isComplanary(const Direction& d1, const Direction& d2)
{
	return (d1.m_up && d2.m_down
			|| d1.m_down && d2.m_up
			|| d1.m_left && d2.m_right
			|| d1.m_right && d2.m_left);
}

sf::Vector2f getCenter(const sf::CircleShape& shape)
{
	sf::Vector2f pieceCenter;
	sf::FloatRect bounds = shape.getGlobalBounds();

	// adjust the values (in SFML, 1 rect unit is twice the vector's)
	bounds.top *= 2;
	bounds.left *= 2;

	pieceCenter.x = bounds.left + bounds.width / 2;
	pieceCenter.y = bounds.top + bounds.height / 2;

	return pieceCenter;
}

Snake::Snake()
	:
		m_size(3),
		m_radius(50.f),
		m_spawnPosition(0.f, 0.f),
		m_direction(),
		m_movementSpeed(0.5)
{
	m_direction.m_right = true;

	for (int i = 0; i < m_size; ++i)
	{
		addPiece();
	}
}

void Snake::addPiece()
{
	auto piece = std::make_unique<sf::CircleShape>(sf::CircleShape{m_radius});
	piece->setFillColor(sf::Color::White);

	sf::Vector2f position;

	if (m_snake.size() >= 1)
	{
		position = m_snake[m_snake.size() - 1]->getPosition();

		if (m_direction.m_up) position.y -= m_radius;
		else if (m_direction.m_down) position.y += m_radius;
		else if (m_direction.m_left) position.x -= m_radius;
		else if (m_direction.m_right) position.x += m_radius;
	}
	else
	{
		position = m_spawnPosition;
	}

	piece->setPosition(position);
	m_snake.push_back(std::move(piece));
}

void Snake::move()
{
	sf::Vector2f movement;

	if (m_direction.m_up) movement.y -= m_movementSpeed;
	else if (m_direction.m_down) movement.y += m_movementSpeed;
	else if (m_direction.m_left) movement.x -= m_movementSpeed;
	else if (m_direction.m_right) movement.x += m_movementSpeed;

	for (auto& piece : m_snake)
	{
		/* piece->move(movement); */

		for (auto& tPoint : m_turningPoints)
		{
			/* if (getCenter(*piece).x == tPoint.first.x && ); */
		}
	}
}

void Snake::setDirection(const Direction& direction)
{
	// can't turn to opposite direction
	if (isComplanary(m_direction, direction) || m_direction == direction)
	{
		return;
	}
	else
	{
		m_direction = direction;

		auto turningPoint = std::make_pair(getCenter(*m_snake[0]), direction);
		m_turningPoints.insert(turningPoint);
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_snake)
	{
		states.transform = piece->getTransform();
		target.draw(*piece, states);
	}
}
