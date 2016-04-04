#include "hero.h"

Hero::Hero(string description, int health):Character(description,health)
{

}

void Hero::addItems(Item *itemCheck) {
        itemsInCharacter.push_back(itemCheck);
}

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

bool Hero:: getItem(string itemDesc)
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

vector<Item*> Hero:: getItems()
{
    return itemsInCharacter;
}

int Hero:: itemListSize()
{
    return itemsInCharacter.size();
}




void Hero::deleteItem(int &index)
{
    itemsInCharacter.erase(itemsInCharacter.begin()+index);
}
