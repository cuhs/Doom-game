#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Player.h"
#include "utilities.h"
#include "globals.h"
#include "Monster.h"
#include "Goblin.h"
#include "Scroll.h"

//class for making the board of the game and its properties
class Board {
protected:
	int level;
	char board[18][70];
	char itemsPlacement[18][70];
	Player p1;
	std::vector<Monster*> monsters;
	std::vector<Item*> m_items;
	int numMonsters;
	Room* rooms;
	int numRooms;
	Item staircase;
	int gobSmellDistance;
public:

	//so that the main game class can directly access board properties
	friend class Game;

	Board(int currLevel, int smellDistance);
	Board();

	~Board();

	//tests to see if there are characters at position
	bool isEmpty(Coord c) const;
	bool isMonster(Coord c) const;

	//gets what is at a certain position
	Monster* getMonstAtPosition(Coord p);
	Item* getItemAtPosition(Coord p, int& index);

	//board modifying functions
	void createLevelBoard();
	void resetBoard();

	//displays the board
	void displayBoard();
};
#endif