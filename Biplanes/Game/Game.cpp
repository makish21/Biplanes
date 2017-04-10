#include "Game.h"
#include "GameState.hpp"

#include <iostream>

Game::Game() :
	window_(sf::VideoMode(800, 480), "Biplanes", sf::Style::Default),
	view_(sf::FloatRect(0.f, 0.f, 533.f, 300)),
	lag_(0.f)
{
	window_.setView(view_);
}


Game::~Game()
{
}

void Game::pushState(GameState * state)
{
	states_.push(state);
}

void Game::popState()
{
	delete states_.top();
	states_.pop();
}

void Game::changeState(GameState * state)
{
	if (!states_.empty())
	{
		popState();
	}
	pushState(state);
}

GameState * Game::peekState()
{
	if (states_.empty())
	{
		return nullptr;
	}
	return states_.top();
}

void Game::gameLoop()
{
	while (window_.isOpen())
	{
		elapsed_ = clock_.getElapsedTime().asSeconds();
		clock_.restart();

		lag_ += elapsed_ * 10.f;

		mouse_ = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

		if (peekState() == nullptr)
		{
			continue;
		}

		while (window_.pollEvent(event_))
		{
			if (event_.type == sf::Event::Closed)
			{
				window_.close();
			}
		}

		while (lag_ >= MS_PER_UPDATE)
		{
			peekState()->handleInput(event_);
			peekState()->update(0.01f);//elapsed_ * 10.f);// * 50.f);
			lag_ -= MS_PER_UPDATE;
		}

		window_.clear(sf::Color::Black);
		window_.setView(view_);
		peekState()->draw(window_);
		window_.display();
	}
}
