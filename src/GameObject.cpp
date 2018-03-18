#include "GameObject.hpp"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(Coord pos)
{
  pos_ = pos;
}

Coord GameObject::getPos() const
{
  return pos_;
}