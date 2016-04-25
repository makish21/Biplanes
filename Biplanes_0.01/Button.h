#include <SFML\Graphics.hpp>

#pragma once
class Button
{
public:
	Button(sf::Font&, const sf::String, unsigned int Character_Size);
	~Button();
	
	sf::IntRect getRect();
	bool isSelected();

	bool isSelected_;
	void setPosition(float X, float Y);
	void update();
	void draw(sf::RenderWindow& window);
private:
	float x_, y_, w_, h_;
	sf::String string_;
	sf::Text text_;
	sf::RectangleShape rectangle_;
};

