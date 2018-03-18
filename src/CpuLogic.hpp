#ifndef CPULOGIC_HPP
#define CPULOGIC_HPP

#include "GameField.hpp"
#include "GameCtrl.hpp"

class CpuLogic
{
  public:
    static const int ACTION_DELAY = 7;

    CpuLogic(GameField& gameField, GameCtrl& gameCtrl);
    ~CpuLogic();

    void act();
    void desideNextMove(Actor* cpuTank);

  private:
    CpuLogic();
    CpuLogic(const CpuLogic& classRef);
    CpuLogic& operator=(const CpuLogic& classRef);

    GameField& gameField_;
    GameCtrl& gameCtrl_;
    int actDelay_;
};

#endif // CPULOGIC_HPP