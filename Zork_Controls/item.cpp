#include "item.h"



Item::Item(string description) {
    this->description = description;
}
/*
Item::Item(string description, int value) {
    this->description = description;
    this->value = value;
}

Item::Item (string inDescription, int value, int weaponCheck) {
{
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
    weaponCheck(isWeapon);
}


void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > ZERO || isWeapon < ZERO)
        cout << "Item not a weapon" ;
    else
        cout << "Item is a weapon" ;
}*/

string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}

int Item::getValue()
{
    return value;
}

void Item::setValue(int value)
{
    this->value=value;
}
