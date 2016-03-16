#include "Character.h"

Character::Character(string description, int health) {
    this->description = description;
    this->health = health;
}

void Character::addItems(Item *itemCheck) {

        itemsInCharacter.push_back(itemCheck); //Add item if not in list.


}

string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item *>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i)->getLongDescription() + "\n";
  return ret;
}

/*bool Character::compareItems(string itemCheck)
{
  string ret;
  int size = itemsInCharacter.size();

  cout <<"Room: " << itemCheck << "\n";

  if(size > ZERO)
  {
    //Test to see if keycard matches door description.
    for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    {
     ret = (*i).getShortDescription();
     cout << "Item : " << ret << endl;
        {
            if(ret.compare(itemCheck)==ZERO)
            {
                itemsInCharacter.erase(i);
                return false;               //false unlocks the objects (Door/Stairwell).
            }
        }
    }
  }
  return true;

}*/

string Character::displayItems()
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

bool Character:: getItem(string itemDesc)
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

vector<Item*> Character:: getItems()
{
    return itemsInCharacter;
}

int Character:: itemListSize()
{
    return itemsInCharacter.size();
}

int Character::getHealth()
{
    return health;
}

void Character::setHealth(int health)
{
    this->health += health;

        if(this->health < 0)
            this->health = 1;


        else if(this->health > 500)
            this->health = 500;

}

void Character::deleteItem(int index)
{
    itemsInCharacter.erase(itemsInCharacter.begin()+index);
}


