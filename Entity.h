#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Entity
{
public:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;
	Entity();
	~Entity();
};

