// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;


//main play function
void Game::play()
{

    //declare variables to use during execution
    char condition = ' ';
    int pRow, pCol;
    std::string printString;
    std::string attackString = "";
    bool shouldPrint = false;
    Weapon* temp;
    Scroll* temp1;

    //while loop for getting player action
    while (condition != 'q') {
        m_board.createLevelBoard();
        m_board.displayBoard();
        if(shouldPrint)
            std::cout << std::endl << printString; // prints string if there is an action that should be printed
        printString = "";
        shouldPrint = false;

        //if player is dead, quit game when q is pressed
        if (m_board.p1.getHp() <= 0) {
            std::cout << std::endl << "Press q to exit game." << std::endl;
            while (getCharacter() != 'q');
            condition = 'q';
        }

        //gets player input
        if(condition != 'q')
            condition = getCharacter();
        //gets player position
        pRow = m_board.p1.getPosition().row;
        pCol = m_board.p1.getPosition().col;
        
        //chance for healing player
        if (m_board.p1.getHp() < m_board.p1.getMaxHealth()) {
            if (randInt(1, 10) == 4) {
                m_board.p1.setHealth(m_board.p1.getHp() + 1);
            }
        }

        
        if (m_board.p1.getSleep() == 0) {
            //handles player action if player is not asleep
            switch (condition) {

            case ARROW_RIGHT:
                //if there is a monster there, attack
                if (pCol < 68 && m_board.isMonster(Coord(pRow, pCol + 1))) {
                    m_board.p1.attackActor(m_board.getMonstAtPosition(Coord(pRow, pCol + 1)), attackString);
                    printString += attackString;
                    shouldPrint = true;
                }
                //otherwise move
                else if (pCol < 68 && m_board.isEmpty(Coord(pRow, pCol + 1))) {
                    m_board.board[pRow][pCol] = m_board.itemsPlacement[pRow][pCol];
                    m_board.board[pRow][pCol + 1] = '@';
                    m_board.p1.move('r');
                }
                break;
            case ARROW_LEFT:
                //if there is a monster there, attack

                if (pCol < 68 && m_board.isMonster(Coord(pRow, pCol - 1))) {
                    m_board.p1.attackActor(m_board.getMonstAtPosition(Coord(pRow, pCol - 1)), attackString);
                    printString += attackString;
                    shouldPrint = true;
                }
                //otherwise move
                else if (pCol > 1 && m_board.isEmpty(Coord(pRow, pCol - 1))) {
                    m_board.board[pRow][pCol] = m_board.itemsPlacement[pRow][pCol];
                    m_board.board[pRow][pCol - 1] = '@';
                    m_board.p1.move('l');
                }
                break;
            case ARROW_UP:
                //if there is a monster there, attack
                if (pCol < 68 && m_board.isMonster(Coord(pRow - 1, pCol))) {
                    m_board.p1.attackActor(m_board.getMonstAtPosition(Coord(pRow-1, pCol)), attackString);
                    printString += attackString;
                    shouldPrint = true;
                }
                //otherwise move
                else if (pRow > 1 && m_board.isEmpty(Coord(pRow - 1, pCol))) {
                    m_board.board[pRow][pCol] = m_board.itemsPlacement[pRow][pCol];
                    m_board.board[pRow - 1][pCol] = '@';
                    m_board.p1.move('u');
                }
                break;
            case ARROW_DOWN:
                //if there is a monster there, attack
                if (pCol < 68 && m_board.isMonster(Coord(pRow + 1, pCol))) {
                    m_board.p1.attackActor(m_board.getMonstAtPosition(Coord(pRow + 1, pCol)), attackString);
                    printString += attackString;
                    shouldPrint = true;
                }
                //otherwise move
                else if (pRow < 16 && m_board.isEmpty(Coord(pRow + 1, pCol))) {
                    m_board.board[pRow][pCol] = m_board.itemsPlacement[pRow][pCol];
                    m_board.board[pRow + 1][pCol] = '@';
                    m_board.p1.move('d');
                }
                break;
            case 'C':
            case 'c':
                //handle cheat
                m_board.p1.cheat();
                break;
            case '>':
                //handle getting to next level
                if (level < 4 && m_board.p1.getPosition() == m_board.staircase.getPos()) {
                    level++;
                    m_board.resetBoard();
                    
                    m_board.displayBoard(); 
                    continue;
                }
                break;
            case 'G':
            case 'g':
                //if golden idol is at positoin, end game in victory
                if (level == 4 && m_board.p1.getInventory()->getNumItems() <= 25 && m_board.p1.getPosition() == m_board.staircase.getPos()) {
                    std::cout << std::endl << "You pick up the golden idol" << std::endl << "Congratulations, you won!" << std::endl << "Press q to exit game." << std::endl;
                    while (getCharacter() != 'q');
                    condition = 'q';
                }
                else {
                    //handle picking up items
                    if (m_board.p1.getInventory()->getNumItems() <=25 && ( m_board.itemsPlacement[m_board.p1.getPosition().row][m_board.p1.getPosition().col] == ')' || m_board.itemsPlacement[m_board.p1.getPosition().row][m_board.p1.getPosition().col] == '?')) {
                        int tempIdx;
                        Item* itAtPos = m_board.getItemAtPosition(m_board.p1.getPosition(), tempIdx);
                        if (itAtPos == nullptr) break;
                        if (m_board.p1.getInventory()->addItem(itAtPos)) {//if item is successfully added, take it out of the board
                            printString += itAtPos->pickedUp();
                            shouldPrint = true;
                            itAtPos->setIsInInvent(true);
                            m_board.m_items.erase(m_board.m_items.begin() + tempIdx);
                            m_board.itemsPlacement[m_board.p1.getPosition().row][m_board.p1.getPosition().col] = ' ';
                            m_board.createLevelBoard();
                        }
                    }
                    
             
                }
                break;
            case 'I':
            case 'i':
                //display inventory
                m_board.p1.getInventory()->displayInventory();
                getCharacter();
                break;
            case 'W':
            case 'w':
                //display inventory and allow player to choose weapon
                temp = m_board.p1.getInventory()->chooseWeapon(printString);
                if (temp != nullptr) {
                    m_board.p1.setWeapon(*temp);
                    shouldPrint = true;
                }
                break;
            case 'R':
            case 'r':
                //display inventory and allow player to choose scroll
                temp1 = m_board.p1.getInventory()->chooseScroll(printString);
                if (temp1 != nullptr) {
                    TeleportScroll* teleportPoint = dynamic_cast<TeleportScroll*>(temp1);
                    if (teleportPoint != nullptr) {
                        teleportPoint->scrollEffect(m_board.board, m_board.rooms, m_board.numRooms);
                        m_board.createLevelBoard();
                    }
                    else {
                        temp1->scrollEffect();
                    }
                    shouldPrint = true;
                }

                break;
            default:
                break;
            }
        }
        else {
            //if player is asleep, decrement sleep instead of an action
            m_board.p1.setSleep(m_board.p1.getSleep()-1);
        }
        if (condition == 'q')
            continue;




        for (int i = 0; i < m_board.monsters.size(); i++) {
            
            if (m_board.monsters[i]->getHp() <= 0) {
                //if monster is dead, drop item and get rid of monster
                Item* theDrop = m_board.monsters[i]->drops();
                char cTemp = m_board.itemsPlacement[m_board.monsters[i]->getPosition().row][m_board.monsters[i]->getPosition().col];
                if (theDrop != nullptr && (cTemp == ' ')) {
                    Scroll* scrollPoint = dynamic_cast<Scroll*>(theDrop);
                    if (scrollPoint != nullptr) {
                        Player* tempPlay = &m_board.p1;
                        scrollPoint->setPlayer(tempPlay);
                    }
                    m_board.m_items.push_back(theDrop);
                }

                Monster* temp = m_board.monsters[i];
                m_board.monsters.erase(m_board.monsters.begin() + i);
                delete temp;
                m_board.numMonsters--;
                i--;
                m_board.createLevelBoard();
                continue;
            }
            //if monster is asleep, skip turn
            if (m_board.monsters[i]->getSleep() > 0) {
                m_board.monsters[i]->setSleep(m_board.monsters[i]->getSleep() - 1);
                continue;
            }
            //if monster is next to player, attack
            if (m_board.p1.getPosition().row != 0 && m_board.monsters[i]->isAdjPlayer(m_board.p1.getPosition())) {
                Player* pPointer = &m_board.p1;
                m_board.monsters[i]->attackActor(pPointer, attackString);
                printString += attackString;
                shouldPrint = true;
                if (m_board.p1.getHp() <= 0) {
                    break;
                }
                    
                continue;
            }
            //handle monster movement
            char theMove = m_board.monsters[i]->whereToMove(m_board.board, m_board.p1.getPosition());
            switch (theMove) {
            case 'r':
            case 'l':
            case 'u':
            case 'd':
                m_board.monsters[i]->move(theMove);
                m_board.createLevelBoard();
            default:
                break;
            }
            //dragon healing
            Dragon* isDrag = dynamic_cast<Dragon*>(m_board.monsters[i]);
            if (isDrag != nullptr && isDrag->getHp()<isDrag->getMaxHp() && randInt(1,10)==4) {
                isDrag->setHealth(isDrag->getHp() + 1);
            }
        }




    }
}
