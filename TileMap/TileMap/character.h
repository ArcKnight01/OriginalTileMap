#pragma once
#include <SFML/Graphics.hpp>
// Include Needed for Animations
#include <SFML/Graphics/Rect.hpp>
// Include Needed for Text
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Tile.h"
class Character {
public: 
	//reference board
	Board* boardref;
	//character shape (circle)
	sf::CircleShape characterShape;
	//position of character (tile)
	int tilePosition;
	int prevTilePosition;
	//position of character (coordinates)
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	//start & end position (get from board)
	int startPosition, endPosition;
	float height, width;

	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;

	Character(Board& bref, int spawnPos);
	void update();
	void drawCharacter(sf::RenderWindow& window);
	void move();
	void updateNavigation();
	void getTile();

};
