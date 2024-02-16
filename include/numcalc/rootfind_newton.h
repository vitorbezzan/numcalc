#ifndef __NUMCALC_NEWTON__
#define __NUMCALC_NEWTON__

#include <cmath>
#include <concepts>
#include <iostream>

#include "derivative.h"
#include "rootfind.h"

namespace RootFind {

template <typename PrT>
requires std::is_floating_point_v<PrT>
class Newton final: public BaseRootFind<PrT, PrT> {

public:
    Newton() = default;
    Newton(PrT (*function)(const PrT &), const PrT &x0, const int &n_iter = 50,
           const PrT &precision = 1e-4, const PrT &dx_precision = 1e-4)
        : BaseRootFind<PrT, PrT>(n_iter, precision) {
        _x0 = x0;
        _func = function;
        _dx_precision = dx_precision;
    }

    virtual PrT run() override {
        PrT x = _x0;
        PrT x_new = PrT(0);

        for (int N = 0; N < this->n_iter(); N++) {
            x_new = x - _func(x) / _derivative(_func, x, _dx_precision);

            if (std::fabs(x_new - x) <= this->precision())
                break;

            x = x_new;
        }

        return x;
    }

    void set_derivative(PrT (*d)(PrT (*f)(const PrT &), const PrT &x,
                                 const PrT &dx)) {
        _derivative = d;
    }

private:
    PrT (*_derivative)(PrT (*f)(const PrT &), const PrT &x,
                       const PrT &dx) = Derivatives::derivative4<PrT>;
    PrT (*_func)(const PrT &) = nullptr;
    PrT _x0 = 0.0;
    PrT _dx_precision = 1e-4;
};

} // namespace RootFind

#endif
