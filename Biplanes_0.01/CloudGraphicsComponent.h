#pragma once
#include "GraphicsComponent.h"
#include "CloudDataComponent.h"
#include "GameObject.h"

class CloudGraphicsComponent :
	public GraphicsComponent
{
public:
	CloudGraphicsComponent(CloudDataComponent*);
	
	virtual void update(GameObject&, float time);
	virtual void draw(GameObject&, sf::RenderWindow&);

	~CloudGraphicsComponent();
private:
	CloudDataComponent* data_;
};

