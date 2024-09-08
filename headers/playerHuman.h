#pragma once
#include <memory>
#include "player.h"
#include "types.h"
#include "gameTypes.h"
#include "playerTypes.h"

class PlayerHuman : public Player {
public:
    PlayerHuman(std::string&& name)
        : Player(std::move(name))
    {}
    PlayerHuman() : Player() {}

    // detail review about player's ships and their state
    void outputShipsInfo() const;

    // state construction
    std::unique_ptr<Ship> constructSingleShip(ShipType type, BoardLocations& boardLocations) const override;

    void constructShips(BoardLocations& locations) override;

    // util
    bool checkBorderForShipInput(const TupleLocInt& startLoc,
        PlayerDirection direction,
        ShipType shipType
    ) const;

    void fillShipLocations(
        BoardLocations& boardLocs,
        const TupleLocInt& startLoc,
        Ship* shipPtr,
        PlayerDirection direction
    ) const;

// overload for 1-location ship (BOAT), it does not need a direction
    void fillShipLocations(
        BoardLocations& boardLocs,
        const TupleLocInt& shipLoc,
        Ship* shipPtr
    ) const;


    // game actions
    LocationAttackStatus attackLocation(BoardLocations& boardLocs) const override;
};