#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
    int value;

public:
    Item (string description);
    ~Item();

    inline string getShortDescription(){
        return description;
    }

    inline string getLongDescription(){
        return " item(s), " + description + ".\n";
    }

    inline int getValue(){
        return value;
    }

    inline void setValue(int value){
        this->value=value;
    }

};

#endif /*ITEM_H_*/
