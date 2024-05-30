#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prob_table.h"

/** @brief Represents a node of the Huffman binary tree.
 *
 *  A node represents a character, which has a certain probability to appear.
 *  A node also points to a left and right node in the Huffman binary tree.
 */
typedef struct node {
    char character;
    float probability;
    struct node *left;
    struct node *right;
} NODE;

/** @brief Saves the probability table in a specified file.
 *
 *   @param prob_table the probability table to use for building the Huffman binary tree
 *   @return the root of the Huffman binary tree
 */
NODE *generate_huffman_tree(char *prob_file);

/** @brief Reads the probabilites of each character from the specified file and returns them in a table.
 * 
 *  @param prob_file the file to read the probabilities from
 *  @return the probability table
*/
float *get_prob_table(char *prob_file);

/** @brief Generates the Huffman table.
 *
 *   @param root the root of the Huffman binary tree
 *   @return Huffman table
 */
char** generate_huffman_table(NODE *root);

/** @brief Traverses through the Huffman binary tree and builds the character codes.
 * 
 *  Uses recursion.
 *
 *   @param huffman_table the huffman table to fill with the codes
 *   @param current_node  the node the recursion is currently on
 *   @param binary        the binary string to build each code on
 *   @return void
 */
void build_codes(char **huffman_table, NODE *current_node, char *binary);

/** @brief Exports the codes from the Huffman table.
 * 
 *   Saves them in the output file "codes.txt".
 * 
 *   Also prints on the screen the codes for characters with ASCII value from 32 to 126.
 * 
 *   @param huffman_table the Huffman table to export the codes from
 *   @return void
 */
void export_huffman_codes(char **huffman_table);

/** @brief Frees up the Huffman binary tree from memory.
 * 
 *   Uses recursion.
 * 
 *   @param current_node the node the recursion is currently on
 *   @return void
*/
void free_huffman_tree(NODE *current_node);

/** @brief Frees up the Huffman table from memory.
 * 
 *  @param huffman_table the Huffman table
 *  @return void
*/
void free_huffman_table(char ** huffman_table);

#endif