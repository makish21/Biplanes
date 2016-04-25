#pragma once

#include <SFML\Graphics.hpp>

class Entity
{
public:
	bool  life = true;

	virtual enum Type
	{
		Player,
		Bullet,
		VisualEntity,
	};

	Entity();
	Entity(sf::Image &image, float X, float Y, int W, int H, int Layer);
	Entity(sf::Sprite &sprite, float X, float Y, int W, int H);

	sf::FloatRect getRect();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPosition();

	sf::String getName();
	sf::Vector2f getVectorSpeed();
	Type getType();
	int getLayerNumber();

	void setName(sf::String Name);
	void setType(Type type);
	void setImage(sf::Image &image);
	void setTextureRect(int X, int Y, int W, int H);
	void setPosition(int X, int Y);
	void setSize(int W, int H);

	virtual void update(sf::RenderWindow &window, float time) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;

	void pause();
	void resume();

	~Entity();

protected:
	int layer;
	float dx, dy, x, y, w, h, currentFrame;
	Type			type;
	sf::FloatRect	rect;
	sf::IntRect		textureRect;
	sf::Sprite		sprite;
	sf::Texture		texture;
	sf::String		name;
};