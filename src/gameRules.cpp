#include <iostream>
#include "gameRules.h"
#include "types.h"

void GameRules::outputGameRules() {
    std::cout << "GAME RULES: \n\n" << "Firstly, each player has a " << GameRules::allShipCount << " ships.\n\n";

    std::cout << "To be more detailed, each Player has: \n" << GameRules::boatShipCount << " boats;\n" << GameRules::destroyerShipCount << " destroyers;\n" << GameRules::battleShipCount << " battleships;\n" << "And " << GameRules::cruiserShipCount << " cruiser.\n\n";

    std::cout << "Each type of ship have a different amount of locations - this determines its durability.\n";
    std::cout << "Boats have " << GameRules::boatShipLocations << " locations;\n";
    std::cout << "Destroyers have " << GameRules::destroyerShipLocations << " locations;\n";
    std::cout << "Battleships have " << GameRules::battleShipLocations << " locations;\n";
    std::cout << "Cruisers have " << GameRules::cruiserLocations << " locations;\n\n";

    std::cout << "To win - just eliminate all ships of your opponent and don't let him to do this before you did.\n\n";
}