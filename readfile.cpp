#include "readfile.h"
#include <fstream>
#include <sstream>
#include <string>

// Read txt file 
Atom_1d read_atoms_1d(const std::string& filename1d) {
    Atom_1d atom;
    std::ifstream file(filename1d);

    if (file.is_open()) {
        file >> atom.x_w1 >> atom.w1 >> atom.x_angular_w1;
        file >> atom.x_w2 >> atom.w2 >> atom.x_angular_w2;
    } else {
        std::cerr << "Unable to open file: " << filename1d << std::endl;
        // Handle error properly, for example by exiting the program or throwing an exception
        throw std::runtime_error("File read error.");
    }

    file.close();
    return atom;
}



