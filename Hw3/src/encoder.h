#ifndef ENCODER
#define ENCODER

#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

/** @brief Encodes a data file using the Huffman codes.
 *  
 *   Saves the resulting encoded data in an output file.
 *   Huffman codes are given in huffman_table and the output file name
 *   is specified from the encoded_file.
 *
 *   @param huffman_table the Huffman table to get the Huffman codes
 *   @param data_file     the file to get the data to encode
 *   @param encoded_file  the file name of the output file to save the encoded data in
 *   @return void
 */
void encode(char **huffman_table, char *data_file, char *encoded_file);

#endif