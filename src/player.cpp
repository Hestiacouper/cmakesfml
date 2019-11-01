#include "player.h"
#include "globals.h"
#include <iostream>
#include <SFML/Audio.hpp>

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
	fixtureDef.userData = this;
	playerBody_->CreateFixture(&fixtureDef);
}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{
	playerPosition_ = meter2pixel(playerBody_->GetPosition());
	playerSprite_.setPosition(playerPosition_);
	window.draw(playerSprite_);
}

void PlayerCharacter::LoadSoundShit()
{
	
	if (!buffer.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\ISSOU.wav"))
	{
		std::cout << "J'ai raté mon coup";
	}
	sound.setBuffer(buffer);
}


void PlayerCharacter::PlayerMove(float dt)
{

	float move = 0.0f;
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move += 1.0f;
	}
	
	const float deltaVelX = move * pixel2meter(playerSpeed_) - playerBody_->GetLinearVelocity().x; //If the soustraction of playerbody current velocity is removed
	//player will be fast and keep mooving for a bit. Good to know for later
	const float forceX = movementFactor_ * playerBody_->GetMass() * deltaVelX / dt;

	
	//if deltaVelX is used instead of forceX will slide slowly. Good to know.
	playerBody_->ApplyForce(b2Vec2(forceX, playerBody_->GetPosition().y), playerBody_->GetWorldCenter(), true);
	
}

void PlayerCharacter::PlayerJump(float dt)
{
	const float deltaVelY = jump - playerBody_->GetLinearVelocity().y;
	const float forceY = playerBody_->GetMass() * deltaVelY / dt;
	if (contactNmb_ > 0)
	{
		sound.play();
		playerBody_->ApplyForce(b2Vec2(playerBody_->GetPosition().x, forceY), playerBody_->GetWorldCenter(), true);
	}
}

void PlayerCharacter::OnContactBegin()
{
	contactNmb_++;
}

void PlayerCharacter::OnContactEnd()
{
	contactNmb_--;
}

int PlayerCharacter::GetPlayerPosX()
{
	return playerSprite_.getPosition().x;
}

int PlayerCharacter::GetPlayerPosY()
{
	return playerSprite_.getPosition().y;
}
