#include "Bullet.h"



Bullet::Bullet()
{
	velocity = 900;
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setSize(sf::Vector2f(9, 54));
}

void Bullet::UpdateBullet(float deltaTime)
{
	if (friendly == true)
	{
		rect.move(sf::Vector2f(0, -velocity * deltaTime));
		sprite.setPosition(rect.getPosition());
	}

	if (friendly == false)
	{
		sprite.setRotation(180);
		rect.move(sf::Vector2f(0, velocity * deltaTime));
		sprite.setPosition(rect.getPosition());
	}
}

Bullet::~Bullet()
{
}
