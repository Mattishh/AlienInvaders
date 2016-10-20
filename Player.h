#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
	bool isKilled = false;
	int movementSpeed;
	Player();
	void UpdatePlayer(float deltaTime);
	~Player();
};



