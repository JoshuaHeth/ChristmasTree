#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <iostream>
using namespace std;


class Character {
private:

protected:
    string description;
    int health;

public:

    Character(string description, int health);
    ~Character(){}

    virtual string const whatAmI(){return "\nThat is a Narlak!!!\nShoot him now.";}

    inline int getHealth(){
        return health;
    }

    void setHealth(int health);


    inline string getDescription(){
        return description;
    }



    Character& operator-(Character &c)
        {
           this->health = this->getHealth()-c.getHealth();
           return *this;
        }




};

#endif
