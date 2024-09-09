#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "ship.h"
#include "gameTypes.h"

using ShipMap = std::unordered_map<
    ShipType, 
    std::vector<std::unique_ptr<Ship>> 
>;

typedef struct {
    int all;
    int alive;
    int dead;
} ShipCountInfo;

enum class PlayerDirection {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
    DIRS_COUNT,
};