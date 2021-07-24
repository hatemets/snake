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
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
