#include "gameRules.h"
#include "player.h"
#include "gameLoop.h"
#include "ship.h"
#include "location.h"
#include "playerAi.h"
#include "types.h"
#include "gameTypes.h"
#include "userio.h"
#include "playerTypes.h"

TupleLocInt PlayerAi::genLocation() const {
    return {
      m_index_generator.gen(),
      m_index_generator.gen(),
    };
}

TupleLocInt PlayerAi::genLocationForAttack() const {
    // dont want to do separate generator for numeric char
    char numericLocationIndex{ static_cast<char>(
        m_index_generator.gen() + Userio::asciiNumLowerBnd) 
    };

    TupleLocChar locChar{ m_char_generator.gen(), numericLocationIndex };

    std::cout << "Player " << getName() << " attacks " << locChar[0] << ':' << locChar[1] << '\n';

    TupleLocInt locInt{ Userio::convertCharLocToInt(locChar) };

    return locInt;
}

// gen location that was not choosen by previous player(-s)
TupleLocInt PlayerAi::genFreeStartLocation(BoardLocations& boardLocs) const {

    TupleLocInt locationIndeces{ genLocation() };

    Location* locPtr{ &boardLocs(locationIndeces[0], locationIndeces[1]) };

    while (!locPtr->isFree()) {
        locationIndeces[0] = m_index_generator.gen();
        locationIndeces[1] = m_index_generator.gen();
        locPtr = &boardLocs(locationIndeces[0], locationIndeces[1]);
    }

    return locationIndeces;
}


// check border and FREE status of locations, if all true - dimension is possible or good
std::vector<PlayerDirection> PlayerAi::checkForGoodDimensions(
    // [0] - row, [1] - col
    const BoardLocations& boardLocs,
    const TupleLocInt& startLocIndeces,
    ShipType shipType
) const {

    std::vector<PlayerDirection> possibleDimensions;
    int shipSize{ GameRules::getLocationCountForShip(shipType) };

    // top
    if ((startLocIndeces[0] + 1) - shipSize >= 0
        && PlayerAi::iterateDimAndCheckIfFree(boardLocs, startLocIndeces, shipSize, PlayerDirection::TOP)) {
        possibleDimensions.push_back(PlayerDirection::TOP);
    }
    // bottom
    if ((startLocIndeces[0] - 1) + shipSize < GameRules::boardRowLength
        && PlayerAi::iterateDimAndCheckIfFree(boardLocs, startLocIndeces, shipSize, PlayerDirection::BOTTOM))
        possibleDimensions.push_back(PlayerDirection::BOTTOM);
    // left
    if (((startLocIndeces[1] + 1) - shipSize) >= 0
        && PlayerAi::iterateDimAndCheckIfFree(boardLocs, startLocIndeces, shipSize, PlayerDirection::LEFT))
        possibleDimensions.push_back(PlayerDirection::LEFT);
    // right
    if (((startLocIndeces[1] - 1) + shipSize) < GameRules::boardColLength
        && PlayerAi::iterateDimAndCheckIfFree(boardLocs, startLocIndeces, shipSize, PlayerDirection::RIGHT))
        possibleDimensions.push_back(PlayerDirection::RIGHT);

    return possibleDimensions;
};


bool PlayerAi::iterateDimAndCheckIfFree(
    const BoardLocations& boardLocs,
    const TupleLocInt& startLocIndeces,
    int shipSize,
    PlayerDirection choosenDim
) const {

    // does not check border, because it was already checked
    switch (choosenDim)
    {
        case PlayerDirection::TOP: {
            int dest{ startLocIndeces[0] - shipSize };

            for (int i{ startLocIndeces[0] }; i > dest; --i) {
                if (!boardLocs(i, startLocIndeces[1]).isFree()) {
                    return false;
                }
            }

            return true;
        }

        case PlayerDirection::BOTTOM: {
            int dest{ startLocIndeces[0] + shipSize };

            for (int i{ startLocIndeces[0] }; i < dest; ++i) {
                if (!boardLocs(i, startLocIndeces[1]).isFree()) {
                    return false;
                }
            }

            return true;
        }

        case PlayerDirection::LEFT: {
            int dest{ startLocIndeces[1] - shipSize };

            for (int i{ startLocIndeces[1] }; i > dest; --i) {
                if (!boardLocs(startLocIndeces[0], i).isFree()) {
                    return false;
                }
            }

            return true;
        }

        case PlayerDirection::RIGHT: {
            int dest{ startLocIndeces[1] + shipSize };

            for (int i{ startLocIndeces[1] }; i < dest; ++i) {
                if (!boardLocs(startLocIndeces[0], i).isFree()) {
                    return false;
                }
            }

            return true;
        }

        default: {
            return false;
        }
    }
}


PlayerDirection PlayerAi::chooseRandDimFromGood(
    const std::vector<PlayerDirection>& goodDims
) const {
    RandomGen<size_t> randomIndexGen{ static_cast<size_t>(0), (goodDims.size() - 1) };

    size_t randomIndex{ randomIndexGen.gen() };

    return goodDims[randomIndex];
}

// fills successfully founded good dimension from start location
// does not check ownership or border of locations
void PlayerAi::fillShipLocations(
    BoardLocations& boardLocs,
    const TupleLocInt& startLocation,
    Ship* shipPtr,
    PlayerDirection choosenDim
) const {
    const int shipSize{ shipPtr->getLocationCount() }; 

    switch (choosenDim) {
        case PlayerDirection::TOP: {
            const int dest{ startLocation[0] - shipSize };

            for (int i{ startLocation[0] }; i > dest; --i) {
                Location* location{ &boardLocs(i, startLocation[1]) };
                location->setShipPtr(shipPtr);
                location->setOwnerType(LocationOwner::COMPUTER);
                shipPtr->pushLocation(location);
            }
            break;
        }

        case PlayerDirection::BOTTOM: {
            const int dest{ startLocation[0] + shipSize };

            for (int i{ startLocation[0] }; i < dest; ++i) {
                Location* location{ &boardLocs(i, startLocation[1]) };
                location->setShipPtr(shipPtr);
                location->setOwnerType(LocationOwner::COMPUTER);
                shipPtr->pushLocation(location);
            }
            break;
        }

        case PlayerDirection::LEFT: {
            const int dest{ startLocation[1] - shipSize };

            for (int i{ startLocation[1] }; i > dest; --i) {
                Location* location{ &boardLocs(startLocation[0], i) };
                location->setShipPtr(shipPtr);
                location->setOwnerType(LocationOwner::COMPUTER);
                shipPtr->pushLocation(location);
            }
            break;
        }

        case PlayerDirection::RIGHT: {
            const int dest{ startLocation[1] + shipSize };

            for (int i{ startLocation[1] }; i < dest; ++i) {
                Location* location{ &boardLocs(startLocation[0], i) };
                location->setShipPtr(shipPtr);
                location->setOwnerType(LocationOwner::COMPUTER);
                shipPtr->pushLocation(location);
            }
            break;
        }

        default: {
            assert(true && "fillShipsLocation error, invalid switch case");
        }
    }
}


// overload for BOAT-ship, it has no direction
void PlayerAi::fillShipLocations(
    BoardLocations& boardLocs,
    const TupleLocInt& shipLoc,
    Ship* shipPtr
) const {
    Location* boardLoc{ &boardLocs(shipLoc[0], shipLoc[1]) };
    boardLoc->setOwnerType(LocationOwner::PLAYER);
    boardLoc->setShipPtr(shipPtr);
    shipPtr->pushLocation(boardLoc);
}


// looking up board and choosing locations that are not taken by human player
std::unique_ptr<Ship> PlayerAi::constructSingleShip(
    ShipType shipType,
    BoardLocations& boardLocations
) const
{
    auto ship{ std::make_unique<Ship>(ShipOwner::COMPUTER, this, shipType) };

    TupleLocInt startLocIndeces{ PlayerAi::genFreeStartLocation(boardLocations) };

    std::vector<PlayerDirection> goodDimensions{ 
        PlayerAi::checkForGoodDimensions(boardLocations, startLocIndeces, shipType)
    };

    // check if goodDims.size() > 1 and we can choose good dim from it
    while (goodDimensions.size() == 0) {
        startLocIndeces = PlayerAi::genFreeStartLocation(boardLocations);
        goodDimensions = PlayerAi::checkForGoodDimensions(boardLocations, startLocIndeces, shipType);
    }

    PlayerDirection goodDimension{ PlayerAi::chooseRandDimFromGood(goodDimensions) };

    if (shipType == ShipType::BOAT) {
        fillShipLocations(boardLocations, startLocIndeces, ship.get());
    }
    else {
        // fill locations with choosen goodDim and startLoc
        fillShipLocations(boardLocations, startLocIndeces, ship.get(), goodDimension);
    }

    return ship;
}

// ai ships constructed after playerHuman constructed his state
void PlayerAi::constructShips(BoardLocations& boardLocations) {
    for (const ShipType& shipType : Ship::typesAsArr) {
        const int shipCount{ GameRules::getShipsCountForType(shipType) };
        m_ships[shipType].reserve(shipCount);

        for (int i = 0; i < shipCount; ++i) {
            m_ships[shipType].push_back(constructSingleShip(shipType, boardLocations));
        }
    }

    bool constrSuccess{ checkShipsWellConstructed() };
    assert(constrSuccess && "Error when constructing player ships, map is not full\n");
};


// Game Actions
LocationAttackStatus PlayerAi::attackLocation(BoardLocations& boardLocs) const {

    TupleLocInt locationIndexToAttack{ genLocationForAttack() };

    Location& loc{ boardLocs(locationIndexToAttack[0], locationIndexToAttack[1]) };

    return loc.killLocation(LocationOwner::COMPUTER);
};