#include "InputHandler.h"

InputHandler::InputHandler(sf::Keyboard::Key accelerate,
						   sf::Keyboard::Key decelerate,
						   sf::Keyboard::Key turnLeft,
						   sf::Keyboard::Key turnRight,
						   sf::Keyboard::Key fire) :
	accelerateKey_(accelerate),
	decelerateKey_(decelerate),
	leftKey_(turnLeft),
	rightKey_(turnRight),
	fireKey_(fire)
{
	accelerate_ = new AccelerateCommand;
	decelerate_ = new DecelerateCommand;
	left_ = new TurnLeftCommand;
	right_ = new TurnRightCommand;
	fire_ = new FireCommand;
}

InputHandler::~InputHandler()
{
	delete accelerate_;
	delete decelerate_;
	delete left_;
	delete right_;
	delete fire_;
}

std::list<Command*> InputHandler::handleInput(const sf::Event& event)
{
	std::list<Command*> commands;

	if (sf::Keyboard::isKeyPressed(accelerateKey_)) commands.push_back(accelerate_);
	else if (sf::Keyboard::isKeyPressed(decelerateKey_)) commands.push_back(decelerate_);

	if (sf::Keyboard::isKeyPressed(leftKey_)) commands.push_back(left_);
	else if (sf::Keyboard::isKeyPressed(rightKey_)) commands.push_back(right_);

	if (sf::Keyboard::isKeyPressed(fireKey_)) commands.push_back(fire_);

	return commands;
}