#ifndef __NUMCALC_BASET__
#define __NUMCALC_BASET__

#include <algorithm>
#include <concepts>
#include <numeric>
#include <stdexcept>

namespace Matrix {
    template<typename T = float>
        requires std::is_arithmetic_v<T>
    class BaseArray {
        friend class BaseArray<T>;

    public:
        BaseArray() = default;

        template<int N>
        explicit BaseArray(const int (&dimensions)[N]) {
            _set_storage(N, dimensions);
        }

        template<int N>
        BaseArray(const int (&dimensions)[N], const T &value)
            : BaseArray(dimensions) {
            std::fill_n(_data, _nelements, value);
        }

        BaseArray(BaseArray<T> &&src) noexcept {
            _nelements = src._nelements;
            _ndim = src._ndim;
            _dimensions = src._dimensions;
            _data = src._data;

            src._dimensions = nullptr;
            src._data = nullptr;
        }

        virtual ~BaseArray() {
            delete[] _dimensions;
            delete[] _data;
        }

        int nelements() const {
            return _nelements;
        }

        int ndim() const {
            return _ndim;
        }

        int *dimensions() const {
            return _dimensions;
        }

        T *data() {
            return _data;
        }

        template<int N>
        T &operator()(const int (&index)[N]) {
            int _index = 0;
            for (int i = 0; i < N; i++) {
                int _product = 1;
                for (int j = i + 1; j < N; j++) {
                    _product *= _dimensions[j];
                }
                _index += index[i] * _product;
            }

            return _data[_index];
        }

        BaseArray(const BaseArray<T> &right) {
            _set_storage(right._ndim, right._dimensions);

            std::copy(right._dimensions, right._dimensions + right._ndim, _dimensions);
            std::copy(right._data, right._data + right._nelements, _data);
        }

        BaseArray<T> &operator=(const BaseArray<T> &right) {
            if (this != &right) {
                _set_storage(right._ndim, right._dimensions);

                std::copy(right._dimensions, right._dimensions + right._ndim, _dimensions);
                std::copy(right._data, right._data + right._nelements, _data);
            }

            return *this;
        }

        BaseArray<T> &operator+=(const BaseArray<T> &right) {
            _check_sizes(right);

            std::transform(
                _data,
                _data + _nelements,
                right._data,
                _data,
                std::plus<T>());

            return *this;
        }

        BaseArray<T> &operator-=(const BaseArray<T> &right) {
            _check_sizes(right);

            std::transform(
                _data,
                _data + _nelements,
                right._data,
                _data,
                std::minus<T>());

            return *this;
        }

        BaseArray<T> operator+(const BaseArray<T> &right) const {
            return BaseArray<T>(*this) += right;
        }

        BaseArray<T> operator-(const BaseArray<T> &right) const {
            return BaseArray<T>(*this) -= right;
        }

        virtual void print() {
        }

    private:
        int _nelements = 0;
        int _ndim = 0;
        int *_dimensions = nullptr;
        T *_data = nullptr;

        void _set_storage(const int &N, const int *dimensions) {
            if (_data != nullptr)
                delete[] _data;
            if (_dimensions != nullptr)
                delete[] _dimensions;

            _ndim = N;
            _nelements = 1;
            _dimensions = new int[N];

            for (int i = 0; i < N; i++) {
                _dimensions[i] = dimensions[i];
                _nelements *= dimensions[i];
            }

            _data = new T[_nelements]();
        }

        void _check_sizes(const BaseArray<T> &other) {
            auto n_check = (_nelements == other._nelements);
            auto d_check = std::equal(_dimensions, _dimensions + _ndim, other._dimensions);

            if (!n_check)
                throw std::runtime_error("Element number mismatch");

            if (!d_check)
                throw std::runtime_error("Dimesion size mismatch");
        }
    };
} // namespace Matrix

#endif
