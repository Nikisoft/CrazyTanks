#ifndef GAMECTRL_HPP
#define GAMECTRL_HPP

#include "GameField.hpp"
#include "ConsoleView.hpp"

const int ARROW_UP = 72;
const int ARROW_DOWN = 80;
const int ARROW_LEFT = 75;
const int ARROW_RIGHT = 77;
const int SPACEBAR = 32;

const int GAMEFIELD_HEIGTH = 13;
const int GAMEFIELD_WIDTH = 25;
const int PLAYER_LIVES = 3;
const int NUMBER_OF_ENEMIES = 5;

class GameCtrl
{
  public:
    enum GameState {
      GAMESTATE_IN_PROCESS = 0,
      GAMESTATE_VICTORY = 1,
      GAMESTATE_GAMEOVER = 2
    };

    enum Command
    {
      COMMAND_MOVE_UP = 0,
      COMMAND_MOVE_DOWN = 1,
      COMMAND_MOVE_LEFT = 2,
      COMMAND_MOVE_RIGHT = 3,
      COMMAND_SHOOT = 4
    };

    GameCtrl();
    ~GameCtrl();

    void init();

    void generateBorderWalls();
    void generateWalls(int count);
    void spawnEnemyTanks(int count);
    void spawnPlayer();
    void spawnProjectile(const Actor& source);
    void moveTank(Actor& actor, Actor::Direction direction);
    void calculateProjectileHit();
    void updateProjectiles();
    void checkForVictory();
    Coord calculateNewPos(Coord pos, Actor::Direction direction);

    void handleInput(int key);
    void handleCpuCommand(Actor* tank, Command command);
    void handlePlayerCommand(Command command);
    void updateView();
    void changeGameState(GameState state);

    GameField& getGameField();
    GameState getGameState();
    int getPlayerLives();

  private:
    GameCtrl(const GameCtrl& classRef);
    GameCtrl& operator=(const GameCtrl& classRef);

    GameField gameField_;
    ConsoleView view_;
    int playerLives_;
    GameState gameState_;

};

#endif // GAMECTRL_HPP