#pragma once
#include <vector>
#include <memory>
#include "randomGen.h"
#include "types.h"
#include "gameTypes.h"
#include "userio.h"
#include "playerTypes.h"
#include "player.h"

class GameRules;
class GameLoop;
class Ship;

class PlayerAi : public Player {
public:
    using DimensionGenerator = RandomGen<int>;
    using IndexGenerator = RandomGen<int>;
    using CharGenerator = RandomGen<char>;

    PlayerAi(std::string_view name)
        : Player(name)
    {}

    PlayerAi(std::string&& name)
        : Player(std::move(name))
    {}
    PlayerAi() : Player() {}

    // state construction
    void fillShipLocations(BoardLocations& boardLocs, const TupleLocInt& startLocation, Ship* shipPtr, PlayerDirection choosenDim) const;

    // overload for 1-location shipType - BOAT, it does not need direction
    void fillShipLocations(BoardLocations& boardLocs, const TupleLocInt& startLocation, Ship* shipPtr) const;

    std::unique_ptr<Ship> constructSingleShip(ShipType type, BoardLocations& boardLocations) const override;

    void constructShips(BoardLocations& boardLocations) override;

    // game actions
    LocationAttackStatus attackLocation(BoardLocations& boardLocs) const override;

    // utils
        // check if we should see specific dimensions to go, when constructing ship (borders)
        // uses 'iterateDimAndCheckIfFree'
    std::vector<PlayerDirection> checkForGoodDimensions(const BoardLocations& boardLocs, const TupleLocInt& startLocIndeces, ShipType shipType) const;

    // iterates through random dimension on board and checks if it's free
    // this is done before filling the vector of AI ship's locations
    bool iterateDimAndCheckIfFree( const BoardLocations& boardLocs, const TupleLocInt& startLocIndeces, int shipSize, PlayerDirection choosenDim) const;

    PlayerDirection chooseRandDimFromGood(const std::vector<PlayerDirection>& goodDims) const;

    TupleLocInt genLocation() const;
    TupleLocInt genFreeStartLocation(BoardLocations& boardLocs) const;
    TupleLocInt genLocationForAttack() const;

private:
    IndexGenerator m_index_generator{ 0, GameRules::boardColLength - 1 };

    CharGenerator m_char_generator{ Userio::asciiCharLowerBnd, Userio::asciiCharHigherBnd };

    DimensionGenerator m_dimension_generator{ 
        static_cast<int>(PlayerDirection::TOP), 
        static_cast<int>(
            static_cast<int>(PlayerDirection::DIRS_COUNT) - 1
        )
    };
};