#include "door.h"

/**
     * @brief Door::Door
     * @param description
     * @param locked
     * @param direction
     */
    Door::Door(const string description,const bool locked,const string direction)
    {
      this->description = description;
      this->locked = locked;
      this->direction = direction;
    }

    /**
     * @brief Door::Door
     * @param dr
     */
    Door::Door(const Door* dr)
    {
        locked = dr->locked;
        direction = dr->direction;
        description = dr->description;
    }

    /**
     * @brief Door::Door
     * @param dr
     * @param description
     */
    Door::Door(const Door* dr,const string description)
    {
        locked = dr->locked;
        direction = dr->direction;
        setDescription(description);
    }







