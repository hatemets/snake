#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <memory>

class Food : public sf::Drawable
{
	public:
		Food(const sf::RenderWindow& window);
		Food(Food&& other) noexcept;
		sf::Vector2f getCenter() const;

	private:
		std::unique_ptr<sf::CircleShape> m_food;
		sf::Vector2u m_spawnArea;
		float m_radius;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	
	public:
		float getRadius() { return m_radius; }
		void setRandomPosition();
};

#endif
