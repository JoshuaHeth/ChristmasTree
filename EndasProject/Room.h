#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "door.h"
#include "hero.h"
//#include "mainwindow.h"

using namespace std;
using std::vector;
class Hero;

class Room {

private:
    string description;
    map<string, Room*> exits;
    string exitString();
    vector <Item *> itemsInRoom;
    vector<int> characterPosition;
    vector <Door *> doorsInRoom;
    int flag;

public:

    Room(string description, int flag);
    ~Room();

    void setExits(Room *up, Room *right, Room *down, Room *left);
    inline string shortDescription() {
        return description;
    }
    string longDescription();
    Room* nextRoom(string direction);

    inline void setFlag(int entered){
        flag = entered;
    }

    inline int getFlag(){return flag;}

    //Item methods
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    Item* getItem(string item);
    int numberOfItems();

    vector<int> getCharacterPosition();
    inline void setCharacterPosition(int x, int y){
        characterPosition.push_back(x);
        characterPosition.push_back(y);
    }

    inline void addItem(Item *inItem) {
        itemsInRoom.push_back(inItem);
    }

    inline void addDoor(Door *inDoor){
        doorsInRoom.push_back(inDoor);
    }

    //Door methods
    string unlockDoor(Hero *testCharacter);
    bool checkForDoor(string direction2);
    Door* getDoor(string direction);
};


#endif
