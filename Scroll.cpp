#include "Scroll.h"
#include "Player.h"




Scroll::~Scroll() {

}

//returns strings to print relating to scroll
std::string Scroll::pickedUp() {
	return "You pick up a scroll called " + getName() + "\n";
}

std::string Scroll::scrollUsedStr() {
	return "You read the " + getName() + "\n" + usedStr + "\n";
}

void Scroll::scrollEffect() {


}

//gets player pointer
Player* Scroll::getPlayer() const{
	return p;
}

//sets player pointer
void Scroll::setPlayer(Player* theP) {
	p = theP;
}

//scroll effects for each scroll, modifying the Player pointed to by the Player pointer
void HealthScroll::scrollEffect() {
	getPlayer()->setMaxHealth(getPlayer()->getMaxHealth() + randInt(3, 8));
}

void DexScroll::scrollEffect() {
	getPlayer()->setDex(getPlayer()->getDex() + 1);
}

void StrScroll::scrollEffect() {
	getPlayer()->setStr(getPlayer()->getStr() + randInt(1, 3));
}

void ArmorScroll::scrollEffect() {
	getPlayer()->setArmor(getPlayer()->getArmor()+randInt(1,3));
}

void TeleportScroll::scrollEffect(char bo[18][70], Room* rooms, int numRooms) {
	getPlayer()->setRandomPos(rooms, numRooms);
	while (bo[getPlayer()->getPosition().row][getPlayer()->getPosition().col] != ' ') {
		getPlayer()->setRandomPos(rooms, numRooms);
	}
}