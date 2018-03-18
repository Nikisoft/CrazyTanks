#include <cstdlib>
#include <time.h>
#include "GameCtrl.hpp"

GameCtrl::GameCtrl()
: gameField_(GAMEFIELD_HEIGTH, GAMEFIELD_WIDTH),
  view_(gameField_),
  playerLives_(PLAYER_LIVES)
{
}

GameCtrl::~GameCtrl()
{
}

void GameCtrl::init()
{
  srand(time(0));
  spawnPlayer();
  const int wallCount = (gameField_.getHeigth() * gameField_.getHeigth()) / 4;
  generateWalls(wallCount);
  spawnEnemyTanks(NUMBER_OF_ENEMIES);
}

void GameCtrl::generateBorderWalls()
{
  Coord pos;
  Wall* wall = 0;

  for (int i = 1; i < gameField_.getHeigth() -1; i++) {
    wall = new Wall();
    pos.x = i;
    pos.y = 0;
    wall->setPosition(pos);
    wall->setBreakable(false);
    gameField_.getWalls().push_back(wall);

    wall = new Wall();
    pos.x = i;
    pos.y = gameField_.getWidth() - 1;
    wall->setPosition(pos);
    wall->setBreakable(false);
    gameField_.getWalls().push_back(wall);
  }

  for (int i = 1; i < gameField_.getWidth() -1; i++) {
    wall = new Wall();
    pos.x = 0;
    pos.y = i;
    wall->setPosition(pos);
    wall->setBreakable(false);
    gameField_.getWalls().push_back(wall);

    wall = new Wall();
    pos.x = gameField_.getHeigth() - 1;
    pos.y = i;
    wall->setPosition(pos);
    wall->setBreakable(false);
    gameField_.getWalls().push_back(wall);
  }

  wall = new Wall();
  pos.x = gameField_.getHeigth() - 1;
  pos.y = gameField_.getWidth() - 1;
  wall->setPosition(pos);
  wall->setBreakable(false);
  gameField_.getWalls().push_back(wall);

  wall = new Wall();
  pos.x = 0;
  pos.y = gameField_.getWidth() - 1;
  wall->setPosition(pos);
  wall->setBreakable(false);
  gameField_.getWalls().push_back(wall);

  wall = new Wall();
  pos.x = gameField_.getHeigth() - 1;
  pos.y = 0;
  wall->setPosition(pos);
  wall->setBreakable(false);
  gameField_.getWalls().push_back(wall);

  wall = new Wall();
  pos.x = 0;
  pos.y = 0;
  wall->setPosition(pos);
  wall->setBreakable(false);
  gameField_.getWalls().push_back(wall);
}

void GameCtrl::generateWalls(int count)
{
  generateBorderWalls();

  int i = 0;
  while (i < count) {
    Coord pos;
    pos.x = rand() % gameField_.getHeigth();
    pos.y = rand() % gameField_.getWidth();

    if (false == gameField_.isValidPos(pos)) continue;

    Wall* wall = new Wall();
    wall->setPosition(pos);
    gameField_.getWalls().push_back(wall);

    i++;
  }
}

void GameCtrl::spawnEnemyTanks(int count)
{
  int i = 0;
  while (i < count)
  {
    Coord pos;
    pos.x = rand() % gameField_.getHeigth();
    pos.y = rand() % gameField_.getWidth();

    if (false == gameField_.isValidPos(pos)) continue;

    Actor* tank = new Actor();
    tank->setPosition(pos);
    tank->setOwner(Actor::OWNER_CPU);
    gameField_.getTanks().push_back(tank);

    i++;
  }
}

void GameCtrl::spawnPlayer()
{
  Actor* player = new Actor();
  Coord pos;
  pos.x = gameField_.getHeigth() - 2;
  pos.y = gameField_.getWidth() / 2;

  player->setPosition(pos);
  player->setOwner(Actor::OWNER_PLAYER);
  gameField_.getTanks().push_back(player);
}

void GameCtrl::spawnProjectile(const Actor& source)
{
  Actor* projectile = new Actor();
  Coord pos = calculateNewPos(source.getPos(), source.getDirection());
  projectile->setPosition(pos);
  projectile->setDirection(source.getDirection());
  projectile->setOwner(source.getOwner());
  gameField_.getProjectiles().push_back(projectile);
}

void GameCtrl::calculateProjectileHit()
{
  for (int i = 0; i < gameField_.getProjectiles().size(); i++) {
    Coord pos = gameField_.getProjectiles()[i]->getPos();

    for (int k = 0; k < gameField_.getTanks().size(); k++) {
      if (pos == gameField_.getTanks()[k]->getPos()) {

        if (gameField_.getTanks()[k]->getOwner() ==
            gameField_.getProjectiles()[i]->getOwner()) {
          delete gameField_.getProjectiles()[i];
          gameField_.getProjectiles().erase(
              gameField_.getProjectiles().begin() + i);

          break;
        }

        if (Actor::OWNER_PLAYER == gameField_.getTanks()[k]->getOwner()) {
          playerLives_--;
          if (0 != playerLives_) {
            spawnPlayer();
          } else {
            changeGameState(GameCtrl::GAMESTATE_GAMEOVER);
          }
        }

        delete gameField_.getTanks()[k];
        gameField_.getTanks().erase(gameField_.getTanks().begin() + k);

        delete gameField_.getProjectiles()[i];
        gameField_.getProjectiles().erase(
            gameField_.getProjectiles().begin() + i);

        break;
      }
    }

    for (int k = 0; k < gameField_.getWalls().size(); k++) {
      if ((pos == gameField_.getWalls()[k]->getPos()) &&
          (true == gameField_.getWalls()[k]->isBreakable())) {
        delete gameField_.getWalls()[k];
        gameField_.getWalls().erase(gameField_.getWalls().begin() + k);

        delete gameField_.getProjectiles()[i];
        gameField_.getProjectiles().erase(
            gameField_.getProjectiles().begin() + i);

        break;
      }
    }
  }

  checkForVictory();
}

void GameCtrl::checkForVictory()
{
  bool victory = true;
  for (int i = 0; i < gameField_.getTanks().size(); i++) {
    if (Actor::OWNER_CPU == gameField_.getTanks()[i]->getOwner()) {
      victory = false;
    }
  }

  if (true == victory) changeGameState(GAMESTATE_VICTORY);
}

void GameCtrl::updateProjectiles()
{
  for (int i = 0; i < gameField_.getProjectiles().size(); i++) {
    Coord pos = gameField_.getProjectiles()[i]->getPos();
    Actor::Direction direction = gameField_.getProjectiles()[i]->getDirection();
    gameField_.getProjectiles()[i]->setPosition(calculateNewPos(pos,direction));
  }
}

void GameCtrl::moveTank(Actor& actor, Actor::Direction direction)
{
  actor.setDirection(direction);
  Coord newPos = calculateNewPos(actor.getPos(), direction);

  if (true == gameField_.isValidPos(newPos)) {
    actor.setPosition(newPos);
  }
}

Coord GameCtrl::calculateNewPos(Coord pos, Actor::Direction direction)
{
  switch (direction) {
    case Actor::DIRECTION_UP:
      pos.x--;
      break;
    case Actor::DIRECTION_DOWN:
      pos.x++;
      break;
    case Actor::DIRECTION_LEFT:
      pos.y--;
      break;
    case Actor::DIRECTION_RIGHT:
      pos.y++;
      break;
  }

  return pos;
}

void GameCtrl::handleInput(int key)
{
  switch (key) {
    case ARROW_UP:
      handlePlayerCommand(COMMAND_MOVE_UP);
      break;
    case ARROW_DOWN:
      handlePlayerCommand(COMMAND_MOVE_DOWN);
      break;
    case ARROW_LEFT:
      handlePlayerCommand(COMMAND_MOVE_LEFT);
      break;
    case ARROW_RIGHT:
      handlePlayerCommand(COMMAND_MOVE_RIGHT);
      break;
    case SPACEBAR:
      handlePlayerCommand(COMMAND_SHOOT);
      break;
  }
}

void GameCtrl::handleCpuCommand(Actor* tank, Command command)
{

}

void GameCtrl::handlePlayerCommand(Command command)
{
  for (int i = 0; i < gameField_.getTanks().size(); i++) {
    if (Actor::OWNER_PLAYER == gameField_.getTanks().at(i)->getOwner()) {
      switch (command) {
        case COMMAND_MOVE_UP:
          moveTank(*gameField_.getTanks().at(i), Actor::DIRECTION_UP);
          break;
        case COMMAND_MOVE_DOWN:
          moveTank(*gameField_.getTanks().at(i), Actor::DIRECTION_DOWN);
          break;
        case COMMAND_MOVE_LEFT:
          moveTank(*gameField_.getTanks().at(i), Actor::DIRECTION_LEFT);
          break;
        case COMMAND_MOVE_RIGHT:
          moveTank(*gameField_.getTanks().at(i), Actor::DIRECTION_RIGHT);
          break;
        case COMMAND_SHOOT:
          spawnProjectile(*gameField_.getTanks().at(i));
          break;
      }
    }
  }
}

void GameCtrl::updateView()
{
  switch (gameState_) {
    case GAMESTATE_IN_PROCESS:
      view_.printToConsole(playerLives_, clock());
      break;
    case GAMESTATE_VICTORY:
      view_.printVictory();
      break;
    case GAMESTATE_GAMEOVER:
      view_.printGameOver();
      break;
  }
}

GameField& GameCtrl::getGameField()
{
  return gameField_;
}

void GameCtrl::changeGameState(GameState state)
{
  gameState_ = state;
}

GameCtrl::GameState GameCtrl::getGameState()
{
  return gameState_;
}

int GameCtrl::getPlayerLives()
{
  return playerLives_;
}