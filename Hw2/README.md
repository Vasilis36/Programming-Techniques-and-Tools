# Assignment 2

This is a program that finds the transitive closure of a group of cities that are linked together and lets the user know whether a linked path between two specified cities exists.

Features:
1. Reads the name of the file that has the neighbor cities as an argument through the console. File needs to be in the same directory as the executable.
2. User can decide different procedures to execute through command line arguments.
3. Options are: <br>
-r <source>,<destination> to find and print, if it exists, a path between the two specified cities. <br>
-p to print the whole transitive closure in the console. <br>
-o to save the whole transitive closure in an output file saved in the same directory as the executable.

Compiling and running:

To compile the program enter:
gcc -std=c99 cityLink.c -o cityLink

To run the program enter:
./cityLink -i <inputfile> -r <source >,<destination> -p -o
