#include "decoder.h"

void decode(NODE *huffman_tree_root, char *encoded_file, char *decoded_file)
{
    FILE *fp_read = NULL, *fp_write = NULL;
    NODE *current_node = huffman_tree_root;
    char bit = 0;
    char character = 0;

    if ((fp_read = fopen(encoded_file, "r")) == NULL)
    {
        printf("\"%s\" file cannot be opened\n", encoded_file);
        exit(EXIT_FAILURE);
    }

    if ((fp_write = fopen(decoded_file, "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", decoded_file);
        exit(EXIT_FAILURE);
    }

    /* Reads each character - bit from the encoded file and decodes it.*/
    while ((bit = fgetc(fp_read)) != EOF)
    {     
        /* If next bit is 0 traverse left, and if it is 1 traverse right. */
        if (bit == '0')
        {
            current_node = current_node->left;
        }
        else if (bit == '1')
        {
            current_node = current_node->right;
        }
         /* If the current node is a leaf, then it is also the decoded character. */
        if (current_node->left == NULL && current_node->right == NULL)
        {
            character = current_node->character;
            fprintf(fp_write, "%c", character);
            /* 
             * After finding a character the traversal for the next character needs
             * to start from the root of the Huffman binary tree.
             */
            current_node = huffman_tree_root;
        }       
    }
    printf("Decoding done. Result in: \"%s\"\n", decoded_file);
    fclose(fp_read);
    fclose(fp_write);
}

#ifdef TEST_D
int main(int argc, char **argv)
{
    char *prob_file = argv[1];
    char *encoded_file = argv[2];
    char *decoded_file = argv[3];

    NODE *huffman_tree_root = generate_huffman_tree(prob_file);
    decode(huffman_tree_root, encoded_file, decoded_file);
    free_huffman_tree(huffman_tree_root);
    return 0;
}
#endif