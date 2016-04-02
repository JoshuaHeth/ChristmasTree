#ifndef DOOR_H
#define DOOR_H
#include "entry_interface.h"


class Door:public entry_interface
{
private:
    bool locked;
    string description,direction;
    int flag;


public:
    Door(string description,bool locked, string direction);
    ~Door();

    inline bool getLock(){
        return locked;
    }

    inline string getDescription(){
        return description;
    }

    inline void setLock(bool key){
        locked = key;
    }

    inline string getDirection(){
        return direction;
    }

};

#endif // DOOR_H

