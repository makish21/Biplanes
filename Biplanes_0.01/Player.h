#pragma once

#include <SFML\Graphics.hpp>
#include <list>
#include <iostream>

#include "entity.h"



#define INCREASE 0.01
#define DECREASE -0.01
#define GROUND_LEVEL 285
#define CONTROLLED_SPEED 0.70
#define REVIVE_TIME 3
#define PI 3.14159265
#define KP sf::Keyboard::isKeyPressed
#define K sf::Keyboard

class InputComponent;

class Player :
	public Entity
{
public:
	bool isShoot, isInvulnerability;

	enum Team
	{
		Blue = 1,
		Red = -1
	};

	Player();

	Player(sf::Image &image,
		   float X, float Y,
		   int W, int H, int Layer);

	void setDamage(unsigned int Damage);

	void setControl(K::Key Up,
					K::Key Down,
					K::Key Right,
					K::Key Left,
					K::Key Shoot);

	void acceleration();
	void deceleration();
	void rotationLeft();
	void rotationRight();
	void fire();

	void setSmokeSize(int W, int H);

	void setTeam(Player::Team dir);

	void addScore(int summand);
	void deductHitpoints(int subtrahend);

	int getHitpoints();
	int getDamage();
	int getScore();
	float getSpeed();
	Team getTeam();

	void update(sf::RenderWindow &window, float time);
	void draw(sf::RenderWindow &window);

	~Player();

private:
	unsigned int score_;

	int damage_, hitpoints_, dir_, startPositionX_, startPositionY_;

	float speed_, rotation_, angle_, acceleration_,
		gravity_, explosionFrame_, burningFrame_,
		maxSpeed_, rotationSpeed_, maxRotationSpeed_,
		shotRate_;

	bool onGround_;

	struct Smoke_
	{
		int w; int h;
		sf::Sprite sprite;
		float frame;
	};

	Smoke_ smoke_;

	Team team_;

	InputComponent* input_;

	std::list<Smoke_*> smokes_;
	std::list<Smoke_*>::iterator smokeNo_;

	sf::Clock shotTimer_, deathTimer_, invulnerabilityTimer_, smokeEmergenceTimer_;
	sf::Sprite burningSprite_;
	sf::Keyboard::Key up_, down_, right_, left_, shoot_;

	void explosion(float time);
	void burning(float time);
	void collision(sf::RenderWindow &window);
	void rotationComputing();
	void smokeUpdate(float time);
	void hitpointsCounter(float time);
	void control();
};

