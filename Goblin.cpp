#include "Goblin.h"


Goblin::~Goblin() {

}

//determines where goblin will move
char Goblin::whereToMove(char bo[18][70], Coord playerPos) {
	//finds distance of shortest path to player starting in each tile adjacent to monster tile
	int rDist = whereMoveHelper(bo, playerPos, 1, getPosition().row, getPosition().col + 1);
	int lDist = whereMoveHelper(bo, playerPos, 1, getPosition().row, getPosition().col - 1);
	int uDist = whereMoveHelper(bo, playerPos, 1, getPosition().row - 1, getPosition().col);
	int dDist = whereMoveHelper(bo, playerPos, 1, getPosition().row + 1, getPosition().col);
	
	//find minimum distance
	int minimum = std::min(std::min(rDist, lDist), std::min(uDist, dDist));
	if (minimum == smellDistance+1) return 'n';
	//return the direction with the minimum distance
	if (rDist == minimum) return 'r';
	if (lDist == minimum) return 'l';
	if (uDist == minimum) return 'u';
	if (dDist == minimum) return 'd';
	return 'n';

}

//helper function that returns distance of shortest path to player, or gobSmellDistance+1 if no path
int Goblin::whereMoveHelper(char bo[18][70], Coord playerPos, int iterations, int curRow, int curCol) {
	//if invalid, return gobSmellDistance+1
	if (iterations > smellDistance || curRow>16 || curCol > 68 || curRow < 1 || curCol < 1 || bo[curRow][curCol] != ' ' && bo[curRow][curCol] != '@')
		return smellDistance + 1;
	//if player is found, return the number of steps taken
	if (bo[curRow][curCol] == '@') return iterations;
	if (playerPos.row == curRow && playerPos.col == curCol) {
		return iterations;
	}
	//set current tile to visited
	bo[curRow][curCol] = 'v';

	//recurse for each direction adjacent to current tile
	int rDist = whereMoveHelper(bo, playerPos, iterations+1, curRow, curCol + 1);
	int lDist = whereMoveHelper(bo, playerPos, iterations+1, curRow, curCol - 1);
	int uDist = whereMoveHelper(bo, playerPos, iterations+1, curRow - 1, curCol);
	int dDist = whereMoveHelper(bo, playerPos, iterations+1, curRow + 1, curCol);
	//set current tile back to space to not affect other paths
	bo[curRow][curCol] = ' ';
	//return the minimum distance of the 4 directions
	return std::min(std::min(rDist, lDist), std::min(uDist, dDist));


}

//dropped item getter
Item* Goblin::drops() {
	if (randInt(1, 3) == 1) {
		if (randInt(1, 2) == 1) {
			return new MagicAx(false, getPosition());
		}
		else {
			return new MagicFang(false, getPosition());
		}
	}
	return nullptr;
}