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
    //~Character();

    inline int getHealth(){
        return health;
    }

    void setHealth(int health);


    inline string getDescription(){
        return description;
    }

/*
    Character operator-(Character& c){
        {
            cout<<"Entered method"<<endl;
            int x = this->getHealth();
            cout<<x<<endl;
            int y = c.getHealth();
            cout<<y<<endl;
            int z = x-y;
            cout<<z<<endl;

          return Character("Result",z);
        }
    };*/

};

#endif
