#ifndef __NUMCALC_VECTOR__
#define __NUMCALC_VECTOR__

#include <cblas.h>
#include <cmath>
#include <stdexcept>

#include "base_array.h"

namespace Matrix {

template<typename T = float>
class Vector: public BaseArray<T> {

    friend class Vector<T>;

public:
    Vector(): BaseArray<T>() {}
    Vector(const int &N): BaseArray<T>({N}) {}
    Vector(const int &N, const T &value): BaseArray<T>({N}, value) {}
    Vector(const BaseArray<T> &base): BaseArray<T>(base) {}

    T& operator[](const int &i) {
        return BaseArray<T>::operator()({i});
    }

    Vector(T (*function)(const T &)) {
        for(int i = 0; i < this->nelements(); i++)
            this->operator[](i) = function(i);
    }

};

// Vector * scalar

template<typename T, typename PrT>
requires std::is_arithmetic_v<PrT>
Vector<T> operator*(const Vector<T> &V, const PrT &value) {
    throw std::runtime_error("Unsupported type for multiply");
}


template<typename PrT>
requires std::is_arithmetic_v<PrT>
Vector<float> operator*(const Vector<float> &V, const PrT &value) {
    auto result = Vector<float>(V);
    cblas_sscal(result.nelements(), (float)value, result.data(), 1);

    return result;
}

template<typename PrT>
requires std::is_arithmetic_v<PrT>
Vector<float> operator*(const PrT &value, const Vector<float> &V) {
    auto result = Vector<float>(V);
    cblas_sscal(result.nelements(), (float)value, result.data(), 1);

    return result;
}

template<typename PrT>
requires std::is_arithmetic_v<PrT>
Vector<double> operator*(const Vector<double> &V, const PrT &value) {
    auto result = Vector<double>(V);
    cblas_dscal(result.nelements(), (double)value, result.data(), 1);

    return result;
}

template<typename PrT>
requires std::is_arithmetic_v<PrT>
Vector<double> operator*(const PrT &value, const Vector<double> &V) {
    auto result = Vector<double>(V);
    cblas_dscal(result.nelements(), (double)value, result.data(), 1);

    return result;
}

float dot(Vector<float> &left, Vector<float> &right) {
    if (left.nelements() != right.nelements())
        throw std::runtime_error("Axis size error");

    return cblas_sdot(left.nelements(), left.data(), 1, right.data(), 1);
}

double dot(Vector<double> &left, Vector<double> &right) {
    if (left.nelements() != right.nelements())
        throw std::runtime_error("Axis size error");

    return cblas_ddot(left.nelements(), left.data(), 1, right.data(), 1);
}

template<typename T>
T fabs(Vector<T> &v) {
    return std::sqrt(dot(v,v));
}

}
#endif
