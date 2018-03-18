#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "GameObject.hpp"

class Actor : public GameObject
{
  public:
    enum Owner
    {
      OWNER_NONE = -1,
      OWNER_PLAYER = 0,
      OWNER_CPU = 1
    };

    enum Direction
    {
      DIRECTION_NONE = -1,
      DIRECTION_UP = 0,
      DIRECTION_DOWN = 1,
      DIRECTION_LEFT = 2,
      DIRECTION_RIGHT = 3
    };

    Actor();
    ~Actor();

    void setDirection(Direction direction);
    void setOwner(Owner owner);

    Direction getDirection() const;
    Owner getOwner() const;

  private:
    Actor(const Actor& classRef);
    Actor& operator=(const Actor& classRef);

    Direction direction_;
    Owner owner_;
};

#endif // ACTOR_HPP