#include "presentation/ConsoleMenu.h"

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
std::array<int, 5> parseCardLine(const std::string& line) {
    std::array<int, 5> cards{};
    std::istringstream input(line);

    for (int i = 0; i < 5; ++i) {
        if (!(input >> cards[i])) {
            throw std::invalid_argument("Введите ровно пять целых чисел.");
        }
    }

    std::string extraToken;
    if (input >> extraToken) {
        throw std::invalid_argument("Введите ровно пять целых чисел.");
    }

    return cards;
}

int readMenuOption(const std::string& line) {
    std::istringstream input(line);
    int option = -1;

    if (!(input >> option)) {
        throw std::invalid_argument("Пункт меню должен быть числом.");
    }

    std::string extraToken;
    if (input >> extraToken) {
        throw std::invalid_argument("Введите только один пункт меню.");
    }

    return option;
}
}

void ConsoleMenu::run() {
    bool isRunning = true;

    while (isRunning) {
        showMenu();

        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Ввод закрыт. Завершение программы.\n";
            return;
        }

        try {
            int option = readMenuOption(line);

            switch (option) {
                case 1:
                    handleManualInput();
                    break;
                case 2:
                    handleFileInput();
                    break;
                case 3:
                    showRules();
                    break;
                case 0:
                    isRunning = false;
                    std::cout << "До свидания!\n";
                    break;
                default:
                    std::cout << "Неизвестный пункт меню. Попробуйте еще раз.\n";
                    break;
            }
        } catch (const std::exception& exception) {
            std::cout << "Ошибка: " << exception.what() << "\n";
        }

        if (isRunning) {
            std::cout << "\n";
        }
    }
}

void ConsoleMenu::showMenu() const {
    std::cout << "=== Игра в пьяницу ===\n"
              << "1. Ввести карты вручную\n"
              << "2. Загрузить карты из файла\n"
              << "3. Показать правила\n"
              << "0. Выход\n"
              << "Выберите пункт меню: ";
}

void ConsoleMenu::handleManualInput() {
    try {
        Deal deal = readDealFromConsole();
        GameResult result = gameService_.play(deal);
        printResult(result);
    } catch (const std::exception& exception) {
        std::cout << "Ошибка: " << exception.what() << "\n";
    }
}

void ConsoleMenu::handleFileInput() {
    std::cout << "Введите путь к файлу: ";

    std::string path;
    if (!std::getline(std::cin, path)) {
        std::cout << "Ввод закрыт. Не удалось прочитать путь к файлу.\n";
        return;
    }

    try {
        Deal deal = fileReader_.readFromFile(path);
        GameResult result = gameService_.play(deal);
        printResult(result);
    } catch (const std::exception& exception) {
        std::cout << "Ошибка: " << exception.what() << "\n";
    }
}

void ConsoleMenu::showRules() const {
    std::cout << "У каждого игрока по пять карт. Карты задаются числами от 0 до 9.\n"
              << "Обычно большая карта побеждает меньшую, но карта 0 побеждает карту 9.\n"
              << "Победитель хода кладет обе открытые карты вниз своей колоды:\n"
              << "сначала карту первого игрока, затем карту второго игрока.\n"
              << "Если игра не заканчивается за 1000000 ходов, результатом считается botva.\n";
}

Deal ConsoleMenu::readDealFromConsole() const {
    std::cout << "Введите пять карт первого игрока: ";
    std::string firstLine;
    if (!std::getline(std::cin, firstLine)) {
        throw std::runtime_error("Не удалось прочитать карты первого игрока.");
    }

    std::cout << "Введите пять карт второго игрока: ";
    std::string secondLine;
    if (!std::getline(std::cin, secondLine)) {
        throw std::runtime_error("Не удалось прочитать карты второго игрока.");
    }

    return Deal{parseCardLine(firstLine), parseCardLine(secondLine)};
}

void ConsoleMenu::printResult(const GameResult& result) const {
    if (result.winner == Winner::Botva) {
        std::cout << "Результат: botva\n";
        return;
    }

    if (result.winner == Winner::First) {
        std::cout << "Победил: first " << result.moveCount << "\n";
    } else {
        std::cout << "Победил: second " << result.moveCount << "\n";
    }
}
