#include "Helper.hpp"

bool isComplanary(const Direction& d1, const Direction& d2)
{
	return (d1.m_up && d2.m_down
			|| d1.m_down && d2.m_up
			|| d1.m_left && d2.m_right
			|| d1.m_right && d2.m_left);
}

float getDistanceBetweenPoints(const sf::Vector2f a, const sf::Vector2f b)
{
	return (sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2)));
}

const sf::Vector2f getCenter(const sf::CircleShape& shape)
{
	sf::Vector2f center;
	sf::FloatRect bounds = shape.getGlobalBounds();

	// adjust the values (in SFML, 1 rect unit is twice the vector's)
	bounds.top *= 2;
	bounds.left *= 2;

	center.x = bounds.left + bounds.width / 2;
	center.y = bounds.top + bounds.height / 2;

	return center;
}
