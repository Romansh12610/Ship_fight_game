#include "playerAiCash.h"
#include "userio.h"

void PlayerAiCash::initCash(const TupleLocInt& initAttackLoc) {
    m_valid = true;
    m_startAttackLocation = initAttackLoc;
    m_currAttackLocation = initAttackLoc;
    m_goodDirectionsForNextAttack = getGoodDirectionsForCurrentLoc();
}

void PlayerAiCash::eraseCash() {
    m_successAttackCount = 0;
    m_currGoodDirIndex = 0;
    m_valid = false;
}

void PlayerAiCash::incrementSuccessAttackCount() {
    m_successAttackCount++;
}

int PlayerAiCash::getSuccessAttackCount() const {
    return m_successAttackCount;
}

const TupleLocInt& PlayerAiCash::getNextAttackLocationAndUpdateState() {
    const PlayerDirection& currGoodDirection{ getCurrentAttackDir() };

    switch (currGoodDirection) {
    case PlayerDirection::TOP: 
        m_currAttackLocation[0]--;
        break;
    case PlayerDirection::BOTTOM:
        m_currAttackLocation[0]++;
        break;
    case PlayerDirection::LEFT:
        m_currAttackLocation[1]--;
        break;
    case PlayerDirection::RIGHT:
        m_currAttackLocation[1]++;
        break;
    default:
        assert(true && "not a valid switch case"); 
    }

    return m_currAttackLocation;
}

void PlayerAiCash::changeAttackDirectionToNext() {
    setCurrAttackLocToStart();
    m_currGoodDirIndex++;
};

void PlayerAiCash::changeAttackDirectionToOrthogonal() {
    setCurrAttackLocToStart();
    
    const auto& currAttackDir{ getCurrentAttackDir() };
    const PlayerDirection dirOrthogonalToCurr{ getOrthogonalDir(currAttackDir) };

    const int dirVectSize{ static_cast<int>(m_goodDirectionsForNextAttack.size()) };

    for (int i{ 0 }; i < dirVectSize; ++i) {
        if (m_goodDirectionsForNextAttack[i] == dirOrthogonalToCurr) {
            m_currGoodDirIndex = i;
            return;
        }
    }
};



// PRIVATE
const PlayerDirection& PlayerAiCash::getCurrentAttackDir() const {
    return m_goodDirectionsForNextAttack[m_currGoodDirIndex];
}

PlayerDirection PlayerAiCash::getOrthogonalDir(PlayerDirection dir) const {
     switch (dir) {
        case PlayerDirection::TOP: return PlayerDirection::BOTTOM;
        case PlayerDirection::BOTTOM: return PlayerDirection::TOP;
        case PlayerDirection::LEFT: return PlayerDirection::RIGHT;
        case PlayerDirection::RIGHT: return PlayerDirection::LEFT;
        // to avoid compiler warning
        default: return PlayerDirection::DIRS_COUNT;
    }
}

// checks border for next attack location from current
bool PlayerAiCash::checkDirectionBorderForNextAttack() const {
    const PlayerDirection& currAttackDir{ getCurrentAttackDir() };

    switch (currAttackDir) {
        case PlayerDirection::TOP: 
            return m_currAttackLocation[0] - 1 >= 0;
        case PlayerDirection::BOTTOM: 
            return m_currAttackLocation[0] + 1 < GameRules::boardRowLength;
        case PlayerDirection::LEFT: 
            return m_currAttackLocation[1] - 1 >= 0;
        case PlayerDirection::RIGHT:
            return m_currAttackLocation[1] + 1 < GameRules::boardColLength;
        // to avoid compiler warning
        default: return false;
    }
}

// overload for cash
std::vector<PlayerDirection> PlayerAiCash::getGoodDirectionsForCurrentLoc() const {
    std::vector<PlayerDirection> goodDirections;
    constexpr int directionCount{ 4 };
    goodDirections.reserve(directionCount);

    bool isCloseToVerticalBounds{ closeToVerticalBounds() };
    bool isCloseToHorizontalBounds{ closeToHorizontalBounds() };

    if (isCloseToVerticalBounds && !isCloseToHorizontalBounds) {
        goodDirections.push_back(PlayerDirection::LEFT);
        goodDirections.push_back(PlayerDirection::RIGHT);
        if ((m_currAttackLocation[0] - 1) >= 0) 
            goodDirections.push_back(PlayerDirection::TOP);
        if ((m_currAttackLocation[0] + 1) < GameRules::boardRowLength)
            goodDirections.push_back(PlayerDirection::BOTTOM);
    }
    else if (isCloseToHorizontalBounds && !isCloseToVerticalBounds) {
        goodDirections.push_back(PlayerDirection::TOP);
        goodDirections.push_back(PlayerDirection::BOTTOM);
        if ((m_currAttackLocation[1] - 1) >= 0) 
            goodDirections.push_back(PlayerDirection::LEFT);
        if ((m_currAttackLocation[1] + 1) < GameRules::boardColLength)
            goodDirections.push_back(PlayerDirection::RIGHT);
    }
    else {
        if ((m_currAttackLocation[0] - 1) >= 0) 
            goodDirections.push_back(PlayerDirection::TOP);
        if ((m_currAttackLocation[0] + 1) < GameRules::boardRowLength)
            goodDirections.push_back(PlayerDirection::BOTTOM);
        if ((m_currAttackLocation[1] - 1) >= 0) 
            goodDirections.push_back(PlayerDirection::LEFT);
        if ((m_currAttackLocation[1] + 1) < GameRules::boardColLength)
            goodDirections.push_back(PlayerDirection::RIGHT);
    }

    return goodDirections;
}

void PlayerAiCash::setCurrAttackLocToStart() {
    m_currAttackLocation = m_startAttackLocation;
}

bool PlayerAiCash::closeToVerticalBounds() const {
    return m_currAttackLocation[0] == 0 || m_currAttackLocation[0] == (GameRules::boardRowLength - 1);
}

bool PlayerAiCash::closeToHorizontalBounds() const {
    return m_currAttackLocation[1] == 0 || m_currAttackLocation[1] == (GameRules::boardColLength - 1);
}