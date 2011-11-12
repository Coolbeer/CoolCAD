#include "pwanmath.h"

double pwan::math::distance(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B)
{
    int dx = A.at(0) - B.at(0);
    int dy = A.at(1) - B.at(1);
    return sqrt(static_cast<double>(dx)*dx + dy*dy);
}

int pwan::math::dot(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B, const std::vector<uint32_t> &C)
{
    int dot = (B.at(0) - A.at(0)) * (C.at(0) - B.at(0)) + (B.at(1) - A.at(1)) * (C.at(1) - B.at(1));
    return dot;
}

int pwan::math::cross(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B, const std::vector<uint32_t> &C)
{
    int cross = (B.at(0) - A.at(0)) * (C.at(1) - A.at(1)) - (B.at(1) - A.at(1)) * (C.at(0) - A.at(0));
    return cross;
}
