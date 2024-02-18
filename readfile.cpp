// readfile.cpp
#include "readfile.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>


// 1 NUMERICAL INTEGRATION IN ONE DIMENSION.
Atom_1d read_atoms_1d(const std::string& filename1d) {
    Atom_1d atom;
    std::ifstream file(filename1d);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename1d << std::endl;
        throw std::runtime_error("File read error.");
    }

    file >> atom.x_w1 >> atom.w1 >> atom.x_angular_w1;
    file >> atom.x_w2 >> atom.w2 >> atom.x_angular_w2;

    file.close();
    return atom;
}

// 2 ANALYTICAL 3-D OVERLAP INTEGRAL OF PRIMITIVE GAUSSIANS



// Function to read shell data from a file
Overlap read_overlap(const std::string& filename) {
    Overlap atom_overlap;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        throw std::runtime_error("File read error.");
    }

    // Read the data for shell 1
    file >> atom_overlap.x1 >> atom_overlap.y1 >> atom_overlap.z1 
         >> atom_overlap.exponent1 >> atom_overlap.angular_momentum1;

    // Read the data for shell 2
    file >> atom_overlap.x2 >> atom_overlap.y2 >> atom_overlap.z2 
         >> atom_overlap.exponent2 >> atom_overlap.angular_momentum2;

    file.close();
    return atom_overlap;
}