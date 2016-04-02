#include "Room.h"



Room::Room(string description, int flag) {
    this->description = description;
    this->flag = flag;
}

void Room::setExits(Room *up, Room *right, Room *down, Room *left) {
    if (up != NULL)
        exits["up"] = up;
    if (right != NULL)
        exits["right"] = right;
    if (down != NULL)
        exits["down"] = down;
    if (left != NULL)
        exits["left"] = left;
}

string Room::longDescription() {
    if (description.compare("Prison") == 0)
    {
        if(flag == 0)
        {
           return "Room - Prison"
                  "\n\nYou blearly open your eyes and groggily get to your feet. What happened?"
                  "\nOh yeah, your vessel was raided by Narlak scum! Why did they keep you alive?"
                  "\nWho knows?!"
                  "\nYou look at your surroundings, looks like they've locked you into your prison."
                  "\nWhat's that on the floor? Looks like the guard dropped the prison key card!"
                  "\nNarlaks are tough, not to bright though!";
        }
        else
        {
            return "Room - Prison"
                   "\n\nYou were already in here, nothing to see!";
        }
    }
    else if (description.compare("Observation_Room") == 0)
    {
        return "Room - Observation"
               "\n\nYou enter the observation room, there's a window with a stunning view of open space,"
               "\neven now it stops you in your tracks. How many hours have you spent gazing out at the"
               "\ninfinite beauty of the cosmos.....*cough* the Narlaks remember!";
    }
    else if (description.compare("Battle") == 0)
    {
        if(flag == 0)
        {
            return "Room - Battle"
                   "\n\nYou enter the room, the Narlak stops scratching his....Oh crap he's got"
                   "\na gun. Of course he does you numpty, you think he raided the ship with his"
                   "\nfinger in his pocket?! He growls something unintelligible and fires his gun."
                   "\nThe world grows black.";
        }
        else
        {
            return  "Room - Battle"
                    "\n\nYou burst into the room, John Wayne swagger down to a tee! Hand on your weapon,"
                    "\nYou feelin' lucky punk? you say to the Narlak, of course he doesn't understand. "
                    "\nHe growls and starts to bring up his gun. Pew Pew Pew - you start blasting. You "
                    "\nstand over your defeated foe, blow gently on the nozzle of your weapon. No smoke"
                    "\ncoming out of it but it's a key part of a gun battle!";
        }
    }
    else if (description.compare("Stairwell_Level_1") == 0)
    {
        return "Room - Main Stairwell"
               "\n\nYou enter the Main Stairwell, this is a spaceship for god's sake when are you going to"
               "\nupgrade to a bloody lift!";
    }
    else if (description.compare("SickBay") == 0)
    {
        if(flag == 0)
        {
            return "Room - Sick-bay"
                   "\n\nYou enter the Sickbay, not much in here but medical supplies.";
        }
        else
        {
            return "Room - Sick-bay"
                   "\n\nYou wake up, cough, splutter, fall off the sick bed. Idiot! Confronting a Narlak"
                   "\nunarmed, what did you think would happen? How did I get to the sick bay? Who knows?!";
        }
    }
    else if (description.compare("Hallway") == 0)
    {
        return "Room - Hallway"
               "\n\nYou enter the hallway, a robot is blocking your way to the cockpit. Laser guns pointed"
               "\ndirectly at you!"
               "\n\"You may not pass until you've answered my riddle!\", the robot says.";
    }
    else if (description.compare("Cockpit") == 0)
    {
        return "Room - Cockpit"
               "\n\nWell done you've reached the cockpit! You can go home now!";
    }
    else
        return "";
}

string Room::exitString() {
    string returnString = "\nExits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

//need to pass pointer to current room
Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.

    //Check if door in that direction is locked, if so stop access.
    else if (checkForDoor(direction) == true)
    {
     if(this->getDoor(direction)->getLock()==true)
        {

            //cout << this->getDoor(direction)->getDescription() << " is locked." << endl;
            return NULL;
        }
    }

    //this->setEntered(1);
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

Door* Room::getDoor(string direction)
{
    int x = doorsInRoom.size();
    int i =0;

    while(i<x && x!=0)
    {
     if(doorsInRoom[i]->getDirection().compare(direction)==0)
         x=0;

     else
         i++;
    }
    return doorsInRoom[i];
}


void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(inItem);
}

void Room::addDoor(Door *inDoor){
    doorsInRoom.push_back(inDoor);
}


string Room::unlockDoor(Hero *testCharacter)
{
    int sizeDoors = doorsInRoom.size();
    int sizeItems = testCharacter->itemListSize();
    bool found;
    string doorName;

        for (int i = 0; i<sizeDoors; i++)
        {
            if(doorsInRoom[i]->getLock() == true)
            {
                doorName = doorsInRoom[i]->getDescription()+"Keycard";
                for(int j = 0; j<sizeItems; j++)
                    {
                        //itemName = list[j].getShortDescription();
                        found =  testCharacter->getItem(doorName);
                        if(found)
                        {
                        /*If an item matched to a specific door
                            then return door name and delete used item.*/
                            testCharacter->deleteItem(j);
                            doorsInRoom[i]->setLock(false);
                            return (doorsInRoom[i]->getDescription());
                        }

                     }
                return "You don`t have the key!";
            }
        }

        return "All doors are unlocked in current room!";

}



string Room::displayDoor()
{
    string tempString = "door(s) in room = ";
    int sizeItems = (doorsInRoom.size());
    if (sizeItems < 1) {
        tempString = "\nNo doors in room";
        }
    else if (sizeItems > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = "\n"+tempString + doorsInRoom[x]->getDescription()+" : " ;
            x++;
            }
        }
    return tempString;
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (sizeItems < 1) {
        tempString = "\nNo items in room";
        }
    else if (sizeItems > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x]->getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }


int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (sizeItems < 1)
        return false;

    else
        {
        for (int n = 0; n < sizeItems; n++) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[n]->getShortDescription());

                if (tempFlag == 0)
                    return true;

            }
        }
    return false;
}

Item* Room::getItem(string command)
{
    int sizeItems = (itemsInRoom.size());

       int x = (0);
        for (int n = sizeItems; n > 0; n--)
        {
            if(itemsInRoom[x]->getShortDescription().compare(command)==0)
                n = 0;
            else
                x++;
        }
        return(itemsInRoom[x]);

}

bool Room::checkForDoor(string direction)
{
    int sizeItems = (doorsInRoom.size());

     if (sizeItems > 0)
     {
       int x = 0;
        for (int n = sizeItems; n > 0; n--)
        {
            if(direction.compare(doorsInRoom[x]->getDirection())==0)
                return true;
            else
                x++;
        }
     }

    return false;
}

vector<int> Room::getCharacterPosition()
{
    return characterPosition;
}

void Room::setCharacterPosition(int x, int y)
{
    characterPosition.push_back(x);
    characterPosition.push_back(y);
}


void Room :: setFlag(int entered)
{
    flag = entered;
}

int Room :: getFlag()
{
    return flag;
}
