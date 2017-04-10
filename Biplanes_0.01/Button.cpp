#include "Button.h"


Button::Button(sf::Font& Font, const sf::String String, unsigned int Caracter_Size)
{
	text_.setFont(Font);
	text_.setString(String);
}

sf::IntRect Button::getRect()
{
	return sf::IntRect(rectangle_.getGlobalBounds().left,
					   rectangle_.getGlobalBounds().top,
					   rectangle_.getGlobalBounds().width,
					   rectangle_.getGlobalBounds().height);
}

void Button::setPosition(float X, float Y)
{
	x_ = X;
	y_ = Y;
}

void Button::update()
{
	text_.setFillColor(sf::Color::White);
	text_.setCharacterSize(19);
	text_.setOrigin(text_.getGlobalBounds().width / 2,
					text_.getGlobalBounds().height);
	text_.setPosition(x_, y_);


	rectangle_.setFillColor(sf::Color(0, 99, 99));
	rectangle_.setOutlineThickness(0);
	rectangle_.setSize(sf::Vector2f(text_.getGlobalBounds().width + 20,
		text_.getGlobalBounds().height + 10));
	rectangle_.setOrigin(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2);
	rectangle_.setPosition(x_, y_);

	if (isSelected_)
	{
		text_.setFillColor(sf::Color(6, 45, 110));
		rectangle_.setFillColor(sf::Color(0, 153, 153));
		rectangle_.setOutlineThickness(1);
		rectangle_.setOutlineColor(sf::Color(0, 191, 50));
	}
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(rectangle_);
	window.draw(text_);
}

Button::~Button()
{
}
