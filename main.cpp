#include "fft.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <random>
using namespace std;

void print_complex_vector(const string& title, const vector<complex<double>>& v) {
    cout << title << ":\n";
    for (const auto& x : v) {
        cout << "  " << fixed << setprecision(5)
            << "(" << x.real() << ", " << x.imag() << "i)\n";
    }
    cout << endl;
}

vector<complex<double>> generate_random_signal(size_t n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-1.0, 1.0);

    vector<complex<double>> signal(n);
    for (size_t i = 0; i < n; ++i) {
        signal[i] = { dis(gen), dis(gen) };
    }
    return signal;
}
void check_reconstruction(const vector<complex<double>>& original,
    const vector<complex<double>>& reconstructed) {
    double max_error = 0.0;
    double avg_error = 0.0;

    for (size_t i = 0; i < original.size(); ++i) {
        double error = abs(original[i] - reconstructed[i]);
        max_error = max(max_error, error);
        avg_error += error;
    }
    avg_error /= original.size();

    cout << "Reconstruction accuracy:\n";
    cout << "  Max error: " << scientific << setprecision(6) << max_error << "\n";
    cout << "  Avg error: " << scientific << setprecision(6) << avg_error << "\n\n";
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

    // Тест для 360
    {
        const size_t N = 360;
        cout << "Input signal (N=360)\n";

  
        auto signal = generate_random_signal(N);
        print_complex_vector("First 10 elements of input signal (N=360)", signal);

  
        auto spectrum = FFT::transform(signal);
        print_complex_vector("First 10 elements of FFT spectrum (N=360)", spectrum);

   
        auto reconstructed = FFT::inverse_transform(spectrum);
        print_complex_vector("First 10 elements of reconstructed signal (N=360)", reconstructed);

   
        check_reconstruction(signal, reconstructed);

      
        vector<complex<double>> real_signal(N);
        for (size_t i = 0; i < N; ++i) {
            real_signal[i] = { double(i % 10), 0.0 }; 
        }

        auto real_spectrum = FFT::transform(real_signal);
        cout << "Checking symmetry for real-valued signal:\n";
        for (size_t k = 1; k <= 5; ++k) {
            size_t conjugate_k = N - k;
            cout << "  X[" << k << "] = (" << real_spectrum[k].real() << ", " << real_spectrum[k].imag() << "i)\n";
            cout << "  X[" << conjugate_k << "] = (" << real_spectrum[conjugate_k].real() << ", "
                << real_spectrum[conjugate_k].imag() << "i) \n";
        }
        cout << endl;
    }

    return 0;
}
