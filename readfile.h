//readfile.h
#ifndef READ_FILE
#define READ_FILE

#include <vector>
#include <tuple>

// Structure for 1D atom data
struct Atom_1d {
    double x_w1, w1, x_angular_w1;
    double x_w2, w2, x_angular_w2;
};



struct Overlap {
    double x1, y1, z1, exponent1;
    int angular_momentum1;

    double x2, y2, z2, exponent2;
    int angular_momentum2;
};



// Function declarations
Atom_1d read_atoms_1d(const std::string& filename1d);
Overlap read_overlap(const std::string& filename);

#endif // READ_FILE
