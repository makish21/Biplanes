#include "PlayerGraphicsComponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(PlayerDataComponent* data) : data_(data)
{
}

PlayerGraphicsComponent::~PlayerGraphicsComponent()
{
}

void PlayerGraphicsComponent::explosion(GameObject& player, float time)
{
	if (data_->explosionFrame_ <= 4)
	{
		data_->explosionFrame_ += static_cast<float>(0.06) *time;
		player.sprite_.setRotation(NULL);
		player.sprite_.setTextureRect(sf::IntRect(40 * int(data_->explosionFrame_), 20, 40, 36));
		player.sprite_.setPosition(player.x_, player.y_ - 3);
	}
}

void PlayerGraphicsComponent::burning(GameObject& player, float time)
{
	data_->burningSprite_.setTexture(player.texture_);
	data_->burningSprite_.setOrigin(10 / 2, 11 / 2);
	data_->burningSprite_.setPosition(player.getCenterPosition().x, player.getCenterPosition().y - 2);
	data_->burningSprite_.setScale(static_cast<float>(data_->dir_), 1);
	data_->burningFrame_ += (float)0.1 * time;
	data_->burningSprite_.setRotation(data_->rotation_);
	data_->burningSprite_.setTextureRect(sf::IntRect(10 * int(data_->burningFrame_), 140, 10, 11));
	data_->burningSprite_.setColor(sf::Color::White);
	if (data_->burningFrame_ >= 3)
	{
		data_->burningFrame_ = 0;
	}
}

void PlayerGraphicsComponent::hitpointsCounter(GameObject& player, float time)
{
	data_->smoke_.sprite.setTexture(player.texture_);
	switch (data_->hitpoints_)
	{
		case 3:
		break;

		case 2:
		if (data_->smokeEmergenceTimer_.getElapsedTime().asSeconds() >= 0.2)
		{
			smokes_.push_front(new PlayerDataComponent::Smoke_(data_->smoke_));
			data_->smokeEmergenceTimer_.restart();
		}
		break;

		case 1:
		burning(player, time);
		if (data_->smokeEmergenceTimer_.getElapsedTime().asSeconds() >= 0.1)
		{
			smokes_.push_front(new PlayerDataComponent::Smoke_(data_->smoke_));
			data_->smokeEmergenceTimer_.restart();
		}
		break;

		default:
		explosion(player, time);
		break;
	}
}

void PlayerGraphicsComponent::smokeUpdate(float time)
{
	for (smokeNo_ = smokes_.begin(); smokeNo_ != smokes_.end();)
	{
		PlayerDataComponent::Smoke_ *del = *smokeNo_;
		del->frame += 0.1 * time;
		del->sprite.setTextureRect(sf::IntRect(del->w * int(del->frame), 58, del->w, del->h));
		del->sprite.setOrigin(data_->smoke_.w / 2, data_->smoke_.h / 2);
		if (del->frame > 4)
		{
			smokeNo_ = smokes_.erase(smokeNo_); delete del;
		}
		else
		{
			smokeNo_++;
		}
	}
}

void PlayerGraphicsComponent::update(GameObject& player, float time)
{
	player.sprite_.setColor(sf::Color::White);
	hitpointsCounter(player, time);
	smokeUpdate(time);
	if (data_->hitpoints_ > 0)
	{
		player.sprite_.setOrigin(player.w_ / 2, player.h_ / 2);
		player.sprite_.setPosition(player.getCenterPosition().x, player.getCenterPosition().y);

		player.sprite_.setRotation(data_->rotation_);
		player.sprite_.setTextureRect(sf::IntRect(player.textureRect_));

		data_->smoke_.sprite.setPosition(player.getCenterPosition().x, player.getCenterPosition().y);

		if (data_->invulnerabilityTimer_.getElapsedTime().asSeconds() < 3)
		{
			if (int(data_->invulnerabilityTimer_.getElapsedTime().asSeconds() * 10) % 2 == 0)
			{
				player.sprite_.setColor(sf::Color::Transparent);
			}
		}
	}
	else
	{
		data_->burningSprite_.setColor(sf::Color::Transparent);
	}
}

void PlayerGraphicsComponent::draw(GameObject& player, sf::RenderWindow& window)
{
	window.draw(player.sprite_);
	window.draw(data_->burningSprite_);
	for (smokeNo_ = smokes_.begin(); smokeNo_ != smokes_.end(); smokeNo_++)
	{
		window.draw((*smokeNo_)->sprite);
	}
}