#pragma once
#include <list>
#include <iterator>
#include <SFML\Graphics.hpp>

struct Object
{
	std::string name;
	sf::FloatRect rect;
	bool isCollidable;
};

class Map
{
public:
	Map();
	~Map();

	void loadFromFile(const std::string& fliename);

	std::list<Object>* getCollidableObjects();

private:
	std::list<Object> objects_;
	std::list<Object> collidableObjects_;
	unsigned int numCollidableObjects_;

	void sortObjects();
	void activateObject(std::list<Object>::iterator it);
	void deactivateObject(std::list<Object>::iterator it);
};

