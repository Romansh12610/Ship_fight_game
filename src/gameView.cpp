#include <iostream>
#include "gameRules.h"
#include "gameView.h"
#include "gameTypes.h"

GameView::GameView(const BoardLocations& locations)
    : m_locations{ locations }
{}

char GameView::convIntIndexToChar(int i) {
    assert((i < 0 || i > (GameRules::boardRowLength - 1)) && "convIntIndexToChar Error: column index is out of bounds");

    return static_cast<char>(i + GameView::firstCharCode);
}

void GameView::drawFirstLine() const {
    std::cout << "   ";

    for (int i{ 0 }; i < GameRules::boardColLength; ++i) {
        std::cout << i << ' ';
    }

    std::cout << '\n';
}

// template:
/*
    std::cout << "   0 1 2 3 4 5 6 7 8 9 \n";
    std::cout << "a |_ _ _ _ x x x _ _ _|\n";
    std::cout << "b |_ _ _ _ x x x _ _ _|\n";
    std::cout << "c |+ + + + + x + + + +|\n";
    std::cout << "d |+ + + + + x + + + +|\n";
    std::cout << "e |+ + + + + + + + + +|\n";
    std::cout << "f |+ + + + + + + + + +|\n";
    std::cout << "g |+ + + + + + + + + +|\n";
    std::cout << "h |+ + + + + + + + + +|\n";
    std::cout << "i |+ + + + + + + + + +|\n";
    std::cout << "j |+ + + + + + + + + +|\n";
*/

void GameView::drawBoard() const {
    std::cout << "\nCurrent game state:\n";

    drawFirstLine();

    char stringLetterIdentifier{ GameView::firstCharCode };

    for (char i{ 0 }; i < GameRules::boardRowLength; ++i, ++stringLetterIdentifier) {
        std::cout << stringLetterIdentifier << " |";

        for (int j{ 0 }; j < GameRules::boardColLength; ++j) {
            const Location& currLocation{ m_locations(i, j) };
            LocationSymbol symbolToDraw;
            if (currLocation.getSymbol() == LocationSymbol::COMPUTER_ALIVE) {
                symbolToDraw = LocationSymbol::NEUTRAL_ALIVE;
            }
            else {
                symbolToDraw = currLocation.getSymbol();
            }

            std::cout << static_cast<char>(symbolToDraw);
            if (j != (GameRules::boardColLength - 1)) {
                std::cout << ' ';
            }
        }

        std::cout << "|\n";
    }
}


void GameView::drawBoardEndGame() const {
    std::cout << "\nFinal game result looks like this:\n";

    drawFirstLine();

    char stringLetterIdentifier{ GameView::firstCharCode };

    for (char i{ 0 }; i < GameRules::boardRowLength; ++i, ++stringLetterIdentifier) {
        std::cout << stringLetterIdentifier << " |";

        for (int j{ 0 }; j < GameRules::boardColLength; ++j) {
            std::cout << static_cast<char>(m_locations(i, j).getSymbol());
            if (j != (GameRules::boardColLength - 1)) {
                std::cout << ' ';
            }
        }

        std::cout << "|\n";
    }
}