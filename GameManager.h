#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
class GameManager
{
public:
	GameManager();
	
	sf::Time GetDeltaTime(sf::Time deltaTime);
	~GameManager();
};

