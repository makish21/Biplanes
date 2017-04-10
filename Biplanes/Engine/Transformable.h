#pragma once
#include <SFML\System.hpp>
#include "World.h"

namespace gm
{
	class Transformable
	{
	public:
		Transformable();
		Transformable(const sf::Vector2f& position);
		Transformable(const sf::Vector2f& position,
					  const float& rotation, 
					  const float& speed, 
					  const sf::Vector2f& direction);

		virtual ~Transformable();
		
		void setSpeed(const float& speed);
		void setRotation(const float& rotation);
		void setDirection(const sf::Vector2f direction);

		float getSpeed();
		float getRotation();
		sf::Vector2f getDirection();

		virtual void update(const float& elapsed) = 0;
		//virtual void update(const float& elapsed, World& world) = 0;

	protected:
		sf::Vector2f position;
		sf::Vector2f direction;
		float rotation;
		float speed;
	};
}
