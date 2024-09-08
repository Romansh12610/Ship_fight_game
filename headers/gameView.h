#pragma once
#include <vector>
#include "gameTypes.h"

// gets array of initialized locations and draws them to console
class GameView {
public:
    GameView(const BoardLocations& locations);

    // board 10x10
    void drawBoard() const;
    void drawBoardEndGame() const;

    static char convIntIndexToChar(int i);

    static constexpr int firstCharCode{ 97 };
private:
    void drawFirstLine() const;
    const BoardLocations& m_locations;
};
