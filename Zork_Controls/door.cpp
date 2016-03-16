#include "door.h"


    Door::Door(string description,bool locked, string direction)
    {
      this->description = description;
      this->locked = locked;
      this->direction = direction;
    }

    bool Door::getLock()
    {
        return locked;
    }



    string Door::getDescription()
    {
        return description;
    }

    void Door::setLock(bool key)
    {
        locked = key;
    }

    string Door::getDirection()
    {
        return direction;
    }










