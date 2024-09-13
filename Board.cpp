#include "Board.h"
#include <math.h>
#include <iostream>

Board::Board() {

}

//board constructor that makes the levels and the things in the levels
Board::Board(int currLevel, int smellDistance) {

    //sets initial variables
    gobSmellDistance = smellDistance;
    level = currLevel;
    numMonsters = randInt(2, 5 * (level + 1) + 1);
    
    numRooms = randInt(4, 6);
    rooms = new Room[numRooms];


    //randomly generates dimensions of rooms
    for (int i = 0; i < numRooms; i++) {
        rooms[i].length = randInt(11, 20);
        rooms[i].height = randInt(4, 6);
        rooms[i].roomPos.row = 20;
    }

    //sets random position of first room
    rooms[0].roomPos.row = randInt(1, 8);
    rooms[0].roomPos.col = randInt(1, 15);

    
    int direction = randInt(1, 2); // 1=right, 2=down, 3=left, 4=up
    //sets coordinates of the rooms
    for (int i = 1; i < numRooms; i++) {
        //set the board based on what the rooms are so far
        createLevelBoard();
        bool caseOneChecked = false;
        switch (direction) {
            int hSpace, hCoord, vSpace, vCoord;

        case 1:
            hSpace = randInt(2, 8);
            hCoord = rooms[i - 1].roomPos.col + rooms[i - 1].length + hSpace;
            vSpace = randInt(0, rooms[i-1].height/2);
            vCoord = rooms[i - 1].roomPos.row + vSpace;
            caseOneChecked = true;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height-1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length-1] == '#' && board[vCoord + rooms[i].height-1][hCoord + rooms[i].length-1] == '#') {
                //sets the room to a random position to the right of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 2:
            hSpace = randInt(0, rooms[i-1].length/2);
            hCoord = rooms[i - 1].roomPos.col + hSpace;
            vSpace = randInt(2,4);
            vCoord = rooms[i - 1].roomPos.row + rooms[i-1].height +vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height-1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length-1] == '#' && board[vCoord + rooms[i].height-1][hCoord + rooms[i].length-1] == '#') {
                //sets the room to a random position to the bottom of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 3:
            hSpace = randInt(2,8);
            hCoord = rooms[i - 1].roomPos.col - rooms[i].length - hSpace;
            vSpace = randInt(0, rooms[i-1].height/2);
            vCoord = rooms[i - 1].roomPos.row + vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord > 0 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the left of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 4:
            hSpace = randInt(0, rooms[i - 1].length / 2);
            hCoord = rooms[i - 1].roomPos.col + hSpace;
            vSpace = randInt(2, 4);
            vCoord = rooms[i - 1].roomPos.row - rooms[i].height - vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord > 0 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the top of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
            //loops back if it didn't check all directions
            if (!caseOneChecked) {
                direction = 1;
                i--;
                continue;
            }
        default:
            //if the room made can't fit, stop making rooms
            numRooms = i;
        }
        direction = randInt(1, 4);
    }



    //sets monster positions
    Monster* temp;
    int whatMonst;
    for (int i = 0; i < numMonsters; i++) {
        createLevelBoard();

        //determine what monster is made
        int shouldIncreaseRand = 0;
        if (level >= 2)
            shouldIncreaseRand = 1;
        whatMonst = randInt(0, 1 + shouldIncreaseRand + level / 3);


        switch (whatMonst) {
        case 0:
            //makes a goblin
            monsters.push_back(new Goblin(gobSmellDistance, Coord(0, 0)));
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 1:
            //makes a snakewoman
            monsters.push_back(new Snakewoman());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 2:
            //makes a bogeyman
            monsters.push_back(new Bogeyman());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 3:
            //makes a dragon
            monsters.push_back(new Dragon());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        default:
            break;
        }
    }

    createLevelBoard();

    //generate initial position of player
    while (board[p1.getPosition().row][p1.getPosition().col] != ' ') {
        p1.setRandomPos(rooms, numRooms);
    }
    createLevelBoard();

    //generate staircase or trophy position
    staircase.setRandomPos(rooms, numRooms);
    while (board[staircase.getPos().row][staircase.getPos().col] != ' ') {
        staircase.setRandomPos(rooms, numRooms);
    }

    createLevelBoard();

    //generate items
    int nItems = randInt(2, 3);
    int randWeap, randItem, randScroll;
    Item* t;
    for (int i = 0; i < nItems; i++) {
        //determine whether the item is a weapon or scroll
        randItem = randInt(1, 2);
        t = nullptr;
        if (randItem == 1) {
            randWeap = randInt(1, 3);
            switch (randWeap) {
            case 1:
                //makes mace, puts at random position
                t = new Mace(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 2:
                //makes short sword, puts at random position
                t = new ShortSword(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 3:
                //makes long sword, puts at random position
                t = new LongSword(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            default:
                break;
            }

        }
        else {
            randScroll = randInt(1, 4);
            Player* playerPoint = &p1;
            switch (randScroll) {
            case 1:
                //makes armor scroll, puts at random position
                t = new ArmorScroll(playerPoint, Coord(0,0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 2:
                //makes strength scroll, puts at random position
                t = new StrScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 3:
                //makes dexterity scroll, puts at random position
                t = new DexScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 4:
                //makes health scroll, puts at random position
                t = new HealthScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            default:
                break;
            }

        }

        //puts items into vector
        if (t != nullptr)
            m_items.push_back(t);
        createLevelBoard();
    }

}


Board::~Board() {
    //delete dynamically allocated stuff
    while(monsters.size()>0) {
        Monster* temp = monsters[0];
        monsters.erase(monsters.begin());
        delete temp;
    }
    while (m_items.size()>0) {
        Item* temp = m_items[0];
        m_items.erase(m_items.begin());
        delete temp;
    }
    delete[] rooms;
}

//fills in 2d array containing the board
void Board::createLevelBoard() {
    
    //initially fill in board with all walls
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            itemsPlacement[i][j] = '#';
            board[i][j] = '#';

        }
    }

    
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomPos.row > 16 || rooms[i].roomPos.col > 68) {
            continue;
        }
        //fill in rooms - put space where room should be
        for (int j = rooms[i].roomPos.row; j < rooms[i].roomPos.row+ rooms[i].height; j++) {
            for (int k = rooms[i].roomPos.col; k < rooms[i].roomPos.col+rooms[i].length; k++) {
                board[j][k] = ' ';
                itemsPlacement[j][k] = ' ';
            }
        }
        //connect the rooms if room is to the right
        if (i<numRooms - 1 && rooms[i+1].roomPos.row < 16 && rooms[i + 1].roomPos.col>(rooms[i].roomPos.col + rooms[i].length)) {
            int connector = rooms[i].roomPos.col + rooms[i].length;
            while (connector < rooms[i + 1].roomPos.col) {
                board[rooms[i].roomPos.row + rooms[i].height / 2][connector] = ' ';
                itemsPlacement[rooms[i].roomPos.row + rooms[i].height / 2][connector] = ' ';
                connector++;
            }
        }
        //connect the rooms if room is down
        else if (i < numRooms - 1  && rooms[i + 1].roomPos.row < 16 && rooms[i + 1].roomPos.row>(rooms[i].roomPos.row + rooms[i].height)) {
            int connector = rooms[i].roomPos.row + rooms[i].height;
            while (connector < rooms[i + 1].roomPos.row) {
                board[connector][rooms[i].roomPos.col+rooms[i].length/2] = ' ';
                itemsPlacement[connector][rooms[i].roomPos.col + rooms[i].length / 2] = ' ';
                connector++;
            }
        }
        //connect if room is left
        else if (i < numRooms - 1 && rooms[i + 1].roomPos.row < 16 && rooms[i + 1].roomPos.col+rooms[i+1].length<rooms[i].roomPos.col) {
            int connector = rooms[i+1].roomPos.col + rooms[i+1].length;
            while (connector < rooms[i].roomPos.col) {
                board[rooms[i].roomPos.row + rooms[i].height / 2][connector] = ' ';
                itemsPlacement[rooms[i].roomPos.row + rooms[i].height / 2][connector] = ' ';
                connector++;
            }
        }
        //connect if room is up
        else if (i < numRooms - 1 && rooms[i + 1].roomPos.row < 16 && rooms[i + 1].roomPos.row+rooms[i+1].height<rooms[i].roomPos.row) {
            int connector = rooms[i+1].roomPos.row + rooms[i+1].height;
            while (connector < rooms[i].roomPos.row) {
                board[connector][rooms[i].roomPos.col + rooms[i].length / 2] = ' ';
                itemsPlacement[connector][rooms[i].roomPos.col + rooms[i].length / 2] = ' ';
                connector++;
            }
        }

    }

    //put monsters into board
    for (int i = 0; i < monsters.size(); i++) {
        board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] = monsters[i]->getName().at(4);
    }

    //put player into board
    board[p1.getPosition().row][p1.getPosition().col] = '@';

    //put stairs or trophy into board
    if (level < 4) {
        itemsPlacement[staircase.getPos().row][staircase.getPos().col] = '>';

    }
    else if (level == 4) {
        itemsPlacement[staircase.getPos().row][staircase.getPos().col] = '&';
    }

    //put items into board
    for (int i = 0; i < m_items.size(); i++) {
        Weapon* weapCast = dynamic_cast<Weapon*>(m_items[i]);
        if(weapCast != nullptr)
            itemsPlacement[m_items[i]->getPos().row][m_items[i]->getPos().col] = ')';
        else
            itemsPlacement[m_items[i]->getPos().row][m_items[i]->getPos().col] = '?';
    }
    
}

//displays board that is stored in 2d array
void Board::displayBoard() {
    clearScreen();
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (board[i][j] == ' ' && itemsPlacement[i][j] != ' ') {
                std::cout << itemsPlacement[i][j];
            }
            else {
                std::cout << board[i][j];
            }
        }
        std::cout << "\n";
    }
    std::cout << "Level: " << level << ", Hit points: " << p1.getHp() << ", Armor: " << p1.getArmor() << ", Strength: " << p1.getStr() << ", Dexterity: " << p1.getDex() << std::endl;

}

//tests if coordinate in board is empty
bool Board::isEmpty(Coord c) const{
    if (board[c.row][c.col] == '#' || board[c.row][c.col] == 'G' || board[c.row][c.col] == 'S' || board[c.row][c.col] == 'D' || board[c.row][c.col] == 'B')
        return false;
    return true;
}

//tests if there is a monster at a coordinate in the board
bool Board::isMonster(Coord c) const {
    for (int i = 0; i < numMonsters; i++) {
        if (monsters[i]->getPosition() == c)
            return true;
    }
    return false;
}

//gets the monster at a position in the board
Monster* Board::getMonstAtPosition(Coord p) {
    for (int i = 0; i < numMonsters; i++) {
        if (monsters[i]->getPosition() == p)
            return monsters[i];
    }
    return nullptr;
}

//resets the board after a level
void Board::resetBoard() {
    
    //deletes dynamically allocated memory
    while(monsters.size()>0) {
        Monster* temp = monsters[0];
        monsters.erase(monsters.begin());
        delete temp;
    }

    while (m_items.size() > 0) {
        Item* temp = m_items[0];
        m_items.erase(m_items.begin());
        delete temp;
    }

    delete[] rooms;
    
    //reset variables
    level++;
    numMonsters = randInt(2, 5 * (level + 1) + 1);

    numRooms = randInt(4, 6);


    rooms = new Room[numRooms];

    //make new rooms
    for (int i = 0; i < numRooms; i++) {
        rooms[i].length = randInt(11, 20);
        rooms[i].height = randInt(4, 6);
        rooms[i].roomPos.row = 20;
    }
    rooms[0].roomPos.row = randInt(1, 8);
    rooms[0].roomPos.col = randInt(1, 15);


    int direction = randInt(1, 2); // 1=right, 2=down, 3=left, 4=up
    //sets coordinates of the rooms
    for (int i = 1; i < numRooms; i++) {
        //set the board based on what the rooms are so far
        createLevelBoard();
        bool caseOneChecked = false;
        switch (direction) {
            int hSpace, hCoord, vSpace, vCoord;

        case 1:
            hSpace = randInt(2, 8);
            hCoord = rooms[i - 1].roomPos.col + rooms[i - 1].length + hSpace;
            vSpace = randInt(0, rooms[i - 1].height / 2);
            vCoord = rooms[i - 1].roomPos.row + vSpace;
            caseOneChecked = true;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the right of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 2:
            hSpace = randInt(0, rooms[i - 1].length / 2);
            hCoord = rooms[i - 1].roomPos.col + hSpace;
            vSpace = randInt(2, 4);
            vCoord = rooms[i - 1].roomPos.row + rooms[i - 1].height + vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the bottom of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 3:
            hSpace = randInt(2, 8);
            hCoord = rooms[i - 1].roomPos.col - rooms[i].length - hSpace;
            vSpace = randInt(0, rooms[i - 1].height / 2);
            vCoord = rooms[i - 1].roomPos.row + vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord > 0 && vCoord + rooms[i].height < 17 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the left of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
        case 4:
            hSpace = randInt(0, rooms[i - 1].length / 2);
            hCoord = rooms[i - 1].roomPos.col + hSpace;
            vSpace = randInt(2, 4);
            vCoord = rooms[i - 1].roomPos.row - rooms[i].height - vSpace;
            //check to make sure room is in bounds and does not overlap with other rooms
            if (hCoord + rooms[i].length < 69 && vCoord > 0 && board[vCoord][hCoord] == '#' && board[vCoord + rooms[i].height - 1][hCoord] == '#' && board[vCoord][hCoord + rooms[i].length - 1] == '#' && board[vCoord + rooms[i].height - 1][hCoord + rooms[i].length - 1] == '#') {
                //sets the room to a random position to the top of the first room
                rooms[i].roomPos.row = vCoord;
                rooms[i].roomPos.col = hCoord;
                direction = randInt(1, 4);
                break;
            }
            //loops back if it didn't check all directions
            if (!caseOneChecked) {
                direction = 1;
                i--;
                continue;
            }
        default:
            //if the room made can't fit, stop making rooms
            numRooms = i;
        }
        direction = randInt(1, 4);
    }



    //sets monster positions
    Monster* temp;
    int whatMonst;
    for (int i = 0; i < numMonsters; i++) {
        createLevelBoard();

        //determine what monster is made
        int shouldIncreaseRand = 0;
        if (level >= 2)
            shouldIncreaseRand = 1;
        whatMonst = randInt(0, 1 + shouldIncreaseRand + level / 3);


        switch (whatMonst) {
        case 0:
            //makes a goblin
            monsters.push_back(new Goblin(gobSmellDistance, Coord(0, 0)));
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 1:
            //makes a snakewoman
            monsters.push_back(new Snakewoman());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 2:
            //makes a bogeyman
            monsters.push_back(new Bogeyman());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        case 3:
            //makes a dragon
            monsters.push_back(new Dragon());
            monsters[i]->setRandomPos(rooms, numRooms);
            //keeps setting to a random position until it is unoccupied
            while (board[monsters[i]->getPosition().row][monsters[i]->getPosition().col] != ' ') {
                monsters[i]->setRandomPos(rooms, numRooms);
            }
            break;
        default:
            break;
        }
    }

    createLevelBoard();

    //generate initial position of player
    while (board[p1.getPosition().row][p1.getPosition().col] != ' ') {
        p1.setRandomPos(rooms, numRooms);
    }
    createLevelBoard();

    //generate staircase or trophy position
    staircase.setRandomPos(rooms, numRooms);
    while (board[staircase.getPos().row][staircase.getPos().col] != ' ') {
        staircase.setRandomPos(rooms, numRooms);
    }

    createLevelBoard();

    //generate items
    int nItems = randInt(2, 3);
    int randWeap, randItem, randScroll;
    Item* t;
    for (int i = 0; i < nItems; i++) {
        //determine whether the item is a weapon or scroll
        randItem = randInt(1, 2);
        t = nullptr;
        if (randItem == 1) {
            randWeap = randInt(1, 3);
            switch (randWeap) {
            case 1:
                //makes mace, puts at random position
                t = new Mace(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 2:
                //makes short sword, puts at random position
                t = new ShortSword(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 3:
                //makes long sword, puts at random position
                t = new LongSword(false, Coord(0, 0));
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            default:
                break;
            }

        }
        else {
            randScroll = randInt(1, 4);
            Player* playerPoint = &p1;
            switch (randScroll) {
            case 1:
                //makes armor scroll, puts at random position
                t = new ArmorScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 2:
                //makes strength scroll, puts at random position
                t = new StrScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 3:
                //makes dexterity scroll, puts at random position
                t = new DexScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            case 4:
                //makes health scroll, puts at random position
                t = new HealthScroll(playerPoint, Coord(0, 0), false);
                while (itemsPlacement[t->getPos().row][t->getPos().col] != ' ')
                    t->setRandomPos(rooms, numRooms);
                break;
            default:
                break;
            }

        }

        //puts items into vector
        if (t != nullptr)
            m_items.push_back(t);
        createLevelBoard();
    }

}

//gets the item at a position in the board
Item* Board::getItemAtPosition(Coord p, int& index) {
    for (int i = 0; i < m_items.size(); i++) {
        if (m_items[i]->getPos() == p) {
            index = i;
            return m_items[i];
        }
    }
    return nullptr;
}