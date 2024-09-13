#ifndef ACTOR_H
#define ACTOR_H
#include "globals.h"
#include "Weapon.h"

class Actor {
private:
	Coord pos;
	int hp;
	int armor;
	int strength;
	int dex;
	int sleep;
	Weapon m_weap;
	std::string name;
public:
	Actor();
	//constructors defining properties
	Actor(Coord p, int health, int arm, int str, int d, int slp, Weapon weap, std::string nName);
	Actor(Coord p, int health, int arm, int str, int d, int slp, std::string nName);

	//virtual destructor for inheritance
	virtual ~Actor();

	Actor& operator=(const Actor& other);

	//getters
	Coord getPosition() const;
	int getHp() const;
	int getArmor() const;
	int getStr() const;
	int getDex() const;
	int getSleep() const;
	std::string getName() const;

	//setters
	void setAttributes(Coord p, int health, int arm, int str, int d, int slp);
	void setPos(int r, int c);
	virtual void setSleep(int newSlp);
	virtual void setHealth(int newHp);
	virtual void setArmor(int newArmor);
	void setWeapon(Weapon weap);
	virtual void setDex(int newDex);
	virtual void setStr(int newStr);

	//actor actions
	bool attackActor(Actor* b, std::string & s);
	void move(char dir);
	void setRandomPos(Room* tRoom, int numRoom);

};

#endif