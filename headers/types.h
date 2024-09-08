#pragma once
#include <array>

// SHIP
enum class ShipOwner {
    PLAYER,
    COMPUTER,
};

enum class ShipType : int {
    BOAT,
    DESTROYER,
    BATTLESHIP,
    CRUISER,
    SHIP_TYPE_COUNT,
};

// LOCATION
enum class LocationOwner {
    PLAYER,
    COMPUTER,
    NONE,
};

enum class LocationSymbol : char {
    PLAYER_ALIVE = 'P',
    PLAYER_DEAD = 'x',
    COMPUTER_ALIVE = 'C',
    COMPUTER_DEAD = '+',
    NEUTRAL_ALIVE = 'N',
    NEUTRAL_KILLED_BY_PLAYER = '-',
    NEUTRAL_KILLED_BY_COMPUTER = '*',
};

constexpr std::array<LocationSymbol, 7> locationSymbolsArr{
    LocationSymbol::COMPUTER_ALIVE,
    LocationSymbol::COMPUTER_DEAD,
    LocationSymbol::PLAYER_ALIVE,
    LocationSymbol::PLAYER_DEAD,
    LocationSymbol::NEUTRAL_KILLED_BY_COMPUTER,
    LocationSymbol::NEUTRAL_KILLED_BY_PLAYER,
    LocationSymbol::NEUTRAL_ALIVE,
};

enum LocationAttackStatus {
    KILL_ENEMY_LOCATION,
    KILL_ENEMY_SHIP,
    NEUTRAL_MISS,
    ATTACK_YOURSELF,
    ATTACK_ALREADY_DEAD,
};