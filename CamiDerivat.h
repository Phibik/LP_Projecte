#pragma once
#include "CamiBase.h"
#include "Common.h"
#include <vector>

class CamiDerivat : public CamiBase {
private:
    std::vector<Coordinate> m_coords;

public:
    CamiDerivat(const std::vector<Coordinate>& coords) : m_coords(coords) {}

    std::vector<Coordinate> getCamiCoords() override {
        return m_coords;
    }
};