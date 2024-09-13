#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include "Inventory.h"

class Player: public Actor {
private:
	Inventory* inventory;
	int maxHealth;
public:
	Player();
	~Player();



	void cheat();

	//setters
	void setMaxHealth(int newMax);
	void setSleep(int newSlp);
	void setDex(int newDex);
	void setHealth(int newHp);
	void setStr(int newStr);
	void setArmor(int newArmor);

	//getters
	int getMaxHealth();
	Inventory* getInventory();

};

#endif