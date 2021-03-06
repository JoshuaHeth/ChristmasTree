#ifndef DOOR_H
#define DOOR_H
#include "IEntry.h"


class Door:public IEntry
{
private:
    bool locked;
    string description,direction;
    int flag;


public:
    Door(string description,bool locked, string direction);
    ~Door();
    Door(const Door*);
    Door(const Door*, string description);

    inline void setDescription(string description)
    {
        this->description = description;
    }

    inline string getDescription(){
        return description;
    }

    inline bool getLock(){
        return locked;
    }

    inline void setLock(bool key){
        locked = key;
    }

    inline string getDirection(){
        return direction;
    }

};

#endif // DOOR_H

