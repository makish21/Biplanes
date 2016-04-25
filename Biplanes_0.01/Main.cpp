#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>

#include "PlayerDataComponent.h"

#include "GameObject.h"
#include "EmptyInputComponent.h"
#include "PlayerDataComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerGraphicsComponent.h"
#include "CloudDataComponent.h"
#include "CloudPhysicsComponent.h"
#include "CloudGraphicsComponent.h"
#include "menu.h"

#define INITIAL_WINDOW_WIDTH 533
#define INITIAL_WINDOW_HEIGHT 300

float windowHeight = static_cast<float>(GetSystemMetrics(SM_CYFULLSCREEN) - 50);
float windowWidth = windowHeight / INITIAL_WINDOW_HEIGHT * INITIAL_WINDOW_WIDTH;

float windowPositionX = (GetSystemMetrics(SM_CXFULLSCREEN) - windowWidth) / 2;
float windowPositionY = (GetSystemMetrics(SM_CYFULLSCREEN) - windowHeight) / 2;

void main()
{
	bool isFullscreen = false;

	sf::View view;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Biplanes");
	window.setPosition(sf::Vector2i(windowPositionX, windowPositionY));
	window.setView(sf::View(sf::FloatRect(0, 0, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT)));

	sf::Image Icon;
	Icon.loadFromFile("icon.png");
	window.setIcon(23, 23, Icon.getPixelsPtr());

	sf::Image TileSetImage;
	TileSetImage.loadFromFile("tileset.png");
	TileSetImage.createMaskFromColor(sf::Color(0, 203, 247));

	sf::Texture PolygonImage;
	PolygonImage.loadFromFile("polygon.png");

	sf::Sprite Polygon;
	Polygon.setTexture(PolygonImage);

	sf::Font GameText;
	GameText.loadFromFile("Bitmap Regular.ttf");
	
	std::list<GameObject*> Objects;
	std::list<GameObject*>::iterator ObjectNo;

	Menu mainMenu;
	mainMenu.addItem("PLAY");
	mainMenu.addItem("FULLSCREEN");
	mainMenu.addItem("EXIT");
	mainMenu.setFont("Bitmap Regular.ttf");

	PlayerDataComponent* pServerData = new PlayerDataComponent(PlayerDataComponent::Blue, 10, 269, 13, 13);

	GameObject* playerServer = new GameObject(TileSetImage, 10, 269, 23, 16,
											  pServerData,
											  new PlayerInputComponent(pServerData),
											  new PlayerPhysicsComponent(pServerData),
											  new PlayerGraphicsComponent(pServerData));
	
	playerServer->setLayer(5);
	playerServer->setTextureRect(0, 0, 23, 16);

	CloudDataComponent* CData = new CloudDataComponent(rand() % 5);

	sf::Clock clock;

	sf::Clock cloudSpawnTime;

	enum GameState
	{
		mainMenuOpened,
		gamePlayed
	} GameStatus;

	GameStatus = mainMenuOpened;

	double elapsed;

	while (window.isOpen())
	{
		elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();

		elapsed = elapsed * 100;

		switch (GameStatus)
		{
			//------------------------MAIN_MENU---------------------------------------------------------------------
			case mainMenuOpened:

			sf::Event mainMenuEvent;

			mainMenu.setCharacterSize(19);
			mainMenu.KeyboardControl(window);
			mainMenu.MouseControl(window);
			mainMenu.update(window);


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
				(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mainMenu.itemIsSelected))
			{
				switch (mainMenu.getSelectedItemIndex())
				{
					case 0:
					GameStatus = gamePlayed;
					break;
					case 1:
					if (!isFullscreen)
					{
						window.create(sf::VideoMode(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT), "Biplanes", sf::Style::Fullscreen);
						window.setView(sf::View(sf::FloatRect(0, 0, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT)));
						isFullscreen = true;
					}
					else
					{
						window.create(sf::VideoMode(windowWidth, windowHeight), "Biplanes", sf::Style::Default);
						window.setPosition(sf::Vector2i(windowPositionX, windowPositionY));
						window.setView(sf::View(sf::FloatRect(0, 0, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT)));
						isFullscreen = false;
					}
					break;
					case 2:
					window.close();
					break;
				}
			}
			window.clear(sf::Color(127, 199, 255));
			window.draw(Polygon);
			mainMenu.draw(window);
			window.display();
			break;

			//---------------------------GAME-------------------------------------------
			case gamePlayed:


			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				pServerData->hitpoints_ = 1;
			}

			

			if (cloudSpawnTime.getElapsedTime().asSeconds() >= 4)
			{
				Objects.push_back(GameObject::createCloud(TileSetImage, INITIAL_WINDOW_WIDTH, rand() % 180, 75, 38, rand() % 5));
				cloudSpawnTime.restart();
			}

			for (ObjectNo = Objects.begin(); ObjectNo != Objects.end();)
			{
				GameObject* del = *ObjectNo;
				del->update(window, elapsed);
				if (!del->isAlive())
				{
					ObjectNo = Objects.erase(ObjectNo); delete del;
				}
				else ObjectNo++;
			}
			
			playerServer->update(window, elapsed);

			window.draw(Polygon);

			for (int i = 1; i <= 5; i++)
			{
				for (ObjectNo = Objects.begin(); ObjectNo != Objects.end(); ObjectNo++)
				{
					if ((*ObjectNo)->getLayerNumber() == i)
					{
						(*ObjectNo)->draw(window);
					}
				}
			}

			playerServer->draw(window);

			window.display();
			break;
		}
	}
}