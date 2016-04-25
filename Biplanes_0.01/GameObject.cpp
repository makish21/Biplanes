#include "GameObject.h"

#include "DataComponent.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "EmptyInputComponent.h"
#include "PlayerDataComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerGraphicsComponent.h"
#include "CloudDataComponent.h"
#include "CloudPhysicsComponent.h"
#include "CloudGraphicsComponent.h"


/*Entity::Entity(sf::Image &image, float X, float Y, int W, int H, int Layer)
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
*/
GameObject::GameObject()
{
}

GameObject::GameObject(sf::Image &image, float X, float Y, int W, int H,
					   DataComponent* Data,
					   PhysicsComponent* Physics,
					   GraphicsComponent* Graphics)
					   : data_(Data),
					   physics_(Physics),
					   graphics_(Graphics)
{
	x_ = X; y_ = Y; w_ = W; h_ = H;
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);
	sprite_.setOrigin(w_ / 2, h_ / 2);
}

GameObject::GameObject(sf::Image &image, float X, float Y, int W, int H, 
					   DataComponent* Data,
					   InputComponent* Input,
					   PhysicsComponent* Physics,
					   GraphicsComponent* Graphics)
					   : data_(Data),
					   input_(Input),
					   physics_(Physics),
					   graphics_(Graphics)
{
	x_ = X; y_ = Y; w_ = W; h_ = H;
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);
	sprite_.setOrigin(w_ / 2, h_ / 2);
	life_ = true;
}

sf::String GameObject::getName()
{
	return name_;
}

GameObject::Type GameObject::getType()
{
	return type_;
}

int GameObject::getLayerNumber()
{
	return layer_;
}

bool GameObject::isAlive()
{
	return life_;
}

void GameObject::setImage(sf::Image& image)
{
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);
	sprite_.setOrigin(w_ / 2,
					  h_ / 2);
}

void GameObject::setName(sf::String Name)
{
	name_ = Name;
}

void GameObject::setType(GameObject::Type Type)
{
	type_ = Type;
}

void GameObject::setLayer(int layerNumber)
{
	layer_ = layerNumber;
}

void GameObject::setTextureRect(int X, int Y, int W, int H)
{
	textureRect_.left = X;
	textureRect_.top = Y;
	textureRect_.width = W;
	textureRect_.height = H;
}

void GameObject::setPosition(int X, int Y)
{
	x_ = X;
	y_ = Y;
}

void GameObject::setSize(int W, int H)
{
	w_ = W;
	h_ = H;
}

sf::Vector2f GameObject::getVectorSpeed()
{
	return sf::Vector2f(dx_, dy_);
}

sf::FloatRect GameObject::getRect()
{
	return sf::FloatRect(x_, y_, w_, h_);
}

sf::Vector2f GameObject::getPosition()
{
	return sf::Vector2f(x_, y_);
}

sf::Vector2f GameObject::getCenterPosition()
{
	return sf::Vector2f(x_ + w_ / 2, y_ + h_ / 2);
}

void GameObject::update(sf::RenderWindow& window, float time)
{
	data_->update(*this);
	input_->update(*this);
	physics_->update(*this, time, window);
	graphics_->update(*this, time);
}

void GameObject::draw(sf::RenderWindow& window)
{
	graphics_->draw(*this, window);
}

GameObject::~GameObject()
{
}


GameObject* GameObject::createCloud(sf::Image& image, float X, float Y, int W, int H, __int8 Distance)
{
	CloudDataComponent* data = new CloudDataComponent(Distance);
	return new GameObject(image, X, Y, W, H, 
						  data,
						  new EmptyInputComponent(),
						  new CloudPhysicsComponent(data),
						  new CloudGraphicsComponent(data));
	delete data;
}

GameObject* GameObject::createPlayer(sf::Image& image, float X, float Y, int W, int H, PlayerDataComponent* data)
{
	return new GameObject(image, X, Y, W, H,
						  data,
						  new PlayerInputComponent(data),
						  new PlayerPhysicsComponent(data),
						  new PlayerGraphicsComponent(data));
}