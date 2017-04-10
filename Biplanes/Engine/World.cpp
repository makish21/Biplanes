#include "World.h"


World::World() :
	terrain(0,0, WORLD_WIDTH, WORLD_HEIGHT)
{
	map_ = new Map();
	loadFromFile("sadasd");
}


World::~World()
{
}

void World::loadFromFile(const std::string& filename)
{
	map_->loadFromFile(filename);
}

Map * World::getMap()
{
	return map_;
}
