#pragma once
#include <array>
#include "arrayFlat2d.h"
#include "userio.h"
#include "playerAi.h"
#include "playerHuman.h"
#include "gameTypes.h"
#include "types.h"
#include "gameView.h"

class GameRules;
class Location;
class GameView;

// TO DO 
// handle GAME menu input choices 

class GameLoop {
public:
    GameLoop(PlayerHuman&& playerHum, PlayerAi&& playerComp);

    // main
    void startGameLoop();
    bool attackPlayerLocation(Player* playerWhoAttacks, Player* playerBeingAttacked);
    // returns winner or null
    bool checkIsGameEndForPlayer(Player* possibleWinner, Player* possibleLoser);

    // util
    bool answerGameMenuInput();

    // getters
    const BoardLocations& getBoardLocations() const;
    BoardLocations& getBoardLocations();
    std::string_view getPlayerName() const;
private:
    BoardLocations m_locations;
    PlayerHuman m_player_hum;
    PlayerAi m_player_ai;

    Player* m_winner{ nullptr };
    Player* m_looser{ nullptr };

    GameView m_view;
};
