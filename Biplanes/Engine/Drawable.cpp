#include "Drawable.h"

gm::Drawable::Drawable()
{
}

gm::Drawable::~Drawable()
{

}

void gm::Drawable::addSprite(sf::Sprite * sprite)
{
	sprites.push_back(sprite);
}

std::vector<sf::Sprite*> gm::Drawable::getSprites()
{
	return sprites;
}