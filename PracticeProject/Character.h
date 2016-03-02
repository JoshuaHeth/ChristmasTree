#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "ZorkUL.h"
#include "mainwindow.h"
#include <vector>
#include <string>
#include "item.h"
using namespace std;
class Item;


class Character {
private:
     string description;
     vector < Item > itemsInCharacter;
public:
    void addItems(Item Item);
	Character(string description);
	string shortDescription();
	string longDescription();
    bool compareItems(string key);
    void displayItems();
    bool getItem(string itemDesc);
    vector<Item> getItems();
    int itemListSize();

};

#endif
