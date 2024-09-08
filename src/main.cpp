#include <iostream>
#include <string>
#include "playerAi.h"
#include "playerHuman.h"
#include "gameLoop.h"
#include "userio.h"

int main() {
    std::string name{ Userio::greetUserAndAskName() };
    PlayerHuman playerHum{ std::move(name) };
    Userio::greetUserNamed(playerHum.getName());

    Userio::MainMenuOptions userChoise{ Userio::getMainMenuInputLoop() };

    if (userChoise == Userio::MainMenuOptions::EXIT_GAME) {
        Userio::sayGoodbyeToUser(playerHum.getName());
        return EXIT_SUCCESS;
    }

    // user choose START_GAME here
    using namespace std::string_view_literals;    
    GameLoop game{ std::move(playerHum), PlayerAi{ "computer"sv } };


    while (true) {
        game.startGameLoop();
        if (Userio::getMainMenuInput() == Userio::MainMenuOptions::EXIT_GAME) {
            break;
        }
    }

    std::cout << "Thanks for playing!\nEnjoy your day, " << game.getPlayerName() << '!' << std::endl;

    return EXIT_SUCCESS;
}