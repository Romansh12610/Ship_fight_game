#include <iostream>
#include "ship.h"
#include "types.h"
#include "location.h"

LocationAttackStatus Location::killLocation(LocationOwner attackerType) {
    // error codes
    if (!m_isAlive) {
        std::cout << "Error: location already dead\nPlease try again\n";
        return LocationAttackStatus::ATTACK_ALREADY_DEAD;
    }
    else if (m_ownerType == attackerType) {
        std::cout << "Error: your trying to attack your own ship!\nPlease try again\n";
        return LocationAttackStatus::ATTACK_YOURSELF;
    }
    // success codes
    else if (m_ownerType == LocationOwner::NONE) {
        std::cout << "Current attack was a miss:(\n";
        if (attackerType == LocationOwner::PLAYER) {
            m_symbol = LocationSymbol::NEUTRAL_KILLED_BY_PLAYER;
        }
        else {
            m_symbol = LocationSymbol::NEUTRAL_KILLED_BY_COMPUTER;
        }
        // return generic miss
        return LocationAttackStatus::NEUTRAL_MISS;
    }

    // location was killed successfully
    else {
        std::cout << "Enemy location was successfully killed!\n";
        m_isAlive = false;

        if (m_ownerType == LocationOwner::PLAYER) {
            m_symbol = LocationSymbol::PLAYER_DEAD;
        }
        else {
            m_symbol = LocationSymbol::COMPUTER_DEAD;
        }

        m_shipPtr->checkIsAlive();
        if (!m_shipPtr->getIsAlive()) {
            std::cout << "You also kill an enemy ship!\n";
            return LocationAttackStatus::KILL_ENEMY_SHIP;
        }

        return LocationAttackStatus::KILL_ENEMY_LOCATION;
    }
}

void Location::setOwnerType(LocationOwner ownerType) {
    m_ownerType = ownerType;
    if (m_ownerType == LocationOwner::PLAYER) {
        m_symbol = LocationSymbol::PLAYER_ALIVE;
    } else {
        m_symbol = LocationSymbol::COMPUTER_ALIVE;
    }
}

void Location::setShipPtr(Ship* shipPtr) {
    m_shipPtr = shipPtr;
}


// ctors
Location::Location(LocationOwner owner)
    : m_ownerType{ owner }
    , m_isAlive{ true }
{}

// getters
bool Location::isAlive() const
{
    return m_isAlive;
}

bool Location::isFree() const
{
    return m_ownerType == LocationOwner::NONE;
}

LocationOwner Location::getOwnerType() const
{
    return m_ownerType;
}

Ship* Location::getShipOwner() const
{
    return m_shipPtr;
}

LocationSymbol Location::getSymbol() const
{
    return m_symbol;
}