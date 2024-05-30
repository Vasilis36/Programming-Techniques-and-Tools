/** @file threeMusketeers.c
 *  @brief Plays the game of Three Musketeers between two players.
 *
 *  Reads a starting board from the command line and starts the game.
 *  Each player is prompted to either play their turn or end the game.
 *  Each turn the current board is displayed in the console. When the game
 *  finishes the final board is saved in the directory of the executable.
 *
 *  @author Vasilis Ilia
 *  @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief the size of the board
 */
#define N 5

/** @brief Represents the state the game is currently in.
 * 
 *   Unless the game is over by either of the players winning or has been 
 *   terminated early, its state will be PLAYING.
 */
typedef enum {
    PLAYING,
    MUSKETEERS_WON,
    ENEMY_WON,
    TERMINATED
} STATE;

/** @brief Starts the game.
 *
 *   Uses functions to execute different parts of the game.
 *
 *   @param filename the name of the file to read the board from
 *   @return void
 */
void start_game(char filename[]);

/** @brief Prints the rules of the game.
 *
 *   @return void
 */
void print_rules(void);

/** @brief Reads the board.
 *
 *   The board is read from a specified file and is saved in a matrix.
 *
 *   @param filename the name of the file to read the board from
 *   @param board    the board of the game
 *   @return void
 */
void readBoard(char filename[], char board[][N]);

/** @brief Prints the board in console.
 *
 *   @param board the board to print
 *   @return void
 */
void display_board(char board[][N]);

/*
 * Helper function for printing the board in the console.
 */
void print_line(void);

/** @brief Plays the game.
 *
 *   Each round either the Musketeers or the enemy plays. Each player
 *   gives their move through the console. The validity of the input
 *   is checked and the move is played. At the end of the round the
 *   current board is displayed in the console. The rounds go on until
 *   a player terminates the game or has won.
 *
 *   @param board the board of the game
 *   @return void
 */
void play(char board[][N]);

/** @brief Prints a message depending on the state of the game.
 * 
 *   Announces the winner, game termination, or nothing if the game is still
 *   going on.
 *
 *   @param game_state the state the game is currently in
 *   @return void
 */
void print_winning_message(STATE game_state);

/** @brief Plays the round of the Musketeers.
 *
 *   Asks the player for input and checks the validity of it. If the
 *   input and the move the player chose are valid, a move is made on 
 *   the board. Finally, it tests for game completion and returns
 *   an appropriate value for the state of the game.
 *
 *   @param board the board of the game
 *   @return a value corresponding to the state of the game after the round is over
 */
STATE play_musketeer_round(char board[][N]);

/** @brief Plays the round of the Enemy.
 *
 *   Asks the player for input and checks the validity of it. If the
 *   input and the move the player chose are valid, a move is made on 
 *   the board. Finally, it tests for game completion and returns
 *   an appropriate value for the state of the game.
 *
 *   @param board the board of the game
 *   @return a value corresponding to the state of the game after the round is over
 */
STATE play_enemy_round(char board[][N]);

/** @brief Checks whether the input the user gave has the correct format.
 *
 *   Format includes valid characters, limited number of characters and 
 *   the sequence of characters.
 *      
 *   @param input the input the user gave
 *   @return true if the input format is valid
 */
_Bool check_input_format(char input[]);

/** @brief Registers the move of the user.
 *
 *   Assigns each variable to its corresponding value, taken from the user input.
 *   A move includes the coordinates of the piece to move and the direcion
 *   to move it to.
 * 
 *   @param row       the row of the piece
 *   @param column    the column of the piece
 *   @param direction the direction to move the piece
 *   @param input     the input the user gave
 *   @return void
 */
void register_move(char *row, char *column, char *direction, char input[]);

/** @brief Checks whether the move the user made for the Musketeers is valid and makes it.
 * 
 *   The checks include trying to move an incorrect piece, trying to move
 *   out of the board, or trying to make an illegal move based on the
 *   game's rules.
 * 
 *   @param row       the row of the piece
 *   @param column    the column of the piece
 *   @param direction the direction to move the piece
 *   @param board     the board of the game
 *   @return true if the move is valid
 */
_Bool check_valid_musketeer_move(char row, char column, char direction, char board[][N]);

/** @brief Checks whether the move the user made for the Enemy is valid and makes it.
 * 
 *   The checks include trying to move an incorrect piece, trying to move
 *   out of the board, or trying to make an illegal move based on the
 *   game's rules.
 * 
 *   @param row       the row of the piece
 *   @param column    the column of the piece
 *   @param direction the direction to move the piece
 *   @param board     the board of the game
 *   @return true if the move is valid
 */
_Bool check_valid_enemy_move(char row, char column, char direction, char board[][N]);

/** @brief Checks whether the move is trying to move the piece out of the board.
 *
 *   @param row       the row of the piece
 *   @param column    the column of the piece
 *   @param direction the direction to move the piece
 *   @param board     the board of the game
 *   @return true if the move is valid
 */
_Bool check_valid_bound_move(char row, char column, char direction, char board[][N]);


/** @brief Checks whether the move for the Musketeers is legal or not and makes it, if it is.
 *
 *   @param row_index the row index of the piece
 *   @param col_index the column index of the piece
 *   @param direction the direction to move the piece
 *   @param board     the board of the game
 *   @return true if the move is valid
 */
_Bool check_legal_musketeer_move(int row_index, int col_index, char direction, char board[][N]);

/** @brief Checks whether the move for the Enemy is legal or not and makes it, if it is.
 *
 *   @param row_index the row index of the piece
 *   @param col_index the column index of the piece
 *   @param direction the direction to move the piece
 *   @param board     the board of the game
 *   @return true if the move is valid
 */
_Bool check_legal_enemy_move(int row_index, int col_index, char direction, char board[][N]);

/** @brief Makes the move on the board.
 *
 *   @param row_index     the old row index of the piece
 *   @param col_index     the old column index of the piece
 *   @param new_row_index the new row index of the piece
 *   @param new_col_index the new column index of the piece
 *   @param board         the board of the game
 *   @return void
 */
void play_move(int row_index, int col_index, int new_row_index, int new_col_index, char board[][N]);

/** @brief Checks whether there is a winner or the game still goes on.
 *
 *   @param board the board of the game
 *   @return A value that indicates whether there is a winner or not.
 */
STATE check_game_over(char board[][N]);

/** @brief Saves the current board of the game in a txt file.
 *
 *   The output file is located in the directory of the executable.
 *
 *   @param board the board to save
 *   @return void
 */
void writeBoard(char board[][N]);

/************************** Function definitions **************************/

void start_game(char filename[])
{
    char board[N][N];

    readBoard(filename, board);
    print_rules();
    display_board(board);
    play(board);
    writeBoard(board);
}

void print_rules(void)
{
    printf("\n*** The Three Musketeers Game ***\n"
           "To make a move, enter the location of the piece you want to move,\n"
           "and the direction you want it to move. Locations are indicated as\n"
           "a letter (A, B, C, D, E) followed by a number (1, 2, 3, 4, or 5).\n"
           "Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d).\n"
           "For example, to move the Musketeer from the top right-hand corner\n"
           "to the row below, enter 'A,5=D' or 'a,5=d'(without quotes).\n"
           "For convenience in typing, use lowercase letters.\n\n");
}

/*
 * Reads the file character by character and builds the board.
 */
void readBoard(char filename[], char board[][N])
{
    FILE *fp;
    /* The indices of the board to save the next character at. */
    int current_row = 0, current_col = 0;    
    int count_characters = 0; /* To make sure the board is complete. */
    int count_musketeers = 0; /* A board must always have 3 Musketeers. */
    char character;           /* To save the characters from the file. */

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Error: Could not open \"%s\" file\n", filename);
        exit(EXIT_FAILURE);
    }

    /*
     * Reads the next character until it reaches the end of file.
     */
    while ((character = fgetc(fp)) != EOF)
    {
        /*
         * Finding a new line character means the row that we write on the
         * board must increment.
         */
        if (character == '\n')
        {
            current_row++;
            current_col = 0;
            continue;
        }

        /*
         * If it is not a space character, then it is a character that needs to
         * be saved on the board.
         */
        if (character != ' ')
        {
            /* Checks for character validity in the input file. */
            if (character != 'o' && character != 'M' && character != '.')
            {
                printf("Error: Invalid character '%c' in input file \"%s\"\n", character, filename);
                exit(EXIT_FAILURE);
            }

            /*
             * If the index of the columns is N and a valid character has been found,
             * then the format of the input file is invalid(a row has at least N+1 columns)
             * and the program terminates.
             */
            if (current_col == N)
            {
                printf("Error: Invalid format in input file \"%s\"\n", filename);                
                exit(EXIT_FAILURE);
            }
            /*
             * If the index of the rows is N and a valid character has been found,
             * then the format of the input file is invalid(a column has at least N+1 rows)
             * and the program terminates.
             */
            if (current_row == N)
            {
                printf("Error: Invalid format in input file \"%s\"\n", filename);
                exit(EXIT_FAILURE);
            }

            if (character == 'M')
            {
                count_musketeers++;
            }

            board[current_row][current_col] = character;
            count_characters++;
            current_col++;
        }
    }

    if (count_characters != N * N)
    {
        printf("Error: File \"%s\" is invalid. Incomplete board\n", filename);
        exit(EXIT_FAILURE);
    }

    if (count_musketeers != 3) 
    {
        printf("Error: File \"%s\" is invalid. A board must have 3 Musketeers\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void display_board(char board[][N])
{
    printf("    1   2   3   4   5\n");

    for (int i = 0; i < N; i++)
    {
        print_line();
        printf("%c | ", ('A' + i));

        for (int j = 0; j < N; j++)
        {
            printf("%c | ", board[i][j]);
        }
        printf("\n");
    }
    print_line();
}

void print_line(void)
{
    printf("  +---+---+---+---+---+\n");
}

void play(char board[][N])
{
    /* 
    * In case the starting board is from a completed game, this makes it so
    * the loop is skipped and a winning message is printed.
    */
    STATE game_state = check_game_over(board);
  
    while (game_state == PLAYING)
    {
        /* If the game ends on musketeers round, game_state is changed appropriately. */
        game_state = play_musketeer_round(board);
        display_board(board);
        
        /* The loop needs to break if the game ends in musketeers round. */
        if (game_state != PLAYING)
        {
            break;
        }

        game_state = play_enemy_round(board);   
        display_board(board);   
    }

    print_winning_message(game_state);
}

void print_winning_message(STATE game_state)
{
    if (game_state == MUSKETEERS_WON)
    {
        printf("The Musketeers win!\n");
    }
    else if (game_state == ENEMY_WON)
    {
        printf("Cardinal Richelieu's men win!\n");
    }
    else if (game_state == TERMINATED)
    {
        printf("Game has been terminated\n");
    }
}

STATE play_musketeer_round(char board[][N])
{
    char row, column; /* The coordinates of the piece. */
    char direction;   /* The direction to move the piece. */
    char input[30];
    _Bool valid_input = 0;
    
    do 
    {
        printf("Give the Musketeer's move\n");
        fgets(input, sizeof(input), stdin);

        /* 
        * Checks for early game termination. If input is over 6 characters, then the 
        * input format is wrong, which is checked in check_input_format().
        */
        if (!strncmp(input, "0,0=E", 5) && strlen(input) == 6)
        {           
            return TERMINATED;
        }

        valid_input = check_input_format(input);
        if (!valid_input)
        {
            printf("Invalid input format\n");
            continue;
        }

        /* Gives values to the row, column and direction variables. */
        register_move(&row, &column, &direction, input);

        valid_input = check_valid_musketeer_move(row, column, direction, board);   

    } while (!valid_input);

    return check_game_over(board);
}

STATE play_enemy_round(char board[][N])
{
    char row, column; /* The coordinates of the piece. */
    char direction;   /* The direction to move the piece. */
    char input[30];
    _Bool valid_input = 0;
    
    do 
    {
        printf("Give the enemy's move\n");
        fgets(input, sizeof(input), stdin);

        /* 
        * Checks for early game termination. If input is over 6 characters, then the 
        * input format is wrong, which is checked in check_input_format().
        */
        if (!strncmp(input, "0,0=E", 5) && strlen(input) == 6)
        {           
            return TERMINATED;
        }

        valid_input = check_input_format(input);
        if (!valid_input)
        {
            printf("Invalid input format\n");
            continue;
        }

        /* Gives values to the row, column and direction variables. */
        register_move(&row, &column, &direction, input);

        valid_input = check_valid_enemy_move(row, column, direction, board);   

    } while (!valid_input);
    
    return check_game_over(board);
}

_Bool check_input_format(char input[])
{
    /* 
    * If the input has more than 6 characters (including the new line character),
    * then it is invalid.
    */
    if (strlen(input) > 6)
    {
        return 0;
    }

    /*
    * If the second character is not ',' or the fourth character not '=',
    * then the input is invalid.
    */
    if (input[1] != ',' || input[3] != '=')
    {
        return 0;
    }

    /* 
    * If the first character is not a character between 'A' and 'E" and not a 
    * character between 'a' and 'e', then input is invalid.
    */
    if ((input[0] < 'A' || input[0] > 'E') && (input[0] < 'a' || input[0] > 'e'))       
    {
        return 0;
    }

    /*
    * If the third character is not a character between '1' and '5', 
    * then the input is invalid.
    */
    if (input[2] < '1' || input[2] > '5')
    {
        return 0;
    }

    /*
    * If the fifth character is not one of 'L'/'l', 'R'/'r', 'U'/'u' and 'D'/'d',
    * then the input is invalid.
    */
    if (input[4] != 'L' && input[4] != 'l' && input[4] != 'R' && input[4] != 'r'
        && input[4] != 'U' && input[4] != 'u' && input[4] != 'D' && input[4] != 'd')       
    {
        return 0;
    }

    /* If it passes all the checks, then the format of the input is correct. */
    return 1;
}

void register_move(char *row, char *column, char *direction, char input[])
{
    *row = input[0];
    *column = input[2];
    *direction = input[4];
}

_Bool check_valid_musketeer_move(char row, char column, char direction, char board[][N])
{
    /* To get the board indices as integers from 0 to N - 1. */
    int row_index;
    int col_index = ((int) column) - '1';

    if (row >= 'A' && row <= 'E')
    {
        row_index = ((int) row) - 'A';
    }
    else
    {
        row_index = ((int) row) - 'a';
    }

    /* Checks whether the piece the user is trying to move is a Musketeer. */
    if (board[row_index][col_index] != 'M')
    {
        printf("This is not a Masketeer piece\n");
        return 0;
    }

    /* If the move is trying to move the piece out of the board, return false. */
    if (!check_valid_bound_move(row, column, direction, board))
    {
        printf("This move takes the piece out of the board\n");
        return 0;
    }

    /* Checks whether the move is legal and returns the corresponding value. */
    return check_legal_musketeer_move(row_index, col_index, direction, board);
}

_Bool check_valid_enemy_move(char row, char column, char direction, char board[][N])
{
    /* To get the board indices as integers from 0 to N - 1. */
    int row_index;
    int col_index = ((int) column) - '1';

    if (row >= 'A' && row <= 'E')
    {
        row_index = ((int) row) - 'A';
    }
    else
    {
        row_index = ((int) row) - 'a';
    }

    /* Checks whether the piece the user is trying to move is an enemy. */
    if (board[row_index][col_index] != 'o')
    {
        printf("This is not an enemy piece\n");
        return 0;
    }

    /* If the move is trying to move the piece out of the board, return false. */
    if (!check_valid_bound_move(row, column, direction, board))
    {
        printf("This move takes the piece out of the board\n");
        return 0;
    }

    /* Checks whether the move is legal and returns the corresponding value. */
    return check_legal_enemy_move(row_index, col_index, direction, board);
}

_Bool check_valid_bound_move(char row, char column, char direction, char board[][N])
{
    /* Checks for invalid upper bound move. */
    if ((row == 'A' || row == 'a') && (direction == 'U' || direction == 'u'))
    {
        return 0;
    }

    /* Checks for invalid lower bound move. */
    if ((row == 'E' || row == 'e') && (direction == 'D' || direction == 'd'))
    {
        return 0;
    }

    /* Checks for invalid left bound move. */
    if (column == '1' && (direction == 'L' || direction == 'l'))
    {
        return 0;
    }
    /* Checks for invalid right bound move. */
    if (column == '5' && (direction == 'R' || direction == 'r'))
    {
        return 0;
    }
    
    return 1;
}

_Bool check_legal_musketeer_move(int row_index, int col_index, char direction, char board[][N])
{
    int new_row_index = row_index;
    int new_col_index = col_index;

    /* Changes new_row_index or new_col_index based on direction of the move. */
    (direction == 'r' || direction == 'R') ? (new_col_index += 1) : ((void) 0);
    (direction == 'l' || direction == 'L') ? (new_col_index -= 1) : ((void) 0);
    (direction == 'u' || direction == 'U') ? (new_row_index -= 1) : ((void) 0);
    (direction == 'd' || direction == 'D') ? (new_row_index += 1) : ((void) 0);

    /* Musketeers can only move to squares with 'o'. */
    if (board[new_row_index][new_col_index] != 'o')
    {
        printf("This is an illegal move\n");
        return 0;
    }

    play_move(row_index, col_index, new_row_index, new_col_index, board); 
    return 1;  
}

_Bool check_legal_enemy_move(int row_index, int col_index, char direction, char board[][N])
{
    int new_row_index = row_index;
    int new_col_index = col_index;

    /* Changes new_row_index or new_col_index based on direction of the move. */
    (direction == 'r' || direction == 'R') ? (new_col_index += 1) : ((void) 0);
    (direction == 'l' || direction == 'L') ? (new_col_index -= 1) : ((void) 0);
    (direction == 'u' || direction == 'U') ? (new_row_index -= 1) : ((void) 0);
    (direction == 'd' || direction == 'D') ? (new_row_index += 1) : ((void) 0);

    /* Enemy pieces can only move to squares with '.'. */
    if (board[new_row_index][new_col_index] != '.')
    {
        printf("This is an illegal move\n");
        return 0;
    }

    play_move(row_index, col_index, new_row_index, new_col_index, board); 
    return 1;  
}

/* 
* New position of the piece gets the character of the old position of the piece and old position
* of the piece gets the character '.'.
*/
void play_move(int row_index, int col_index, int new_row_index, int new_col_index, char board[][N])
{
    board[new_row_index][new_col_index] = board[row_index][col_index];
    board[row_index][col_index] = '.';
}

STATE check_game_over(char board[][N])
{
    /* Structure Musketeer to save the coordinates of each one. */
    typedef struct 
    {
        int row_index;
        int col_index;
    } MUSKETEER;

    int count_musketeers_found = 0;

    MUSKETEER musketeers[3];

    /* Finds the coordinates of each Musketeer. */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            /* Saves the coordinates of the Musketeer and increments their count. */
            if (board[i][j] == 'M')
            {
                musketeers[count_musketeers_found].row_index = i;
                musketeers[count_musketeers_found].col_index = j;
                count_musketeers_found++;
            }
        }
    }

    /* Checks if enemy won, based on the Musketeers being on the same row. */
    for (int i = 1; i < 3; i++)
    {
        if (musketeers[i].row_index != musketeers[0].row_index)
        {
            break;
        }     

        /* If loop did not break with i = 2, then all 3 of the Musketeers are on the same row. */   
        if (i == 2)
        {
            return ENEMY_WON;
        }
    }

    /* Checks if enemy won, based on the Musketeers being on the same column. */
    for (int i = 1; i < 3; i++)
    {
        if (musketeers[i].col_index != musketeers[0].col_index)
        {
            break;
        }  

        /* If loop did not break with i = 2, then all 3 of the Musketeers are on the same column. */     
        if (i == 2)
        {
            return ENEMY_WON;
        }
    }
    
    /* 
    * Checks if the Musketeers still have moves to make, therefore they have not won yet.
    * For each coordinate a check is done to make sure a coordinate is within the board, and then
    * if it is, and the character at those coordinates is 'o', then the Musketeers
    * do still have a move to make.
    */
    for (int i = 0; i < 3; i++)
    {
        /* Row indices of the Musketeers + 1 . */
        if (musketeers[i].row_index + 1 != N 
            && board[musketeers[i].row_index + 1][musketeers[i].col_index] == 'o')
        {
            return PLAYING;
        }

        /* Row indices of the Musketeers - 1 . */
        if (musketeers[i].row_index - 1 != -1 
            && board[musketeers[i].row_index - 1][musketeers[i].col_index] == 'o')
        {
            return PLAYING;
        }

        /* Column indices of the Musketeers + 1 . */
        if (musketeers[i].col_index + 1 != N          
            && board[musketeers[i].row_index][musketeers[i].col_index + 1] == 'o')
        {        
            return PLAYING;
        }

        /* Column indices of the Musketeers - 1 . */
        if (musketeers[i].col_index -1 != -1 
            && board[musketeers[i].row_index][musketeers[i].col_index - 1] == 'o')
        {
            return PLAYING;
        }
    }

    return MUSKETEERS_WON;
}

void writeBoard(char board[][N])
{
    const char *output_filename = "out-inputfile.txt";

    FILE *fp = NULL;

    if ((fp = fopen(output_filename, "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", output_filename);
        exit(EXIT_FAILURE);
    }

    printf("Saving out-inputfile.txt...");

    /* Goes until N - 1 to avoid putting an extra line after the final row. */
    for (int i = 0; i < N - 1; i++)
    {
        /* Goes until N - 1 to avoid putting an extra space at the end of each row. */
        for (int j = 0; j < N - 1; j++)
        {
            fprintf(fp, "%c ", board[i][j]);
        }        
        fprintf(fp, "%c\n", board[i][N-1]);
    }

    /* Puts the last row of the board. */
    for (int j = 0; j < N - 1; j++) 
    {
        fprintf(fp, "%c ", board[N-1][j]);
    }
    fprintf(fp, "%c", board[N-1][N-1]);

    printf("Done\nAu revoir!\n");
    fclose(fp);
}

/** @brief Program entrypoint.
 * 
 *   Calls start_game(filename) to begin the game.
 * 
 *   @param argc number of arguments in command line
 *   @param argv the arguments in command line
 */
int main(int argc, char *argv[])
{    
    start_game(argv[argc - 1]);

    return 0;
}