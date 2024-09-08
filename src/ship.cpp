#include "location.h"
#include "gameRules.h"
#include "types.h"
#include "ship.h"

Ship::Ship(ShipOwner ownerType, const Player* owner, ShipType shipType)
    : m_owner{ owner }
    , m_ownerType{ ownerType }
    , m_type{ shipType }
{
    m_locations.reserve(this->getLocationCount());
}

void Ship::checkIsAlive() {
    if (m_isAlive == false) return;

    for (const Location* loc : m_locations) {
        if (loc->isAlive()) {
            // even if 1 location is alive ship is alive
            return;
        }
    }
    // all locations dead here, so ship too
    m_isAlive = false;
}

std::string_view Ship::getShipTypeStrStatic(ShipType type) {
    switch (type)
    {
    case ShipType::BOAT:
        return "Boat";
    case ShipType::DESTROYER:
        return "Destroyer";
    case ShipType::BATTLESHIP:
        return "Battleship";
    case ShipType::CRUISER:
        return "Cruiser";
    default:
        return "Undefined";
    }
}

std::string_view Ship::getShipTypeStr() const {
    return Ship::getShipTypeStrStatic(this->m_type);
}

void Ship::setLocations(std::vector<const Location*>&& locations) {
    m_locations = std::move(locations);
}

void Ship::pushLocation(const Location* locPtr) {
    m_locations.push_back(locPtr);
}

// getters
ShipOwner Ship::getOwnerType() const { 
    return m_ownerType;
}

ShipType Ship::getType() const { 
    return m_type; 
}

int Ship::getLocationCount() const { 
    return GameRules::getLocationCountForShip(m_type); 
}

bool Ship::getIsAlive() const { 
    return m_isAlive; 
}