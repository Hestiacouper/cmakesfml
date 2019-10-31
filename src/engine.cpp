#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "platforms.h"
#include "player.h"
#include "SFML/Audio/SoundBuffer.hpp"

Engine::Engine()
{
	
}



void Engine::loop()
{

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound.wav"))
	{
		std::cout << "J'ai raté mon coup";
	}


	sf::RenderWindow window(sf::VideoMode(1000, 1000), "PLATFORMER");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(maxFramerate);
	window.setKeyRepeatEnabled(false);

	b2World world(b2Vec2(0.0f, 9.81f));

	std::vector<Platform> platforms = {
		{sf::Vector2f(400.0f, 550), sf::Vector2f(800,50) },
		{sf::Vector2f(50, 300), sf::Vector2f(50,600) },
		{sf::Vector2f(750, 300), sf::Vector2f(50,600) },
	};

	PlayerCharacter player = PlayerCharacter();

	player.InitPlayer(world);

	for (auto& platform : platforms)
	{
		platform.PlatformInit(world);
	}

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();	
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					player.PlayerJump(deltaTime.asSeconds());
				}
			}

		}

		player.PlayerMove(deltaTime.asSeconds());
		world.Step(deltaTime.asSeconds(), velocityIterations, positionIterations);
		window.clear(sf::Color::Black);

		for (auto& platform : platforms)
		{
			platform.Draw(window);
		}
		player.Draw(window);
		window.display();
	}
}