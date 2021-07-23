#include "Food.hpp"
#include <ctime>
#include <algorithm>

Food::Food(const sf::RenderWindow& window)
	: m_spawnArea(window.getSize()),
	m_food(),
	m_radius(10.f)
{
	srand((unsigned)time(0));

	m_food = std::make_unique<sf::CircleShape>(m_radius);
	m_food->setFillColor(sf::Color::Yellow);
	setRandomPosition();
}

sf::Vector2f Food::getCenter() const
{
	return ::getCenter(*m_food); // access global namespace
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
