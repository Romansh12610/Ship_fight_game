#include <iostream>
#include <algorithm>
#include <cassert>
#include <memory>
#include "gameRules.h"
#include "gameLoop.h"
#include "ship.h"
#include "types.h"
#include "playerTypes.h"
#include "player.h"

void Player::checkIsAlive() {
    if (!m_isAlive) return;

    for (const auto& shipPair : m_ships) {
        // .second == vector<std::unique_ptr<Ship>>
        for (const auto& ship : shipPair.second) {
            if (ship->getIsAlive()) {
                return;
            }
        }
    }

    m_isAlive = false;
}


ShipCountInfo Player::getShipCountForType(ShipType type) const {
    const std::vector<std::unique_ptr<Ship>>& shipsByType{ m_ships.at(type) };
    int arrSize{ static_cast<int>(shipsByType.size()) };

    ShipCountInfo shipCountInfo{ .all = arrSize, .alive = 0 , .dead = 0 };

    for (const auto& ship : shipsByType) {
        if (ship->getIsAlive()) {
            shipCountInfo.alive++;
        }
        else {
            shipCountInfo.dead++;
        }
    }

    assert(((shipCountInfo.alive + shipCountInfo.dead) == shipCountInfo.all) && "Error in function getShipCountInfoType: \nalive ships + dead ships does not equal to all ship count\n");

    return shipCountInfo;
}

bool Player::checkShipsWellConstructed() {
    for (auto& it : m_ships) {
        if (static_cast<int>(it.second.size()) != GameRules::getShipsCountForType(it.first)) {
            return false;
        }
    }

    return true;
}

// ctors
Player::Player(std::string_view name)
    : m_name{ name }
{}

Player::Player(const std::string& name)
    : m_name{ name }
{}

Player::Player(std::string&& name)
    : m_name{ std::move(name) }
{}

// getters
std::string_view Player::getName() const { return m_name; }
bool Player::getIsAlive() const { return m_isAlive; }