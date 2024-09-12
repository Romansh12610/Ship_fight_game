#include <iostream>
#include <cassert>
#include "ship.h"
#include "gameRules.h"
#include "userio.h"
#include "location.h"
#include "types.h"
#include "gameTypes.h"
#include "playerTypes.h"
#include "playerHuman.h"

void PlayerHuman::outputShipsInfo() const {
    auto logShipsOfType = [](ShipType shipType, const ShipCountInfo& shipCountInfo) {
        std::cout << "You have " << shipCountInfo.all << " ships of type: " << Ship::getShipTypeStrStatic(shipType) << ".\nAlive of them: " << shipCountInfo.alive << ", Dead: " << shipCountInfo.dead << '\n';
        };

    std::cout << "There's detailed info about your current ships:\n";

    for (const auto& shipPair : m_ships) {
        ShipCountInfo shipCountInfo{ getShipCountForType(shipPair.first) };
        logShipsOfType(shipPair.first, shipCountInfo);
    }
}


bool PlayerHuman::checkBorderForShipInput(const TupleLocInt& startLoc, PlayerDirection direction, ShipType shipType) const {
    int shipSizeIndex{ GameRules::getLocationCountForShip(shipType) - 1 };

    switch (direction) {
        // [0] - rows / y; [1] - cols / x
    case PlayerDirection::TOP:
        return (startLoc[0] - shipSizeIndex) >= 0;
    case PlayerDirection::BOTTOM:
        return (startLoc[0] + shipSizeIndex) < GameRules::boardRowLength;
    case PlayerDirection::LEFT:
        return (startLoc[1] - shipSizeIndex) >= 0;
    case PlayerDirection::RIGHT:
        return (startLoc[1] + shipSizeIndex) < GameRules::boardRowLength;
    default:
        return false;
    }
}


void PlayerHuman::fillShipLocations(
    BoardLocations& boardLocs,
    const TupleLocInt& startLoc,
    Ship* shipPtr,
    PlayerDirection direction
) const {

    const int shipSize{ shipPtr->getLocationCount() };

    switch (direction) {
        case PlayerDirection::TOP: {
            const int dest{ startLoc[0] - shipSize };

            for (int i{ startLoc[0] }; i > dest; --i) {
                Location* loc{ &boardLocs(i, startLoc[1]) };
                loc->setShipPtr(shipPtr);
                loc->setOwnerType(LocationOwner::PLAYER);
                shipPtr->pushLocation(loc);
            }
            break;
        }
        case PlayerDirection::BOTTOM: {
            const int dest{ startLoc[0] + shipSize };

            for (int i{ startLoc[0] }; i < dest; ++i) {
                Location* loc{ &boardLocs(i, startLoc[1]) };
                loc->setShipPtr(shipPtr);
                loc->setOwnerType(LocationOwner::PLAYER);
                shipPtr->pushLocation(loc);
            }
            break;
        }
        case PlayerDirection::LEFT: {
            const int dest{ startLoc[1] - shipSize };

            for (int i{ startLoc[1] }; i > dest; --i) {
                Location* loc{ &boardLocs(startLoc[0], i) };
                loc->setShipPtr(shipPtr);
                loc->setOwnerType(LocationOwner::PLAYER);
                shipPtr->pushLocation(loc);
            }
            break;
        }
        case PlayerDirection::RIGHT: {
            const int dest{ startLoc[1] + shipSize };

            for (int i{ startLoc[1] }; i < dest; ++i) {
                Location* loc{ &boardLocs(startLoc[0], i) };
                loc->setShipPtr(shipPtr);
                loc->setOwnerType(LocationOwner::PLAYER);
                shipPtr->pushLocation(loc);
            }
            break;
        }

        default: {
            assert("fillShipLocations error: invalid switch case");
        }
    }
}

// overload for BOAT-ship, it has no direction
void PlayerHuman::fillShipLocations(
    BoardLocations& boardLocs,
    const TupleLocInt& shipLoc,
    Ship* shipPtr
) const {
    Location* boardLoc{ &boardLocs(shipLoc[0], shipLoc[1]) };
    boardLoc->setOwnerType(LocationOwner::PLAYER);
    boardLoc->setShipPtr(shipPtr);
    shipPtr->pushLocation(boardLoc);
}


std::unique_ptr<Ship> PlayerHuman::constructSingleShip(ShipType shipType, BoardLocations& boardLocations) const {

    auto ship{ std::make_unique<Ship>(ShipOwner::PLAYER, this, shipType) };

    // ask start loc and direction
    Userio::prepareStartLockInput(shipType);
    TupleLocInt startLocIndeces;

    while (true) {
        startLocIndeces = Userio::getLocationInput();
        const Location& boardLoc{ boardLocations(startLocIndeces[0], startLocIndeces[1]) };

        if (boardLoc.isFree() == false) {
            std::cout << "location already owned\ntry again\n";
            continue;
        }
        else {
            break;
        }
    }

    if (shipType == ShipType::BOAT) {
        fillShipLocations(boardLocations, startLocIndeces, ship.get());
    }
    else {
        PlayerDirection direction{ Userio::getDirectionForShipConstr(shipType) };

        while (checkBorderForShipInput(startLocIndeces, direction, shipType) == false) {
            std::cout << "Invalid direction for choosen start location. Try again\n";
            direction = Userio::getDirectionForShipConstr(shipType);
        }

        // have valid direction and start loc -> fill ship
        fillShipLocations(
            boardLocations,
            startLocIndeces,
            ship.get(),
            direction
        );
    }

    return ship;
}


void PlayerHuman::constructShips(BoardLocations& boardLocs) {
    for (const ShipType shipType : Ship::typesAsArr) {
        const int shipCount{ GameRules::getShipsCountForType(shipType) };
        m_ships[shipType].reserve(shipCount);

        for (int i = 0; i < shipCount; ++i) {
            m_ships[shipType].push_back(constructSingleShip(shipType, boardLocs));
        }
    }

    // now shipMap fully constructed
    bool constrSuccess{ checkShipsWellConstructed() };
    assert(constrSuccess && "Error when constructing player ships, map is not full\n");
}


// game actions
LocationAttackStatus PlayerHuman::attackLocation(BoardLocations& boardLocs) const {
    Userio::prepareAttackLockInput();
    LocationAttackStatus status;

    while (true) {
        TupleLocInt locIndexForAttack{ Userio::getLocationInputForAttack(getName()) };

        Location& boardLoc{ boardLocs(locIndexForAttack[0], locIndexForAttack[1]) };

        status = boardLoc.killLocation(LocationOwner::PLAYER);

        if (status == LocationAttackStatus::ATTACK_ALREADY_DEAD || status == LocationAttackStatus::ATTACK_YOURSELF) {
            continue;
        }
        else {
            break;
        }
    }

    return status;
}