#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include "types.h"
#include "gameTypes.h"
#include "playerTypes.h"


class Ship;

class Player {
public:
    Player() = default;
    Player(std::string_view name);
    Player(const std::string& name);
    Player(std::string&& name);

    ShipCountInfo getShipCountForType(ShipType) const;
    std::string_view getName() const;
    void checkIsAlive();
    bool getIsAlive() const;
    bool checkShipsWellConstructed();

    virtual LocationAttackStatus attackLocation(BoardLocations& boardLocs) const = 0;
    virtual void constructShips(BoardLocations& boardLocations) = 0;
    virtual std::unique_ptr<Ship> constructSingleShip(ShipType type, BoardLocations& boardLocations) const = 0;

protected:
    ShipMap m_ships;
    std::string m_name;
    bool m_isAlive{ true };
};