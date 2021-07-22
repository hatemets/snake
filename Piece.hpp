#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Direction.hpp"

class Piece : public sf::Drawable
{
	public:
		Piece(const sf::Vector2f position, const Direction direction, const float radius);
		Piece(Piece&& anotherPiece) noexcept;

	private:
		std::unique_ptr<sf::CircleShape> m_shape;
		Direction m_direction;

	public:
		sf::CircleShape* getShape() const { return m_shape.get(); }
		const sf::Vector2f getCenter() const;
		void move(const float distance);
		void move(const float distance, const Direction direction);
		bool hasHitTurningPoint(sf::Vector2f turningPoint) const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	
	public:
		void setDirection(const Direction direction) { m_direction = direction; }
		const Direction getDirection() { return m_direction; }
};

#endif
