#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Direction.hpp"
#include "Piece.hpp"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <utility>
#include <vector>

class Snake : public sf::Drawable
{
	private:
		std::vector<Piece> m_snake;
		int m_size;
		float m_movementSpeed;
		sf::Vector2f m_spawnPosition;
		std::vector<std::pair<sf::Vector2f, Direction>> m_turningPoints;

		Direction m_direction;

	public:
		Snake();
		void addPiece(const Direction direction);
		void move();
		void setDirection(const	Direction& direction);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif
