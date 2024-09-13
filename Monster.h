#ifndef MONSTER_H
#define MONSTER_H
#include "Actor.h"
#include <iostream>
#include <math.h>
#include "utilities.h"
#include "Scroll.h"

class Monster : public Actor {
private:
	
public:
	Monster(Coord p, int health, int arm, int str, int d, int slp, Weapon weap, std::string nName) :Actor(p, health, arm, str, d, slp, weap,nName) {};
	
	//returns true if a monster is next to the player
	bool isAdjPlayer(Coord pPos);

	//virtual methods for abstract class
	virtual ~Monster();

	//determines where a monster should move, should be overwritten for each monster
	virtual char whereToMove(char bo[18][70], Coord playerPos) = 0;

	//determines what a monster drops
	virtual Item* drops() = 0;
};

//snakewoman class
class Snakewoman : public Monster {
private:

public:
	Snakewoman() :Monster(Coord(0, 0), randInt(3, 6), 3, 2, 3, 0, MagicFang(true, Coord(0, 0)), "the Snakewoman") {};
	Snakewoman(Coord p) :Monster(p, randInt(3, 6), 3, 2, 3, 0, MagicFang(true, Coord(0, 0)), "the Snakewoman") {};
	~Snakewoman();

	virtual char whereToMove(char bo[18][70], Coord playerPos);
	virtual Item* drops();
};

//bogeyman class
class Bogeyman : public Monster {
public:
	Bogeyman() :Monster(Coord(0, 0), randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, ShortSword(true, Coord(0, 0)), "the Bogeyman") {};
	Bogeyman(Coord p) :Monster(p, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, ShortSword(true, Coord(0, 0)), "the Bogeyman") {};
	~Bogeyman();

	virtual char whereToMove(char bo[18][70], Coord playerPos);
	virtual Item* drops();

};

//dragon class
class Dragon : public Monster {
private:
	int maxHp;
public:
	Dragon() :Monster(Coord(0, 0), randInt(20, 25), 4, 4, 4, 0, LongSword(true, Coord(0, 0)), "the Dragon") {
		maxHp = getHp();
	};
	Dragon(Coord p) :Monster(p, randInt(20, 25), 4, 4, 4, 0, LongSword(true, Coord(0, 0)), "the Dragon") {
		maxHp = getHp();
	};
	~Dragon();

	virtual char whereToMove(char bo[18][70], Coord playerPos);
	virtual Item* drops();

	int getMaxHp() const;

};



#endif