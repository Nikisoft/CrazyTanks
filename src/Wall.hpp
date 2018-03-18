#ifndef WALL_HPP
#define WALL_HPP

#include "GameObject.hpp"

class Wall : public GameObject
{
  public:
    Wall();
    ~Wall();

    void setBreakable(bool breakable);
    bool isBreakable() const;

  private:
    Wall(const Wall& classRef);
    Wall& operator=(const Wall& classRef);

    bool breakable_;
};

#endif // WALL_HPP