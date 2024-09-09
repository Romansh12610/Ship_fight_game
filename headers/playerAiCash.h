#include <vector>
#include "gameTypes.h"
#include "playerTypes.h"

struct PlayerAiCash {
public:
    void initCash(const TupleLocInt& initAttackLoc);
    void eraseCash();
    void incrementSuccessAttackCount();
    const TupleLocInt& getNextAttackLocationAndUpdateState();
    bool isValid() const { return m_valid; }
    void changeAttackDirectionToNext();
    void changeAttackDirectionToOrthogonal();
    bool checkDirectionBorderForNextAttack() const;
    int getSuccessAttackCount() const;

private:
    // flag for checking cash valid state
    bool m_valid{ false };
    // does not include success attacks from random gen locations
    int m_successAttackCount{ 0 };
    int m_currGoodDirIndex{ 0 };
    TupleLocInt m_startAttackLocation;
    TupleLocInt m_currAttackLocation;
    std::vector<PlayerDirection> m_goodDirectionsForNextAttack;

    const PlayerDirection& getCurrentAttackDir() const;
    PlayerDirection getOrthogonalDir(PlayerDirection dir) const;
    std::vector<PlayerDirection> getGoodDirectionsForCurrentLoc() const;
    void setCurrAttackLocToStart();
    bool closeToVerticalBounds() const;
    bool closeToHorizontalBounds() const;
};