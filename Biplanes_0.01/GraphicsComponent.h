#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"
class GraphicsComponent
{
public:
	virtual void update(GameObject&, float time) = 0;
	virtual void draw(GameObject&, sf::RenderWindow&) = 0;

	~GraphicsComponent() {}
};

