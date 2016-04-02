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


    string longDescription();

    void addItems(Item *Item);
    //bool compareItems(string key);
    string displayItems();
    bool getItem(string itemDesc);

    vector<Item*>getItems();
    int itemListSize();

    //Use pointers to achieve this optimally
    void deleteItem(int index);

};

#endif // HERO_H
