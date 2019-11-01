#include "platforms.h"
#include "globals.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size) : position_(position), size_(size)
{
	gameObjectType_ = GameObjectType::PLATFORM;
}



void Platform::PlatformInit(b2World& world)
{
	rectShape_.setPosition(position_);
	rectShape_.setSize(size_);
	rectShape_.setOrigin(size_ / 2.0f);
	rectShape_.setFillColor(sf::Color::Blue);


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
	window.draw(rectShape_);
}
