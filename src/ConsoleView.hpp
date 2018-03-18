#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include "GameField.hpp"

class ConsoleView
{
  public:
    ConsoleView(GameField& gameField);
    ~ConsoleView();

    void printToConsole(int playerLives, int timer);
    void printVictory();
    void printGameOver();

  private:
    ConsoleView();
    ConsoleView(const ConsoleView& classRef);
    ConsoleView& operator=(const ConsoleView& classRef);

    GameField& gameField_;
};

#endif // CONSOLEVIEW_HPP