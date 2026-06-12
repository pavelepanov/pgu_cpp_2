#ifndef PRESENTATION_CONSOLE_MENU_H
#define PRESENTATION_CONSOLE_MENU_H

#include "application/GameService.h"
#include "domain/Deal.h"
#include "domain/GameResult.h"
#include "infrastructure/DealFileReader.h"

class ConsoleMenu {
public:
    void run();

private:
    void showMenu() const;
    void handleManualInput();
    void handleFileInput();
    void showRules() const;
    Deal readDealFromConsole() const;
    void printResult(const GameResult& result) const;

    GameService gameService_;
    DealFileReader fileReader_;
};

#endif
