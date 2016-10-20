#include "Enemy.h"
#include <random>
#include <stdlib.h>



Enemy::Enemy() 
{
	direction = true;
	movementSpeed = 400;
	rect.setSize(sf::Vector2f(91, 91));
	
}

void Enemy::UpdateEnemy(float deltaTime)
{
	if (direction == true)
	{
		rect.move(sf::Vector2f((-movementSpeed  * deltaTime) / 2, (movementSpeed * deltaTime) / 1.2f));
		if (rect.getPosition().x<0)
		{
			direction = false;
		}
	}
	if (direction == false)
	{
		rect.move(sf::Vector2f((movementSpeed  * deltaTime) / 2, (movementSpeed * deltaTime) / 1.2f));
		if (rect.getPosition().x>549)
		{
			direction = true;
		}
	}
	sprite.setPosition(rect.getPosition());
}

Enemy::~Enemy()
{
}
