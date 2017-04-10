#pragma once
#include <SFML\Graphics.hpp>
#include <stack>

#define TIME_FACTOR 50
#define MS_PER_UPDATE 0.016f

class GameState;

class Game
{
public:
	Game();
	~Game();

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);

	GameState* peekState();

	void gameLoop();

private:
	std::stack<GameState*> states_;

	sf::RenderWindow window_;
	sf::Event event_;

	sf::View view_;
	sf::Vector2f mouse_;

	sf::Clock clock_;
	float elapsed_;
	float lag_;
};

