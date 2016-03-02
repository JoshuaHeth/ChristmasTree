#include "item.h"

Item::Item (string inDescription)//, int inWeightGrams, float inValue/**, int weaponCheck*/) {
{
	description = inDescription;
    /*setWeight(inWeightGrams);
    value = inValue;
    weaponCheck(isWeapon);*/
}

/*Item::Item(string inDescription) {
	description = inDescription;
}


void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < LOOP_STARTER)
       cout << "weight invalid, must be LOOP_STARTER<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < LOOP_STARTER)
       cout << "value invalid, must be LOOP_STARTER<value<9999" ;
    else
	   value = inValue;
}

void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > LOOP_STARTER || isWeapon < LOOP_STARTER)
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

