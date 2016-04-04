#include "door.h"


    Door::Door(string description,bool locked, string direction)
    {
      this->description = description;
      this->locked = locked;
      this->direction = direction;
    }

    Door::Door(const Door* dr)
    {
        locked = dr->locked;
        direction = dr->direction;
        description = dr->description;
    }

    Door::Door(const Door* dr, string description)
    {
        locked = dr->locked;
        direction = dr->direction;
        setDescription(description);
    }







