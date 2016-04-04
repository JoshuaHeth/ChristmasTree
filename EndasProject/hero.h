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
    Hero(string description, int health);
    ~Hero();
    friend string getList(Hero*, Item*);

    virtual string const whatAmI(){return "\nI am the Hero.";}

    void addItems(Item *Item);
    string displayItems();
    bool getItem(string itemDesc);

    vector<Item*>getItems();
    int itemListSize();

    void deleteItem(int &);

};

#endif // HERO_H
