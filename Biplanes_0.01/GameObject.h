#pragma once
#include <SFML\Graphics.hpp>

class DataComponent;
class InputComponent;
class GraphicsComponent;
class PhysicsComponent;
class CollisionComponent;
class PlayerDataComponent;

class GameObject
{
	//friend class PlayerCollisionComponent;
	//friend class PlayerGraphicsComponent;
	//friend class PlayerPhysicsComponent;
	//friend class PlayerDataComponent;
public:
	
	virtual enum Type
	{
		VisualEntity,
		Player,
		Bullet
	};

	GameObject();
	GameObject(sf::Image&, float X, float Y, int W, int H,
			   DataComponent*, PhysicsComponent*, GraphicsComponent*);
	GameObject(sf::Image&, float X, float Y, int W, int H, 
			   DataComponent*, InputComponent*, PhysicsComponent*, GraphicsComponent*);


	sf::FloatRect getRect();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPosition();
	sf::Vector2f getSize();

	sf::String getName();
	sf::Vector2f getVectorSpeed();
	Type getType();
	int getLayerNumber();
	bool isAlive();
	
	void setImage(sf::Image&);
	void setName(sf::String Name);
	void setType(Type type);
	void setTextureRect(int X, int Y, int W, int H);
	void setPosition(int X, int Y);
	void setSize(int W, int H);
	void setLayer(int LayerNumber);

	void update(sf::RenderWindow &window, float time);
	void draw(sf::RenderWindow &window);
	
	~GameObject();

	static GameObject* createPlayer(sf::Image&, float X, float Y, int W, int H, PlayerDataComponent*);
	static GameObject* createCloud(sf::Image&, float X, float Y, int W, int H, __int8 Distance);

//protected:
	bool life_;
	int layer_;
	float dx_, dy_, x_, y_, w_, h_, currentFrame_;
	sf::Sprite			sprite_;
	sf::Texture			texture_;
	Type				type_;
	sf::FloatRect		rect_;
	sf::IntRect			textureRect_;
	sf::String			name_;

	DataComponent*		data_;
	InputComponent*		input_;
	GraphicsComponent*	graphics_;
	PhysicsComponent*	physics_;
};

