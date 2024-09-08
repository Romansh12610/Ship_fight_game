#ifndef ARRAYFLAT2D_H
#define ARRAYFLAT2D_H

#include <array>
#include <corecrt.h>
#include <cassert>
//#include "gameLoop.h"

template<typename T, size_t Rows, size_t Cols>
using ArrFlat2d_t = std::array<T, Rows * Cols>;

template<typename T, size_t Rows, size_t Cols>
class ArrFlat2d {
public:
    ArrFlat2d() = default;

    T& operator[](int ind) { 
        assert((ind >= 0 && ind < length()) && "Invalid indexing of ArrFlat2d");
        return m_arr[ind];
    }
    const T& operator[](int ind) const { 
        assert((ind >= 0 && ind < length()) && "Invalid indexing of ArrFlat2d");
        return m_arr[ind]; 
    }

    T& operator()(int row, int col) {
        int ind{ row * cols() + col };
        assert((ind >= 0 && ind < length()) && "Invalid indexing of ArrFlat2d");
        return m_arr[ind];
    }

    const T& operator()(int row, int col) const {
        int ind{ row * cols() + col };
        assert((ind >= 0 && ind < length()) && "Invalid indexing of ArrFlat2d");
        return m_arr[ind];
    }
    
    constexpr int rows() const { return static_cast<int>(Rows); }
    constexpr int cols() const { return static_cast<int>(Cols); }
    constexpr int length() const { return static_cast<int>(Rows * Cols); }

private:
    ArrFlat2d_t<T, Rows, Cols> m_arr;
};

#endif // ARRAYFLAT2D_H