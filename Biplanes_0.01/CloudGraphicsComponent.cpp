#include "CloudGraphicsComponent.h"


CloudGraphicsComponent::CloudGraphicsComponent(CloudDataComponent* data) : data_(data)
{
}

void CloudGraphicsComponent::update(GameObject& cloud, float time)
{
	cloud.sprite_.setOrigin(cloud.w_ / 2, cloud.h_ / 2);
	cloud.sprite_.setTextureRect(sf::IntRect(cloud.w_ * data_->distance_, 100, cloud.w_, cloud.h_));
	cloud.sprite_.setPosition(cloud.getCenterPosition());
}

void CloudGraphicsComponent::draw(GameObject& cloud, sf::RenderWindow& window)
{
	window.draw(cloud.sprite_);
}

CloudGraphicsComponent::~CloudGraphicsComponent()
{
}
