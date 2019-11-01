#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "player.h"
#include "platforms.h"
#include "Jesus.h"

Engine::Engine() : platformListener_(this)
{
	
}

void Engine::Win(sf::RenderWindow& window)
{
	if (!font.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\arial.ttf"))
	{
		std::cout << "Wrong file path\n";
	}
	text.setFont(font);
	text.setString("You won");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(500, 500);
	window.draw(text);
}

void Engine::Lose(sf::RenderWindow& window)
{
	if (!font.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\arial.ttf"))
	{
		std::cout << "Wrong file path\n";
	}
	text.setFont(font);
	text.setString("You lost");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(500, 500);
	window.draw(text);
}

void Engine::Loop()
{
	
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "PLATFORMER");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(maxFramerate);
	window.setKeyRepeatEnabled(false);

	b2World world(b2Vec2(0.0f, 9.81f));
	world.SetContactListener(&platformListener_);

	Jesus jesus = Jesus();
	
	std::vector<Platform> platforms = {
		{sf::Vector2f(200.0f, 550), sf::Vector2f(800,50) },
		{sf::Vector2f(100, 200), sf::Vector2f(100,50) },
		{sf::Vector2f(750, 420), sf::Vector2f(200,50) },
		{sf::Vector2f(750,650), sf::Vector2f(300,50)},
		{sf::Vector2f(450,750),sf::Vector2f(700,50)},
	};

	//PlayerCharacter player = PlayerCharacter();
	playerCharacter_.InitPlayer(world);
	playerCharacter_.LoadSoundShit();
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
					playerCharacter_.PlayerJump(deltaTime.asSeconds());
				}
			}

		}

		playerCharacter_.PlayerMove(deltaTime.asSeconds());
		world.Step(deltaTime.asSeconds(), velocityIterations, positionIterations);
		window.clear(sf::Color::Black);

		for (auto& platform : platforms)
		{
			platform.Draw(window);
		}
		playerCharacter_.Draw(window);
		jesus.Draw(window);
		window.display();
		if(playerCharacter_.GetPlayerPosY()>1000)
		{
			Lose(window);
			window.display();
			std::cout << "You lost\n";
			system("pause");
			break;
		}
		if (playerCharacter_.playerSprite_.getGlobalBounds().intersects(jesus.JesusSprite_.getGlobalBounds()))
		{
			Win(window);
			window.display();
			std::cout << "You won\n";
			system("pause");
			break;
		}
	}
}

void Engine::OnContactEnter(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactBegin();
	}
}

void Engine::OnContactExit(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactEnd();
	}
}

PlatformContactListener::PlatformContactListener(Engine* engine) : engine_(engine)
{
}

void PlatformContactListener::BeginContact(b2Contact* contact)
{
	engine_->OnContactEnter(contact->GetFixtureA(), contact->GetFixtureB());
}

void PlatformContactListener::EndContact(b2Contact* contact)
{
	engine_->OnContactExit(contact->GetFixtureA(), contact->GetFixtureB());
}