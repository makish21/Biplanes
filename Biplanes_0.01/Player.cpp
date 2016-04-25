#include "player.h"
#include "PlayerInputComponent.h"

Player::Player() : Entity()
{
}

Player::Player(sf::Image &image,
			   float X, float Y,
			   int W, int H, int Layer) : Entity(image, X, Y, W, H, Layer)
{
	type = Entity::Player;
	damage_ = 1; score_ = 0; speed_ = 0; angle_ = 0;
	rotation_ = 0; gravity_ = -0.1; hitpoints_ = 3;
	maxRotationSpeed_ = 1.2; maxSpeed_ = 1; shotRate_ = 1.2;
	isShoot = false; onGround_ = true;
	dx = 0; dy = 0;
	explosionFrame_ = 0;
	startPositionX_ = X; startPositionY_ = Y;

	sprite.setOrigin(w / 2, h / 2);

	smoke_.sprite.setTexture(texture);
}

void Player::setDamage(unsigned int Damage)
{
	damage_ = Damage;
}

void Player::setControl(K::Key Up,
						K::Key Down,
						K::Key Right,
						K::Key Left,
						K::Key Shoot)
{
	up_ = Up;
	down_ = Down;
	right_ = Right;
	left_ = Left;
	shoot_ = Shoot;
}

void Player::setSmokeSize(int W, int H)
{
	smoke_.w = W;
	smoke_.h = H;
}

void Player::setTeam(Player::Team Dir)
{
	team_ = Dir;
	dir_ = Dir;
}

int	 Player::getDamage()
{
	return damage_;
}

int  Player::getScore()
{
	return score_;
}

int  Player::getHitpoints()
{
	return hitpoints_;
}

Player::Team Player::getTeam()
{
	return team_;
}

float Player::getSpeed()
{
	return speed_;
}

void Player::addScore(int summand)
{
	score_ += summand;
}

void Player::deductHitpoints(int subtrahend)
{
	hitpoints_ -= subtrahend;
}

void Player::collision(sf::RenderWindow &window)
{
	if (x >= window.getView().getSize().x)
	{
		x -= window.getView().getSize().x + w;
	}
	if (x <= -w)
	{
		x += window.getView().getSize().x + w;
	}
	if (y <= 0 && speed_ >= 0)
	{
		acceleration_ = DECREASE;
	}
	if (y + h >= GROUND_LEVEL)
	{
		if (!onGround_)
		{
			hitpoints_ = 0;
			if (score_ > 0) score_--;
		}
		if (onGround_)
		{
			gravity_ = 0;
		}
	}
	if (y + 1 < GROUND_LEVEL - h) onGround_ = false;

	if (getRect().intersects(sf::FloatRect(243, 265, 32, 21)))
	{
		hitpoints_ = 0;
		if (score_ > 0) score_--;
	}
}

void Player::rotationComputing()
{
	if (rotation_ > 180)
	{
		rotation_ -= 360;
	}
	if (rotation_ < -180)
	{
		rotation_ += 360;
	}
	dx = cos(rotation_ * PI / 180) * dir_;
	dy = sin(rotation_ * PI / 180) * dir_;
}

void Player::hitpointsCounter(float time)
{
	switch (getHitpoints())
	{
		case 3:
		break;
		case 2:
		if (smokeEmergenceTimer_.getElapsedTime().asSeconds() >= 0.2)
		{
			smokes_.push_front(new Smoke_(smoke_));
			smokeEmergenceTimer_.restart();
		}
		break;
		case 1:
		Player::burning(time);
		if (smokeEmergenceTimer_.getElapsedTime().asSeconds() >= 0.1)
		{
			smokes_.push_front(new Smoke_(smoke_));
			smokeEmergenceTimer_.restart();
		}
		break;
		default:
		Player::explosion(time);
		break;
	}
}

void Player::acceleration()
{
	if (speed_ < maxSpeed_)
	{
		acceleration_ = INCREASE;
	}
}

void Player::deceleration()
{
	if (speed_ > 0)
	{
		acceleration_ = DECREASE;
	}
}

void Player::rotationLeft()
{
	angle_ = -rotationSpeed_ * dir_;
}

void Player::rotationRight()
{
	if (!onGround_)
	{
		angle_ = rotationSpeed_ * dir_;
	}
}

void Player::fire()
{
	if (shotTimer_.getElapsedTime().asSeconds() >= shotRate_ &&
		life == true)
	{
		isShoot = true;
		shotTimer_.restart();
	}
	else
	{
		isShoot = false;
	}
}

void Player::control()
{
	if (life)
	{
		if (KP(shoot_))
		{
			fire();
		}
		if (KP(up_))
		{
			acceleration();
		}
		if (KP(down_))
		{
			deceleration();
		}
		if (KP(left_))
		{
			rotationLeft();
		}

		if (KP(right_))
		{
			rotationRight();
		}
	}
}

void Player::explosion(float time)
{
	if (explosionFrame_ <= 4)
	{
		explosionFrame_ += 0.06*time;
		sprite.setRotation(NULL);
		sprite.setTextureRect(sf::IntRect(40 * int(explosionFrame_), 20, 40, 36));
		sprite.setPosition(x, y - 3);
	}
}

void Player::burning(float time)
{
	burningSprite_.setTexture(texture);
	burningSprite_.setOrigin(10 / 2, 11 / 2);
	burningSprite_.setPosition(getCenterPosition().x, getCenterPosition().y - 2);
	burningSprite_.setScale(dir_, 1);
	burningFrame_ += 0.1 * time;
	burningSprite_.setRotation(rotation_);
	burningSprite_.setTextureRect(sf::IntRect(10 * int(burningFrame_), 140, 10, 11));
	burningSprite_.setColor(sf::Color::White);
	if (burningFrame_ >= 3)
	{
		burningFrame_ = 0;
	}
}

void Player::smokeUpdate(float time)
{
	for (smokeNo_ = smokes_.begin(); smokeNo_ != smokes_.end();)
	{
		Smoke_ *del = *smokeNo_;
		del->frame += 0.1 * time;
		del->sprite.setTextureRect(sf::IntRect(del->w * int(del->frame), 58, del->w, del->h));
		del->sprite.setOrigin(smoke_.w / 2, smoke_.h / 2);
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

void Player::update(sf::RenderWindow &window, float time)
{
	Player::hitpointsCounter(time);
	Player::smokeUpdate(time);
	if (life)
	{
		sprite.setColor(sf::Color::White);
		sprite.setPosition(getCenterPosition().x, getCenterPosition().y);
		angle_ = 0; acceleration_ = 0; explosionFrame_ = 0;

		//Player::control();
		//input_->update(*this);

		gravity_ = (speed_ - maxSpeed_);

		Player::rotationComputing();
		Player::collision(window);

		rotationSpeed_ = ((speed_ - CONTROLLED_SPEED) * (maxRotationSpeed_ / (maxSpeed_ - CONTROLLED_SPEED)));

		rotation_ += angle_ * time;
		speed_ += acceleration_ * time;

		y += (dy * speed_ - gravity_) * time;
		x += (dx * speed_) * time;

		sprite.setRotation(rotation_);
		sprite.setTextureRect(sf::IntRect(textureRect));

		smoke_.sprite.setPosition(getCenterPosition().x, getCenterPosition().y);

		if (rotationSpeed_ < 0) rotationSpeed_ = 0;
		if (hitpoints_ <= 0) life = false;
		if (speed_ < 0) speed_ = 0;
		if (speed_ > maxSpeed_) speed_ = maxSpeed_;
		if (invulnerabilityTimer_.getElapsedTime().asSeconds() < 3)
		{
			isInvulnerability = true;
			if (int(invulnerabilityTimer_.getElapsedTime().asSeconds() * 10) % 2 == 0)
			{
				sprite.setColor(sf::Color::Transparent);
			}
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
		burningSprite_.setColor(sf::Color::Transparent);
		invulnerabilityTimer_.restart();
		speed_ = 0; gravity_ = 0;
		if (deathTimer_.getElapsedTime().asSeconds() >= REVIVE_TIME)
		{
			isInvulnerability = true;
			life = true;
			hitpoints_ = 3;
			x = startPositionX_; y = startPositionY_; rotation_ = 0;
			angle_ = 0; acceleration_ = 0; explosionFrame_ = 0;
			onGround_ = true;
		}
	}
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
	window.draw(burningSprite_);
	for (smokeNo_ = smokes_.begin(); smokeNo_ != smokes_.end(); smokeNo_++)
	{
		window.draw((*smokeNo_)->sprite);
	}
}

Player::~Player()
{
}