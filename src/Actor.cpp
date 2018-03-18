#include "Actor.hpp"

Actor::Actor() : direction_(DIRECTION_UP), owner_(OWNER_NONE)
{
}

Actor::~Actor()
{
}

void Actor::setDirection(Direction direction)
{
  direction_ = direction;
}

void Actor::setOwner(Owner owner)
{
  owner_ = owner;
}

Actor::Direction Actor::getDirection() const
{
  return direction_;
}

Actor::Owner Actor::getOwner() const
{
  return owner_;
}