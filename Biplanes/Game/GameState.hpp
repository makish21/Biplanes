#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"

class GameState
{
public:
	Game* game;

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(const float& elapsed) = 0;
	virtual void handleInput(const sf::Event& event) = 0;
};