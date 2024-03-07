#ifndef __NUMCALC_BASEROOT__
#define __NUMCALC_BASEROOT__

#include <concepts>

namespace numcalc::root {
    // Rootfinding techniques for explicit equations

    template<typename OutT, typename PrT> requires std::is_floating_point_v<PrT>
    class BaseRootFind {
    public:
        BaseRootFind() = default;

        BaseRootFind(const int &n_iter, const PrT &precision) {
            _n_iter = n_iter;
            _precision = precision;
        }

        virtual ~BaseRootFind() = default;

        virtual OutT run() {
            return OutT();
        }

        int n_iter() const {
            return _n_iter;
        }

        PrT precision() const {
            return _precision;
        }

    private:
        int _n_iter = 50;
        PrT _precision = 1e-4;
    };

    // Newton rootfinding method
    template<typename PrT> requires std::is_floating_point_v<PrT>
    class Newton final : public BaseRootFind<PrT, PrT> {
    public:
        Newton() = default;

        Newton(PrT (*f)(const PrT &), const PrT &x0, const int &n_iter = 50,
               const PrT &precision = 1e-4, const PrT &dx_precision = 1e-4)
                : BaseRootFind<PrT, PrT>(n_iter, precision) {
            _x0 = x0;
            _func = f;
            _dx_precision = dx_precision;
        }

        PrT run() override {
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
                           const PrT &dx) = derivatives::derivative4<PrT>;

        PrT (*_func)(const PrT &) = nullptr;

        PrT _x0 = 0.0;
        PrT _dx_precision = 1e-4;
    };
}

#endif
