#ifndef __NUMCALC_EFDE__
#define __NUMCALC_EFDE__

#include <concepts>
#include <utility>
#include <vector>

namespace numcalc::explicit_fde {
    // Explicit first order differential equations

    template<typename T = float> requires std::is_floating_point_v<T>
    class FDESolution {
    public:
        FDESolution(const T &x0, const T &y0, const T &step_size, const int &steps) {
            _x = std::vector(steps + 1, x0);
            _y = std::vector(steps + 1, y0);

            for (int step = 1; step <= steps; step++)
                _x[step] = _x[0] + (step_size * step);
        }

        virtual ~FDESolution() = default;

        T &operator[](int step) {
            return _y[step];
        }

        int size() { return _x.size(); }

        std::vector<std::pair<T, T>> solution() {
            auto result = std::vector<std::pair<T, T>>(_x.size());
            for (int i = 0; i < _x.size(); i++)
                result[i] = std::make_pair(_x[i], _y[i]);

            return result;
        }

    private:
        std::vector<T> _x;
        std::vector<T> _y;

    };

    template<typename T = float> requires std::is_floating_point_v<T>
    class FDEBase {
    public:
        explicit FDEBase(const T &x0, const T &y0, const T &step_size = 1e-4) {
            _x0 = x0;
            _y0 = y0;
            _step_size = step_size;
        }

        virtual ~FDEBase() = default;

        T x0() { return _x0; }

        T y0() { return _y0; }

        T step_size() { return _step_size; }

        virtual FDESolution<T> run(T (*function)(const T &, const T &), int steps) {
            return FDESolution<T>(_x0, _y0, _step_size, steps);
        }

    private:
        T _x0;
        T _y0;
        T _step_size;
    };

    template<typename T = float> requires std::is_floating_point_v<T>
    class Euler final : FDEBase<T> {
    public:
        Euler(const T &x0, const T &y0, const T &step_size = 0.01) : FDEBase<T>(x0, y0, step_size) {}

        FDESolution<T> run(T (*function)(const T &, const T &), int steps) override {
            auto solution = FDEBase<T>::run(function, steps);
            auto x = this->x0();

            for (int step = 1; step <= steps; step++) {
                solution[step] = solution[step - 1] + (function(x, solution[step - 1]) * this->step_size());

                x += this->step_size();
            }

            return solution;
        }
    };

    template<typename T = double> requires std::is_floating_point_v<T>
    class RK4 final : FDEBase<T> {
    public:
        RK4(const T &x0, const T &y0, const T &step_size = 0.01) : FDEBase<T>(x0, y0, step_size) {}

        FDESolution<T> run(T (*function)(const T &, const T &), int steps) override {
            auto solution = FDEBase<T>::run(function, steps);
            auto x = this->x0();

            for (int step = 1; step <= steps; step++) {
                auto k1 = function(x, solution[step - 1]);
                auto k2 = function(x + (this->step_size() / 2), solution[step - 1] + this->step_size() * (k1 / 2));
                auto k3 = function(x + (this->step_size() / 2), solution[step - 1] + this->step_size() * (k2 / 2));
                auto k4 = function(x + this->step_size(), solution[step - 1] + this->step_size() * k3);

                solution[step] = solution[step - 1] + (this->step_size() / 6) * (k1 + 2 * k2 + 2 * k3 + k4);

                x += this->step_size();
            }

            return solution;
        }
    };

}

#endif