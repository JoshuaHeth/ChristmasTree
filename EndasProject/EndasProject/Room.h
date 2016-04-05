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

    Room(const string,const int);
    ~Room();

    void setExits(Room*, Room*, Room*, Room*);
    Room* nextRoom(const string &);
    string longDescription();

    /**
     * @brief shortDescription
     * @return
     */
    inline string shortDescription() {
        return description;
    }

    /**
     * @brief setFlag
     * @param entered
     */
    inline void setFlag(const int entered){
        flag = entered;
    }

    /**
     * @brief getFlag
     * @return
     */
    inline int getFlag(){return flag;}

    //Item methods
    int isItemInRoom(const string &);
    void removeItemFromRoom(const int &);
    Item* getItem(const string &);
    int numberOfItems();

    /**
     * @brief addItem
     * @param inItem
     */
    inline void addItem(Item *inItem) {
        itemsInRoom.push_back(inItem);
    }

    //Character methods
    int getCharacterPosition(const int &);

    /**
     * @brief setCharacterPosition
     * @param x
     * @param y
     */
    inline void setCharacterPosition(const int &x,const int &y){
        characterPosition.push_back(x);
        characterPosition.push_back(y);
    }



    //Door methods
    string unlockDoor(Hero*);
    bool checkDoor(const string &);

    /**
     * @brief addDoor
     * @param inDoor
     */
    inline void addDoor(Door *inDoor){
        doorsInRoom.push_back(inDoor);
    }


};


#endif
