#pragma once

#include <SFML\Graphics.hpp>
#include "DataComponent.h"
#include <list>

#define INCREASE 0.01
#define DECREASE -0.01
#define GROUND_LEVEL 285
#define CONTROLLED_SPEED 0.8
#define REVIVE_TIME 3
#define PI 3.14159265
#define KP sf::Keyboard::isKeyPressed
#define K sf::Keyboard

class PlayerDataComponent :
	public DataComponent
{
	//friend class PlayerCollisionComponent;
	//friend class PlayerPhysicsComponent;
	//friend class PlayerGraphicsComponent;
	//friend class PlayerInputComponent;
public:
	bool isShoot, isInvulnerability;

	enum Team
	{
		Blue = 1,
		Red = -1
	};
	
	PlayerDataComponent(Team, int StartX, int StartY, int SmokeW, int SmokeH);

	void setDamage(unsigned int Damage);

	/*void setControl(K::Key Up,
					K::Key Down,
					K::Key Right,
					K::Key Left,
					K::Key Shoot);
					*/

	void setSmokeSize(int W, int H);

	void setStartPosition(int X, int Y);

	void setTeam(Team dir);

	void addScore(int summand);
	void deductHitpoints(int subtrahend);

	int getHitpoints();
	int getDamage();
	int getScore();
	float getSpeed();
	Team getTeam();

	virtual void update(GameObject&);

	~PlayerDataComponent();

//private:
	struct Smoke_
	{
		float w; float h;
		sf::Sprite sprite;
		float frame;
	};

	Smoke_ smoke_;

	unsigned int score_;

	int damage_, hitpoints_, dir_, startPositionX_, startPositionY_;

	float speed_, rotation_, angle_, acceleration_,
		gravity_, explosionFrame_, burningFrame_,
		maxSpeed_, rotationSpeed_, maxRotationSpeed_,
		shotRate_;

	bool onGround_;

	Team team_;

	sf::Clock shotTimer_, deathTimer_, invulnerabilityTimer_, smokeEmergenceTimer_;
	sf::Sprite burningSprite_;
	//sf::Keyboard::Key up_, down_, right_, left_, shoot_;

	void rotationComputing();
	void control();
};

