#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "door.h"
#include "Command.h"
#include "Character.h"
//#include "mainwindow.h"

using namespace std;
using std::vector;
class Character;

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
    //~Room();

    void setExits(Room *up, Room *right, Room *down, Room *left);
	string shortDescription();
    string longDescription();
	Room* nextRoom(string direction);

    void setFlag(int entered);
    int getFlag();

    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    Item* getItem(string command);
    int numberOfItems();

    vector<int> getCharacterPosition();
    void setCharacterPosition(int x, int y);

    //Door methods/variables
    void addDoor(Door *inDoor);
    string displayDoor();

    //Pass reference to vector. Vector will be edited.
    string unlockDoor(Character *testCharacter);

    bool checkForDoor(string direction2);
    Door* getDoor(string direction);
};

/*********MODIFY TO FIT
template <typename T>
void addToList (T *addedValue){

    //Check to see if variable points to an object of Item type.
    if(dynamic_cast<Item*>(addedValue))
        itemsInRoom.push_back(addedValue);

    else
        doorsInRoom.push_back(addedValue);

}


};*/

#endif
