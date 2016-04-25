#include "menu.h"
#include <iostream>

Menu::Menu()
{
}

void Menu::addItem(const sf::String &string)
{
	items_.push_back(new Button(font_, string, characterSize_));
}

void Menu::setFont(const std::string &filename)
{
	font_.loadFromFile(filename);
}

void Menu::setCharacterSize(unsigned int size)
{
	characterSize_ = size;
}

void Menu::MoveUp()
{
	if (selectedItemIndex_ > 0)
	{
		selectedItemIndex_--;
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex_ < items_.size()-1)
	{
		selectedItemIndex_++;
	}
}

void Menu::MouseControl(sf::RenderWindow &window)
{
	itemIsSelected = false;
	for (itemNo_ = items_.begin(); itemNo_ != items_.end(); itemNo_++)
	{
		if ((*itemNo_)->getRect().contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{ 
			itemIsSelected = true;
			selectedItemIndex_ = std::distance(items_.begin(), itemNo_);
		}
	}
}

void Menu::KeyboardControl(sf::RenderWindow &window)
{
	while (window.pollEvent(event_))
	{
		switch (event_.type)
		{
		case sf::Event::KeyPressed:
			window.setMouseCursorVisible(false);
			switch (event_.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;
			}
		break;
		case sf::Event::MouseMoved:
			window.setMouseCursorVisible(true);
		break;
		}
		if (event_.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

int Menu::getSelectedItemIndex()
{
	return selectedItemIndex_;
}

void Menu::draw(sf::RenderWindow &window)
{
	for (itemNo_ = items_.begin(); itemNo_ != items_.end(); itemNo_++)
	{
		(*itemNo_)->draw(window);
	}
}

void Menu::update(sf::RenderWindow &window)
{
	items_[selectedItemIndex_]->isSelected_ = true;
	for (itemNo_ = items_.begin(); itemNo_ != items_.end(); itemNo_++)
	{
		(*itemNo_)->setPosition(window.getView().getSize().x / 2,
								window.getView().getSize().y / (items_.size() + 1) * (std::distance(items_.begin(), itemNo_) + 1));
		(*itemNo_)->update();
		(*itemNo_)->isSelected_ = false;
	}
}

Menu::~Menu()
{
}
