#include "PlayerPhysicsComponent.h"
#include <iostream>

PlayerPhysicsComponent::PlayerPhysicsComponent(PlayerDataComponent* data) : data_(data)
{
}

void PlayerPhysicsComponent::rotationComputing(GameObject& player)
{
	if (data_->rotation_ > 180)
	{
		data_->rotation_ -= 360;
	}
	if (data_->rotation_ < -180)
	{
		data_->rotation_ += 360;
	}
	player.dx_ = cos(data_->rotation_ * PI / 180) * data_->dir_;
	player.dy_ = sin(data_->rotation_ * PI / 180) * data_->dir_;
}

void PlayerPhysicsComponent::collision(GameObject& player, sf::RenderWindow& window)
{
	if (player.x_ >= window.getView().getSize().x)
	{
		player.x_ -= window.getView().getSize().x + player.w_;
	}
	if (player.x_ <= -player.w_)
	{
		player.x_ += window.getView().getSize().x + player.w_;
	}
	if (player.y_ <= 0 && data_->speed_ >= 0)
	{
		data_->acceleration_ = DECREASE;
	}
	if (player.getCenterPosition().y >= GROUND_LEVEL - player.h_ / 2)
	{
		if (!data_->onGround_)
		{
			data_->hitpoints_ = 0;
			if (data_->score_ > 0) data_->score_--;
		}
		if (data_->onGround_)
		{
			data_->gravity_ = 0;
		}
	}
	if (player.getCenterPosition().y < GROUND_LEVEL - player.h_ / 2) data_->onGround_ = false;

	if (player.getRect().intersects(sf::FloatRect(243, 265, 32, 21)))
	{
		data_->hitpoints_ = 0;
		if (data_->score_ > 0) data_->score_--;
	}
}

void PlayerPhysicsComponent::update(GameObject& player, float time, sf::RenderWindow& window)
{
	if (data_->hitpoints_ > 0)
	{
		data_->gravity_ = (data_->speed_ - 0.8);
		if (data_->gravity_ > 0) data_->gravity_ = 0;

		collision(player, window);
		rotationComputing(player);

		data_->rotationSpeed_ = ((data_->speed_ - CONTROLLED_SPEED) * (data_->maxRotationSpeed_ / (data_->maxSpeed_ - CONTROLLED_SPEED)));
	
		data_->rotation_ += data_->angle_ * time;
		data_->speed_ += data_->acceleration_ *  time;

		player.y_ += (player.dy_ * data_->speed_ - data_->gravity_) * time;
		player.x_ += (player.dx_ * data_->speed_) * time;

		
		if (data_->rotationSpeed_ < 0) data_->rotationSpeed_ = 0;
		if (data_->speed_ < 0) data_->speed_ = 0;
		if (data_->speed_ > data_->maxSpeed_) data_->speed_ = data_->maxSpeed_;
	}
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}
