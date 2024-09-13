#include "Actor.h"
#include "utilities.h"
#include <iostream>

Actor::Actor() {
	sleep = 0;
}


Actor::~Actor() {

}

//constructor for actor, sets all attributes
Actor::Actor(Coord p, int health, int arm, int str, int d, int slp, Weapon weap, std::string nName) {
	
	setAttributes(p, health, arm, str, d, slp);
	name = nName;
	m_weap = weap;
}

//constructor for actor that doesn't set weapon
Actor::Actor(Coord p, int health, int arm, int str, int d, int slp, std::string nName) {
	setAttributes(p, health, arm, str, d, slp);
	name = nName;
}

//equal operator for actor
Actor& Actor::operator=(const Actor& other) {
	if (this == &other)
		return *this;
	setAttributes(other.pos, other.hp, other.armor, other.strength, other.dex, other.sleep);
	m_weap = other.m_weap;
	name = other.name;
	return *this;
}

//sets position, health, armor, strength, dexterity, and sleep of actor
void Actor::setAttributes(Coord p, int health, int arm, int str, int d, int slp) {
	pos = p;
	hp = health;
	armor = arm;	
	strength = str;
	dex = d;
	sleep = slp;
}

//sets position
void Actor::setPos(int r, int c) {
	pos.row = r;
	pos.col = c;
}

//sets actor to a random position within the rooms that are passed by parameter
void Actor::setRandomPos(Room* tRoom, int numRoom) {
	int p1CurrRoom = randInt(0,numRoom-1);
	setPos(randInt(tRoom[p1CurrRoom].roomPos.row, tRoom[p1CurrRoom].roomPos.row + tRoom[p1CurrRoom].height-1), randInt(tRoom[p1CurrRoom].roomPos.col, tRoom[p1CurrRoom].roomPos.col + tRoom[p1CurrRoom].length-1));
}

//gets position
Coord Actor::getPosition() const{
	return pos;
}

//gets hp
int Actor::getHp() const{
	return hp;
}

//gets armor
int Actor::getArmor() const{
	return armor;
}

//gets strength
int Actor::getStr() const{
	return strength;
}

//gets dexterity
int Actor::getDex() const{
	return dex;
}

//gets sleep
int Actor::getSleep() const{
	return sleep;
}

//moves actor 
void Actor::move(char dir) {
	if (dir == 'r') {
		pos.col++;
	}
	else if (dir == 'd') {
		pos.row++;
	}
	else if (dir == 'l') {
		pos.col--;
	}
	else if(dir=='u'){
		pos.row--;
	}
}

//sets sleep
void Actor::setSleep(int newSlp) {

	sleep = newSlp;
}

//sets health
void Actor::setHealth(int newHp) {
	hp = newHp;
}

//sets dexterity
void Actor::setDex(int newDex) {
	dex = newDex;
}

//sets armor
void Actor::setArmor(int newArmor) {
	armor = newArmor;
}

//sets weapon
void Actor::setWeapon(Weapon weap) {
	m_weap = weap;
}

//sets strength
void Actor::setStr(int newStr) {
	strength = newStr;
}

//gets name
std::string Actor::getName() const{
	return name;
}

//actor attacks actor
bool Actor::attackActor(Actor* b, std::string & s) {
	//points as defined by the specs
	int attackerPoints = dex + m_weap.getDexBonus();
	int defenderPoints = b->dex + b->m_weap.getDexBonus();

	//string that would be added to s if the attacked actor falls asleep
	std::string sleepStr = ".";

	if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) { //if the defender is hit
		//random damage points
		int damagePoints = randInt(0, strength + m_weap.getWeaponDmg() - 1);
		b->setHealth(b->getHp()-damagePoints);
		//handles sleep if magic fangs are equipped
		if (m_weap.getName() == "magic fangs") {
			if (randInt(1, 5) ==3) {
				b->setSleep(std::max(randInt(2, 6), b->getSleep()));
				sleepStr = ", putting " + b->getName() + " to sleep.";
			}
		}
		//sets s to strings to print for the attack
		if (b->getHp() <= 0) {
			s = getName() + m_weap.getActionStr() + b->getName() + " dealing a final blow.\n";
		}else
			s = getName() + m_weap.getActionStr() + b->getName() + " and hits" + sleepStr + "\n";
		return true;
	}
	s = getName() + m_weap.getActionStr() + b->getName() + " and misses.\n";
	return false;
}