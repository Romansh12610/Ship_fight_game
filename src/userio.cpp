#include <iostream>
#include <string>
#include <limits>
#include "ship.h"
#include "types.h"
#include "gameTypes.h"
#include "playerTypes.h"
#include "gameRules.h"
#include "player.h"
#include "userio.h"


// UTILS
void Userio::tellInvalidInput() {
    std::cout << "Input failed. Please try again.\n";
}

void Userio::ignoreExtraInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Userio::greetUserAndAskName() {
    std::string name;
    std::cout << "Welcome to the Ship Fight game!\n" << "Please, enter your name: ";

    while (true) {
        std::cin >> name;
        Userio::ignoreExtraInput();

        if (std::cin.good()) {
            return name;
        }
        else {
            std::cin.clear();
            Userio::tellInvalidInput();
        }
    }
}

void Userio::greetUserNamed(std::string_view userName) {
    std::cout << "\nHello, " << userName << ", again, you are welcome!\n";
}

void Userio::prepareForShipConstruction() {
    std::cout << "Good, now you ready to start!\n";
    std::cout << "Now enter locations for your ships\n";
}

void Userio::prepareStartLockInput(ShipType shipType) {
    std::cout << "\nEnter start location for your " << Ship::getShipTypeStrStatic(shipType) << " ship\nEnter first character as a lowercase letter from a-j and second as a digit from 0-9\nFor example: g2, c0, j9\n";
}

void Userio::prepareAttackLockInput() {
    std::cout << "\nGet ready to attack enemy ship.\nEnter location you want to attack.\nEnter first character as a lowercase letter from a-j and second as a digit from 0-9\nFor example: g2, c0, j9\nAnd try to not blow up your own ships:)\n";
}

bool Userio::getCharFromUser(char& input) {
    std::cin.get(input);
    Userio::ignoreExtraInput();

    if (!std::cin) {
        std::cin.clear();
        std::cout << "Input failed. Please try again.\n";
        return false;
    }

    return true;
}

// get with validation
bool Userio::getCharFromUser(char& input, Userio::ValidateFunc validateFunc) {
    std::cin.get(input);
    Userio::ignoreExtraInput();

    if (!std::cin) {
        std::cin.clear();
        std::cout << "Input failed. Please try again.\n";
        return false;
    }
    else if (validateFunc(input) == false) {
        std::cout << "Input is invalid. Please try again.\n";
        return false;
    }
    return true;
}


void Userio::getLocationInputFromUser(TupleLocChar& locChar, Userio::ValidateFuncTuple validateFunc) {
    while (true) {
        std::cin >> locChar[0] >> locChar[1];
        std::cin.ignore(2, '\n');

        if (!std::cin) {
            std::cin.clear();
            std::cout << "Input failed. Please try again.\n";
            Userio::ignoreExtraInput();
            continue;
        }
        else if (validateFunc(locChar) == false) {
            std::cout << "Input is invalid. Please try again.\n";
            continue;
        }
        else {
            return;
        }
    }
}


void Userio::sayGoodbyeToUser(std::string_view userName) {
    std::cout << "Thank you for playing our game, " << userName << ", hope you will play with us again sometime!\n";
}

// main menu
Userio::MainMenuOptions Userio::getMainMenuInput() {
    std::cout << "\n1 - Start game\n2 - Show rules\n3 - Show what board symbols mean\n4 - Finally Exit game\n";
    char input;

    while (true) {
        bool inpRes{ Userio::getCharFromUser(input) };
        if (!inpRes)
            continue;

        switch (static_cast<Userio::MainMenuOptions>(input)) {
        case Userio::MainMenuOptions::START_GAME:
        case Userio::MainMenuOptions::SHOW_RULES:
        case Userio::MainMenuOptions::SHOW_SYMBOL_MEANING:
        case Userio::MainMenuOptions::EXIT_GAME:
            return static_cast<Userio::MainMenuOptions>(input);
        default:
            Userio::tellInvalidInput();
        }
    }
}

// menu when inside game
Userio::GameMenuOptions Userio::getGameMenuInput() {
    std::cout << "\n1 - Continue game\n2 - Show rules\n3 - Show what board symbols mean\n4 - Exit to main menu\n";

    char input;

    while (true) {
        bool inpRes{ Userio::getCharFromUser(input) };
        if (!inpRes)
            continue;

        switch (static_cast<Userio::GameMenuOptions>(input)) {
        case Userio::GameMenuOptions::CONTINUE_GAME:
        case Userio::GameMenuOptions::SHOW_RULES:
        case Userio::GameMenuOptions::SHOW_SYMBOL_MEANING:
        case Userio::GameMenuOptions::EXIT_GAME:
            return static_cast<Userio::GameMenuOptions>(input);
        default:
            Userio::tellInvalidInput();
        }
    }
}

// ask main menu input with loop
// can't return SHOW_RULES option
// because it will continue the loop
Userio::MainMenuOptions Userio::getMainMenuInputLoop() {
    Userio::MainMenuOptions userChoise;

    while (true) {
        userChoise = Userio::getMainMenuInput();
        if (userChoise == Userio::MainMenuOptions::SHOW_RULES) {
            GameRules::outputGameRules();
        }
        else if (userChoise == Userio::MainMenuOptions::SHOW_SYMBOL_MEANING) {
            Userio::showBoardSymbolsMeaning();
        }
        else {
            return userChoise;
        }
    }
}

Userio::GameMenuOptions Userio::getGameMenuInputLoop() {
    Userio::GameMenuOptions userChoise;

    while (true) {
        userChoise = Userio::getGameMenuInput();
        if (userChoise == Userio::GameMenuOptions::SHOW_RULES) {
            GameRules::outputGameRules();
        }
        else if (userChoise == Userio::GameMenuOptions::SHOW_SYMBOL_MEANING) {
            Userio::showBoardSymbolsMeaning();
        }
        else {
            return userChoise;
        }
    }
}

// Validation
bool Userio::validateInputChar(const char& inp) {
    return inp >= Userio::asciiCharLowerBnd && inp <= Userio::asciiCharHigherBnd;
}

bool Userio::validateInputNum(const char& inp) {
    return inp >= Userio::asciiNumLowerBnd && inp <= Userio::asciiNumHigherBnd;
}

bool Userio::validateInputDirection(const char& inp) {
    switch (inp) {
    case Userio::TOP:
    case Userio::BOTTOM:
    case Userio::LEFT:
    case Userio::RIGHT:
        return true;
    default:
        return false;
    }
}

bool Userio::validateInputCharTuple(TupleLocChar& inp) {
    return Userio::validateInputChar(inp[0]) && Userio::validateInputNum(inp[1]);
}

// CONSTRUCTING USER STATE

// example input: b7
TupleLocInt Userio::convertCharLocToInt(const TupleLocChar& locationChar) {
    TupleLocInt locationInt{
        static_cast<int>(locationChar[0]) - Userio::asciiCharLowerBnd,
        static_cast<int>(locationChar[1]) - Userio::asciiNumLowerBnd
    };

    return locationInt;
}

// start location
TupleLocInt Userio::getLocationInput() {
    TupleLocChar locChar;

    Userio::getLocationInputFromUser(locChar, Userio::validateInputCharTuple);

    TupleLocInt locInt{ Userio::convertCharLocToInt(locChar) };

    return locInt;
}

TupleLocInt Userio::getLocationInputForAttack(std::string_view playerName) {
    TupleLocChar locChar;

    Userio::getLocationInputFromUser(locChar, Userio::validateInputCharTuple);

    std::cout << "\nPlayer " << playerName << " attacks " << locChar[0] << ':' << locChar[1] << '\n';

    TupleLocInt locInt{ Userio::convertCharLocToInt(locChar) };

    return locInt;
}

// direction
PlayerDirection Userio::getDirectionForShipConstr(ShipType shipType) {
    std::cout << "Choose direction for your new " << Ship::getShipTypeStrStatic(shipType) << " type of ship.\nEnter 'l' for left, 'r' for right, 't' for top or 'b' for bottom:\n";
    char inp;

    while (Userio::getCharFromUser(inp, Userio::validateInputDirection) == false) {};

    switch (inp) {
    case Userio::TOP: return PlayerDirection::TOP;
    case Userio::BOTTOM: return PlayerDirection::BOTTOM;
    case Userio::LEFT: return PlayerDirection::LEFT;
    case Userio::RIGHT: return PlayerDirection::RIGHT;
    default: return PlayerDirection::DIRS_COUNT;
    }
}

void Userio::declareEndOfGame(Player* winner, Player* looser) { 
    std::cout << "Game is finished\nResults:\n";
    std::cout << "Winner is: " << winner->getName() << '\n';
    std::cout << "Looser is: " << looser->getName() << '\n';
}

void Userio::showBoardSymbolsMeaning() {
    std::cout << "Each symbol on board means:\n";

    for (const auto locationSymbol : locationSymbolsArr) {
        switch (locationSymbol) {
        case LocationSymbol::PLAYER_ALIVE:
            std::cout << static_cast<char>(locationSymbol) << " - player (you) alive\n";
            break;
        case LocationSymbol::PLAYER_DEAD:
            std::cout << static_cast<char>(locationSymbol) << " - player (you) dead\n";
            break;
        case LocationSymbol::COMPUTER_ALIVE: 
            std::cout << static_cast<char>(locationSymbol) << " - computer alive (hidden untill game ends)\n";
            break;
        case LocationSymbol::COMPUTER_DEAD:
            std::cout << static_cast<char>(locationSymbol) << " - computer dead\n";
            break;
        case LocationSymbol::NEUTRAL_KILLED_BY_PLAYER:
            std::cout << static_cast<char>(locationSymbol) << " - player (you) miss\n";
            break;
        case LocationSymbol::NEUTRAL_KILLED_BY_COMPUTER:
            std::cout << static_cast<char>(locationSymbol) << " - computer miss\n";
            break;
        default: 
            std::cout << '\n';
        }
    }
}