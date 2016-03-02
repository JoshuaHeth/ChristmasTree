#ifndef DOOR_H
#define DOOR_H
#include "entry_interface.h"


class Door:public entry_interface
{
private:
    bool locked;
    string description,direction;


public:
    Door(string description,bool locked, string direction);
    bool getLock();
    string getDescription();
    void setLock(bool key);
    string getDirection();
};

#endif // DOOR_H
