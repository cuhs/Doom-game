#include "Inventory.h"
#include "Scroll.h"

Inventory::Inventory() {
	numItems = 0;
	//add short sword to inventory
	Item* sword = new ShortSword(true, Coord(0,0));
	addItem(sword);

}

Inventory::~Inventory() {
	while (allItems.size() > 0) {
		Item* temp = allItems[0];
		allItems.erase(allItems.begin());
		delete temp;
	}
}

//adds item to inventory vector
bool Inventory::addItem(Item* nItem) {
	if (numItems > 26)
		return false;
	allItems.push_back(nItem);
	numItems++;

	return true;
}

//display current inventory
void Inventory::displayInventory() {
	clearScreen();
	std::cout << "Inventory:" << std::endl;
	for (int i = 0; i < numItems; i++) {
		std::cout << char(i + 'a');
		std::cout << ". " << allItems[i]->getName() << std::endl;
	}
}

//displays inventory, lets player choose weapon
Weapon* Inventory::chooseWeapon(std::string& s){
	displayInventory();
	char c = getCharacter();
	if (c < 'a' || int(c) >= int('a') + numItems) {
		return nullptr;
	}
	//dynamic cast to test for weapon
	Weapon* w = dynamic_cast<Weapon*>(allItems[int(c - 'a')]);
	if (w == nullptr) return nullptr;
	s = "You are wielding " + w->getName() + "\n";
	return w;
}

//displays inventory, lets player choose scroll
Scroll* Inventory::chooseScroll(std::string& s) {
	displayInventory();
	char c = getCharacter();
	if (c < 'a' || int(c) >= int('a') + numItems) {
		return nullptr;
	}

	//dynamic cast to test for scroll
	Scroll* w = dynamic_cast<Scroll*>(allItems[int(c - 'a')]);
	if (w == nullptr) return nullptr;

	allItems.erase(allItems.begin() + int(c - 'a'));
	s = w->scrollUsedStr();
	numItems--;
	return w;
}

//returns number of items
int Inventory::getNumItems() const{
	return numItems;
}