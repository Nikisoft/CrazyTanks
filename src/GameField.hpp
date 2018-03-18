#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include <vector>

#include "Actor.hpp"
#include "Wall.hpp"

class GameField
{
  public:
    GameField(int height, int width);
    ~GameField();

    void clear();
    int getHeigth() const;
    int getWidth() const;
    std::vector<Wall*>& getWalls();
    std::vector<Actor*>& getTanks();
    std::vector<Actor*>& getProjectiles();
    bool isValidPos(Coord pos) const;

  private:
    GameField();
    GameField(const GameField& classRef);
    GameField& operator=(const GameField& classRef);

    int height_;
    int width_;
    std::vector<Wall*> walls_;
    std::vector<Actor*> tanks_;
    std::vector<Actor*> projectiles_;
};

#endif // GAMEFIELD_HPP