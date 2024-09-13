#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include <string>
#include <iostream>


class Weapon : public Item {
private:
	std::string actionString;
	int dexBonus;
	int weaponDmg;
public:
	Weapon() :Item(Coord(0, 0), "NULL", false) {
		actionString = "NULL";
		dexBonus = -1;
		weaponDmg = -1;
	};
	virtual ~Weapon();
	//weapon constructor, each weapon would overwrite with relevant information
	Weapon(std::string actStr, int dex, int dmg, std::string theName, Coord position, bool isInInvent) :Item(position, theName, isInInvent) {
		actionString = actStr;
		dexBonus = dex;
		weaponDmg = dmg;
	};

	Weapon operator=(const Weapon& other);

	//getters
	int getDexBonus() const;
	int getWeaponDmg() const;
	std::string getActionStr() const;


};

//long sword class
class LongSword : public Weapon {
public:
	LongSword(bool isIn, Coord p) :Weapon(" swings long sword at ", 2, 4, "long sword", p, isIn) {

	};

};

//mace class
class Mace : public Weapon {
public:
	Mace(bool isIn, Coord p) :Weapon(" swings mace at ", 0, 2, "mace", p, isIn) {
	};

};

//magic axe class
class MagicAx : public Weapon {
public:
	MagicAx(bool isIn, Coord p) :Weapon(" chops magic axe at  ", 5, 5, "magic axe", p, isIn) {
	};

};

//magic fang class
class MagicFang : public Weapon {
public:
	MagicFang(bool isIn, Coord p) :Weapon(" strikes magic fangs at ", 0, 2, "magic fangs", p, isIn) {
	};
};

//short sword class
class ShortSword : public Weapon {
public:
	ShortSword(bool isIn, Coord p) :Weapon(" slashes short sword at ", 0, 2, "short sword", p, isIn) {
	};

};



#endif