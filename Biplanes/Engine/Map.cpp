#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

void Map::loadFromFile(const std::string & fliename)
{
	Object object1;
	object1.name = "Ground";
	object1.rect = sf::FloatRect(0.f, 285.f, 533.f, 15.f);
	object1.isCollidable = true;
	objects_.push_back(object1);

	Object object2;
	object2.name = "Hut";
	object2.rect = sf::FloatRect(243.f, 265.f, 32.f, 21.f);
	object2.isCollidable = true;
	objects_.push_back(object2);

	sortObjects();
}

std::list<Object>* Map::getCollidableObjects()
{
	return &collidableObjects_;
}

void Map::sortObjects()
{
	for (auto i = objects_.begin(); 
		 std::distance(objects_.begin(), i) <= numCollidableObjects_; )
	{
		numCollidableObjects_ = 0;

		if (i->isCollidable)
		{
			numCollidableObjects_++;
			collidableObjects_.push_back(*i);
		}
		else
		{
			objects_.splice(objects_.end(), objects_, i);
		}

		i++;
	}
}

void Map::activateObject(std::list<Object>::iterator it)
{
	objects_.splice(objects_.begin(), objects_, it);
	collidableObjects_.push_front(*it);
	numCollidableObjects_++;
}

void Map::deactivateObject(std::list<Object>::iterator it)
{
	objects_.splice(objects_.end(), objects_, it);
	collidableObjects_.erase(it);
	numCollidableObjects_--;
}

