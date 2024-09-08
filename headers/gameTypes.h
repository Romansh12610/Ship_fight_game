#include <array>
#include "arrayFlat2d.h"
#include "gameRules.h"
#include "location.h"

using TupleLocChar = std::array<char, 2>;
using TupleLocInt = std::array<int, 2>;
using BoardLocations = ArrFlat2d<Location, GameRules::boardRowLength, GameRules::boardColLength>;