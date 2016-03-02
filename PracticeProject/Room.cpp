#include "Room.h"
#include "Command.h"


Room::Room(string description) {
	this->description = description;
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

string Room::shortDescription() {
	return description;
}

string Room::longDescription() {
    //return "room = " + description + ".\n" + displayItem() + exitString();
    if (description.compare("Prison") == 0)
    {
       return "Room - Prison"
              "\n\nYou blearly open your eyes and groggily get to your feet. What happened?"
              "\nOh yeah, your vessel was raided by Narlak scum! Why did they keep you alive?"
              "\nWho knows?!"
              "\nYou look at your surroundings, looks like they've locked you into your prison."
              "\nWhat's that on the floor? Looks like the guard dropped the prison key card!"
              "\nNarlaks are tough, not to bright though!"
              "\n" + displayItem() + exitString();
    }
    else if (description.compare("Observation Room") == 0)
    {
        return "Room - Observation"
               "\n\nYou enter the observation room, there's a window with a stunning view of open space,"
               "\neven now it stops you in your tracks. How many hours have you spent gazing out at the"
               "\ninfinite beauty of the cosmos.....*cough* the Narlaks remember!"
               "\n"+ displayItem() + exitString();
    }
    else if (description.compare("Battle") == 0)
    {
        return "Room - Battle"
               "\nScenario 1(Unarmed) - You enter the room, the Narlak stops scratching his....Oh crap he's got"
               "\na gun. Of course he does you numpty, you think he raided the ship with his finger in his"
               "\npocket?! He growls something unintelligible and fires his gun. The world grows black."
               "\n\nScenario 2(Armed) - You burst into the room, John Wayne swagger down to a tee! Hand on your weapon,"
               "\nYou feelin' lucky punk? you say to the Narlak, of course he doesn't understand. He growls and starts to bring up his gun."
               "\nPew Pew Pew - you start blasting. You stand over your defeated foe, blow gently on the nozzle of your weapon. No smoke"
               "\ncoming out of it but it's a key part of a gun battle!"
               "\n" + displayItem() + exitString();
    }
    else if (description.compare("Stairwell Level 1") == 0)
    {
        return "Room - Main Stairwell"
               "\n\nYou enter the Main Stairwell, this is a spaceship for god's sake when are you going to"
               "\nupgrade to a bloody lift!"
               "\n\nExit(s) - Up - Observation"
               "\n\tRight - Hallway(Blocked)"
               "\n\tDown - Sickbay"
               "\n\tLeft(Descend) - Secondary Stairwell";
    }
    else if (description.compare("SickBay") == 0)
    {
        return "Room - Sick-bay"
               "\n\nScenario 1(Enter yourself) - You enter the Sickbay, not much in here but medical supplies."
               "\nScenario 2(Blasted by Narlak) - You wake up, cough, splutter, fall off the sick bed. Idiot! Confronting a Narlak"
               "\nunarmed, what did you think would happen? How did I get to the sick bay? Who knows?!"
               "\n\nExit(s) - Up - Main Stairwell";
    }
    else if (description.compare("Hallway of Something") == 0)
    {
        return "Room - Hallway of Soemthing"
               "\n\nSomething needs to be done here."
               "\n\nExit(s) - Up - Battle"
               "\n\tLeft(Blocked) - Main Stairwell"
               "\n\tRight - Cockpit";
    }
    else if (description.compare("Cockpit") == 0)
    {
        return "Room - Cockpit"
               "\n\nWell done you've reached the cockpit! You can go home now!"
               "\n\nExit(s) - Left - Hallway of Something";
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
     if(this->getDoor(direction).getLock()==true)
        {
            //cout << "Direction : " << direction << "\n" << endl;
            cout << this->getDoor(direction).getDescription() << " is locked." << endl;
            return NULL;
        }
    }

    //this->setEntered(1);
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

Door Room::getDoor(string direction)
{
    int x = doorsInRoom.size();

    for(int i = LOOP_STARTER;i<x;i++)
    {
     if(doorsInRoom[i].getDirection().compare(direction)==0)
         return doorsInRoom[i];
    }
}


void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

void Room::addDoor(Door *inDoor){
    doorsInRoom.push_back(*inDoor);
}


int Room::unlockDoor(vector<Item> list)
{
    int sizeDoors = doorsInRoom.size();
    int sizeItems = list.size();
    string doorName, itemName;

        for (int i = LOOP_STARTER; i<sizeDoors; i++)
        {
            if(doorsInRoom[i].getLock() == true)
            {
                doorName = doorsInRoom[i].getDescription()+"Keycard";
                for(int j = LOOP_STARTER; j<sizeItems; j++)
                    {
                        itemName = list[j].getShortDescription();
                        if(doorName.compare(itemName) == LOOP_STARTER)
                        {
                        /*If an item matched to a specific door
                            then delete the door
                              and stop all the loops.*/

                         //doorsInRoom[i].setLock(false);
                         doorsInRoom.erase(doorsInRoom.begin()+i);
                            return (j);
                        }

                     }
                cout <<"You don`t have the key!" << endl;
                return (-1);
            }
        }

        cout <<"All doors are unlocked!" << endl;
        return (-1);

}



string Room::displayDoor()
{
    string tempString = "door(s) in room = ";
    int sizeItems = (doorsInRoom.size());
    if (sizeItems < 1) {
        tempString = "\nNo doors in room";
        }
    else if (sizeItems > LOOP_STARTER) {
       int x = (LOOP_STARTER);
        for (int n = sizeItems; n > LOOP_STARTER; n--) {
            tempString = "\n"+tempString + doorsInRoom[x].getDescription()+" : " ;
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
    else if (sizeItems > LOOP_STARTER) {
       int x = (LOOP_STARTER);
        for (int n = sizeItems; n > LOOP_STARTER; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }


int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (sizeItems < 1) {
        return false;
        }
    else if (sizeItems > LOOP_STARTER) {
       int x = (LOOP_STARTER);
        for (int n = sizeItems; n > LOOP_STARTER; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == LOOP_STARTER) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

Item Room::getItem(string command)
{
    int sizeItems = (itemsInRoom.size());

       int x = (LOOP_STARTER);
        for (int n = sizeItems; n > LOOP_STARTER; n--)
        {
            if(itemsInRoom[x].getShortDescription().compare(command)==LOOP_STARTER)
                n = LOOP_STARTER;
            else
                x++;
        }
        return(itemsInRoom[x]);

}

bool Room::checkForDoor(string direction)
{
    int sizeItems = (doorsInRoom.size());

     if (sizeItems > LOOP_STARTER)
     {
       int x = LOOP_STARTER;
        for (int n = sizeItems; n > LOOP_STARTER; n--)
        {
            if(direction.compare(doorsInRoom[x].getDirection())==LOOP_STARTER)
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

