#include "hero.h"

/**
 * @brief Hero::Hero
 * @param description
 * @param health
 */
Hero::Hero(const string description,const int health):Character(description,health)
{

}

/**
 * @brief Hero::addItems
 * @param itemCheck
 */
void Hero::addItems(Item *itemCheck) {
        itemsInCharacter.push_back(itemCheck);
}

/**
 * @brief Hero::displayItems
 * @return
 */
string Hero::displayItems()
{
    string ret;
    if(itemsInCharacter.size()>0)
    {
    ret+=("\nInventory \n");
    ret+=("_____________________________\n");

        for (vector<Item*>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
        {
            ret += (*i)->getShortDescription() + "\n";
        }
    }

    else
        ret = "\nYou have no items!!";

    return ret;
}

/**
 * @brief Hero::getItem
 * @param itemDesc
 * @return
 */
bool Hero:: getItem(const string &itemDesc)
{
    string ret;
    for (vector<Item*>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    {
        ret = (*i)->getShortDescription();
        if(ret.compare(itemDesc)== 0)
              return true;
    }

    return false;
}

/**
 * @brief Hero::getItems
 * @return
 */
vector<Item*> Hero:: getItems(){
    return itemsInCharacter;
}

/**
 * @brief Hero::itemListSize
 * @return
 */
int Hero:: itemListSize(){
    return itemsInCharacter.size();
}

/**
 * @brief Hero::deleteItem
 * @param index
 */
void Hero::deleteItem(const int &index){
    itemsInCharacter.erase(itemsInCharacter.begin()+index);
}
