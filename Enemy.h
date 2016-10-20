#pragma once
#include "Entity.h"
#include"iostream"
class Enemy : public Entity
{
public:
	bool isKilled = false;
	int movementSpeed;
	bool direction;
	Enemy();
	void UpdateEnemy(float deltaTime);
	~Enemy();

};

