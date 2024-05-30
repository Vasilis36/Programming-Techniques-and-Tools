#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "prob_table.h"
#include "huffman_tree.h"
#include "encoder.h"
#include "decoder.h"

/** @brief Starts executing all the procedures of the program.
 *
 *   Declares necessary variables and calls the functions for each procedure.
 *
 *   @param argc number of arguments in command line
 *   @param argv the arguments in command line
 *   @return void
 */
void start(int argc, char **argv);

/** @brief Reads the user input.
 *
 *   The input is given as command line arguments. Reads the options
 *   for the desired functionality and the corresponding filenames.
 *
 *   @param argc         number of arguments in command line
 *   @param argv         the arguments in command line
 *   @param p_flag       flag for caclulating probabilites
 *   @param s_flag       flag for creating the Huffman tree
 *   @param e_flag       flag for encoding a file
 *   @param d_flag       flag for decoding a file
 *   @param sample_file  the file to read the cities from
 *   @param prob_file    the file to read or write the prbabilities
 *   @param data_file    the data file to encode
 *   @param encoded_file the file to read or write the encoded result
 *   @param decoded_file the file to write the decoded result
 *   @return void
 */
void read_user_input(int argc, char **argv, int *p_flag, int *s_flag, int *e_flag, int *d_flag,
                     char **sample_file, char **prob_file, char **data_file, char **encoded_file,
                     char **decoded_file);

/************************************ Function definitions **************************************/

void start(int argc, char **argv)
{
    int p_flag = 0, s_flag = 0, e_flag = 0, d_flag = 0; /* Options the user chooses. */
    /* Filenames from command line arguments.*/
    char *sample_file = NULL, *prob_file = NULL, *data_file = NULL;
    char *encoded_file = NULL, *decoded_file = NULL;

    read_user_input(argc, argv, &p_flag, &s_flag, &e_flag, &d_flag,
                    &sample_file, &prob_file, &data_file, &encoded_file, &decoded_file);
    
    /* Program functionality depends on the option the user chose from the command line. */
    if (p_flag == 1)
    {
        generate_prob_table(sample_file, prob_file);
    }
    else if (s_flag == 1)
    {      
        NODE *huffman_tree_root = generate_huffman_tree(prob_file);
        char **huffman_table = generate_huffman_table(huffman_tree_root);
        export_huffman_codes(huffman_table);
        free_huffman_tree(huffman_tree_root);
        free_huffman_table(huffman_table);
    }
    else if (e_flag == 1)
    {
        NODE *huffman_tree_root = generate_huffman_tree(prob_file);
        char **huffman_table = generate_huffman_table(huffman_tree_root); 
        encode(huffman_table, data_file, encoded_file);
        free_huffman_tree(huffman_tree_root);
        free_huffman_table(huffman_table);    
    }
    else if (d_flag == 1)
    {
        NODE *huffman_tree_root = generate_huffman_tree(prob_file);
        decode(huffman_tree_root, encoded_file, decoded_file);
        free_huffman_tree(huffman_tree_root);        
    }
}

void read_user_input(int argc, char **argv, int *p_flag, int *s_flag, int *e_flag, int *d_flag,
                     char **sample_file, char **prob_file, char **data_file, char **encoded_file,
                     char **decoded_file)
{
    int option; /* To save the command line options. */

    /* If argc == 1(the program name), then no arguments have been given. */
    if (argc == 1)
    {
        printf("No arguments given\n");
        printf("One of -p, -s, -e or -d must be used\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Scans the command line arguments and searches for options 'p', 's', 'e' and 'd'.
     */
    while ((option = getopt(argc, argv, "psed")) != -1)
    {
        switch (option)
        {
        /* Probability arguments. */
        case (int)'p':
            if (argc != 4)
            {
                printf("Invalid arguments.\n");
                printf("To use -p: ./huffman -p sample.txt probfile.txt\n");
                exit(EXIT_FAILURE);
            }
            *p_flag = 1;
            *sample_file = argv[2];
            *prob_file = argv[3];
            break;

        /* Creating Huffman tree arguments. */
        case (int)'s':
            if (argc != 3)
            {
                printf("Invalid arguments.\n");
                printf("To use -s: ./huffman -s probfile.txt\n");
                exit(EXIT_FAILURE);
            }
            *s_flag = 1;
            *prob_file = argv[2];
            break;

        /* Encoding arguments. */
        case (int)'e':
        if (argc != 5)
            {
                printf("Invalid arguments.\n");
                printf("To use -e: ./huffman -e probfile.txt data.txt data.txt.enc\n");
                exit(EXIT_FAILURE);
            }
            *e_flag = 1;
            *prob_file = argv[2];
            *data_file = argv[3];
            *encoded_file = argv[4];
            break;

        /* Decoding arguments. */        
        case (int)'d':
        if (argc != 5)
            {
                printf("Invalid arguments.\n");
                printf("To use -d: ./huffman -d probfile.txt data.txt.enc data.txt.new\n");
                exit(EXIT_FAILURE);
            }
            *d_flag = 1;
            *prob_file = argv[2];
            *encoded_file = argv[3];
            *decoded_file = argv[4];
            break;

        /* Case when an unrecognized option is given or there is a missing argument. */
        case (int)'?':
            /*
             * Case '?' means there is an error with arguments, therefore the program
             * needs to be terminated.
             */      
            printf("One of -p, -s, -e or -d must be used\n");      
            exit(EXIT_FAILURE);
        }
    }
    if (*p_flag == 0 && *s_flag == 0 && *e_flag == 0 && *d_flag == 0)
    {
        printf("One of -p, -s, -e or -d must be used\n");      
        exit(EXIT_FAILURE);
    }
}

#ifdef MAIN
/** @brief Program entrypoint.
 *
 *   Calls start(argc, argv).
 *
 *   @param argc number of arguments in command line
 *   @param argv the arguments in command line
 */
int main(int argc, char **argv)
{
    start(argc, argv);  
    return 0;
}
#endif