#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

namespace gm
{
	class Drawable
	{
	public:
		Drawable();
		~Drawable();

		void addSprite(sf::Sprite*);

		std::vector<sf::Sprite*> getSprites();

		virtual void draw(sf::RenderWindow& window) = 0;
	protected:
		std::vector<sf::Sprite*> sprites;
	};
}