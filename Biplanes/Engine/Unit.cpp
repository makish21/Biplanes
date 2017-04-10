#include "Unit.h"



Unit::Unit()
{
}

Unit::Unit(sf::Sprite * sprite, sf::Vector2f position) :
	Transformable(position)
{
	addSprite(sprite);
}


Unit::~Unit()
{
}
