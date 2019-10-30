#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "platforms.h"

Engine::Engine()
{
	
}

void Engine::loop()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Je hais sfml");

	b2World world(b2Vec2(0.0f, 9.81f));
	
	std::vector<Platform> platforms = {
		{sf::Vector2f(400.0f, 550), sf::Vector2f(800,50) },
		{sf::Vector2f(50, 300), sf::Vector2f(50,600) },
		{sf::Vector2f(750, 300), sf::Vector2f(50,600) },
	};

	for (auto& platform : platforms)
	{
		platform.PlatformInit(world);
	}
	while (window.isOpen())
	{
		//sf::Time deltaTime = clock.restart();
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

		}

		for (auto& platform : platforms)
		{
			platform.Draw(window);
		}
		// Update the window
		window.display();

	}
}
