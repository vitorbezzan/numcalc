#ifndef __NUMCALC_DERIVATIVE__
#define __NUMCALC_DERIVATIVE__

#include <concepts>
#include <functional>

namespace numcalc::derivatives {
    // Definitions for derivatives

    template<typename T>
    requires std::is_floating_point_v<T>
    inline T derivative2(T (*f)(const T &), const T &x, const T &dx)
    // 2-th order derivative for floating types
    {
        return (f(x + dx) - f(x - dx)) / (2 * dx);
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    inline T derivative4(T (*f)(const T &), const T &x, const T &dx)
    // 4-th order derivative for floating types
    {
        return (-f(x + 2 * dx) + 8 * f(x + dx) - 8 * f(x - dx) + f(x - 2 * dx)) /
               (12 * dx);
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    inline T derivative(T (*f)(const T &), const T &x, const T &dx,
                        const int &order = 4) {
        if (order == 2)
            return derivative2(f, x, dx);

        return derivative4(f, x, dx);
    }
}

#endif
