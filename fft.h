#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>

class FFT {
private:
    static constexpr double PI = 3.14159265358979323846;
public:

    static bool is_valid_size(size_t n);

    static std::vector<std::complex<double>> transform(
        const std::vector<std::complex<double>>& input,
        bool inverse = false
    );

    static std::vector<std::complex<double>> inverse_transform(
        const std::vector<std::complex<double>>& input
    );
};

#endif 