#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"
#include <vector>
using namespace std;

int main()
{
	//Variables
	int windowX = 640;
	int windowY = 960;
	float bulletTimer = 0;
	float reloadTime = 0.50;
	float enemyTimer = 0;
	float enemySpawnRate = 2.2;
	float enemyReloadTime = 0.50;
	float enemyBulletTimer = 0;
	string stringLives;

	//Fonts & text
	sf::Font thin;
	sf::Font regular;
	if (!thin.loadFromFile("assets/kenvector_future_thin.ttf"))
	{
		std::cout << "Thin font loading error";
	}
	if (!regular.loadFromFile("assets/kenvector_future.ttf"))
	{
		std::cout << "Regular font loading error";
	}
	sf::Text Lives;
	sf::Text Score;
	sf::Text gameOver;
	Score.setCharacterSize(25);
	Lives.setCharacterSize(25);
	Lives.setFont(regular);
	Score.setFont(thin);
	gameOver.setFont(regular);
	Lives.setPosition(sf::Vector2f(90, 20));
	Score.setPosition(sf::Vector2f(400, 20));
	gameOver.setString("Game Over");
	gameOver.setCharacterSize(50);
	gameOver.setPosition(150, 500);

	//Sprites
	sf::Sprite background;
	background.setTextureRect(sf::IntRect(0, 0, windowX, windowY));

	//Textures
	sf::Texture uiX;
	sf::Texture uiLives;
	sf::Texture enemyTexture;
	sf::Texture playerBulletTexture;
	sf::Texture enemyBulletTexture;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	backgroundTexture.setRepeated(true);

	if (!uiX.loadFromFile("assets/numeralX.png"))
	{
		std::cout << "Error loading numeralX from file" << std::endl;
	}
	if (!uiLives.loadFromFile("assets/player_life.png"))
	{
		std::cout << "Error loading player_life from file" << std::endl;
	}
	if (!backgroundTexture.loadFromFile("assets/background.png"))
	{
		std::cout << "Error loading background from file" << std::endl;
	}
	background.setTexture(backgroundTexture);
	if (!playerTexture.loadFromFile("assets/player.png"))
	{
		std::cout << "Error loading player from file" << std::endl;
	}
	if (!enemyTexture.loadFromFile("assets/enemy.png"))
	{
		std::cout << "Error loading enemy from file" << std::endl;
	}
	if (!playerBulletTexture.loadFromFile("assets/bullet_player.png"))
	{
		std::cout << "Error loading player bullet from file" << std::endl;
	}
	if (!enemyBulletTexture.loadFromFile("assets/bullet_enemy.png"))
	{
		std::cout << "Error loading enemy bullet from file" << std::endl;
	}

	//Vectors
	vector<Enemy>::const_iterator enemyIterate;
	vector<Enemy> enemyVector;
	vector<Bullet> bulletVector;

	//Objects
	Player player;
	player.sprite.setTexture(playerTexture);
	Bullet bullet;
	bullet.sprite.setTexture(playerBulletTexture);
	Enemy enemy;
	enemy.sprite.setTexture(enemyTexture);
	UI ui;
	ui.uiLives.setTexture(uiLives);
	ui.uiX.setTexture(uiX);
	ui.uiLives.setPosition(sf::Vector2f(25, 25));
	ui.uiX.setPosition(sf::Vector2f(65, 30));

	//Stuff
	sf::Clock clock;
	sf::Time time;
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Alien Invaders");

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (ui.playerLives <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			player.isKilled = false;
			bulletVector.clear();
			enemyVector.clear();
			player.rect.setPosition(sf::Vector2f(255, 875));
			ui.playerLives = 10;
			ui.score = 0;
		}

		//Player movement
		player.UpdatePlayer(time.asSeconds());

		//Enemy spawning and spawn timer management
		enemyTimer += time.asSeconds();
		if (enemyTimer >= enemySpawnRate)
		{
			enemy.rect.setPosition(rand() % 549, 0);
			enemyVector.push_back(enemy);
			enemyTimer = 0;
		}


		//Player bullet shooting and reload timer management
		bulletTimer += time.asSeconds();
		if (bulletTimer >= reloadTime && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ui.playerLives > 0)
		{
			bullet.sprite.setTexture(playerBulletTexture);
			bullet.friendly = true;
			bullet.rect.setPosition(player.rect.getPosition().x + 51, player.rect.getPosition().y);
			bulletVector.push_back(bullet);
			bulletTimer = 0;
		}
		
		//Start drawing and managing bullets and enemies
		window.clear();
		window.draw(background);

		for (int i = bulletVector.size() - 1; i >= 0; i--)
		{
			if (bulletVector[i].rect.getPosition().y > 960 + 100)
			{
				bulletVector.erase(bulletVector.begin() + i);
			}
			else if (bulletVector[i].rect.getPosition().y < 0 - 100)
			{
				bulletVector.erase(bulletVector.begin() + i);
			}
			else
			{
				bulletVector[i].UpdateBullet(time.asSeconds());
				window.draw(bulletVector[i].sprite);
			}
		}

		enemyBulletTimer += time.asSeconds();
		for (int i = enemyVector.size() - 1; i >= 0; i--)
		{
			if (enemyVector[i].rect.getPosition().y > 960 + 100)  
			{
				enemyVector.erase(enemyVector.begin() + i);
			}
			else if (enemyVector[i].rect.getPosition().y < 0 - 100)
			{
				enemyVector.erase(enemyVector.begin() + i);
			}
			else if (enemyVector[i].isKilled == true)
			{
				enemyVector.erase(enemyVector.begin() + i);
			}
			else
			{
				if (enemyBulletTimer >= enemyReloadTime)
				{
					bullet.sprite.setTexture(enemyBulletTexture);
					bullet.friendly = false;
					bullet.rect.setPosition(enemyVector[i].rect.getPosition().x + 45, enemyVector[i].rect.getPosition().y + 91);
					bulletVector.push_back(bullet);
					enemyBulletTimer = 0;
				}
				enemyVector[i].UpdateEnemy(time.asSeconds());
				window.draw(enemyVector[i].sprite);
			}

		}

		//Collisions
		for (int i = bulletVector.size() - 1; i >= 0; i--)
		{
			if (bulletVector[i].friendly == true)
			{
				for (int y = enemyVector.size() - 1; y >= 0; y--)
				{
					if (enemyVector[y].rect.getGlobalBounds().intersects(bulletVector[i].rect.getGlobalBounds()))
					{
						bulletVector[i].isKilled = true;
						enemyVector[y].isKilled = true;
					}
				}
			}
			if (bulletVector[i].friendly == false)
			{
				if (bulletVector[i].rect.getGlobalBounds().intersects(player.rect.getGlobalBounds()))
				{
					if (ui.playerLives > 0)
					{
						bulletVector[i].isKilled = true;
						player.isKilled = true;
					}
				}
			}
		}

		for (int i = enemyVector.size() - 1; i >= 0; i--)
		{
			if (enemyVector[i].rect.getGlobalBounds().intersects(player.rect.getGlobalBounds()))
			{
				if (ui.playerLives > 0)
				{
					player.isKilled = true;
					enemyVector[i].isKilled = true;
				}
			}
		}

		//Kill enemies
		for (int i = enemyVector.size() - 1; i >= 0; i--)
		{
			if (enemyVector[i].isKilled == true)
			{
				ui.score += 10;
				enemyVector.erase(enemyVector.begin() + i);
			}
		}

		//Kill bullets
		for (int i = bulletVector.size() - 1; i >= 0; i--)
		{
			if (bulletVector[i].isKilled == true)
			{
				bulletVector.erase(bulletVector.begin() + i);
			}
		}

		//Damage player
		if (player.isKilled == true && ui.playerLives > 0)
		{
			ui.playerLives -= 1;
			player.isKilled = false;
		}

		Score.setString("Score: "+ to_string(ui.score));
		Lives.setString(to_string(ui.playerLives));
		if (ui.playerLives > 0)
		{
			window.draw(player.sprite);
		}
		if (ui.playerLives <= 0)
		{
			window.draw(gameOver);
		}
		window.draw(ui.uiX);
		window.draw(ui.uiLives);
		window.draw(Lives);
		window.draw(Score);
		window.display();
		time = clock.restart();
	}
	return 0;
}
