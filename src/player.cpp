#include "player.h"
#include "globals.h"
#include <iostream>


PlayerCharacter::PlayerCharacter()
{
	if (!playerTexture_.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\risitas.png"))
	{
		std::cout << "J'ai du mal ecrire le fichier";
	}
	playerSprite_.setTexture(playerTexture_);

}

void PlayerCharacter::InitPlayer(b2World& world)
{
	const auto playerSize = sf::Vector2f(playerSprite_.getLocalBounds().width, playerSprite_.getLocalBounds().height);
	playerSprite_.setOrigin(playerSize / 2.0f);
	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(playerPosition_);
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	playerBody_ = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(boxSize.x) / 2.0f, pixel2meter(boxSize.y) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f;
	//fixtureDef.userData = this;

	playerBody_->CreateFixture(&fixtureDef);
}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{
	playerPosition_ = meter2pixel(playerBody_->GetPosition());
	playerSprite_.setPosition(playerPosition_);
	window.draw(playerSprite_);
}
