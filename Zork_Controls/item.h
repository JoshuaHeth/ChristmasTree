#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
    int value;
	bool weaponCheck;

public:
    //Item (string description, int inWeight, float inValue);
    Item (string description);
    //~Item();

	string getShortDescription();
    string getLongDescription();
    int getValue();
    void setValue(int value);
	int getWeaponCheck();
	void setWeaponCheck(int weaponCheck);
};

#endif /*ITEM_H_*/
