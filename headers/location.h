#pragma once
#include <array>
#include "types.h"

class Ship;

class Location {
public:
    Location() = default;
    Location(LocationOwner owner);
    Location(Location&& src) noexcept = default;
    Location& operator=(Location&& src) noexcept = default;

    void setOwnerType(LocationOwner ownerType);
    void setShipPtr(Ship* shipPtr);
    LocationAttackStatus killLocation(LocationOwner attackerType);

    bool isAlive() const;
    bool isFree() const;
    // use isFree if can
    LocationOwner getOwnerType() const;
    Ship* getShipOwner() const;

    // symbol can be changed through setState
    LocationSymbol getSymbol() const;

private:
    LocationOwner m_ownerType{ LocationOwner::NONE };
    bool m_isAlive{ true };
    LocationSymbol m_symbol{ LocationSymbol::NEUTRAL_ALIVE };
    // to immediately check ship on alive state after killing location
    Ship* m_shipPtr{ nullptr };
};