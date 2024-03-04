#ifndef __NUMCALC_EFDE__
#define __NUMCALC_EFDE__

#include <concepts>
#include <utility>
#include <vector>

namespace numcalc::explicit_fde {
    // Explicit first order differential equations

    template<typename T>
        requires std::is_floating_point_v<T>
    class FDESolution {
    public:

    private:
        std::vector<std::pair<T, T>> _solution;

    };
}

#endif