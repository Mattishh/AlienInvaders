#pragma once
#include <SFML/Graphics.hpp>
class UI
{
public:
	sf::Sprite uiLives;
	sf::Sprite uiX;
	int playerLives = 10;
	int score = 0;
	UI();
	~UI();
};

