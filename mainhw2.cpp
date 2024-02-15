// main.cpp
#include <iostream>
#include <string>
#include "readfile.h"
#include "integrals.h"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main() {
    std::string directory_path_n = "numerical"; // Path to the directory with input files

    // section 1 
    // Iterate over files in the directory
    for (const auto& entry_n : fs::directory_iterator(directory_path_n)) {
        if (entry_n.is_regular_file() && entry_n.path().extension() == ".txt") { // Correct method to get the extension
            std::string file_path_n = entry_n.path().string();
            try {
                Atom_1d atom_data = read_atoms_1d(file_path_n);
                double result = compute_overlap_integral(
                    atom_data.w1, atom_data.w2, 
                    static_cast<int>(atom_data.x_angular_w1), static_cast<int>(atom_data.x_angular_w2), 
                    atom_data.x_w1, atom_data.x_w2
                );
                std::cout << "Energy file name: " << entry_n.path().filename();
                std::cout << "1d numerical overlap integral between Gaussian functions is: " << result << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                // Handle the error appropriately
            }
        }
    }
    return 0;
}
