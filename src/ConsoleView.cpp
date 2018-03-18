#include <iostream>

#include "ConsoleView.hpp"

ConsoleView::ConsoleView(GameField& gameField) : gameField_(gameField)
{
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::printToConsole(int playerLives, int timer)
{
  // @todo: Create buffer of previous frame and redraw only changed cells
  //        to reduce flickering

  char symbol;
  for (int x = 0; x < gameField_.getHeigth(); x++) {
    for (int y = 0; y < gameField_.getWidth(); y++) {
      bool hasTank = false;
      bool hasWall = false;
      bool hasProjectile = false;

      for (int i = 0; i < gameField_.getTanks().size(); i++) {
        Coord pos;
        pos.x = x; pos.y = y;
        if (pos == gameField_.getTanks()[i]->getPos()) {
          hasTank = true;
          if (Actor::OWNER_CPU == gameField_.getTanks()[i]->getOwner()) {
            switch (gameField_.getTanks()[i]->getDirection()) {
              case Actor::DIRECTION_UP:
                symbol = '^';
                break;
              case Actor::DIRECTION_DOWN:
                symbol = 'v';
                break;
              case Actor::DIRECTION_LEFT:
                symbol = '<';
                break;
              case Actor::DIRECTION_RIGHT:
                symbol = '>';
                break;
            }
          } else  {
            switch (gameField_.getTanks()[i]->getDirection()) {
              case Actor::DIRECTION_UP:
                symbol = (char)193;
                break;
              case Actor::DIRECTION_DOWN:
                symbol = (char)194;
                break;
              case Actor::DIRECTION_LEFT:
                symbol = (char)180;
                break;
              case Actor::DIRECTION_RIGHT:
                symbol = (char)195;
                break;
            }
          }
        }
      }

      for (int i = 0; i < gameField_.getWalls().size(); i++) {
        Coord pos;
        pos.x = x; pos.y = y;
        if (pos == gameField_.getWalls()[i]->getPos()) {
          hasWall = true;
          if (true == gameField_.getWalls()[i]->isBreakable()) {
            symbol = (char)178;
          } else {
            symbol = (char)219;
          }
        }
      }

      for (int i = 0; i < gameField_.getProjectiles().size(); i++) {
        Coord pos;
        pos.x = x; pos.y = y;
        if (pos == gameField_.getProjectiles()[i]->getPos()) {
          hasProjectile = true;
          switch (gameField_.getProjectiles()[i]->getDirection()) {
            case Actor::DIRECTION_UP:
            case Actor::DIRECTION_DOWN:
              symbol = '|';
              break;
            case Actor::DIRECTION_LEFT:
            case Actor::DIRECTION_RIGHT:
              symbol = '-';
              break;
          }
        }
      }

      if (false == hasTank && false == hasWall && false == hasProjectile) {
        symbol = ' ';
      }

      if ((true == hasTank) && (true == hasProjectile) ||
          (true == hasWall) && (true == hasProjectile)) {
        symbol = '*';
      }

      std::cout << symbol;
    }

    std::cout << std::endl;
  }

  std::cout << "Lives: ";
  for (int i = 0; i < playerLives; i++) {
    std::cout << (char)248 << ' ';
  }

  std::cout << "\tTime: " << timer / 1000 << 's';
}

void ConsoleView::printVictory()
{
  std::cout << "Victory!";
}

void ConsoleView::printGameOver()
{
  std::cout << "GAME OVER";
}