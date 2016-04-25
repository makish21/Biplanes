#include "CloudPhysicsComponent.h"
#include <iostream>

CloudPhysicsComponent::CloudPhysicsComponent(CloudDataComponent* data) : data_(data)
{
	
	
}

void CloudPhysicsComponent::collision(GameObject& cloud, sf::RenderWindow& window)
{
	if (cloud.x_ > window.getView().getSize().x)
	{
		cloud.life_ = false;
	}
	if (cloud.x_ < -cloud.w_)
	{
		cloud.life_ = false;
	}
}

void CloudPhysicsComponent::update(GameObject& cloud, float time, sf::RenderWindow& window)
{
	cloud.dx_ = -0.3 / (data_->distance_ + 1);
	

	collision(cloud, window);
	cloud.x_ += (cloud.dx_ * time);
	//std::cout << cloud.x_ << std::endl;
}

CloudPhysicsComponent::~CloudPhysicsComponent()
{
}
