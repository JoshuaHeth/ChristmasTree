#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;
class Hero;

class Item {
private:
    string description;

public:
    Item (string description);
    ~Item();
    friend string getList(Hero*, Item*);

    inline string getShortDescription(){
        return description;
    }


};

#endif /*ITEM_H_*/
