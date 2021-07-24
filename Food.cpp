#include "Food.hpp"
#include <ctime>
#include <iostream>

Food::Food(const sf::RenderWindow& window)
	: m_spawnArea(window.getSize()),
	m_food(),
	m_radius(15.f)
{
	srand((unsigned)time(0));

	m_food = std::make_unique<sf::CircleShape>(m_radius);
	m_food->setFillColor(sf::Color::Magenta);
	/* setRandomPosition(); */
	m_food->setPosition(300.f, 500.f);
}

Food::Food(Food&& other) noexcept
	: m_food(std::move(other.m_food))
{
}

sf::Vector2f Food::getCenter() const
{
	sf::Vector2f center;
	sf::FloatRect bounds = m_food->getGlobalBounds();

	center.x = bounds.left + bounds.width / 2;
	center.y = bounds.top + bounds.height / 2;

	return center;
}

void Food::setRandomPosition()
{
	sf::Vector2f position;

	position.x = static_cast<float>(rand() % m_spawnArea.x);
	position.y = static_cast<float>(rand() % m_spawnArea.y);

	m_food->setPosition(position);
}


void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_food, states);
}
