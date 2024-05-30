#ifndef DECODER
#define DECODER

#include <stdio.h>
#include "huffman_tree.h"

/** @brief Decodes a data file by traversing the Huffman binary tree.
 *  
 *   Saves the resulting decoded data in an output file.   
 *   decoded_file specifies the file name of the file to output the decoded data.
 *
 *   @param huffman_tree_root the root of the Huffman binary tree 
 *   @param encoded_file      the file to get the encoded data to decode
 *   @param decoded_file      the file name of the output file to save the decoded data in
 *   @return void
 */
void decode(NODE *huffman_tree_root, char *encoded_file, char *decoded_file);

#endif