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
    Door(const string,const bool,const string);
    ~Door();
    Door(const Door*);
    Door(const Door*,const string);

    /**
     * @brief setDescription
     * @param description
     */
    inline void setDescription(string description)
    {
        this->description = description;
    }

    /**
     * @brief getDescription
     * @return
     */
    inline string getDescription(){
        return description;
    }

    /**
     * @brief getLock
     * @return
     */
    inline bool getLock(){
        return locked;
    }

    /**
     * @brief setLock
     * @param key
     */
    inline void setLock(const bool &key){
        locked = key;
    }

    /**
     * @brief getDirection
     * @return
     */
    inline string getDirection(){
        return direction;
    }

};

#endif // DOOR_H

