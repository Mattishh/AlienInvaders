#include "Player.h"



Player::Player()
{
	movementSpeed = 700;
	rect.setPosition(sf::Vector2f(255, 875));
	rect.setSize(sf::Vector2f(112, 75));
	sprite.setPosition(255, 875);
}
void Player::UpdatePlayer(float deltaTime)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rect.getPosition().x > 0)
	{
		rect.move(sf::Vector2f(-movementSpeed * deltaTime, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rect.getPosition().x < 528)
	{
		rect.move(sf::Vector2f(movementSpeed * deltaTime, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rect.getPosition().y > 0)
	{
		rect.move(sf::Vector2f(0, -movementSpeed * deltaTime));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rect.getPosition().y < 890)
	{
		rect.move(sf::Vector2f(0, movementSpeed * deltaTime));
	}
	sprite.setPosition(rect.getPosition());
}


Player::~Player()
{
}
