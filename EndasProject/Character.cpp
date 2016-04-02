#include "Character.h"

Character::Character(string description, int health) {
    this->description = description;
    this->health = health;
    //setPixmap(QPixmap(":/pacman.png"));
}





void Character::setHealth(int health)
{
    this->health += health;

        if(this->health < 0)
            this->health = 1;


        else if(this->health > 500)
            this->health = 500;

}
