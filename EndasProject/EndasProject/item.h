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
    Item (const string);
    ~Item();
    friend string getList(Hero*, Item*);

    /**
     * @brief getShortDescription
     * @return
     */
    inline string getShortDescription(){
        return description;
    }


};

#endif /*ITEM_H_*/
