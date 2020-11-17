#include "Tile.h"
#include "character.h"

Character::Character(Board& bref, int spawnPos) {
	boardref = &bref;
	startPosition = boardref->startPos;
	endPosition = boardref->endPos;
	tilePosition = spawnPos;
	prevTilePosition = 0;
	position = boardref->getTilePos(tilePosition);
	velocity = sf::Vector2f(0.f, 0.f);
	acceleration = sf::Vector2f(0.05f, 0.05f);
	characterShape.setFillColor(sf::Color::Blue);
	height = boardref->tileH, width = boardref->tileW;
	characterShape.setRadius(width * 0.5);
	characterShape.setOutlineColor(sf::Color::Red);
	//characterShape.set
	
}

void Character::update()
{
	getTile();
	move();
	
	
}

void Character::getTile()
{
	if (prevTilePosition != tilePosition) {
		prevTilePosition = tilePosition;
	}
	//tilePosition gets set to the tile index of the center of the character
	tilePosition = boardref->getTileN(position.x + width/2, position.y + height/2);

	//convert ground to checkpoint if on that tile:
	for (int i = 0; i < boardref->tileCount; i++) {
		if (boardref->tileTypes[i] != wall && boardref->tileTypes[i] != startnode && boardref->tileTypes[i] != endnode) {
			if (i == tilePosition && boardref->tileTypes[i] == ground) {
				boardref->tileTypes[i] = checkpoint;
				if (!boardref->playerTileExists) {
					boardref->playerTileExists = true;
				}
				if (boardref->playerTileExists) {
					boardref->playerTile = tilePosition;
				}
			}
			else if (i == prevTilePosition && boardref->tileTypes[i] == checkpoint) {
				boardref->tileTypes[i] = checkpoint;
			}
			else if((i != prevTilePosition || i != tilePosition) && boardref->tileTypes[i] == checkpoint){
				boardref->tileTypes[i] = ground;
			}
			
		}
	}

}
void Character::drawCharacter(sf::RenderWindow& window)
{
	characterShape.setPosition(position);
	window.draw(characterShape);
}

void Character::move()
{	
	if (moveUp && !moveDown) {
		velocity.y -= acceleration.y;
	}
	else if (moveDown && !moveUp) {
		velocity.y += acceleration.y;
	}
	else {
		if (velocity.y != 0.f) {
			if (velocity.y > 0.f) {
				if (velocity.y < 0.1f && !(moveDown || moveUp)) {
					velocity.y = 0.f;
				}
				else{
					velocity.y -= acceleration.y;
				}
				
			}
			else if (velocity.y < 0.f) {
				if (velocity.y > -0.1f && !(moveDown || moveUp)) {
					velocity.y = 0.f;
				}
				else { 
					velocity.y += acceleration.y; 
				}
			}
		}
	}

	if (moveLeft && !moveRight) {
		velocity.x -= acceleration.x;
	}
	else if (moveRight && !moveLeft) {
		velocity.x += acceleration.x;
	}
	else {
		if (velocity.x != 0.f) {
			if (velocity.x > 0.f) {
				if (velocity.x < 0.1f && !(moveLeft || moveRight)) {
					velocity.x = 0.f;
				}
				else {
					velocity.x -= acceleration.x;
				}
			}
			else if (velocity.x < 0.f) {
				if (velocity.x > -0.1f && !(moveDown || moveUp)) {
					velocity.x = 0.f;
				}
				else {
					velocity.x += acceleration.x;
				}
				velocity.x += acceleration.x;
			}
		}
	}
	

	if (!(position.y >= 0 && position.y <= (boardref->boardH - height))) {
		if (position.y <= 0) {
			if (velocity.y < 0.f) {
				position.y = 0;
				velocity.y = 0.f;
			}
		}
		else if (position.y >= (boardref->boardH - height)) {
			if (velocity.y > 0.f) {
				position.y = boardref->boardH - height;
				velocity.y = 0.f;
			}
		}
	}

	if (!(position.x >= 0 && (position.x <= boardref->boardW - width))) {
		if (position.x <= 0) {
			//can not move left but can move right, thus velocity = 0 if velocity < 0 (negative, meaning moving left)
			if (velocity.x < 0.f) {
				position.x = 0;
				velocity.x = 0.f;
			}
		}
		else if (position.x >= (boardref->boardW - width)) {
			if (velocity.x > 0.f) {
				position.x = boardref->boardW - width;
				velocity.x = 0.f;
			}
		}
	}
	//put update nav here:
	updateNavigation();

	if (velocity.x != 0.f || velocity.y != 0.f) {
		position += velocity;
	}
	
}

void Character::updateNavigation()
{
	//tile position is the current tile that the character is on
	//surrounded by 8 adjacent tiles:
	int NorthTile = tilePosition - boardref->tilesPerRow;
	int SouthTile = tilePosition + boardref->tilesPerRow;
	int EastTile = tilePosition + 1;
	int WestTile = tilePosition - 1;
	int NorthEastTile = NorthTile + 1;
	int NorthWestTile = NorthTile - 1;
	int SouthEastTile = SouthTile + 1;
	int SouthWestTile = SouthTile - 1;
	int adjTilesIndex[8] = {
	NorthTile,
	SouthTile,
	WestTile,
	EastTile,
	NorthEastTile,
	NorthWestTile,
	SouthEastTile,
	SouthWestTile
	};
	

/*
for (int i = 0; i < boardref->tileCount; i++) {

	}

*/
	
	//position:
	/*
	position.x = the left bound of character (west side)
	position.y = the top bound of character (north)
	position.x + width = the right bound of character (east)
	position.y + height = the bottom bound of character (south)
	*/
	//boardref->getTileN(position.x + width/2, position.y + height/2); //center of character
	//position = boardref->getTilePos(tilePosition); returns top left corner of the tile as the position
	/*
	//tileW, tileH, tileN >> gets index of tile, tilePos >> position of tile starting at 0,0
	//thus: for tile [0] @ (0,0): the tile's left bound is 0, top is 0, bottom is tileH, right is tileW
	//for tile @ (tilePosition.x , tilePosition.y) 
	*/
	//only run nav if on a ground tile or start/end tile but not wall:

	if (boardref->tileTypes[tilePosition] != wall) {
		for (int i = 0; i < 8; i++) {
			//adjTilesIndex[i] =>wall tile index
			int wallTileIndex = adjTilesIndex[i];
			sf::Vector2f wallTilePos = boardref->getTilePos(wallTileIndex);
			
			if (position.x <= (wallTilePos.x + boardref->tileW)) {
				//left bound of player is less than or equal to the right bound of wall
				if ((wallTileIndex == boardref->getTileN(position.x, position.y + height/2)) && boardref->tileTypes[wallTileIndex] == wall) {
					//if tile is a wall and the index of the tile is the same as the index of the tile that the left bound intersects
					//can not move left but can move right, thus velocity = 0 if velocity < 0 (negative, meaning moving left)
					if (velocity.x < 0.f) {
						//position.x = wallTilePos.x + boardref->tileW;
						velocity.x = 0.f;
					}
					else if (velocity.x == 0.f) {
						if ((wallTileIndex == boardref->getTileN(position.x, position.y + height)) || (wallTileIndex == boardref->getTileN(position.x, position.y))) {
							if ((position.x) != (wallTilePos.x + boardref->tileW)) {
								position.x += 1.0f;
							}
						}
					}
					
				}
			}
			if ((position.x + width) >= wallTilePos.x) {
				// right bound of player is greater than or equal to the left bound of wall
				if ((wallTileIndex == boardref->getTileN(position.x + width, position.y + height/2)) && boardref->tileTypes[wallTileIndex] == wall) {
					//if tile is a wall and the index of the tile is the same as the index of the tile that the right bound intersects
					if (velocity.x > 0.f) {
						//position.x = wallTilePos.x - width;
						velocity.x = 0.f;
					}
					else if (velocity.x == 0.f) {
						if ((wallTileIndex == boardref->getTileN(position.x + width, position.y + height)) || (wallTileIndex == boardref->getTileN(position.x + width, position.y))) {
							if ((position.x + width) != wallTilePos.x) {
								position.x -= 1.0f;
							}
						}
					}
					
				}
			}
			if (position.y <= (wallTilePos.y + boardref->tileH)) {
				//top bound player intersects bottom of wall
				if ((wallTileIndex == boardref->getTileN(position.x + width/2, position.y)) && boardref->tileTypes[wallTileIndex] == wall) {
					//if tile is a wall and the index of the tile is the same as the index of the tile that the top bound intersects
					if (velocity.y < 0.f) {
						//position.y = wallTilePos.y + boardref->tileH;
						velocity.y = 0.f;
					}
					else if (velocity.y == 0.f) {
						if ((wallTileIndex == boardref->getTileN(position.x + width, position.y)) || (wallTileIndex == boardref->getTileN(position.x, position.y))) {
							if ((position.y) != (wallTilePos.y + boardref->tileH)) {
								position.y += 1.0f;
							}
						}
					}
				}
			}
			if ((position.y + height) >= wallTilePos.y) {
				//bottom bound player intersects top of wall
				if (( wallTileIndex == boardref->getTileN(position.x + width/2, position.y + height)) && boardref->tileTypes[wallTileIndex] == wall) {
					//if tile is a wall and the index of the tile is the same as the index of the tile that the bottom bound intersects (using the corners of bounds)
					if (velocity.y > 0.f) {
						//position.y = wallTilePos.y - height;
						velocity.y = 0.f;
					}
					else if (velocity.y == 0.f) {
						if ((wallTileIndex == boardref->getTileN(position.x + width, position.y + height)) || (wallTileIndex == boardref->getTileN(position.x, position.y + height))) {
							if ((position.y + height) != wallTilePos.y) {
								position.y -= 1.0f;
							}
						}
					}
				}
			}


		}
			//wallTilePos = boardref->getTilePos();
			//if (position.x <= (wallTilePos.x + boardref->tileW)) {
				//the left bound of player is intersecting the right bound of wall

			//}
			//if(position.x )
		
			
		/*
		for each tile:
		if the tile is a wall

		 if left bound of player is <= right bound of wall tile
		 && the wall tile is to the left of the player 
		 stop x velocity( set to 0) when xvelocity is < 0 (going right) 

		 if right bound of player is >= left bound of wall tile
		 
		 if top bound of player is <= bottom bound of wall tile
		 
		 if bottom bound of player is >= top bound of wall tile

		*/


	}
}
