This code includes a main.cpp file and a input.csv file which are used to run the program.

In order to run the program use the following instructions:

$ gcc main.cpp -o main

$ ./main


Note when building: In order to change any of the vaiable look at the input.csv file. Each of the different matrix for allocated, max resources and available are seperated by columns with commas seperating each matrix. An example is shown below.
Allocated Resource Matrix:

0 1 0

2 0 0

3 0 2

2 1 1

0 0 2


Max Resource Matrix:

7 5 3

3 2 2

9 0 2

2 2 2

4 3 3


Avaiable Resource Matrix: 

3 3 2

What input file should look like:

0 1 0,7 5 3,3 3 2

2 0 0,3 2 2,

3 0 2,9 0 2,

2 1 1,2 2 2,

0 0 2,4 3 3,

Example of output:
System is in safe state
Safe sequence is: 1 3 4 0 2
