#ifndef PROB_TABLE
#define PROB_TABLE

#include <stdio.h>
#include <stdlib.h>

/** @brief Total amount of characters from the ASCII table to include.
 * 
 * The encoding and decoding will only work for ASCII characters from 0 to 127 in
 * the ASCII table.
 */
extern const int MAX_ASCII;

/** @brief Generates the probability table.
 *
 *   @param sample_file file to read and use to build the probability table
 *   @param prob_file   file to write the probability table to
 *   @return void
 */
void generate_prob_table(char *sample_file, char *prob_file);

/** @brief Counts the characters from the specified file.
 * 
 *  Counts the appearances of each character independently and in total.
 *  Characters need to be in the range of 0-127 in the ASCII table.
 *
 *   @param sample_file file to read the characters from
 *   @param count_char  array to save the number of appearances of each character
 *   @param count_total total characters in the file
 *   @return void
 */
void count_characters(char *sample_file, int *count_char, int *count_total);

/** @brief Caclulates the probabilty of each character appearing.
 * 
 *  Uses the number of appearances of each character and the total amount of characters.
 *
 *   @param count_char  the amount of times each character has appeared
 *   @param count_total total amount of characters
 *   @param prob_table  the array to save the probability of each character
 *   @return void
 */
void calc_probability(int *count_char, int count_total, float *prob_table);

/** @brief Saves the probability table in the specified file.
 *
 *   @param prob_table the probability table to save
 *   @param prob_file  the name of the file to save the table
 *   @return void
 */
void export_prob_table(float *prob_table, char *prob_file);

#endif