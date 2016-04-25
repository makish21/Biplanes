#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent()
{

}

PlayerInputComponent::PlayerInputComponent(PlayerDataComponent* data) : data_(data)
{

}

void PlayerInputComponent::acceleration()
{
	if (data_->speed_ < data_->maxSpeed_)
	{
		data_->acceleration_ = INCREASE;
	}
}

void PlayerInputComponent::deceleration()
{
	if (data_->speed_ > 0)
	{
		data_->acceleration_ = DECREASE;
	}
}

void PlayerInputComponent::rotationLeft()
{
	data_->angle_ = -data_->rotationSpeed_ * data_->dir_;
}

void PlayerInputComponent::rotationRight()
{
	if (!data_->onGround_)
	{
		data_->angle_ = data_->rotationSpeed_ * data_->dir_;
	}
}

void PlayerInputComponent::fire()
{
	if (data_->shotTimer_.getElapsedTime().asSeconds() >= data_->shotRate_ &&
		data_->hitpoints_ > 0)
	{
		data_->isShoot = true;
		data_->shotTimer_.restart();
	}
	else
	{
		data_->isShoot = false;
	}
}

void PlayerInputComponent::update(GameObject& player)
{
	if (data_->hitpoints_>0)
	{
		if (KP(sf::Keyboard::Space))
		{
			fire();
		}
		if (KP(sf::Keyboard::W))
		{
			acceleration();
		}
		if (KP(sf::Keyboard::S))
		{
			deceleration();
		}
		if (KP(sf::Keyboard::A))
		{
			rotationLeft();
		}
		if (KP(sf::Keyboard::D))
		{
			rotationRight();
		}
	}
}

PlayerInputComponent::~PlayerInputComponent()
{
}
