#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "globals.h"


class Platform : public GameObject
{

public:
	Platform(sf::Vector2f position, sf::Vector2f size);
	void PlatformInit(b2World& world);
	void Draw(sf::RenderWindow& window);
private:


	b2Body* platformBody_ = nullptr;
	sf::RectangleShape rectShape_;
	sf::Vector2f position_;
	sf::Vector2f size_;
	
};