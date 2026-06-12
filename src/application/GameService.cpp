#include "application/GameService.h"

#include "domain/CardQueue.h"

GameService::GameService(int maxMoves)
    : maxMoves_(maxMoves) {
}

GameResult GameService::play(const Deal& deal) const {
    validator_.validate(deal);

    CardQueue firstPlayerDeck;
    CardQueue secondPlayerDeck;

    for (int card : deal.firstPlayerCards) {
        firstPlayerDeck.push(card);
    }

    for (int card : deal.secondPlayerCards) {
        secondPlayerDeck.push(card);
    }

    int moveCount = 0;

    while (!firstPlayerDeck.empty() && !secondPlayerDeck.empty()
           && moveCount < maxMoves_) {
        int firstCard = firstPlayerDeck.pop();
        int secondCard = secondPlayerDeck.pop();
        ++moveCount;

        if (isFirstCardStronger(firstCard, secondCard)) {
            firstPlayerDeck.push(firstCard);
            firstPlayerDeck.push(secondCard);
        } else {
            secondPlayerDeck.push(firstCard);
            secondPlayerDeck.push(secondCard);
        }
    }

    if (!firstPlayerDeck.empty() && !secondPlayerDeck.empty()) {
        return GameResult{Winner::Botva, moveCount};
    }

    if (secondPlayerDeck.empty()) {
        return GameResult{Winner::First, moveCount};
    }

    return GameResult{Winner::Second, moveCount};
}

bool GameService::isFirstCardStronger(int firstCard, int secondCard) const {
    // Особое правило из задания: карта 0 побеждает карту 9.
    if (firstCard == 0 && secondCard == 9) {
        return true;
    }

    if (firstCard == 9 && secondCard == 0) {
        return false;
    }

    return firstCard > secondCard;
}
