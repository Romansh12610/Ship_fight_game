#include "userio.h"
#include "ship.h"
#include "location.h"
#include "gameRules.h"
#include "gameLoop.h"
#include "types.h"

GameLoop::GameLoop(PlayerHuman&& playerHum, PlayerAi&& playerAi)
    : m_player_hum{ std::move(playerHum) }
    , m_player_ai{ std::move(playerAi) }
    , m_view{ m_locations }
{}

bool GameLoop::checkIsGameEndForPlayer(Player* possibleWinner, Player* possibleLoser) {
    possibleLoser->checkIsAlive();
    if (possibleLoser->getIsAlive() == false) {
        m_winner = possibleWinner;
        m_looser = possibleLoser;
        return true;
    }
    else {
        return false;
    }
}

// false = miss, true = gameEnds
bool GameLoop::attackPlayerLocation(Player* playerWhoAttacks, Player* playerBeingAttacked) {
    LocationAttackStatus status;
    // player attacks
    // error attacks are not counted
    while (true) {
        status = playerWhoAttacks->attackLocation(m_locations);
        if (status == LocationAttackStatus::ATTACK_ALREADY_DEAD || status == LocationAttackStatus::ATTACK_YOURSELF) {
            continue;
        }
        else {
            break;
        }
    }

    if (status == LocationAttackStatus::NEUTRAL_MISS) {
        std::cout << "Now it's " << playerBeingAttacked->getName() << " player turn to attack\n";
        return false;
    }

    else if (status == LocationAttackStatus::KILL_ENEMY_SHIP) {
        return checkIsGameEndForPlayer(playerWhoAttacks, playerBeingAttacked);
    }

    else {
        return false;
    }
}

// main func
void GameLoop::startGameLoop() {
    m_view.drawBoard();
    std::cout << '\n';
    Userio::showBoardSymbolsMeaning();

    Userio::prepareForShipConstruction();

    // construct ship on both players
    m_player_hum.constructShips(m_locations);
    m_player_ai.constructShips(m_locations);

    m_view.drawBoard();

    // maybe delete condition
    bool isEndOfGame{ false };

    while (m_player_hum.getIsAlive() && m_player_ai.getIsAlive()) {
        // player attacks
        // error attacks are not counted
        isEndOfGame = attackPlayerLocation(&m_player_hum, &m_player_ai);
        if (isEndOfGame) 
            goto endOfGame;
        else {
            m_view.drawBoard();
            if (answerGameMenuInput() == true) 
                goto endOfGamePremature;
        }

        // computer attacks 
        isEndOfGame = attackPlayerLocation(&m_player_ai, &m_player_hum);
        if (isEndOfGame) 
            goto endOfGame;
        else {
            m_view.drawBoard();
            if (answerGameMenuInput() == true) 
                goto endOfGamePremature;
        }
    }

    endOfGame:
    Userio::declareEndOfGame(m_winner, m_looser);

    endOfGamePremature:
    m_view.drawBoardEndGame();
}


// util
// 2 possible inputs: continue or exitGame
// false = continue, true = endOfGame;
bool GameLoop::answerGameMenuInput() {
    Userio::GameMenuOptions userChoise{ Userio::getGameMenuInputLoop() };

    if (userChoise == Userio::GameMenuOptions::EXIT_GAME) {
        m_winner = &m_player_ai;
        m_looser = &m_player_hum;
        return true;
    } 
    else {
        return false;
    }
}

// getters
const BoardLocations& GameLoop::getBoardLocations() const { return m_locations; }

BoardLocations& GameLoop::getBoardLocations() { return m_locations; }

std::string_view GameLoop::getPlayerName() const {
    return m_player_hum.getName();
}