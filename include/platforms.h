#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "globals.h"


class Platform
{

public:
	Platform(sf::Vector2f position, sf::Vector2f size);
	void PlatformInit(b2World& world);
	void Draw(sf::RenderWindow& window);
private:

	sf::RectangleShape rectShape_;
	sf::Vector2f size_;
	sf::Vector2f position_;
	b2Body* platformBody_ = nullptr;
	
};