#ifndef DOMAIN_GAME_RESULT_H
#define DOMAIN_GAME_RESULT_H

enum class Winner {
    First,
    Second,
    Botva
};

struct GameResult {
    Winner winner;
    int moveCount;
};

#endif
