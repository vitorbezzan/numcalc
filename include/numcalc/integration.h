#ifndef __NUMCALC_INTEGRATION__
#define __NUMCALC_INTEGRATION__

namespace numcalc::integration_1d {
    // 1-D integrators and calculators
    template<typename T> requires std::is_floating_point_v<T>
    class BaseIntegrator {
    public:
        virtual T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) {
            return (b - a) / N;
        }
    };

    template<typename T> requires std::is_floating_point_v<T>
    class Rectangle : BaseIntegrator<T> {
    public:
        T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) override {
            auto step_size = BaseIntegrator<T>::integrate(f, a, b, N);

            T result = 0;
            for (int i = 0; i < N; i++) {
                result += f(a + i * step_size);
            }

            return result * step_size;
        }
    };

    template<typename T> requires std::is_floating_point_v<T>
    class Trapezium : BaseIntegrator<T> {
    public:
        T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) override {
            auto step_size = BaseIntegrator<T>::integrate(f, a, b, N);

            T result = 0;
            for (int i = 0; i < N; i++) {
                result += (f(a + i * step_size) + f(a + (i + 1) * step_size));
            }

            return result * (step_size / 2);
        }
    };

    template<typename T> requires std::is_floating_point_v<T>
    class Simpson : BaseIntegrator<T> {
    public:
        T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) override {
            auto step_size = BaseIntegrator<T>::integrate(f, a, b, N);

            T result = 0;
            for (int i = 0; i < N; i++) {
                auto a_n = (a + step_size * i);
                result += f(a_n) + 4 * f(a_n + step_size / 2) + f(a_n + step_size);
            }

            return result * (step_size / 6);
        }
    };
}

#endif
