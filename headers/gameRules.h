#pragma once
#include <iostream>
#include "types.h"

class GameRules {
public:
    static inline constexpr int boatShipCount{ 1 };
    static inline constexpr int destroyerShipCount{ 3 };
    static inline constexpr int battleShipCount{ 2 };
    static inline constexpr int cruiserShipCount{ 1 };
    static inline constexpr int allShipCount{
        boatShipCount + destroyerShipCount + battleShipCount + cruiserShipCount
    };

    static inline constexpr int boatShipLocations{ 1 };
    static inline constexpr int destroyerShipLocations{ 2 };
    static inline constexpr int battleShipLocations{ 3 };
    static inline constexpr int cruiserLocations{ 4 };

    static inline constexpr int boardColLength{ 10 };
    static inline constexpr int boardRowLength{ 10 };
    static inline constexpr int boardSize{ boardColLength * boardRowLength };

    static void outputGameRules();
    static constexpr int getLocationCountForShip(ShipType type) {
        switch (type)
        {
        case ShipType::BOAT: return GameRules::boatShipLocations;
        case ShipType::DESTROYER: return GameRules::destroyerShipLocations;
        case ShipType::BATTLESHIP: return GameRules::battleShipLocations;
        case ShipType::CRUISER: return GameRules::cruiserLocations;
        default: return -1;
        }
    }
    static constexpr int getShipsCountForType(ShipType type) {
        switch (type)
        {
        case ShipType::BOAT: return GameRules::boatShipCount;
        case ShipType::DESTROYER: return GameRules::destroyerShipCount;
        case ShipType::BATTLESHIP: return GameRules::battleShipCount;
        case ShipType::CRUISER: return GameRules::cruiserShipCount;
        default: return -1;
        }
    }
};