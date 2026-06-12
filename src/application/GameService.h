#ifndef APPLICATION_GAME_SERVICE_H
#define APPLICATION_GAME_SERVICE_H

#include "application/DealValidator.h"
#include "domain/Deal.h"
#include "domain/GameResult.h"

class GameService {
public:
    explicit GameService(int maxMoves = 1000000);
    GameResult play(const Deal& deal) const;

private:
    bool isFirstCardStronger(int firstCard, int secondCard) const;

    int maxMoves_;
    DealValidator validator_;
};

#endif
