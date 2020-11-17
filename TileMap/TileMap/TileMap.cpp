// iD Tech Game Plan - SFML Template
// Include Needed for SFML
#include <SFML/Graphics.hpp>
// Include Needed for Animations
#include <SFML/Graphics/Rect.hpp>
// Include Needed for Text
#include <SFML/Graphics/Text.hpp>
#include "Tile.h"
#include "character.h"
#include "stdafx.h"
#include "TileMap.h"
using namespace sf;
/* DEFINE GAMESTATES HERE */

//constants here:
const float windowW = 1000;
const float windowH = 1000;
const int tilesPerRow = 20; 
const int tilesPerCol = 20;


//thus one tile H would equal the windowH, divided by tile s per row
//main code
int main()
{


	// Create a Window to Display Graphics, Define Size and Window Name
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Aidan's TileMap");


	/* CREATE OBJECTS AND ASSIGN OBJECT ATTRIBUTES HERE */
	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);
	
	/* CREATE OBJECTS AND ASSIGN OBJECT ATTRIBUTES HERE */
	GameBoard.importBoard(GameBoard.boardname);
	int initialPos;
	if (GameBoard.startExists) {
		initialPos = GameBoard.startPos;
	}
	else {
		initialPos = GameBoard.firstEmptyTile;
	}
	Character player(GameBoard, initialPos);
	/* DEFINE VARIABLES HERE */
	
	// Run the Program while the Window is Open
	while (window.isOpen())
	{
		window.clear();
		GameBoard.newClick = false;
		GameBoard.spacePressed = false;
		GameBoard.enterPressed = false;
		GameBoard.leftMousePos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		sf::Event event;
		while (window.pollEvent(event))
		{
			// When X Button Clicked, Close Window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Space) {
					if (GameBoard.newSpace == false) {
						GameBoard.spacePressed = true;
						GameBoard.newSpace = true;
					}
					if (GameBoard.spaceWasPressed == false) {
						GameBoard.spaceWasPressed = true;
					}
				}
				if (event.key.code == sf::Keyboard::E) {
					GameBoard.exportBoard(GameBoard.boardname);
					window.close();
				}
				if (event.key.code == sf::Keyboard::Enter) {
					if (GameBoard.newEnter == false) {
						GameBoard.enterPressed = true;
						GameBoard.newEnter = true;
					}
					if (GameBoard.enterWasPressed == false) {
						GameBoard.enterWasPressed = true;
					}
				}
				if (event.key.code == sf::Keyboard::W) {
					player.moveUp = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					player.moveLeft = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					player.moveDown = true;
				}
				if (event.key.code == sf::Keyboard::D) {
					player.moveRight = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					//GameBoard.spacePressed = false;
					GameBoard.newSpace = false;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					GameBoard.newEnter = false;
				}
				if (event.key.code == sf::Keyboard::W) {
					player.moveUp = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					player.moveLeft = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					player.moveDown = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					player.moveRight = false;
				}
			}
			
			/* DEFINE EVENTS (i.e. KEY PRESS & RELEASE) HERE */
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					//Register a new mouse click for piece selection functions
					GameBoard.newClick = true;
					GameBoard.conversionReset = true;
					if (GameBoard.hasClicked == false) {
						GameBoard.hasClicked = true;
					}
					//Find the tile that was clicked in
					GameBoard.clickPos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					// the position of mouse
				}
				if (event.key.code == sf::Mouse::Right) {
					//Register a new mouse click for piece selection functions
					//Register a new mouse click for piece selection functions
					GameBoard.newClick = true;
					GameBoard.conversionReset = true;
					if (GameBoard.hasClicked == false) {
						GameBoard.hasClicked = true;
					}
					//Find the tile that was clicked in
					GameBoard.clickPos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					// the position of mouse
					if (GameBoard.newSpace == false) {
						GameBoard.spacePressed = true;
						GameBoard.newSpace = true;
					}
					if (GameBoard.spaceWasPressed == false) {
						GameBoard.spaceWasPressed = true;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Right) {
					//Register a new mouse click for piece selection functions
					GameBoard.newSpace = false;
				}
			}
		}

		/* DEFINE ACTIONS (i.e. MOVEMENT) HERE */

		/* DRAW OBJECTS HERE */

		//first draw the checkers board:
		GameBoard.convertTile();
		GameBoard.drawBoard(window);
		player.update();
		player.drawCharacter(window);
		/* DRAW OBJECTS HERE */
		
		window.display();
	}
}