#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
#include "utilities.h"
#include "Weapon.h"
#include <vector>

class Scroll;

class Inventory {
private:
	std::vector<Item*> allItems;
	int numItems;
public:
	Inventory();
	~Inventory();

	//adds an item to inventory
	bool addItem(Item* nItem);

	//displays inventory
	void displayInventory();

	//returns number of items
	int getNumItems() const;
	
	//chooses a weapon or scroll
	Weapon* chooseWeapon(std::string& s);
	Scroll* chooseScroll(std::string& s);

};
#endif