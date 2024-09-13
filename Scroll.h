#ifndef SCROLL_H
#define SCROLL_H
#include "Item.h"
#include "globals.h"

class Player;

//class to store scrolls
class Scroll : public Item {
private:
	std::string usedStr;
	Player* p;
public:
	//scroll constructor, each scroll would overwrite the member variables with the relevant information
	Scroll(std::string n, std::string used, Player* tempP, Coord pos, bool isInInventory) :Item(pos, n, isInInventory) {
		usedStr = used;
		p = tempP;
	};
	Scroll();

	~Scroll();

	//sets player pointer
	void setPlayer(Player* theP);


	//applies the scroll effect to the player
	virtual void scrollEffect();

	//returns strings to print
	std::string pickedUp();
	std::string scrollUsedStr();

	//returns a pointer to the player involved with the scroll
	Player* getPlayer() const;
};

//health scroll
class HealthScroll : public Scroll {
public:
	HealthScroll(Player* tempP, Coord pos, bool isIn) :Scroll("scroll of enhance health", "You feel your heart beating stronger.", tempP, pos, isIn) {};
	HealthScroll() :Scroll("scroll of enhance health", "You feel your heart beating stronger.", nullptr, Coord(0,0), true) {};


	void scrollEffect();

};

//dexterity scroll
class DexScroll : public Scroll {
public:
	DexScroll(Player* tempP, Coord pos, bool isIn) :Scroll("scroll of enhance dexterity", "You feel like less of a klutz.", tempP, pos, isIn) {};
	DexScroll() :Scroll("scroll of enhance dexterity", "You feel like less of a klutz.", nullptr, Coord(0,0), true) {};


	void scrollEffect();

};

//strength scroll
class StrScroll : public Scroll {
public:
	StrScroll(Player* tempP, Coord pos, bool isIn) :Scroll("scroll of strength", "Your muscles bulge.", tempP, pos, isIn) {};
	StrScroll() :Scroll("scroll of strength", "Your muscles bulge.", nullptr, Coord(0,0), true) {};


	void scrollEffect();

};

//armor scroll
class ArmorScroll : public Scroll {
public:
	ArmorScroll(Player* tempP, Coord pos, bool isIn) :Scroll("scroll of enhance armor", "Your armor glows blue.", tempP, pos, isIn) {};
	ArmorScroll() :Scroll("scroll of enhance armor", "Your armor glows blue.", nullptr, Coord(0,0), true) {};


	void scrollEffect();

};

//teleportation scroll
class TeleportScroll : public Scroll {
public:
	TeleportScroll(Player* tempP, Coord pos, bool isIn) :Scroll("scroll of teleportation", "You feel your body wrenched in space and time.", tempP, pos, isIn) {};
	TeleportScroll() :Scroll("scroll of teleportation", "You feel your body wrenched in space and time.", nullptr, Coord(0,0), true) {};


	void scrollEffect(char bo[18][70], Room* rooms, int numRooms);

};

#endif