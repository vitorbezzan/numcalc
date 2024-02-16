#ifndef __NUMCALC_BASEROOT__
#define __NUMCALC_BASEROOT__

#include <concepts>

namespace RootFind {

template <typename OutT, typename PrT>
requires std::is_floating_point_v<PrT>
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

} // namespace RootFind

#endif
