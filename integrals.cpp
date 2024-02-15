#include "integrals.h"
#include <armadillo>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <functional>

using namespace std;

// Define the Gaussian function according to the parameters
double gaussian_function(double x, double center, double exponent, int power) {
    if (exponent < 0) {
        throw invalid_argument("Exponent must be non-negative");
    }
    if (power < 0) {
        throw invalid_argument("Power must be non-negative");
    }
    
    double x_shifted = x - center;
    return pow(x_shifted, power) * exp(-exponent * x_shifted * x_shifted);
}

// Trapezoidal rule for numerical integration 
double trapezoidal_rule(function<double(double)> func, double a, double b, int num_points) {
    if (num_points <= 0) {
        throw invalid_argument("Number of points must be positive");
    }
    if (a >= b) {
        throw invalid_argument("Upper limit must be greater than lower limit");
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
pair<double, double> find_integration_limits(double center, double exponent, double tolerance) {
    double spread = sqrt(-log(tolerance) / exponent);
    return {center - spread, center + spread};
}

// Compute the overlap integral of two Gaussian functions with convergence check
double compute_overlap_integral(double alpha, double beta, int lA, int lB, double XA, double XB, double tolerance) {
    // Dynamic limits based on the Gaussian decay
    auto [lower_limit, upper_limit] = find_integration_limits((XA + XB) / 2, (alpha + beta) / 2, tolerance);

    // Initial parameters
    int num_points = 10;
    double previous_result = numeric_limits<double>::infinity();
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
            throw overflow_error("Number of points exceeds maximum allowed value");
        }
    } while (abs(current_result - previous_result) > tolerance && num_points <= numeric_limits<int>::max() / 2);

    return current_result;
}
