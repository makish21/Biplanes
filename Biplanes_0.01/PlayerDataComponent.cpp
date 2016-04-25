#include "PlayerDataComponent.h"

PlayerDataComponent::PlayerDataComponent(PlayerDataComponent::Team team, int StartX, int StartY, int SmokeW, int SmokeH)
{
	team_ = team;
	dir_ = team;
	startPositionX_ = StartX; startPositionY_ = StartY;
	smoke_.w = SmokeW; smoke_.h = SmokeH;
	damage_ = 1; score_ = 0; speed_ = 0; angle_ = 0;
	rotation_ = 0; gravity_ = -0.1; hitpoints_ = 3;
	maxRotationSpeed_ = 1.2; maxSpeed_ = 1; shotRate_ = 1.2;
	isShoot = false; onGround_ = true;
	explosionFrame_ = 0;
}

PlayerDataComponent::~PlayerDataComponent()
{

}

void PlayerDataComponent::setSmokeSize(int W, int H)
{
	smoke_.w = W;
	smoke_.h = H;
}

void PlayerDataComponent::setDamage(unsigned int Damage)
{
	damage_ = Damage;
}

void PlayerDataComponent::setStartPosition(int X, int Y)
{
	startPositionX_ = X;
	startPositionY_ = Y;
}

void PlayerDataComponent::setTeam(PlayerDataComponent::Team Dir)
{
	team_ = Dir;
	dir_ = Dir;
}

int	 PlayerDataComponent::getDamage()
{
	return damage_;
}

int  PlayerDataComponent::getScore()
{
	return score_;
}

int PlayerDataComponent::getHitpoints()
{
	return hitpoints_;
}



PlayerDataComponent::Team PlayerDataComponent::getTeam()
{
	return team_;
}

float PlayerDataComponent::getSpeed()
{
	return speed_;
}

void PlayerDataComponent::addScore(int summand)
{
	score_ += summand;
}

void PlayerDataComponent::deductHitpoints(int subtrahend)
{
	hitpoints_ -= subtrahend;
}

void PlayerDataComponent::update(GameObject& player)
{	
	if (hitpoints_ > 0)
	{
		angle_ = 0; acceleration_ = 0; explosionFrame_ = 0;
		if (invulnerabilityTimer_.getElapsedTime().asSeconds() < 3)
		{
			isInvulnerability = true;
		}
		else
		{
			isInvulnerability = false;
		}
		deathTimer_.restart();
	}
	else
	{
		isShoot = false;
		invulnerabilityTimer_.restart();
		speed_ = 0; gravity_ = 0;
		if (deathTimer_.getElapsedTime().asSeconds() >= REVIVE_TIME)
		{
			isInvulnerability = true;
			hitpoints_ = 3;
			player.x_ = startPositionX_;
			player.y_ = startPositionY_;
			rotation_ = 0;
			angle_ = 0; acceleration_ = 0; explosionFrame_ = 0;
			onGround_ = true;
		}
	}
}