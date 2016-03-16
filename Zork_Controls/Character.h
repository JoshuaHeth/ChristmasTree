#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "mainwindow.h"
#include <vector>
#include <string>
#include "item.h"
using namespace std;
class Item;


class Character {
private:
     string description;
     int health;
     vector < Item *> itemsInCharacter;
public:

    Character(string description, int health);
    //~Character();

	string shortDescription();
	string longDescription();

    void addItems(Item *Item);
    //bool compareItems(string key);
    string displayItems();
    bool getItem(string itemDesc);

    vector<Item*>getItems();
    int itemListSize();
    int getHealth();
    void setHealth(int health);

    //Use pointers to achieve this optimally
    void deleteItem(int index);



};

#endif
