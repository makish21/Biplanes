#pragma once
#include "PhysicsComponent.h"
#include "PlayerDataComponent.h"
#include "GameObject.h"

#define INCREASE 0.01
#define DECREASE -0.01

class PlayerPhysicsComponent :
	public PhysicsComponent
{
	friend class PlayerCollisionComponent;
public:
	PlayerPhysicsComponent(PlayerDataComponent*);

	virtual void update(GameObject&, float time, sf::RenderWindow&);
	
	~PlayerPhysicsComponent();
private:
	void rotationComputing(GameObject&);
	void collision(GameObject&, sf::RenderWindow&);

	PlayerDataComponent* data_;
};

