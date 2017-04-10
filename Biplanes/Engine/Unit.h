#pragma once
#include <SFML\Graphics.hpp>
#include "Transformable.h"
#include "Drawable.h"
#include "World.h"

class Unit :
	public gm::Transformable, public gm::Drawable
{
public:
	Unit();
	Unit(sf::Sprite*, sf::Vector2f position);

	virtual bool isCollide(World& world) = 0;

	virtual ~Unit();
};

