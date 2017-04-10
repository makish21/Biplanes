#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(sf::Sprite * sprite, sf::Vector2f position) :
	Unit(sprite, position)
{
	hitpoints_ = STANDART_HITPOINTS;
	damage_ = STANDART_DAMAGE;
	score_ = 0;

	angle_ = 0;
	turnSpeed_ = 0;
	acceleration_ = 0;

	rect_ = sf::FloatRect(sprite->getTextureRect());
}

unsigned char Plane::getHitpoints()
{
	return hitpoints_;
}

void Plane::directionCalculation()
{
	rotation > 180 ? rotation -= 360 : rotation < -180 ? rotation += 360 : rotation;

	direction = sf::Vector2f(static_cast<float>(cos(rotation * PI / 180) * 1), 
							 static_cast<float>(sin(rotation * PI / 180) * 1));
}

void Plane::turnSpeedCalculation()
{
	turnSpeed_ < 0 ? turnSpeed_ = 0 : 
		turnSpeed_ = ((speed - CONTROLLED_SPEED) * (MAX_TURN_SPEED / (MAX_SPEED - CONTROLLED_SPEED)));
}

void Plane::speedCalculation(const float& elapsed)
{
	speed > MAX_SPEED ? speed = MAX_SPEED : 
		speed < 0 ? speed = 0 : 
		speed += acceleration_ * elapsed;
}

void Plane::positionCalculation(const float& elapsed)
{
	position.x += (direction.x * speed) * elapsed;
	position.y += (direction.y * speed - (speed - MAX_SPEED)) * elapsed;
}

bool Plane::isCollide(World & world)
{
	position.x < world.terrain.left ? position.x = static_cast<float>(world.terrain.width) :
		position.x > world.terrain.width ? position.x = static_cast<float>(world.terrain.left) :
		position.y < world.terrain.top ? acceleration_ = -5.f :
		position.y > world.terrain.height ? hitpoints_ = 0 : false;
	
	std::list<Object> objects = *world.getMap()->getCollidableObjects();

	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		if (rect_.intersects(i->rect))
		{
			hitpoints_ = 0;
		}
	}
	
	return false;
}

void Plane::update(const float& elapsed)
{
	turnSpeedCalculation();

	rotation += angle_ * elapsed;

	directionCalculation();
	speedCalculation(elapsed);

	positionCalculation(elapsed);

	angle_ = 0;
	acceleration_ = 0;
}

void Plane::draw(sf::RenderWindow & window)
{
	for (auto i = sprites.begin(); 
		 i != sprites.end(); 
		 i++)
	{
		rect_ = (*i)->getGlobalBounds();
		(*i)->setRotation(rotation);
		(*i)->setPosition(position);
		window.draw(**i);
	}
}
