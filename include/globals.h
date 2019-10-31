#pragma once

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

const float maxFramerate = 60.f; //Laptop isn't burning anymore

using meter = float;
using pixel = float;

const float pixelPerMeter = 100.0f;

const int velocityIterations = 8;
const int positionIterations = 8;

float pixel2meter(float pixel);
float meter2pixel(float meter);

b2Vec2 pixel2meter(sf::Vector2f pixels);
sf::Vector2f meter2pixel(b2Vec2 meters);


