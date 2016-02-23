#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    vector<int> characterPosition;

public:
    int numberOfItems();
	Room(string description);
    void setExits(Room *up, Room *right, Room *down, Room *left);
	string shortDescription();
    string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    vector<int> getCharacterPosition();
    void setCharacterPosition(int x, int y);
};

#endif
