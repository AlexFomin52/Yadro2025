// fft.cpp
#include "fft.h"
#include <algorithm>
#include <iterator>

bool FFT::is_valid_size(size_t n) {
    if (n == 0) return false;
    while (n % 2 == 0) n /= 2;
    while (n % 3 == 0) n /= 3;
    while (n % 5 == 0) n /= 5;
    return n == 1;
}

void FFT::factorize(size_t n, std::vector<size_t>& factors) {
    factors.clear();
    if (n == 1) return;

 
    while (n % 5 == 0) {
        factors.push_back(5);
        n /= 5;
    }

 
    while (n % 3 == 0) {
        factors.push_back(3);
        n /= 3;
    }


    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    if (n != 1) {
        throw std::invalid_argument("Size must be a product of 2, 3 and 5");
    }
}

void FFT::reorder(std::vector<std::complex<double>>& data) {
    size_t n = data.size();
    size_t j = 0;

    for (size_t i = 0; i < n; ++i) {
        if (j > i) {
            std::swap(data[i], data[j]);
        }

        size_t m = n;
        while (j >= (m /= 2) && m >= 1) {
            j -= m;
        }
        j += m;
    }
}

void FFT::compute(std::vector<std::complex<double>>& data, bool inverse) {
    size_t n = data.size();
    double angle = (inverse ? 2 : -2) * PI / n;

    for (size_t k = 0; k < n; ++k) {
        std::complex<double> sum = 0;
        for (size_t m = 0; m < n; ++m) {
            double phi = angle * k * m;
            sum += data[m] * std::complex<double>(cos(phi), sin(phi));
        }
        if (inverse) {
            sum /= n;
        }
        data[k] = sum;
    }
}

void FFT::fft_recursive(std::vector<std::complex<double>>& data, bool inverse) {
    size_t n = data.size();
    if (n <= 1) return;

    if (n == 2 || n == 3 || n == 5) {
        compute(data, inverse);
        return;
    }

    std::vector<size_t> factors;
    factorize(n, factors);
    size_t factor = factors.back();
    factors.pop_back();
    size_t m = n / factor;

    std::vector<std::vector<std::complex<double>>> temp(factor, std::vector<std::complex<double>>(m));
    for (size_t i = 0; i < factor; ++i) {
        for (size_t j = 0; j < m; ++j) {
            temp[i][j] = data[i + j * factor];
        }
    }

    for (auto& row : temp) {
        fft_recursive(row, inverse);
    }

    double angle = (inverse ? 2 : -2) * PI / n;
    for (size_t j = 0; j < m; ++j) {
        std::vector<std::complex<double>> temp2(factor);
        for (size_t i = 0; i < factor; ++i) {
            double phi = angle * i * j;
            std::complex<double> w(cos(phi), sin(phi));
            temp2[i] = temp[i][j] * w;
        }
        compute(temp2, false); 

        for (size_t i = 0; i < factor; ++i) {
            data[j + i * m] = temp2[i];
        }
    }
}

std::vector<std::complex<double>> FFT::transform(
    const std::vector<std::complex<double>>& input,
    bool inverse
) {
    size_t N = input.size();
    if (!is_valid_size(N)) {
        throw std::invalid_argument("Size must be a product of 2, 3 and 5");
    }

    std::vector<std::complex<double>> output = input;
    fft_recursive(output, inverse);
    return output;
}

std::vector<std::complex<double>> FFT::inverse_transform(
    const std::vector<std::complex<double>>& input
) {
    return transform(input, true);
}