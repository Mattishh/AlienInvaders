#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	bool isKilled = false;
	int velocity;
	bool friendly = true;
	void UpdateBullet(float deltaTime);
	Bullet();
	~Bullet();
};

