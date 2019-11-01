#include "platforms.h"
#include "globals.h"
#include <iostream>

Platform::Platform(sf::Vector2f position, sf::Vector2f size) : position_(position), size_(size)
{
	gameObjectType_ = GameObjectType::PLATFORM;
	if (!platformTexture_.loadFromFile("D:\\Development\\SAE\\919\\ExerciceC++\\SFMLBugPas\\cmakesfml\\data\\ground.png"))
	{
		std::cout << "Fucking plateform not loading again\n";
	}
	platformSprite_.setTexture(platformTexture_);
}


void Platform::PlatformInit(b2World& world)
{
	
	rectShape_.setPosition(position_);
	rectShape_.setSize(size_);
	rectShape_.setOrigin(size_ / 2.0f);
	rectShape_.setFillColor(brown());
	rectShape_.setOutlineColor(sf::Color::Green);
	rectShape_.setOutlineThickness(5.0f);


	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(position_);
	bodyDef.type = b2_staticBody;
	platformBody_ = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(size_.x / 2.0f), pixel2meter(size_.y / 2.0f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f;
	fixtureDef.userData = this;
	platformBody_->CreateFixture(&fixtureDef);
}

void Platform::Draw(sf::RenderWindow& window)
{
	
	platformSprite_.setPosition(meter2pixel(platformBody_->GetPosition()));
	window.draw(rectShape_);
}

sf::Color Platform::brown()
{
	return sf::Color(139, 69, 19);
}

