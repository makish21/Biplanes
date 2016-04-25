#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

#include "Button.h"

class Menu
{
private:
	struct Button_
	{
		sf::Text text_;
		sf::RectangleShape rectangle_;
	};
	unsigned int selectedItemIndex_, characterSize_;
	sf::Font font_;
	std::vector<Button*> items_;
	std::vector<Button*>::iterator itemNo_;
	sf::Event event_;

	void MoveUp();
	void MoveDown();

public:
	bool itemIsSelected;

	Menu();
	~Menu();
	
	int getSelectedItemIndex();
	void addItem(const sf::String &string);
	void setCharacterSize(unsigned int size);
	void setFont(const std::string &filename);
	void draw(sf::RenderWindow &window);
	void MouseControl(sf::RenderWindow &window);
	void KeyboardControl(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
};

