
@mainpage EPL232 - Assignment 1

@author Vasilis Ilia

This is the game of Three Musketeers. Three Musketeers is a 5x5 board game, where the 3 musketeers battle the 22 men of Cardinal Richelieu (also mentioned as 'enemy' during the game).

Rules:
1. Musketeer pieces ('M') can only move to adjacent enemy pieces ('o') and enemy pieces can only move to adjacent squares with no pieces ('.'). No move can be diagonal. Musketeers play first.
2. Enemy wins if it can force all the musketeers to be in the same row or the same column.
3. Musketeers win if they have no possible moves (no adjacent enemy pieces).

To play the game the user needs to give their move as input through the console. The input needs to have a specific format. Locations are indicated as a letter (A/a, B/b, C/c, D/d, E/e), followed by a number (1, 2, 3, 4, or 5). Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d. To terminate the game enter '0,0=E'.

Features:
1. Reads the name of the file that has the starting board, as an argument through the console.
2. Presents the updated board in the console after each round.
3. At the end of the game (including after termination) the board is saved in the directory of the executable in a file called                         'out-inputfile.txt'. This board can be used as a starting board.

Compiling and running:

To compile the program enter:
gcc -std=c99 threeMusketeers.c -o threeMusketeers

To run the program enter:
./threeMusketeers filenameOfTheBoard.txt

