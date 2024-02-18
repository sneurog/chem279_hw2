// integrals.h
#ifndef INTEGRALS_H
#define INTEGRALS_H

#include <vector>
#include <armadillo>
#include <utility>
#include <functional>

// 1 NUMERICAL INTEGRATION IN ONE DIMENSION
double gaussian_function(double x, double center, double exponent, int power);
double trapezoidal_rule(std::function<double(double)> func, double a, double b, int num_points);
double compute_overlap_integral(double alpha, double beta, int lA, int lB, double XA, double XB, double tolerance = 1e-6);

// 2 ANALYTICAL 3-D OVERLAP INTEGRAL OF PRIMITIVE GAUSSIANS
unsigned long long double_factorial(int n);
unsigned long long binomial_coefficient(int n, int k); 
double compute_polynomial_part(int lA, int lB, double PA, double PB, double gamma);
double compute_exponential_prefactor(double alpha, double beta, double xA, double xB);
double compute_overlap_integral_3d(double alpha, double beta, 
                                int lA, int mA, int nA, 
                                double XA, double YA, double ZA,
                                int lB, int mB, int nB, 
                                double XB, double YB, double ZB);



#endif // INTEGRALS_H
