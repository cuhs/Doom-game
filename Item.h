#ifndef ITEM_H
#define ITEM_H
#include "globals.h"
#include "utilities.h"
#include <iostream>
#include <string.h>

class Item {
private:
	Coord pos;
	std::string name;	
	bool isInInventory;
public:
	Item();
	Item(Coord position, std::string theName, bool isInInventory);

	//virtual destructor for inheritance
	virtual ~Item();

	Item& operator=(const Item& other);

	//setters
	void setPos(int r, int c);
	void setName(std::string newName);
	void setRandomPos(Room* tRoom, int numRoom);
	void setIsInInvent(bool b);

	//getters
	std::string getName() const;
	Coord getPos() const;
	bool isInventory() const;

	//function that returns string to print when an item is picked up
	virtual std::string pickedUp();

};



#endif