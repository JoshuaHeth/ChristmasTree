#include "Character.h"

Character::Character(string description) {
    this->description = description;
}

void Character::addItems(Item item) {
    itemsInCharacter.push_back(item);
}

string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getLongDescription() + "\n";
  return ret;
}

bool Character::compareItems(string itemCheck)
{
  string ret;
  int size = itemsInCharacter.size();

  cout <<"Room: " << itemCheck << "\n";

  if(size > LOOP_STARTER)
  {
    //Test to see if keycard matches door description.
    for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    {
     ret = (*i).getShortDescription();
     cout << "Item : " << ret << endl;
        {
            if(ret.compare(itemCheck)==LOOP_STARTER)
            {
                itemsInCharacter.erase(i);
                return false;               //false unlocks the objects (Door/Stairwell).
            }
        }
    }
  }
  return true;

}

void Character::displayItems()
{
    int size = itemsInCharacter.size();
    string ret;
    cout << "Character items number: " << size << endl;
    for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    {
      ret = (*i).getShortDescription();
      {
          cout <<"\n"<< ret<< endl;
      }
    }
}

bool Character:: getItem(string itemDesc)
{
    string ret;
    for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    {
      ret = (*i).getShortDescription();

          if(ret.compare(itemDesc)== 0)
              return true;
    }

    return false;
}

vector<Item> Character:: getItems()
{
    return itemsInCharacter;
}

int Character:: itemListSize()
{
    return itemsInCharacter.size();
}


