#pragma once
#include "GraphicsComponent.h"
#include "PlayerDataComponent.h"
#include "GameObject.h"

class PlayerGraphicsComponent :
	public GraphicsComponent
{
public:
	PlayerGraphicsComponent(PlayerDataComponent* data);

	virtual void update(GameObject&, float time);
	virtual void draw(GameObject&, sf::RenderWindow& window);

	~PlayerGraphicsComponent();
private:
	PlayerDataComponent* data_;

	std::list<PlayerDataComponent::Smoke_*> smokes_;
	std::list<PlayerDataComponent::Smoke_*>::iterator smokeNo_;

	void explosion(GameObject&, float time);
	void burning(GameObject&, float time);
	void smokeUpdate(float time);
	void hitpointsCounter(GameObject&, float time);
};