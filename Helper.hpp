#ifndef HELPER_HPP
#define HELPER_HPP

#include "Direction.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

bool isComplanary(const Direction& d1, const Direction& d2);
float getDistanceBetweenPoints(const sf::Vector2f a, const sf::Vector2f b);
const sf::Vector2f getCenter(const sf::CircleShape& shape);

#endif
