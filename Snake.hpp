#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <vector>
#include <map>

#include "Auxiliary.hpp"

class Snake : public sf::Drawable
{
	public:
		using Piece = std::unique_ptr<sf::CircleShape>;

	private:
		std::vector<Piece> m_snake;
		int m_size;
		float m_radius;
		float m_movementSpeed;
		sf::Vector2f m_spawnPosition;
		std::map<sf::Vector2f, Direction> m_turningPoints;

		Direction m_direction;

	public:
		Snake();
		void addPiece();
		void move();
		void setDirection(const	Direction& direction);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
