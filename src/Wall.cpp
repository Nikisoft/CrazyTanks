#include "Wall.hpp"

Wall::Wall() : breakable_(true)
{

}

Wall::~Wall()
{

}

void Wall::setBreakable(bool breakable)
{
  breakable_ = breakable;
}

bool Wall::isBreakable() const
{
  return breakable_;
}