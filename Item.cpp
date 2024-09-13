#include "Item.h"


//constructors
Item::Item() {
	pos.row = 0;
	pos.col = 0;
	isInInventory = true;
}

Item::Item(Coord position, std::string theName, bool isIn) {
	pos = position;
	name = theName;
	isInInventory = isIn;
}

Item::~Item() {

}

//= operator
Item& Item::operator=(const Item& other) {
	pos = other.pos;
	name = other.name;
	isInInventory = other.isInInventory;
	return *this;
}

//setts
void Item::setPos(int r, int c) {
	pos.row = r;
	pos.col = c;
}

void Item::setName(std::string newName) {
	name = newName;
}

void Item::setIsInInvent(bool b) {
	isInInventory = b;
}


//getters
bool Item::isInventory() const{
	return isInInventory;
}

Coord Item::getPos() const {
	return pos;
}

std::string Item::getName() const {
	return name;
}

//set item to a random position in the rooms
void Item::setRandomPos(Room* tRoom, int numRoom) {
	int p1CurrRoom = randInt(0, numRoom - 1);
	setPos(randInt(tRoom[p1CurrRoom].roomPos.row, tRoom[p1CurrRoom].roomPos.row + tRoom[p1CurrRoom].height - 1), randInt(tRoom[p1CurrRoom].roomPos.col, tRoom[p1CurrRoom].roomPos.col + tRoom[p1CurrRoom].length - 1));
}


//returns string to print when item is picked up
std::string Item::pickedUp() {
	return "You pick up " + name + "\n";
}
