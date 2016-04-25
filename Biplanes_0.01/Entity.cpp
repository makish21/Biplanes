#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(sf::Image &image, float X, float Y, int W, int H, int Layer)
{
	x = X; y = Y; w = W; h = H; layer = Layer;
	currentFrame = 0;
	life = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

Entity::Entity(sf::Sprite &Sprite, float X, float Y, int W, int H)
{
	x = X; y = Y; w = W; h = H;
	sprite = Sprite;
	currentFrame = 0;
	life = true;
	sprite.setOrigin(w / 2, h / 2);
}

sf::String Entity::getName()
{
	return name;
}

Entity::Type Entity::getType()
{
	return type;
}

int Entity::getLayerNumber()
{
	return layer;
}

void Entity::setName(sf::String Name)
{
	name = Name;
}

void Entity::setType(Entity::Type Type)
{
	type = Type;
}

void Entity::setImage(sf::Image &image)
{
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

void Entity::setTextureRect(int X, int Y, int W, int H)
{
	textureRect.left = X;
	textureRect.top = Y;
	textureRect.width = W;
	textureRect.height = H;
}

void Entity::setPosition(int X, int Y)
{
	x = X;
	y = Y;
}

void Entity::setSize(int W, int H)
{
	w = W;
	h = H;
}

sf::Vector2f Entity::getVectorSpeed()
{
	return sf::Vector2f(dx, dy);
}

sf::FloatRect Entity::getRect()
{
	return sf::FloatRect(x, y, w, h);
}

sf::Vector2f Entity::getPosition()
{
	return sf::Vector2f(x, y);
}

sf::Vector2f Entity::getCenterPosition()
{
	return sf::Vector2f(x + w / 2, y + h / 2);
}

void Entity::pause()
{
	dx = 0; dy = 0;
}

Entity::~Entity()
{
}
