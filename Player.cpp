#include "Player.h"
#include "utilities.h"

//constructor setting player's default properties
Player::Player() :Actor(Coord(0,0), 20, 2, 2, 2, 0, "Player") {
	setWeapon(ShortSword(true, Coord(0,0)));
	maxHealth = 20;
	inventory = new Inventory();
}

Player::~Player() {
	if(inventory != nullptr)
		delete inventory;
}

//cheat by increasing strength and health 
void Player::cheat() {
	setAttributes(getPosition(), 50, getArmor(), 9, getDex(), getSleep());
	setMaxHealth(50);
}

//getters
Inventory* Player::getInventory() {
	return inventory;
}

int Player::getMaxHealth() {
	return maxHealth;
}


//setters
void Player::setSleep(int newSlp) {
	if (newSlp > 9)
		Actor::setSleep(9);
	else
		Actor::setSleep(newSlp);
}

void Player::setHealth(int newHp) {
	if (newHp > 99)
		newHp = 99;
	Actor::setHealth(newHp);
}

void Player::setDex(int newDex) {
	if (newDex > 99)
		newDex = 99;
	Actor::setDex(newDex);
}

void Player::setStr(int newStr) {
	if (newStr > 99)
		newStr = 99;
	Actor::setStr(newStr);
}

void Player::setArmor(int newArmor) {
	if (newArmor > 99)
		newArmor = 99;
	Actor::setArmor(newArmor);
}
void Player::setMaxHealth(int newMax) {
	maxHealth = newMax;
}