//integrals.cpp
#include "integrals.h"
#include <armadillo>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <utility>

// 1 NUMERICAL INTEGRATION IN ONE DIMENSION

// Define the Gaussian function according to the parameters
double gaussian_function(double x, double center, double exponent, int power) {
    if (exponent < 0) {
        throw std::invalid_argument("Exponent must be non-negative");
    }
    if (power < 0) {
        throw std::invalid_argument("Power must be non-negative");
    }
    
    double x_shifted = x - center;
    return std::pow(x_shifted, power) * std::exp(-exponent * x_shifted * x_shifted);
}

// Trapezoidal rule for numerical integration 
double trapezoidal_rule(std::function<double(double)> func, double a, double b, int num_points) {
    if (num_points <= 0) {
        throw std::invalid_argument("Number of points must be positive");
    }
    if (a >= b) {
        throw std::invalid_argument("Upper limit must be greater than lower limit");
    }

    double h = (b - a) / num_points;
    arma::vec evaluations(num_points + 1);

    for (int i = 0; i <= num_points; ++i) {
        double x = a + i * h;
        evaluations(i) = func(x);
    }

    double integral = arma::sum(evaluations) * h;
    integral -= 0.5 * (evaluations(0) + evaluations(num_points)) * h; // Adjust the endpoints

    return integral;
}

// Function to find suitable integration limits based on the Gaussian decay
std::pair<double, double> find_integration_limits(double center, double exponent, double tolerance) {
    double spread = std::sqrt(-std::log(tolerance) / exponent);
    return {center - spread, center + spread};
}

// Compute the overlap integral of two Gaussian functions with convergence check
double compute_overlap_integral(double alpha, double beta, int lA, int lB, double XA, double XB, double tolerance) {
    // Dynamic limits based on the Gaussian decay
    auto [lower_limit, upper_limit] = find_integration_limits((XA + XB) / 2, (alpha + beta) / 2, tolerance);

    // Initial parameters
    int num_points = 10;
    double previous_result = std::numeric_limits<double>::infinity();
    double current_result = 0.0;

    // Convergence loop
    do {
        previous_result = current_result;
        // Estimate the integral using the trapezoidal rule
        current_result = trapezoidal_rule(
            [alpha, beta, lA, lB, XA, XB](double x) {
                return gaussian_function(x, XA, alpha, lA) * gaussian_function(x, XB, beta, lB);
            },
            lower_limit, upper_limit, num_points
        );

        num_points *= 2; // Increase the number of points for better accuracy
        if (num_points <= 0) { // overflow check (assuming a very large number of points)
            throw std::overflow_error("Number of points exceeds maximum allowed value");
        }
    } while (std::abs(current_result - previous_result) > tolerance && num_points <= std::numeric_limits<int>::max() / 2);

    return current_result;
}


// 2 ANALYTICAL 3-D OVERLAP INTEGRAL OF PRIMITIVE GAUSSIANS

// Implementation of double factorial functions using a more efficient approach

unsigned long long double_factorial(int n) {
    if (n < 0) return 0;
    unsigned long long result = 1;
    for (int i = n; i > 0; i -= 2) {
        result *= i;
    }
    return result;
}

// Binomial coefficient calculation
unsigned long long binomial_coefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    unsigned long long result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= n - (k - i);
        result /= i;
    }
    return result;
}

double compute_polynomial_part(int lA, int lB, double PA, double PB, double gamma) {
    double polynomial_part = 0.0;
    for (int i = 0; i <= lA; ++i) {
        for (int j = 0; j <= lB; ++j) {
            if ((i + j) % 2 == 0) { // only even powers contribute
                double term = binomial_coefficient(lA, i) * binomial_coefficient(lB, j)
                               * double_factorial(i + j) * pow(PA, lA - i) * pow(PB, lB - j)
                               / pow(gamma, (i + j) / 2);
                polynomial_part += term;
            }
        }
    }
    return polynomial_part;
}

double compute_exponential_prefactor(double alpha, double beta, double xA, double xB) {
    double gamma = alpha + beta;
    return exp(-alpha * beta * (xA - xB) * (xA - xB) / gamma);
}

double compute_overlap_integral(double alpha, double beta, 
                                int lA, int mA, int nA, 
                                double XA, double YA, double ZA,
                                int lB, int mB, int nB, 
                                double XB, double YB, double ZB) {
    double gamma = alpha + beta;
    double prefactor = pow(M_PI / gamma, 1.5);

    double RPx = (alpha * XA + beta * XB) / gamma;
    double RPy = (alpha * YA + beta * YB) / gamma;
    double RPz = (alpha * ZA + beta * ZB) / gamma;

    double Sxx = compute_polynomial_part(lA, lB, RPx, XA - RPx, alpha + beta);
    double Syy = compute_polynomial_part(mA, mB, RPy, YA - RPy, alpha + beta);
    double Szz = compute_polynomial_part(nA, nB, RPz, ZA - RPz, alpha + beta);

    double expFactor = compute_exponential_prefactor(alpha, beta, XA, XB);

    return prefactor * Sxx * Syy * Szz * expFactor;
}
double compute_overlap_integral_3d(double alpha, double beta, 
                                   int lA, int mA, int nA, 
                                   double XA, double YA, double ZA,
                                   int lB, int mB, int nB, 
                                   double XB, double YB, double ZB) {
    // Calculate the product center
    double gamma = alpha + beta;
    arma::vec RA = {XA, YA, ZA};
    arma::vec RB = {XB, YB, ZB};
    arma::vec RP = (alpha * RA + beta * RB) / gamma;

    // Calculate the exponential prefactor
    double expFactor = compute_exponential_prefactor(alpha, beta, arma::dot(RA, RA), arma::dot(RB, RB));

    // Initialize the overlap integral
    double S = pow(M_PI / gamma, 1.5) * expFactor;

    // Compute the polynomial part for each cartesian component
    double Sxx = compute_polynomial_part(lA, lB, RP(0), RA(0) - RP(0), gamma);
    double Syy = compute_polynomial_part(mA, mB, RP(1), RA(1) - RP(1), gamma);
    double Szz = compute_polynomial_part(nA, nB, RP(2), RA(2) - RP(2), gamma);

    // Combine the polynomial parts
    S *= Sxx * Syy * Szz;

    return S;
}