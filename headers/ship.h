#pragma once
#include <vector>
#include <array>
#include <cassert>
#include <string_view>
//#include "player.h"
//#include "gameRules.h"
#include "types.h"

class Location;
class GameRules;
class Player;

class Ship {
public:
    static constexpr std::array<ShipType, static_cast<std::size_t>(ShipType::SHIP_TYPE_COUNT)> typesAsArr{
        ShipType::BOAT, ShipType::DESTROYER, ShipType::BATTLESHIP, ShipType::CRUISER,
    };

    // locations by const& because game also need to have it (can't be moved)
    Ship() = default;
    Ship(ShipOwner ownerType, const Player* owner, ShipType type);
    Ship(const Ship& ship) = default;
    Ship(Ship&& src) noexcept = default;
    Ship& operator=(const Ship& src) = default;
    Ship& operator=(Ship&& src) noexcept = default;

    ShipOwner getOwnerType() const;
    ShipType getType() const;
    int getLocationCount() const;

    // state getter
    bool getIsAlive() const;
    // changes internal state
    void checkIsAlive();

    std::string_view getShipTypeStr() const;
    static std::string_view getShipTypeStrStatic(ShipType type);

    void setLocations(std::vector<const Location*>&& locations);
    void pushLocation(const Location* locPtr);

    const Player* getPlayerOwner() { return m_owner; }

private:
    const Player* m_owner{ nullptr };
    ShipOwner m_ownerType{ ShipOwner::PLAYER };
    ShipType m_type{ ShipType::BOAT };
    bool m_isAlive{ true };
    // can't change locations, only viewing it
    std::vector<const Location*> m_locations;
};