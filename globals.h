#ifndef GLOBALS_H
#define GLOBALS_H


//Coordinate structure that has a row and column for easy comparison and use
struct Coord {
	int row;
	int col;
	Coord(int r, int c) {
		row = r;
		col = c;
	}
	Coord() {
		row = 0;
		col = 0;
	}
	Coord operator=(const Coord& other) {
		row = other.row;
		col = other.col;
		return *this;
	}

	bool operator==(const Coord& other) {
		if (row == other.row && col == other.col)
			return true;
		return false;
	}
};

//Room structure to store data of rooms in a board
struct Room {
	Coord roomPos;
	int length;
	int height;
	Room() {
		roomPos.col = 1;
		roomPos.row = 1;
		length = 68;
		height = 16;
	}
	Room(int r, int c, int l, int h) {
		roomPos.col = c;
		roomPos.row = r;
		length = l;
		height = h;
	}

	Room& operator=(const Room& other) {
		roomPos = other.roomPos;
		length = other.length;
		height = other.height;
		return *this;
	}
	~Room() {

	}
};

#endif