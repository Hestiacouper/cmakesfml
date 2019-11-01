#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


class Jesus
{
public:
	Jesus();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetJesusPos();
	sf::Sprite JesusSprite_;
private:
	const sf::Vector2f JesusSize = sf::Vector2f(30, 30);
	const sf::Vector2f JesusPosition = sf::Vector2f(150, 713.5f);
	sf::Texture JesusTexture_;
};