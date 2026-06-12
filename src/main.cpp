#include "presentation/ConsoleMenu.h"

#include <exception>
#include <iostream>

int main() {
    try {
        ConsoleMenu menu;
        menu.run();
    } catch (const std::exception& exception) {
        std::cout << "Критическая ошибка: " << exception.what() << "\n";
        return 1;
    }

    return 0;
}
