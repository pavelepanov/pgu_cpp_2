#include "infrastructure/DealFileReader.h"

#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
std::array<int, 5> parseCardLine(const std::string& line) {
    std::array<int, 5> cards{};
    std::istringstream input(line);

    for (int i = 0; i < 5; ++i) {
        if (!(input >> cards[i])) {
            throw std::runtime_error(
                "Каждая строка файла должна содержать ровно пять целых чисел.");
        }
    }

    std::string extraToken;
    if (input >> extraToken) {
        throw std::runtime_error(
            "Каждая строка файла должна содержать ровно пять целых чисел.");
    }

    return cards;
}
}

Deal DealFileReader::readFromFile(const std::string& path) const {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть указанный файл.");
    }

    std::string firstLine;
    std::string secondLine;

    if (!std::getline(file, firstLine) || !std::getline(file, secondLine)) {
        throw std::runtime_error(
            "Файл должен содержать две строки по пять карт в каждой.");
    }

    Deal deal{parseCardLine(firstLine), parseCardLine(secondLine)};

    std::string extraLine;
    while (std::getline(file, extraLine)) {
        std::istringstream input(extraLine);
        std::string extraToken;
        if (input >> extraToken) {
            throw std::runtime_error(
                "Файл должен содержать только две непустые строки с картами.");
        }
    }

    return deal;
}
