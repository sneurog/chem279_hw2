#ifndef INTEGRALS_H
#define INTEGRALS_H

#include <iostream>
#include <vector>
#include <armadillo>
#include <utility>
#include <functional>

double gaussian_function(double x, double center, double exponent, int power);
double trapezoidal_rule(std::function<double(double)> func, double a, double b, int num_points);
double compute_overlap_integral(double alpha, double beta, int lA, int lB, double XA, double XB, double tolerance = 1e-6);

#endif // INTEGRALS_H
