#include "fft.h"

bool FFT::is_valid_size(size_t n) {
    return n == 2 || n == 3 || n == 5;
}

std::vector<std::complex<double>> FFT::transform(
    const std::vector<std::complex<double>>& input,
    bool inverse
) {
    size_t N = input.size();
    if (!is_valid_size(N)) {
        throw std::invalid_argument("Size must be 2, 3 or 5");
    }

    std::vector<std::complex<double>> output(N);
    double angle = (inverse ? 2 : -2) * PI / N;

    for (size_t k = 0; k < N; ++k) {
        output[k] = 0; 
        for (size_t n = 0; n < N; ++n) {
            double phi = angle * k * n;
            output[k] += input[n] * std::complex<double>(cos(phi), sin(phi));
        }
        if (inverse) {
            output[k] /= N;
        }
    }

    return output;
}

std::vector<std::complex<double>> FFT::inverse_transform(
    const std::vector<std::complex<double>>& input
) {
    return transform(input, true);
}