// Header file to read in the automic coordinates 
#ifndef READ_FILE
#define READ_FILE

#include <iostream>



struct Atom_1d
{

double x_w1, w1, x_angular_w1;
double x_w2, w2, x_angular_w2;
};



Atom_1d read_atoms_1d(const std::string& filename1d); 


#endif //READ_FILE