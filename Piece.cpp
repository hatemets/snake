#include "Piece.hpp"
#include <math.h>
#include <iostream>

Piece::Piece(const sf::Vector2f position, const Direction direction, const float radius)
	: m_direction(direction)
{
	m_shape = std::make_unique<sf::CircleShape>(radius);
	m_shape->setPosition(position);
	m_shape->setFillColor(sf::Color::White);
}


Piece::Piece(Piece&& anotherPiece) noexcept
	: m_shape(std::move(anotherPiece.m_shape)), m_direction(anotherPiece.m_direction)
{
}


const sf::Vector2f Piece::getCenter() const
{
	sf::Vector2f center;
	sf::FloatRect bounds = m_shape->getGlobalBounds();

	// adjust the values (in SFML, 1 rect unit is twice the vector's)
	bounds.top *= 2;
	bounds.left *= 2;

	center.x = bounds.left + bounds.width / 2;
	center.y = bounds.top + bounds.height / 2;

	return center;
}


void Piece::move(const float distance)
{
	sf::Vector2f movement;

	if (m_direction.m_up) movement.y -= distance;
	else if (m_direction.m_down) movement.y += distance;
	else if (m_direction.m_left) movement.x -= distance;
	else if (m_direction.m_right) movement.x += distance;

	m_shape->move(movement);
}


void Piece::move(const float distance, const Direction direction)
{
	sf::Vector2f movement;

	if (direction.m_up) movement.y -= distance;
	else if (direction.m_down) movement.y += distance;
	else if (direction.m_left) movement.x -= distance;
	else if (direction.m_right) movement.x += distance;

	m_shape->move(movement);
}


bool Piece::hasHitTurningPoint(const sf::Vector2f turningPoint) const
{
	float errorMargin = 1.f;

	if (m_direction.m_up)
	{
		return (getCenter().y <= turningPoint.y && abs(getCenter().x - turningPoint.x) <= errorMargin);
	}
	else if (m_direction.m_down)
	{
		return (getCenter().y >= turningPoint.y && abs(getCenter().x - turningPoint.x) <= errorMargin);
	}
	else if (m_direction.m_right)
	{
		return (getCenter().x >= turningPoint.x && abs(getCenter().y - turningPoint.y) <= errorMargin);
	}
	else if (m_direction.m_left)
	{
		return (getCenter().x <= turningPoint.x && abs(getCenter().y - turningPoint.y) <= errorMargin);
	}
	else
	{
		std::cout << std::boolalpha;
		std::cerr << "error (piece): no valid direction" << std::endl;
		std::cout << "up: " << m_direction.m_up << std::endl;
		std::cout << "down: " << m_direction.m_down << std::endl;
		std::cout << "left: " << m_direction.m_left << std::endl;
		std::cout << "right: " << m_direction.m_right << std::endl;
		std::cout << "---" << std::endl;
		return false;
	}
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_shape, states);
}

