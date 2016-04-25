#pragma once
#include "GameObject.h"
class PhysicsComponent
{
public:
	virtual void update(GameObject&, float time, sf::RenderWindow&) = 0;
	~PhysicsComponent() {}
};

