#include "GameProcessState.h"

GameProcessState::GameProcessState(Game* game) :
	inputHanler_(sf::Keyboard::W,
				 sf::Keyboard::S,
				 sf::Keyboard::A,
				 sf::Keyboard::D,
				 sf::Keyboard::Space)
{
	tileSetImage_.loadFromFile("res/TileSet.png");
	tileSetImage_.createMaskFromColor(sf::Color(0, 203, 247));

	tileSetTexture_.loadFromImage(tileSetImage_);

	polygonTexture_.loadFromFile("res/polygon.png");

	polygonBackground_.setTexture(polygonTexture_);

	sf::Sprite planeSprite(tileSetTexture_, sf::IntRect(0, 0, 23, 16));
	planeSprite.setOrigin(11.5f, 8.f);

	Plane plane(new sf::Sprite(planeSprite), 
				sf::Vector2f(100.f, 150.f));

	controlledPlane_ = new Plane(plane);

	planes_.push_back(controlledPlane_);
}


GameProcessState::~GameProcessState()
{
}

void GameProcessState::handleInput(const sf::Event& event)
{
	std::list<Command*> commands = inputHanler_.handleInput(event);

	for (auto i = commands.begin(); i != commands.end(); i++)
	{
		(*i)->execute(*controlledPlane_);
	}
}

void GameProcessState::update(const float & elapsed)
{
	for (auto i = planes_.begin(); i != planes_.end();)
	{
		if ((*i)->getHitpoints() <= 0 || isEntityCollide(*i, world_))
		{
			i = planes_.erase(i);
		}
		else
		{
			updateEntity(*i, elapsed);

			i++;
		}
	}
}

void GameProcessState::draw(sf::RenderWindow &window)
{
	window.draw(polygonBackground_);

	for (auto i = planes_.begin(); i != planes_.end(); i++)
	{
		drawEntity(*i, window);
	}
}

void GameProcessState::updateEntity(gm::Transformable * tr, const float& elapsed)
{
	tr->update(elapsed);
}

void GameProcessState::drawEntity(gm::Drawable * dr, sf::RenderWindow & window)
{
	dr->draw(window);
}

bool GameProcessState::isEntityCollide(Unit * u, World & world)
{
	return u->isCollide(world);
}
