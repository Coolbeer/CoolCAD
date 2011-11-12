#ifndef PWANMATH_H
#define PWANMATH_H

#include <vector>
#include <boost/cstdint.hpp>

namespace pwan
{
    namespace math
    {
        double distance(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B);
        int cross(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B, const std::vector<uint32_t> &C);
        int dot(const std::vector<uint32_t> &A, const std::vector<uint32_t> &B, const std::vector<uint32_t> &C);
    }
}

#endif
