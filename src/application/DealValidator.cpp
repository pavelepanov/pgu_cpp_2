#include "application/DealValidator.h"

#include <array>
#include <stdexcept>
#include <string>

namespace {
void checkCard(int card, std::array<bool, 10>& usedCards) {
    if (card < 0 || card > 9) {
        throw std::invalid_argument(
            "Значение карты должно быть в диапазоне от 0 до 9.");
    }

    if (usedCards[card]) {
        throw std::invalid_argument("Все карты в раздаче должны быть различными.");
    }

    usedCards[card] = true;
}
}

void DealValidator::validate(const Deal& deal) const {
    std::array<bool, 10> usedCards{};

    for (int card : deal.firstPlayerCards) {
        checkCard(card, usedCards);
    }

    for (int card : deal.secondPlayerCards) {
        checkCard(card, usedCards);
    }
}
