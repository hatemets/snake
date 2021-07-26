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
		float m_pieceRadius;
		sf::Vector2f m_spawnPosition;
		std::vector<std::pair<sf::Vector2f, Direction>> m_turningPoints;
		sf::FloatRect m_worldBounds;

		Direction m_direction;

	public:
		Snake(const sf::RenderWindow& window);
		void addPiece(const Direction direction);
		void addPiece();
		void move(sf::Time dt);
		void setDirection(const	Direction& direction);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
		bool hasHitItself() const;
		bool hasHitBorder() const;
		bool isDead() const { return (hasHitItself() || hasHitBorder()); }

	public:
		const Piece& getPiece(int index=0) const;
		float getPieceRadius() const { return m_pieceRadius; }
		float getVelocity() const { return m_movementSpeed; }
		void setVelocity(float speed) { m_movementSpeed = speed; }
};

#endif
