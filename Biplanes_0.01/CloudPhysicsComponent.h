#pragma once
#include "PhysicsComponent.h"
#include "CloudDataComponent.h"
#include "GameObject.h"

class CloudPhysicsComponent :
	public PhysicsComponent
{
public:
	CloudPhysicsComponent(CloudDataComponent*);

	virtual void update(GameObject&, float time, sf::RenderWindow&);

	~CloudPhysicsComponent();
private:
	void collision(GameObject&, sf::RenderWindow&);
	CloudDataComponent* data_;
};

