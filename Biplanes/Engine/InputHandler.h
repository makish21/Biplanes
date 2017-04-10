#pragma once
#include <SFML\System.hpp>
#include <list>
#include "Commands.hpp"

class InputHandler
{
public:
	InputHandler(sf::Keyboard::Key accelerate, 
				 sf::Keyboard::Key decelerate,
				 sf::Keyboard::Key turnLeft,
				 sf::Keyboard::Key turnRight,
				 sf::Keyboard::Key fire);
	
	~InputHandler();

	std::list<Command*> handleInput(const sf::Event& event);

private:
	sf::Keyboard::Key accelerateKey_;
	sf::Keyboard::Key decelerateKey_;
	sf::Keyboard::Key leftKey_;
	sf::Keyboard::Key rightKey_;
	sf::Keyboard::Key fireKey_;

	Command* accelerate_;
	Command* decelerate_;
	Command* left_;
	Command* right_;
	Command* fire_;
};