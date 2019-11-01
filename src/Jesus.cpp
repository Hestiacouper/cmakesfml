#include "Jesus.h"
#include <iostream>


Jesus::Jesus()
{
	if (!JesusTexture_.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\Jesus.png"))
	{
		std::cout << "J'ai du mal ecrire le fichier";
	}
	JesusSprite_.setTexture(JesusTexture_);
}

void Jesus::Draw(sf::RenderWindow& window)
{
	JesusSprite_.setOrigin(JesusSize / 2.0f);
	JesusSprite_.setPosition(JesusPosition);
	window.draw(JesusSprite_);
}

sf::Vector2f Jesus::GetJesusPos()
{
	return JesusSprite_.getPosition();
}

