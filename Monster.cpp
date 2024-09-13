#include "Monster.h"


Monster::~Monster() {

}


//retruns true if monster is adjacent to player
bool Monster::isAdjPlayer(Coord pPos) {
	
	if (abs(getPosition().row - pPos.row) <= 1 && abs(getPosition().col - pPos.col) <= 1 && !(abs(getPosition().row - pPos.row)==1 && abs(getPosition().col - pPos.col)==1)) {
		return true;
	}
	return false;
}

Snakewoman::~Snakewoman() {

}

//function to determine where a snakewoman should move
char Snakewoman::whereToMove(char bo[18][70], Coord playerPos) {
	int horDiff = getPosition().col - playerPos.col;
	int vertDiff = getPosition().row - playerPos.row;
	//if the difference in position is greater than 3, don't move
	if (abs(horDiff) + abs(vertDiff) > 3)
		return 'n';
	//test which direction the player is, return a corresponding character
	if (horDiff > 0 && bo[getPosition().row][getPosition().col-1] == ' ') {
		return 'l';
	}
	else if (horDiff < 0 && bo[getPosition().row][getPosition().col + 1] == ' ') {
		return 'r';
	}
	else if (vertDiff > 0 && bo[getPosition().row - 1][getPosition().col] == ' ') {
		return 'u';
	}
	else if (vertDiff < 0 && bo[getPosition().row + 1][getPosition().col] == ' ') {
		return 'd';
	}
	return 'n';
}

//function that returns item the snakewoman drops
Item* Snakewoman::drops() {
	if (randInt(1, 3) == 1)
		return new MagicFang(false, getPosition());
	return nullptr;
}

//function to determine where a bogeyman should move
char Bogeyman::whereToMove(char bo[18][70], Coord playerPos) {
	int horDiff = getPosition().col - playerPos.col;
	int vertDiff = getPosition().row - playerPos.row;
	//if total distance is too high, don't move
	if (abs(horDiff) + abs(vertDiff) > 5)
		return 'n';
	//return corresponding letter based on where the player is relative to the bogeyman
	if (horDiff > 0 && bo[getPosition().row][getPosition().col - 1] == ' ') {
		return 'l';
	}
	else if (horDiff < 0 && bo[getPosition().row][getPosition().col + 1] == ' ') {
		return 'r';
	}
	else if (vertDiff > 0 && bo[getPosition().row - 1][getPosition().col] == ' ') {
		return 'u';
	}
	else if (vertDiff < 0 && bo[getPosition().row + 1][getPosition().col] == ' ') {
		return 'd';
	}
	return 'n';
}

//returns item the bogeyman drops
Item* Bogeyman::drops() {
	if (randInt(1, 10) == 1)
		return new MagicAx(false, getPosition());
	return nullptr;
}

Bogeyman::~Bogeyman() {

}

//dragon doesn't move
char Dragon::whereToMove(char bo[18][70], Coord playerPos) {
	return 'n';
}

//returns scroll dropped by dragon
Item* Dragon::drops() {
	int x = randInt(1, 5);
	switch (x) {
	case 1:
		return new TeleportScroll(nullptr, getPosition(), false);
	case 2:
		return new ArmorScroll(nullptr, getPosition(), false);
	case 3:
		return new StrScroll(nullptr, getPosition(), false);
	case 4:
		return new HealthScroll(nullptr, getPosition(), false);
	case 5:
		return new DexScroll(nullptr, getPosition(), false);
	default:
		break;
	}
	return nullptr;
}

Dragon::~Dragon() {

}

//gets max HP of the dragon
int Dragon::getMaxHp() const {
	return maxHp;
}