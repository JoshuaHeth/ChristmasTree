#ifndef HERO_H
#define HERO_H
#include "Character.h"
#include "item.h"
#include <vector>
class Item;

class Hero : public Character
{
private:
    vector < Item *> itemsInCharacter;

public:
    Hero(const string,const int);
    ~Hero();
    friend string getList(Hero*, Item*);

    /**
     * @brief whatAmI
     * @return
     */
    virtual string const whatAmI(){return "\nI am the Hero.";}

    void addItems(Item*);
    string displayItems();
    bool getItem(const string &);

    vector<Item*>getItems();
    int itemListSize();

    void deleteItem(const int &);

};

#endif // HERO_H
