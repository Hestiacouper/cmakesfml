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


	boxRectDebug_.setSize(boxSize);
	boxRectDebug_.setOrigin(boxSize / 2.0f);
	boxRectDebug_.setFillColor(sf::Color(0, 255, 0, 120));
	boxRectDebug_.setOutlineColor(sf::Color::Green);
	boxRectDebug_.setOutlineThickness(2.0f);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(boxSize.x) / 2.0f, pixel2meter(boxSize.y) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f;

	playerBody_->CreateFixture(&fixtureDef);
}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{
	boxRectDebug_.setPosition(meter2pixel(playerBody_->GetPosition()));
	playerPosition_ = meter2pixel(playerBody_->GetPosition());
	playerSprite_.setPosition(playerPosition_);
	window.draw(playerSprite_);
	window.draw(boxRectDebug_);
}

void PlayerCharacter::PlayerMove()
{
	float yPos = playerBody_->GetPosition().y;
	//std::cout << "X before move : " << playerBody_->GetPosition().x << " Y before move : " << playerBody_->GetPosition().y << "\n";
	yPos += 0.5;
	playerBody_->SetTransform(b2Vec2(playerBody_->GetPosition().x, yPos), 0);
	//playerBody_->ApplyForce(b2Vec2(0, 1), playerBody_->GetWorldCenter(), true);
	//std::cout << "X after move : " << playerBody_->GetPosition().x << " Y after move : " << playerBody_->GetPosition().y << "\n";
}
