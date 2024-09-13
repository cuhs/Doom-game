#include "Weapon.h"

//= operator
Weapon Weapon::operator=(const Weapon& other) {
	if (this == &other)
		return *this;
	actionString = other.actionString;
	dexBonus = other.dexBonus;
	weaponDmg = other.weaponDmg;
	setName(other.getName());
	setPos(other.getPos().row, other.getPos().col);
	setIsInInvent(other.isInventory());
	return *this;
}


Weapon::~Weapon() {

}

//getters
int Weapon::getDexBonus() const{
	return dexBonus;//exception ahppened
}

std::string Weapon::getActionStr() const {
	return actionString;
}

int Weapon::getWeaponDmg() const {
	return weaponDmg;
}

