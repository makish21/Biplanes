#pragma once
#include <SFML\Graphics.hpp>
#include <list>

#include "GameState.hpp"
#include "Engine\InputHandler.h"
#include "Engine\Commands.hpp"

#include "Engine\Plane.h"

class GameProcessState :
	public GameState
{
public:
	GameProcessState(Game* game);
	~GameProcessState();

	virtual void handleInput(const sf::Event& event);
	virtual void update(const float& elapsed);
	virtual void draw(sf::RenderWindow&);
private:
	sf::Image tileSetImage_;
	sf::Sprite polygonBackground_;

	sf::Texture tileSetTexture_;
	sf::Texture polygonTexture_;

	World world_;

	std::list<Plane*> planes_;

	Plane* controlledPlane_;
	InputHandler inputHanler_;

	void updateEntity(gm::Transformable*, const float& elapsed);
	void drawEntity(gm::Drawable*, sf::RenderWindow& window);
	bool isEntityCollide(Unit*, World& world);
};

