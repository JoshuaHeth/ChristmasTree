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

    Character(const string,const int);
    ~Character(){}
    void setHealth(const int);

    /**
     * @brief getHealth
     * @return
     */
    inline int getHealth(){
        return health;
    }

    /**
     * @brief getDescription
     * @return
     */
    inline string getDescription(){
        return description;
    }

    /**
     * @brief operator -
     * @param c
     * @return
     */
    Character& operator-(Character &c)
        {
           this->health = this->getHealth()-c.getHealth();
           return *this;
        }

    /**
     * @brief whatAmI
     * @return
     */
    virtual string const whatAmI(){return "\nThat is a Narlak!!!\nShoot him now.";}




};

#endif
