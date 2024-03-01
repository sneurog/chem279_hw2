//mainhw2.cpp
#include <iostream>
#include <string>
#include <iomanip> 
#include "readfile.h"
#include "integrals.h"
#include <filesystem>
#include <vector>
#include <map>


using namespace std;
namespace fs = std::filesystem;

int main() {


    string directory_path_n = "numerical";
    string directory_path_a = "analytical";

    // Numerical integrals section
    for (const auto& entry_n : fs::directory_iterator(directory_path_n)) {
        if (entry_n.is_regular_file() && entry_n.path().extension() == ".txt") {
            string file_path_n = entry_n.path().string();
            try {
                Atom_1d atom_data = read_atoms_1d(file_path_n);
                double result = compute_overlap_integral(
                    atom_data.w1, atom_data.w2,
                    static_cast<int>(atom_data.x_angular_w1), static_cast<int>(atom_data.x_angular_w2),
                    atom_data.x_w1, atom_data.x_w2
                );
                cout << "Energy file name: " << entry_n.path().filename() << " ";
                cout << "1d numerical overlap integral between Gaussian functions is: " << result << endl;
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }

    // Analytical integrals section
 // Orbital dictionary mapping
    map<int, pair<string, vector<tuple<int, int, int>>>> orbitalDictionary = {
        {0, {"s", {{0, 0, 0}}}},  // s orbital has L = 0 and contains 1 function
        {1, {"p", {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}},  // p orbital has L = 1 and contains 3 functions
        {2, {"d", {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}}}}  // d orbital has L = 2 and contains 6 functions
        // Add more for f, g, etc., if needed
    };

    // Analytical integrals section
    for (const auto& entry_a : fs::directory_iterator(directory_path_a)) {
        if (entry_a.is_regular_file() && entry_a.path().extension() == ".txt") {
            string file_path_a = entry_a.path().string();
            try {
                Overlap shell_data = read_overlap(file_path_a);

                // Get the orbital info for each shell
                auto& shell1_info = orbitalDictionary[shell_data.angular_momentum1];
                auto& shell2_info = orbitalDictionary[shell_data.angular_momentum2];

                cout << "Energy file name: " << entry_a.path().filename() << endl;
                cout << "Shell 1 is an " << shell1_info.first << " orbital with "
                     << shell1_info.second.size() << " functions." << endl;
                cout << "Shell 2 is an " << shell2_info.first << " orbital with "
                     << shell2_info.second.size() << " functions." << endl;

                // Compute and print the overlap integral matrix
                cout << "Overlap integral between Shell 1 and Shell 2:" << endl;
                for (const auto& func1 : shell1_info.second) {
                    for (const auto& func2 : shell2_info.second) {
                        double S = compute_overlap_integral_3d(
                            shell_data.exponent1, shell_data.exponent2,
                            get<0>(func1), get<1>(func1), get<2>(func1),  // lA, mA, nA for the i-th function in shell 1
                            shell_data.x1, shell_data.y1, shell_data.z1,
                            get<0>(func2), get<1>(func2), get<2>(func2),  // lB, mB, nB for the j-th function in shell 2
                            shell_data.x2, shell_data.y2, shell_data.z2
                        );
                        cout << setw(10) << S << " ";
                    }
                    cout << endl;  
} //this bracket happened to be deleted 
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }

    return 0;
}

