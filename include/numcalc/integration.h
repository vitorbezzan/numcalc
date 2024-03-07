#ifndef __NUMCALC_INTEGRATION__
#define __NUMCALC_INTEGRATION__

namespace numcalc::integration_1d {
    // 1-D integrators and calculators
    template<typename T> requires std::is_floating_point_v<T>
    class BaseIntegrator {
        virtual T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) {
            return (b - a) / N;
        }
    };

    template<typename T> requires std::is_floating_point_v<T>
    class Rectangle : BaseIntegrator<T> {
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
        T integrate(T (*f)(const T &), const T &a, const T &b, const int &N) override {
            int n = N;
            if (N % 2)
                n += 1;

            auto step_size = BaseIntegrator<T>::integrate(f, a, b, n);

            T result = 0;
            for (int i = 0; i < (n / 2) + 1; i++) {
                result +=
                        f(a + (2 * i - 2) * step_size) + 4 * f(a + (2 * i - 1) * step_size) + f(a + 2 * i * step_size);
            }

            return result * (step_size / 3);
        }
    };
}

#endif
