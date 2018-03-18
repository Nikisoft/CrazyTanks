#include <math.h>
#include "CpuLogic.hpp"

CpuLogic::CpuLogic(GameField& gameField, GameCtrl& gameCtrl)
: gameField_(gameField),
  gameCtrl_(gameCtrl),
  actDelay_(ACTION_DELAY)
{
}

CpuLogic::~CpuLogic()
{
}

void CpuLogic::act()
{
  if (actDelay_ == 0) {
    if (GameCtrl::GAMESTATE_IN_PROCESS == gameCtrl_.getGameState()) {
      for (int i = 0; i < gameField_.getTanks().size(); i++) {
        if (Actor::OWNER_CPU == gameField_.getTanks()[i]->getOwner()) {
          desideNextMove(gameField_.getTanks()[i]);
        }
      }
    }
    actDelay_ = ACTION_DELAY;
  } else {
    actDelay_--;
  }
}

void CpuLogic::desideNextMove(Actor* cpuTank)
{
  Actor* player = 0;
  for (int i = 0; i < gameField_.getTanks().size(); i++) {
    if (Actor::OWNER_PLAYER == gameField_.getTanks()[i]->getOwner()) {
      player = gameField_.getTanks()[i];
    }
  }

  do {
    Actor::Direction desiredCpuDirection = Actor::DIRECTION_NONE;
    Actor::Direction directionToPlayerX = Actor::DIRECTION_NONE;
    Actor::Direction directionToPlayerY = Actor::DIRECTION_NONE;
    int distanceX = abs(cpuTank->getPos().x - player->getPos().x);
    int distanceY = abs(cpuTank->getPos().y - player->getPos().y);

    if (cpuTank->getPos().x < player->getPos().x) {
      directionToPlayerX = Actor::DIRECTION_DOWN;
    } else {
      directionToPlayerX = Actor::DIRECTION_UP;
    }

    if (cpuTank->getPos().y < player->getPos().y) {
      directionToPlayerY = Actor::DIRECTION_RIGHT;
    } else {
      directionToPlayerY = Actor::DIRECTION_LEFT;
    }

    if (cpuTank->getPos().x == player->getPos().x) {
      desiredCpuDirection = directionToPlayerY;
      cpuTank->setDirection(desiredCpuDirection);
      gameCtrl_.spawnProjectile(*cpuTank);
      break;
    } else if (cpuTank->getPos().y == player->getPos().y) {
      desiredCpuDirection = directionToPlayerX;
      cpuTank->setDirection(desiredCpuDirection);
      gameCtrl_.spawnProjectile(*cpuTank);
      break;
    }

    if (distanceX > distanceY) {
      desiredCpuDirection = directionToPlayerY;
    } else if (distanceX < distanceY) {
      desiredCpuDirection = directionToPlayerX;
    }

    Coord nextPos = gameCtrl_.calculateNewPos(cpuTank->getPos(),
                                              desiredCpuDirection);
    if (true == gameField_.isValidPos(nextPos)) {
      gameCtrl_.moveTank(*cpuTank, desiredCpuDirection);
    } else {
      cpuTank->setDirection(desiredCpuDirection);
      gameCtrl_.spawnProjectile(*cpuTank);
    }
  } while (false);
}