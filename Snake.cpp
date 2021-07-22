#include "Snake.hpp"
#include <iostream>
#include <utility>
#include <math.h>

bool isComplanary(const Direction& d1, const Direction& d2)
{
	return (d1.m_up && d2.m_down
			|| d1.m_down && d2.m_up
			|| d1.m_left && d2.m_right
			|| d1.m_right && d2.m_left);
}

Snake::Snake()
	:
		m_size(15),
		m_pieceRadius(10.f),
		m_spawnPosition(200.f, 200.f),
		m_direction(),
		m_movementSpeed(30.f),
{
	m_direction.m_right = true;

	for (int i = 0; i < m_size; ++i)
	{
		addPiece(m_direction);
	}
}

void Snake::addPiece(const Direction direction)
{
	sf::Vector2f position;

	if (m_snake.size() >= 1)
	{
		sf::CircleShape* shape =  m_snake[m_snake.size() - 1].getShape();

		position = shape->getPosition();
		float radius = shape->getRadius();

		if (m_direction.m_up) position.y += radius;
		else if (m_direction.m_down) position.y -= radius;
		else if (m_direction.m_left) position.x += radius;
		else if (m_direction.m_right) position.x -= radius;
	}
	else
	{
		position = m_spawnPosition;
	}

	Piece piece{position, direction, m_pieceRadius};
	m_snake.push_back(std::move(piece));
}


void Snake::setDirection(const Direction& direction)
{
	// can't turn to opposite direction
	if (isComplanary(m_direction, direction) || m_direction == direction)
	{
		return;
	}
	if (m_turningPoints.size() >= 1)
	{
		const Direction direction = m_snake[0].getDirection();

		auto centerPoint = m_snake[0].getCenter();
		auto turningPoint = m_turningPoints[m_turningPoints.size() - 1].first;

		float centerValue = (direction.m_up || direction.m_down) ? centerPoint.y : centerPoint.x;
		float turningPointValue = (direction.m_up || direction.m_down) ? turningPoint.y : turningPoint.x;

		if (abs(centerValue - turningPointValue) <= 2 * m_pieceRadius)
		{
			std::cout << "too close\n";
			return;
		}
	}

	sf::Clock clock;

	m_turningPoints.push_back(std::make_pair(m_snake[0].getCenter(), direction));
	m_snake[0].setDirection(m_direction);

	adjustLead(clock.restart());

	m_direction = direction;
}


bool Snake::isDead() const
{
	for (int i = 0; i < m_snake.size(); ++i)
	{
		if (i > 0 && m_snake[0].getShape()->getGlobalBounds().intersects(m_snake[i].getShape()->getGlobalBounds()))
		{
			return true;
		}

		// check for borders as well
	}

	return false;
}


void Snake::adjustLead(sf::Time dt)
{
	Direction direction = m_snake[0].getDirection();
	Direction opposite;

	if (direction.m_up)
	{
		opposite.m_down = true;
	}
	else if (direction.m_down)
	{
		opposite.m_down = true;
	}
	else if (direction.m_left)
	{
		opposite.m_right = true;
	}
	else if (direction.m_right)
	{
		opposite.m_left = true;
	}

	m_snake[0].move(dt.asSeconds() * m_movementSpeed, opposite);
}


void Snake::move(sf::Time dt)
{
	for (int i = 0; i < m_snake.size(); ++i)
	{
		for (int j = 0; j < m_turningPoints.size(); ++j)
		{
			if (m_snake[i].hasHitTurningPoint(m_turningPoints[j].first))
			{
				m_snake[i].setDirection(m_turningPoints[j].second);

				if (i == m_snake.size() - 1)
				{
					m_turningPoints.erase(m_turningPoints.begin() + j);
				}
			}
		}

		m_snake[i].move(dt.asSeconds() * m_movementSpeed);
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_snake)
	{
		states.transform = piece.getShape()->getTransform();
		target.draw(*piece.getShape(), states);
	}
}
