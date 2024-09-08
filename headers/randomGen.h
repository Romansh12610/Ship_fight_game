#pragma once
#include <random>

template<typename GeneratedType>
class RandomGen {
public:
    RandomGen(GeneratedType min, GeneratedType max)
        : m_dist{ min, max }
    {
        std::random_device rd{};
        std::seed_seq sq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        m_mt.seed(sq);
    }

    GeneratedType gen() const { 
        auto& mt{ const_cast<std::mt19937&>(m_mt) };
        return const_cast<RandomGen<GeneratedType>*>(this)->m_dist(mt);
    }
private:
    std::mt19937 m_mt;
    std::uniform_int_distribution<GeneratedType> m_dist;
};