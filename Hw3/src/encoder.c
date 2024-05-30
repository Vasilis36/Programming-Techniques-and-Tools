#include "encoder.h"

void encode(char **huffman_table, char *data_file, char *encoded_file)
{
    char character = 0;
    int ascii_value = 0;
    FILE *fp_read = NULL, *fp_write = NULL;

    if ((fp_read = fopen(data_file, "r")) == NULL)
    {
        printf("\"%s\" file cannot be opened\n", data_file);
        exit(EXIT_FAILURE);
    }

    if ((fp_write = fopen(encoded_file, "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", encoded_file);
        exit(EXIT_FAILURE);
    }

    /* 
    * Encode each character in the data file using the Huffman codes and write it in the 
    * the output file.
    */
    while ((character = fgetc(fp_read)) != EOF)
    {
        ascii_value = (int) character;
        fprintf(fp_write, "%s", huffman_table[ascii_value]);
    }   
    printf("Encoding done. Result in: \"%s\"\n", encoded_file);
    fclose(fp_read);
    fclose(fp_write); 
}

#ifdef TEST_E
int main(int argc, char **argv)
{
    char *prob_file = argv[1];
    char *data_file = argv[2];
    char *encoded_file = argv[3];

    NODE *huffman_tree_root = generate_huffman_tree(prob_file);
    char **huffman_table = generate_huffman_table(huffman_tree_root);
    encode(huffman_table, data_file, encoded_file);
    free_huffman_tree(huffman_tree_root);
    free_huffman_table(huffman_table);
    return 0;
}
#endif
