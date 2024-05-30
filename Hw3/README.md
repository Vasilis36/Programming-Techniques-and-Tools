# Assignment 3

The program encodes and decodes data from files, using the Huffman algorithm. The Huffman codes are produced based on an input file specified by the user. Works for characters with values 0-127 in the ASCII table.

Features:
1. Calculates the probability of each character appearing in an input file and exports the result in an output file. <br>
2. Makes the Huffman binary tree and the Huffman table and exports the Huffman codes in an output file. Characters from 32 to 126 in the ASCII table are displayed on the screen. Requires file from Feature 1. <br>
3. Encodes a specified input data file using the Huffman table. Requires output file from Feature 1.<br>
4. Decodes a specified input file using the Huffman binary tree. Requires output file from Feature 1 and an encoded file based on the codes produced by this program. <br>
5. Names of output files are chosen by the user.
6. Different options can be ran as arguments to select a feature. <br>

Options are: <br>
-p : Feature 1. <br>
-s : Feature 2. <br> 
-e : Feature 3. <br>
-d : Feature 4. <br>

Compiling and running:

To compile and link the program enter: <br>
make <br>
make all  (also creates the doxygen html, assuming the configuration file is in the directory)

To run the program enter: <br>
./huffman -p sample.txt probfile.txt <br>
./huffman -s probfile.txt <br>
./huffman -e probfile.txt data.txt data.txt.enc <br>
./huffman -d probfile.txt data.txt.enc data.txt.new <br>

The program uses driver functions for debugging. Flags used for each module: <br>
prob_table.c :  TEST_P <br>
huffman_tree.c: TEST_S <br>
encoder.c:      TEST_E <br>
decoder.c:      TEST_D
