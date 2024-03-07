#ifndef __NUMCALC_MATRIX__
#define __NUMCALC_MATRIX__

#include <cblas.h>
#include <stdexcept>

#include "base_array.h"
#include "vector.h"

namespace numcalc::multirray {
    // Definitions for multiarrays - matrix

    template<typename T>
    class Matrix final : public BaseArray<T> {
        friend class Matrix<T>;

    public:
        Matrix() : BaseArray<T>() {
        }

        Matrix(const int &rows, const int &cols) : BaseArray<T>({rows, cols}) {
            _rows = rows;
            _cols = cols;
        }

        Matrix(const int &rows, const int &cols, const T &value) : BaseArray<T>({rows, cols}, value) {
            _rows = rows;
            _cols = cols;
        }

        Matrix(const Matrix<T> &M) : BaseArray<T>(M) {
            _rows = M._rows;
            _cols = M._cols;
        }

        Matrix(const BaseArray<T> &base) : BaseArray<T>(base) {
            _rows = base.dimensions()[0];
            _cols = base.dimensions()[1];
        }

        T &operator()(const int &row, const int &col) {
            return BaseArray<T>::operator()({row, col});
        }

        Matrix(T (*f)(const T &, const T &)) {
            for (int row = 0; row < _rows; row++)
                for (int col = 0; col < _cols; col++)
                    this->operator()(row, col) = f(row, col);
        }

        int rows() const {
            return _rows;
        }

        int cols() const {
            return _cols;
        }

    private:
        int _rows = 0;
        int _cols = 0;
    };

    // Matrix * scalar

    template<typename T, typename PrT>
    requires std::is_arithmetic_v<PrT>
    Matrix<T> operator*(const Matrix<T> &M, const PrT &value) {
        throw std::runtime_error("Unsupported type for multiply");
    }

    template<typename PrT>
    requires std::is_arithmetic_v<PrT>
    Matrix<float> operator*(const Matrix<float> &M, const PrT &value) {
        auto result = Vector<float>(M);
        cblas_sscal(result.nelements(), (float) value, result.data(), 1);

        return result;
    }

    template<typename PrT>
    requires std::is_arithmetic_v<PrT>
    Matrix<float> operator*(const PrT &value, const Matrix<float> &M) {
        auto result = Vector<float>(M);
        cblas_sscal(result.nelements(), (float) value, result.data(), 1);

        return result;
    }

    template<typename PrT>
    requires std::is_arithmetic_v<PrT>
    Matrix<double> operator*(const Matrix<double> &M, const PrT &value) {
        auto result = Vector<double>(M);
        cblas_dscal(result.nelements(), (double) value, result.data(), 1);

        return result;
    }

    template<typename PrT>
    requires std::is_arithmetic_v<PrT>
    Matrix<double> operator*(const PrT &value, const Matrix<double> &M) {
        auto result = Vector<double>(M);
        cblas_dscal(result.nelements(), (double) value, result.data(), 1);

        return result;
    }

    // Matrix * vector

    template<typename T>
    Vector<T> operator*(Matrix<T> &left, Vector<T> &right) {
        throw std::runtime_error("Unsupported type for multiply");
    }

    template<>
    inline Vector<float> operator*<float>(Matrix<float> &left, Vector<float> &right) {
        if (left.cols() != right.nelements())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto result = Vector<float>(left.rows());
        cblas_sgemv(CblasRowMajor, CblasNoTrans, left.rows(), left.cols(), 1.0, left.data(), left.rows(), right.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    template<>
    inline Vector<double> operator*<double>(Matrix<double> &left, Vector<double> &right) {
        if (left.cols() != right.nelements())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto result = Vector<double>(left.rows());
        cblas_dgemv(CblasRowMajor, CblasNoTrans, left.rows(), left.cols(), 1.0, left.data(), left.rows(), right.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    // Vector * Matrix

    template<typename T>
    Vector<T> operator*(Vector<T> &left, Matrix<T> &right) {
        throw std::runtime_error("Unsupported type for multiply");
    }

    template<>
    inline Vector<float> operator*<float>(Vector<float> &left, Matrix<float> &right) {
        if (left.nelements() != right.rows())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto result = Vector<float>(right.cols());
        cblas_sgemv(CblasRowMajor, CblasTrans, right.rows(), right.cols(), 1.0, right.data(), right.rows(), left.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    template<>
    inline Vector<double> operator*<double>(Vector<double> &left, Matrix<double> &right) {
        if (left.nelements() != right.rows())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto result = Vector<double>(right.cols());
        cblas_dgemv(CblasRowMajor, CblasTrans, right.rows(), right.cols(), 1.0, right.data(), right.rows(), left.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    // Matrix * Matrix

    template<typename T>
    Matrix<T> operator*(Matrix<T> &left, Matrix<T> &right) {
        throw std::runtime_error("Unsupported type for multiply");
    }

    template<>
    inline Matrix<float> operator*(Matrix<float> &left, Matrix<float> &right) {
        if (left.cols() != right.rows())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto C = Matrix<float>(left.rows(), right.cols());
        cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, left.rows(), right.cols(), left.cols(), 1.0, left.data(),
                    left.rows(), right.data(), right.rows(), 1.0, C.data(), left.rows());

        return C;
    }

    template<>
    inline Matrix<double> operator*(Matrix<double> &left, Matrix<double> &right) {
        if (left.cols() != right.rows())
            throw std::runtime_error("Invalid axis sizes for multiply");

        auto C = Matrix<double>(left.rows(), right.cols());
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, left.rows(), right.cols(), left.cols(), 1.0, left.data(),
                    left.rows(), right.data(), right.rows(), 1.0, C.data(), left.rows());

        return C;
    }
}

#endif
