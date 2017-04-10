#include "Transformable.h"

gm::Transformable::Transformable() :
	position(0.f,0.f),
	rotation(0.f),
	speed(0.f),
	direction(sf::Vector2f(0, 0))
{
}

gm::Transformable::Transformable(const sf::Vector2f & Position) :
	position(Position),
	rotation(0.f),
	speed(0.f),
	direction(sf::Vector2f(0,0))
{
}

gm::Transformable::Transformable(const sf::Vector2f & Position, 
								 const float & Rotation, 
								 const float & Speed, 
								 const sf::Vector2f & Direction) :
	position(Position),
	rotation(Rotation),
	speed(Speed),
	direction(Direction)
{
}

gm::Transformable::~Transformable()
{
}

void gm::Transformable::setSpeed(const float & Speed)
{
	speed = Speed;
}

void gm::Transformable::setRotation(const float & Rotation)
{
	rotation = Rotation;
}

void gm::Transformable::setDirection(const sf::Vector2f Direction)
{
	direction = Direction;
}

float gm::Transformable::getSpeed()
{
	return speed;
}

float gm::Transformable::getRotation()
{
	return rotation;
}

sf::Vector2f gm::Transformable::getDirection()
{
	return direction;
}
