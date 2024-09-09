// input from / output to User
#pragma once
#include <string_view>
#include <vector>
#include "types.h"
#include "gameTypes.h"
#include "playerTypes.h"

class Player;

namespace Userio {
    enum class MainMenuOptions : char {
        START_GAME = '1',
        SHOW_RULES = '2',
        SHOW_SYMBOL_MEANING = '3',
        EXIT_GAME = '4',
    };

    enum class GameMenuOptions : char {
        CONTINUE_GAME = '1',
        SHOW_RULES = '2',
        SHOW_SYMBOL_MEANING = '3',
        EXIT_GAME = '4',
    };

    enum DirectionInput : char {
        TOP = 't',
        BOTTOM = 'b',
        LEFT = 'l',
        RIGHT = 'r',
    };

    using ValidateFunc = bool(*)(const char&);
    using ValidateFuncTuple = bool(*)(TupleLocChar&);

    // valid codes for location
    constexpr int asciiNumLowerBnd{ 48 };
    constexpr int asciiNumHigherBnd{ 57 };
    constexpr int asciiCharLowerBnd{ 97 };
    constexpr int asciiCharHigherBnd{ 106 };

    // greets and byes
    std::string greetUserAndAskName();
    void greetUserNamed(std::string_view userName);
    void sayGoodbyeToUser(std::string_view userName);

    // menus
    MainMenuOptions getMainMenuInput();
    GameMenuOptions getGameMenuInput();
    // looped versions
    MainMenuOptions getMainMenuInputLoop();
    GameMenuOptions getGameMenuInputLoop();

    // user state construction
    void prepareForShipConstruction();
    TupleLocInt convertCharLocToInt(const TupleLocChar& location);
    TupleLocChar convertIntLocToChar(const TupleLocInt& intLoc);
    TupleLocInt getLocationInput();
    PlayerDirection getDirectionForShipConstr(ShipType shipType);

    // validation
    bool validateInputChar(const char& inp);
    bool validateInputNum(const char& inp);
    bool validateInputDirection(const char& inp);
    bool validateInputCharTuple(TupleLocChar& inp);

    // game actions
    TupleLocInt getLocationInputForAttack(std::string_view PlayerName);

    // utils
    bool getCharFromUser(char& input);
    bool getCharFromUser(char& input, ValidateFunc validateFunc);
    void tellInvalidInput();
    void ignoreExtraInput();
    void getLocationInputFromUser(TupleLocChar& input, ValidateFuncTuple validateFunc);

    void prepareStartLockInput(ShipType shipType);
    void prepareAttackLockInput();

    void declareEndOfGame(Player* winner, Player* looser);
    void declareAttackLocation(const TupleLocChar& loc, std::string_view playerName);
    void showBoardSymbolsMeaning();
};