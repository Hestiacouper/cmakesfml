#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>
#include "globals.h"
#include <SFML/Audio.hpp>
#include <iostream>


class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter();
	void InitPlayer(b2World& world);
	void UpdatePlayer(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void PlayerMove(float dt);
	void PlayerJump(float dt);
	void OnContactBegin();
	void OnContactEnd();
	void LoadSoundShit();
	int GetPlayerPosX();
	int GetPlayerPosY();
	sf::Sprite playerSprite_;
private:
	b2Body* playerBody_ = nullptr;
	sf::Texture playerTexture_; 
	sf::RectangleShape boxRectDebug_;
	sf::Vector2f playerPosition_ = sf::Vector2f(400, 300);
	const sf::Vector2f boxSize = sf::Vector2f(26, 20);
	pixel playerSpeed_ = 200.0f;
	float movementFactor_ = 0.7f;
	float jump = -6.5f;
	int contactNmb_ = 0;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};
