#include "Character.h"

/**
 * @brief Character::Character
 * @param description
 * @param health
 */
Character::Character(const string description,const int health) {
    this->description = description;
    this->health = health;
}

/**
 * @brief Character::setHealth
 * @param health
 */
void Character::setHealth(const int health)
{
    this->health += health;

        if(this->health < 0)
            this->health = 1;


        else if(this->health > 500)
            this->health = 500;

}



