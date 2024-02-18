# Chem 279 Problem set 2 


This repository contains 2 header files and 3 cpp files:

1. `integrals.cpp`: This file includes the function for homework 2.
2. `readfile.cpp`: It consists of functions for reading files.
3. `readfile.h`: This header file provides the API for reading files.
4. `mainhw2.cpp`: This file executes the problem set 2.


### Instructions to compile for mac users (using homebrew)
*to compile and run type this in order:*

Step 1:
~~~
g++ -std=c++17 -c -I/opt/homebrew/include readfile.cpp -o readfile.o
~~~
Step 2:

~~~
g++ -std=c++17 -c -I/opt/homebrew/include integrals.cpp -o integrals.o
~~~

Step 3:
~~~
g++ -std=c++17 -c -I/opt/homebrew/include mainhw2.cpp -o mainhw2.o
~~~
 
Step 4:
~~~
g++ -std=c++17 integrals.o readfile.o mainhw2.o -o hw2 -L/opt/homebrew/lib -larmadillo
~~~

To run type:

~~~
./hw2
~~~

## Instruction to compile using datahub
*to compile and run type this in order:*

Step 1:
~~~
g++ -std=c++17 -c  readfile.cpp -o readfile.o
~~~

Step 2:
~~~
g++ -std=c++17 -c  mainhw2.cpp -o mainhw2.o
~~~

Step 3:
~~~
g++ -std=c++17 -c  integrals.cpp -o integrals.o
~~~

Step 4:
~~~
g++ -std=c++17 integrals.o readfile.o mainhw2.o -o hw2 
~~~

To run type:

~~~
./hw2
~~~
