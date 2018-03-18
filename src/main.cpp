#include <conio.h>
#include <chrono>
#include <thread>

#include "GameCtrl.hpp"
#include "CpuLogic.hpp"

int getInputKey()
{
  int input = _getch();

  if (input == 0xE0) {
    input = _getch();
  }

  return input;
}

int main()
{
  GameCtrl game;
  CpuLogic ai(game.getGameField(), game);
  game.init();

  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    system("cls");

    if (_kbhit())
    {
      int input = getInputKey();
      game.handleInput(input);
    }

    game.updateView();
    if (GameCtrl::GAMESTATE_IN_PROCESS == game.getGameState()) {
      ai.act();
      game.calculateProjectileHit();
      game.updateProjectiles();
    }
  }

  return 0;
}