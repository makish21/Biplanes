#pragma once
#include <SFML\Graphics.hpp>
#include "Unit.h"
#include "World.h"

#define PI 3.14159265

#define STANDART_THRUST 10
#define STANDART_WEIGHT 10
#define STANDART_HITPOINTS 99
#define STANDART_DAMAGE 33
#define MAX_SPEED 20
#define GRAVITATIONAL_ACCELERATION 9.80665f

#define CONTROLLED_SPEED 7
#define MAX_TURN_SPEED 12.f


class Plane : public Unit
{
	friend class AccelerateCommand;
	friend class DecelerateCommand;
	friend class TurnLeftCommand;
	friend class TurnRightCommand;
	friend class FireCommand;

public:
	Plane();
	Plane(sf::Sprite*, sf::Vector2f position);

	unsigned char getHitpoints();

private:
	unsigned char hitpoints_;
	unsigned char damage_;
	unsigned char score_;

	float angle_;
	float turnSpeed_;
	float acceleration_;

	//TODO
	sf::FloatRect rect_;

	virtual bool isCollide(World& world);
	virtual void update(const float& elapsed);
	virtual void draw(sf::RenderWindow& window);

	void directionCalculation();
	void turnSpeedCalculation();
	void speedCalculation(const float& elapsed);
	void positionCalculation(const float& elapsed);
};