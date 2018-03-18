#include "GameField.hpp"

#include <cstdlib>

GameField::GameField(int height, int width) : height_(height), width_(width) {
}

GameField::~GameField() {
  clear();
}

void GameField::clear()
{
  for (int i = 0; i < walls_.size(); i++)
    delete walls_[i];

  for (int i = 0; i < tanks_.size(); i++)
    delete tanks_[i];

  for (int i = 0; i < projectiles_.size(); i++)
    delete projectiles_[i];
}

int GameField::getHeigth() const
{
  return height_;
}

int GameField::getWidth() const
{
  return width_;
}

std::vector<Wall*>& GameField::getWalls() {
  return walls_;
}

std::vector<Actor*>& GameField::getTanks() {
  return tanks_;
}

std::vector<Actor*>& GameField::getProjectiles() {
  return projectiles_;
}

bool GameField::isValidPos(Coord pos) const
{
  bool result = true;

  do {
    if (pos.x > height_ || pos.y > width_) {
      result = false;
      break;
    }

    for (int i = 0; i < walls_.size(); i++)
      if ((pos.x == walls_.at(i)->getPos().x) &&
          (pos.y == walls_.at(i)->getPos().y))
        result = false;

    for (int i = 0; i < tanks_.size(); i++)
      if ((pos.x == tanks_.at(i)->getPos().x) &&
          (pos.y == tanks_.at(i)->getPos().y))
        result = false;
  } while (false);

  return result;
}
