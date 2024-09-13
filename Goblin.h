#ifndef GOBLIN_H
#define GOBLIN_H
#include "Monster.h"
#include <math.h>

//Goblins
class Goblin : public Monster{

private:
	int smellDistance;
	//helper function for determining where the goblin should move
	int whereMoveHelper(char bo[18][70], Coord playerPos, int iterations, int curRow, int curCol);
public:
	~Goblin();

	//Goblin constructors
	Goblin() :Monster(Coord(0, 0), randInt(15, 20), 1, 3, 1, 0, ShortSword(true, Coord(0,0)), "the Goblin"), smellDistance(15) {};
	Goblin(int smell, Coord p) :Monster(p, randInt(15, 20), 1, 3, 1, 0, ShortSword(true, Coord(0, 0)), "the Goblin"), smellDistance(smell) {};

	//determines where the goblin should move, overriting default monster function
	virtual char whereToMove(char bo[18][70], Coord playerPos);

	//returns a pointer to what item is dropped by a killed monster
	virtual Item* drops();
};
#endif