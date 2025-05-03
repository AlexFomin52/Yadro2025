#include "fft.h"
#include <iostream>
#include <iomanip>

using namespace std;

void print_complex_vector(const string& title, const vector<complex<double>>& v) {
    cout << title << ":\n";
    for (const auto& x : v) {
        cout << "  " << fixed << setprecision(5)
            << "(" << x.real() << ", " << x.imag() << "i)\n";
    }
    cout << endl;
}

int main() {
    // Тест для N=2
    {
        vector<complex<double>> signal = { 0.7649 -0.408i , 0.76059 + 0.96364i };
        print_complex_vector("Input signal (N=2)", signal);

        auto spectrum = FFT::transform(signal);
        print_complex_vector("FFT spectrum (N=2)", spectrum);

        auto reconstructed = FFT::inverse_transform(spectrum);
        print_complex_vector("Reconstructed signal (N=2)", reconstructed);
    }

    // Тест для N=3
    {
        vector<complex<double>> signal = { -0.26694 + 0.62342i, 0.71211 -0.49794i, 0.28344 -0.80364i };
        print_complex_vector("Input signal (N=3)", signal);

        auto spectrum = FFT::transform(signal);
        print_complex_vector("FFT spectrum (N=3)", spectrum);

        auto reconstructed = FFT::inverse_transform(spectrum);
        print_complex_vector("Reconstructed signal (N=3)", reconstructed);
    }

    // Тест для N=5
    {
        vector<complex<double>> signal = { 0.68292 -0.28014i, -0.50664 -0.49681i, 0.25191 -0.17211i, -0.60002 + 0.77555i, -0.21111 + 0.8i };
        print_complex_vector("Input signal (N=5)", signal);

        auto spectrum = FFT::transform(signal);
        print_complex_vector("FFT spectrum (N=5)", spectrum);

        auto reconstructed = FFT::inverse_transform(spectrum);
        print_complex_vector("Reconstructed signal (N=5)", reconstructed);
    }

    return 0;
}
