#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include "Map.h"

#define WORLD_WIDTH  533
#define WORLD_HEIGHT 300

class World
{
public:
	World();
	~World();

	void loadFromFile(const std::string& filename);

	Map* getMap();

	sf::Rect<int> terrain;

private:
	Map* map_;
};