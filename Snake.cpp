#include "Snake.hpp"
#include <iostream>
#include <utility>
#include <math.h>
#include "Helper.hpp"
#include "Food.hpp"

Snake::Snake()
	:
		m_size(7),
		m_pieceRadius(5.f),
		m_spawnPosition(100.f, 300.f),
		m_direction(),
		m_movementSpeed(100.f)
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
		position = m_snake[m_snake.size() - 1].getShape()->getPosition();

		if (direction.m_up) position.y += m_pieceRadius;
		else if (direction.m_down) position.y -= m_pieceRadius;
		else if (direction.m_left) position.x += m_pieceRadius;
		else if (direction.m_right) position.x -= m_pieceRadius;
	}
	else
	{
		position = m_spawnPosition;
	}

	Piece piece{position, direction, m_pieceRadius};
	m_snake.push_back(std::move(piece));
}

void Snake::addPiece()
{
	addPiece(m_snake[m_snake.size() - 1].getDirection());
}


const Piece& Snake::getPiece(int index) const
{
	if (index >= m_snake.size())
	{
		throw "invalid index for snake";
	}

	return m_snake[index];
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

	m_snake[0].setDirection(m_direction);
	m_turningPoints.push_back(std::make_pair(m_snake[0].getCenter(), direction));

	m_direction = direction;
}

bool Snake::hasHitItself() const
{
	if (m_snake.size() > 3)
	{
		int i;

		for (i = 2; i < m_snake.size(); ++i)
		{
			float distance = getDistanceBetweenPoints(m_snake[0].getCenter(), m_snake[i].getCenter());
			if (distance < 2 * m_pieceRadius)
			{
				return true;
			}
		}
	}

	return false;
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

				// if last piece has passed tpoint, delete tpoint
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
